#include "status_easy_sleep.h"

#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "audio_wrappers.h"
#include "syscall_wrappers.h"

#include "constants/samus.h"
#include "constants/status_screen.h"

#include "data/menus/pause_debug.h"

#include "structs/samus.h"
#include "structs/menus/pause_screen.h"

/* Easy sleep menu variables (pause screen data) */
#define EASY_SLEEP_STAGE (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
#define EASY_SLEEP_TIMER (PAUSE_SCREEN_DATA.timer)
#define EASY_SLEEP_CURSOR_X (PAUSE_SCREEN_DATA.oam[1].xPosition)

/**
 * @brief Copies one tilemap row segment of the status screen
 *
 * @param dstPos Destination tile position
 * @param srcPos Source tile position
 * @param width Width - 1 (nothing is copied if negative)
 */
static void StatusScreenCopyTiles(s32 dstPos, s32 srcPos, s32 width)
{
    u16* tilemap;
    s32 i;

    tilemap = STATUS_SCREEN_TILEMAP;
    for (i = 0; i <= width; i++)
        tilemap[dstPos + i] = tilemap[srcPos + i];
}

/**
 * @brief 7e678 | 34 | Handler for the status screen
 *
 */
void StatusScreenHandler(void)
{
    if ((gChangedInput & (KEY_B | KEY_L | KEY_R)) && PAUSE_SCREEN_DATA.pauseDebugEditingValue == 0)
    {
        PAUSE_SCREEN_DATA.unk_28 = 7;
        PAUSE_SCREEN_DATA.timer = 0;
        PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
    }
}

/**
 * @brief 7e6ac | a8 | Draws everything on the status screen menu
 *
 */
void StatusScreenDrawEverything(void)
{
    StatusScreenDrawBeamOrSuit(STATUS_SECTION_BEAM, gEquipment.beamStatus);
    StatusScreenDrawMissileOrBomb(STATUS_SECTION_MISSILE, gEquipment.weaponsStatus);
    StatusScreenDrawBeamOrSuit(STATUS_SECTION_SUIT, gEquipment.suitMiscStatus);
    StatusScreenDrawMissileOrBomb(STATUS_SECTION_BOMB, gEquipment.weaponsStatus);
    StatusScreenDrawMisc(STATUS_SECTION_MISC, gEquipment.suitMiscStatus);
    StatusScreenDrawNumber(STATUS_SECTION_ENERGY_CURRENT, gEquipment.currentEnergy, 6, FALSE);
    StatusScreenDrawNumber(STATUS_SECTION_ENERGY_MAX, gEquipment.maxEnergy, 3, TRUE);

    if (gEquipment.weaponsStatus & MBF_MISSILES)
    {
        StatusScreenDrawNumber(STATUS_SECTION_MISSILES_CURRENT, gEquipment.currentMissiles, 6, FALSE);
        StatusScreenDrawNumber(STATUS_SECTION_MISSILES_MAX, gEquipment.maxMissiles, 3, TRUE);
    }
    else
    {
        StatusScreenRemoveAmmoHeader(1);
    }

    if ((gEquipment.weaponsStatus & (MBF_BOMBS | MBF_POWER_BOMBS)) == (MBF_BOMBS | MBF_POWER_BOMBS))
    {
        StatusScreenDrawNumber(STATUS_SECTION_POWER_BOMBS_CURRENT, gEquipment.currentPowerBombs, 6, FALSE);
        StatusScreenDrawNumber(STATUS_SECTION_POWER_BOMBS_MAX, gEquipment.maxPowerBombs, 3, TRUE);
    }
    else
    {
        StatusScreenRemoveAmmoHeader(2);
    }
}

/**
 * @brief 7e754 | e0 | Draws a number on the status screen
 *
 * @param section section
 * @param value value
 * @param palette palette slot
 * @param isMax bool for current vs max ammo count (max is left aligned)
 */
void StatusScreenDrawNumber(u8 section, u16 value, u8 palette, boolu8 isMax)
{
    u16* dst;
    s32 nbrDigits;
    s32 divisor;
    s32 digit;
    s32 started;
    s32 i;
    s32 tile;

    dst = STATUS_SCREEN_TILEMAP + STATUS_SCREEN_SECTION_TOP(section) * 32 + STATUS_SCREEN_SECTION_LEFT(section);
    nbrDigits = STATUS_SCREEN_SECTION_WIDTH(section);
    divisor = sPauseDebugNumbersIncrementValues[nbrDigits];
    nbrDigits++;
    started = FALSE;

    for (i = 0; divisor > 0; divisor /= 10, i++)
    {
        digit = (value / divisor) % 10;

        if (digit != 0)
        {
            started = TRUE;
            tile = digit + 0x80;
        }
        else if (started)
        {
            tile = 0x80;
        }
        else if (isMax)
        {
            // Leading zero of a max value, skip it (left aligned)
            i--;
            continue;
        }
        else
        {
            tile = 0x8C;
        }

        dst[i] = palette << 12 | tile;
    }

    // Fill the remaining digits with blank tiles
    for (; i != nbrDigits; i++)
        dst[i] = palette << 12 | 0x8C;
}

/**
 * @brief 7e834 | 148 | Draws the beam or suit status
 *
 * @param section section
 * @param value beam or suit misc status
 */
void StatusScreenDrawBeamOrSuit(u8 section, u8 value)
{
    s32 i;
    s32 lastRow;
    s32 flag;

    lastRow = 0;
    for (i = 0; i < sStatusScreenSectionSizes[section]; )
    {
        s32 dstPos;
        s32 srcPos;

        dstPos = (STATUS_SCREEN_SECTION_TOP(section) + 1 + i) * 32 + STATUS_SCREEN_SECTION_LEFT(section);
        srcPos = (sStatusScreenSourceInfo[section][0] + 1 + i) * 32 + sStatusScreenSourceInfo[section][2];
        flag = sUnk_79bea8[section][i] & value;
        i++;

        if (flag)
        {
            lastRow = i;
            StatusScreenCopyTiles(dstPos, srcPos, STATUS_SCREEN_SECTION_WIDTH(section));
        }
    }

    if (lastRow != 0)
    {
        // Closing row
        StatusScreenCopyTiles((lastRow + 1 + STATUS_SCREEN_SECTION_TOP(section)) * 32 + STATUS_SCREEN_SECTION_LEFT(section),
            sStatusScreenSourceInfo[section][1] * 32 + sStatusScreenSourceInfo[section][2],
            STATUS_SCREEN_SECTION_WIDTH(section));
    }
}

/**
 * @brief 7e97c | 15c | Draws the missile or bomb status
 *
 * @param section section
 * @param value weapon status
 */
void StatusScreenDrawMissileOrBomb(u8 section, u8 value)
{
    s32 i;
    s32 lastRow;

    lastRow = -1;
    for (i = 0; i < sStatusScreenSectionSizes[section]; i++)
    {
        if (sUnk_79bea8[section][i] & value)
        {
            lastRow = i;
            StatusScreenCopyTiles((STATUS_SCREEN_SECTION_TOP(section) + i) * 32 + STATUS_SCREEN_SECTION_LEFT(section),
                (sStatusScreenSourceInfo[section][0] + i) * 32 + sStatusScreenSourceInfo[section][2],
                STATUS_SCREEN_SECTION_WIDTH(section));
        }
        else if (i == 0)
        {
            // Base item (missiles/bombs) not obtained, draw nothing
            return;
        }
    }

    if (lastRow >= 0)
    {
        // Closing row
        StatusScreenCopyTiles((lastRow + 1 + STATUS_SCREEN_SECTION_TOP(section)) * 32 + STATUS_SCREEN_SECTION_LEFT(section),
            sStatusScreenSourceInfo[section][1] * 32 + sStatusScreenSourceInfo[section][2],
            STATUS_SCREEN_SECTION_WIDTH(section));
    }
}

/**
 * @brief 7ead8 | 1b4 | Draws the misc status
 *
 * @param section section
 * @param value misc status
 */
void StatusScreenDrawMisc(u8 section, u8 value)
{
    s32 i;
    s32 lastRow;
    s32 dstPos;
    s32 srcPos;

    lastRow = 0;
    for (i = 0; i < sStatusScreenSectionSizes[section]; i++)
    {
        if (sUnk_79bea8[section][i] & value)
        {
            lastRow = i + 1;
            StatusScreenCopyTiles((STATUS_SCREEN_SECTION_TOP(section) + 1 + i) * 32 + STATUS_SCREEN_SECTION_LEFT(section),
                (sStatusScreenSourceInfo[section][0] + 1 + i) * 32 + sStatusScreenSourceInfo[section][2],
                STATUS_SCREEN_SECTION_WIDTH(section));
        }
    }

    if (lastRow == 0)
        return;

    for (i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            // Closing row
            lastRow++;
            dstPos = (STATUS_SCREEN_SECTION_TOP(section) + lastRow) * 32 + STATUS_SCREEN_SECTION_LEFT(section);
            srcPos = sStatusScreenSourceInfo[section][1] * 32 + sStatusScreenSourceInfo[section][2];
        }
        else
        {
            // Header row
            dstPos = STATUS_SCREEN_SECTION_TOP(section) * 32 + STATUS_SCREEN_SECTION_LEFT(section);
            srcPos = sStatusScreenSourceInfo[section][0] * 32 + sStatusScreenSourceInfo[section][2];
        }

        StatusScreenCopyTiles(dstPos, srcPos, STATUS_SCREEN_SECTION_WIDTH(section));
    }
}

/**
 * @brief 7ec8c | 94 | Removes an ammo header from the status screen
 *
 * @param position 1 for missiles 2 for power bombs
 */
void StatusScreenRemoveAmmoHeader(u8 position)
{
    s32 header;
    s32 i;

    if (position == 1)
        header = 1;
    else if (position == 2)
        header = 2;
    else
        return;

    for (i = 0; i < 2; i++)
    {
        StatusScreenCopyTiles((sStatusScreenAmmoHeaderInfo[header][0] + i) * 32 + sStatusScreenAmmoHeaderInfo[header][2],
            (sStatusScreenAmmoHeaderInfo[0][0] + i) * 32 + sStatusScreenAmmoHeaderInfo[0][2],
            sStatusScreenAmmoHeaderInfo[0][3] - sStatusScreenAmmoHeaderInfo[0][2]);
    }
}

/**
 * @brief 7ed20 | 184 | Handler for the easy sleep menu
 *
 * @return u8 bool, leaving
 */
u8 EasySleepMenuHandler(void)
{
    u8 leaving;
    u16 ie;

    leaving = FALSE;

    switch (EASY_SLEEP_STAGE)
    {
        case 0:
            if (gChangedInput & KEY_A)
            {
                SoundPlay(0x1FB);
                leaving = TRUE;
                break;
            }

            if (gChangedInput & KEY_LEFT)
            {
                EASY_SLEEP_STAGE = 1;
                EASY_SLEEP_CURSOR_X = 0x3C;
                SoundPlay(0x1FA);
                break;
            }

            if (gChangedInput & (KEY_B | KEY_L | KEY_R))
                leaving = TRUE;
            break;

        case 1:
            if (gChangedInput & KEY_A)
            {
                SoundPlay(0x1FB);
                EASY_SLEEP_STAGE = 2;
                EASY_SLEEP_TIMER = 0;
                break;
            }

            if (gChangedInput & KEY_RIGHT)
            {
                EASY_SLEEP_STAGE = 0;
                EASY_SLEEP_CURSOR_X = 0x8C;
                SoundPlay(0x1FA);
                break;
            }

            if (gChangedInput & (KEY_B | KEY_L | KEY_R))
                leaving = TRUE;
            break;

        case 2:
            EASY_SLEEP_TIMER++;
            if (EASY_SLEEP_TIMER > 30)
            {
                EASY_SLEEP_STAGE++;
                EASY_SLEEP_TIMER = 0;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BLANK;
            EASY_SLEEP_STAGE++;
            break;

        case 4:
            // Wake up on L + R + Select
            WRITE_16(REG_KEY_CONTROL, KEY_CONTROL_ALL_INPUTS | KEY_CONTROL_ENABLE | KEY_L | KEY_R | KEY_SELECT);
            WRITE_16(REG_IME, FALSE);
            ie = READ_16(REG_IE);
            WRITE_16(REG_IE, IF_KEYPAD | IF_GAMEPAK);
            WRITE_16(REG_IME, TRUE);

            // SoundBias0, Stop, SoundBias1
            EasySleepWrapper();

            WRITE_16(REG_IME, FALSE);
            WRITE_16(REG_IE, ie);
            WRITE_16(REG_IME, TRUE);

            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BLANK;
            EASY_SLEEP_CURSOR_X = 0x8C;
            EASY_SLEEP_STAGE++;
            break;

        case 5:
            // Wait for every button to be released
            if (gButtonInput == KEY_NONE)
                EASY_SLEEP_STAGE = 0;
            break;
    }

    if (leaving)
    {
        EASY_SLEEP_STAGE = 0;
        EASY_SLEEP_TIMER = 0;
    }

    return leaving;
}
