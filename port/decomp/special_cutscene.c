#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "callbacks.h"
#include "syscalls.h"
#include "music_wrappers.h"
#include "text.h"
#include "init_helpers.h"
#include "fixed_point.h"
#include "audio/track_internal.h"

#include "structs/cutscene.h"
#include "structs/intro.h"

#include "data/new_file_intro_data.h"
#include "data/sprite_data.h"
#include "data/generic_data.h"
#include "data/haze_data.h"

#include "special_cutscene.h"

#ifndef PLATFORM_PC
// RAM without a name in linker.ld (the native build defines these itself)
asm(".set gUnk_3001238, 0x03001238");
asm(".set gUnk_3005404, 0x03005404");
#endif

#define SC_CHAR_END 0xFF00
#define SC_CHAR_NEW_LINE 0xFE00
#define SC_CHAR_NEW_PAGE 0xFD00
#define SC_CHAR_WAIT_INPUT 0xFC00
#define SC_CHAR_DELAY 0xE100

/**
 * @brief 9741c | a8 | Handler for the died from SR388 collision cutscene
 *
 * @return boolu32 Ended
 */
boolu32 DiedFromSr388CollisionHandler(void)
{
    boolu32 result;

    result = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
            gSubGameMode1 = 1;
            break;

        case 1:
            if (DiedOnSr388Collision())
            {
                INTRO_DATA.unk_20E = 0;
                gSubGameMode1 = 2;
            }
            break;

        case 2:
            if (INTRO_DATA.unk_20E == 0)
            {
                if (gWrittenToBldy < 16)
                    gWrittenToBldy++;
                else
                    result = TRUE;
            }
            else
            {
                INTRO_DATA.unk_20E--;
            }

            SpecialCutsceneDrawAllOam();
            break;
    }

    return result;
}

/**
 * @brief 974c4 | 1f4 | Initializes the died on SR388 collision cutscene
 *
 */
void DiedOnSr388CollisionInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sDiedOnSr388CollisionObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sDiedOnSr388CollisionObjPal, PALRAM_OBJ, 0x200 / 4);
    LZ77UncompVram(sDiedOnSr388CollisionBgGfx, VRAM_BASE);
    LZ77UncompVram(sDiedOnSr388CollisionTilemap_1, VRAM_BASE + 0xF000);
    LZ77UncompVram(sDiedOnSr388CollisionTilemap_2, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sDiedOnSr388CollisionBgPal, PALRAM_BASE, 0x200 / 4);

    gBg1XPosition = 0;
    gBg1YPosition = 8;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 8);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, 0x1C08);
    WRITE_16(REG_BG1CNT, 0x1E01);
    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_BLDCNT, 0xBF);

    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);
    gWrittenToBldalpha_Eva = 8;
    gWrittenToBldalpha_Evb = 14;

    SoundPlay_3b1c(0x24D);

    DiedOnSr388CollisionSetupOam(2, 164, 40, TRUE);
    DiedOnSr388CollisionSetupOam(1, 164, 40, TRUE);
    DiedOnSr388CollisionSetupOam(3, 134, 60, TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, 0x1800);

    CallbackSetVBlank(DiedOnSr388CollisionVblank);
}

/**
 * @brief 976b8 | 1b8 | Processes the died on SR388 collision cutscene
 *
 * @return boolu32 Ended
 */
boolu32 DiedOnSr388CollisionProcess(void)
{
    boolu32 ended;

    ended = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
            }
            else
            {
                WRITE_16(REG_BLDCNT, 0xC40);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
            break;

        case 1:
            INTRO_DATA.timer = 0;
            break;

        case 2:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
                INTRO_DATA.unk_110 = 1;
                INTRO_DATA.unk_111 = 0;
            }
            else if (INTRO_DATA.timer == 2)
            {
                WRITE_16(REG_BLDCNT, 0x842);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | 0x200);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
            break;

        case 3:
            if (INTRO_DATA.unk_111 < 15)
            {
                if (INTRO_DATA.timer == 4)
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.unk_110 = 1;
                    INTRO_DATA.unk_111++;
                }
            }
            else if (INTRO_DATA.timer == 15)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 16;
                INTRO_DATA.subStage = 4;
            }
            break;

        case 4:
            if (gWrittenToBldalpha_Eva < 16)
            {
                if (INTRO_DATA.timer == 6)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldalpha_Eva++;
                    gWrittenToBldalpha_Evb++;
                }
            }
            else
            {
                WRITE_16(REG_BLDCNT, 0xBF);
                if (INTRO_DATA.timer == 15)
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 0;
                    ended = TRUE;
                }
            }
            break;

        default:
            return ended;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    return ended;
}

/**
 * @brief 97870 | 88 | Died on SR388 collision cutscene
 *
 * @return boolu32 Ended
 */
boolu32 DiedOnSr388Collision(void)
{
    boolu32 ended;

    ended = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            DiedOnSr388CollisionInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (DiedOnSr388CollisionProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                ended = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return ended;
}

/**
 * @brief 978f8 | d8 | Processes the falling BSL
 *
 * @param pOam Special cutscene OAM pointer
 */
void DiedOnSr388CollisionProcessFallingBsl(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        pOam->xPosition = pOam->spawnX - pOam->unk_A / 5;
        pOam->yPosition = pOam->spawnY + pOam->unk_A / 5;

        if (pOam->yPosition > 80)
        {
            pOam->unk_A = 0;
            pOam->stage = 2;
        }

        if (pOam->type == 1)
            pOam->scaling -= 1;
        else
            pOam->scaling -= 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->stage = 3;
        if (pOam->type == 1)
        {
            pOam->pOam = sDiedOnSr388CollisionBslOam_Crash;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            INTRO_DATA.subStage = 2;
        }
        else
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
    else if (pOam->stage == 3)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 979d0 | 30 | Kills the OAM once its animation ended
 *
 * @param pOam Special cutscene OAM pointer
 */
void unk_979d0(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->stage == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];
        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 97a00 | 200 | Spawns an OAM for the died on SR388 collision cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search the free slot from the end
 * @return u8 Slot (20 if none free)
 */
u8 DiedOnSr388CollisionSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;

    if (!descendingSearchOrder)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot > 19)
            return 20;
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return 20;
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = TRUE;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].affineMode = 1;
        INTRO_DATA.oam[slot].pOam = sDiedOnSr388CollisionBslOam_1;
        INTRO_DATA.oam[slot].pFunction = DiedOnSr388CollisionProcessFallingBsl;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(2);
        INTRO_DATA.oam[slot].unk_18_3 = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].affineMode = 1;
        INTRO_DATA.oam[slot].pOam = sDiedOnSr388CollisionBslOam_2;
        INTRO_DATA.oam[slot].pFunction = DiedOnSr388CollisionProcessFallingBsl;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sDiedOnSr388CollisionOam_3;
        INTRO_DATA.oam[slot].pFunction = unk_979d0;
    }

    return slot;
}

/**
 * @brief 97c00 | d8 | V-blank for the died on SR388 collision cutscene
 *
 */
void DiedOnSr388CollisionVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;
        DMA3_COPY_32(&sDiedOnSr388CollisionFadingPal[INTRO_DATA.unk_111 * 16], PALRAM_BASE + 0x120, 16 * sizeof(u16) / 4);
    }
}

/**
 * @brief 97cd8 | 94 | V-blank for the died on SR388 collision cutscene (unused)
 *
 */
void DiedOnSr388CollisionVblank_Unused(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

/**
 * @brief 97d6c | 60 | Returns slot, X and Y position of an OAM by type
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot (20 if not found)
 */
u8 DiedOnSr388CollisionGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
            return slot;
        }
    }

    *pXPosition = 300;
    *pYPosition = 200;

    return ARRAY_SIZE(INTRO_DATA.oam);
}

/**
 * @brief 97dcc | 4 | Empty function
 *
 */
void unk_97dcc(void)
{
    return;
}

/**
 * @brief 97dd0 | d8 | Checks if the new file intro monologue ended
 *
 * @return boolu32 Ended
 */
boolu32 NewFileIntroCheckMonologueEnded(void)
{
    boolu32 ended;
    u16 c;
    u16 next;

    ended = FALSE;
    INTRO_DATA.unk_20C++;

    c = *INTRO_DATA.pText;

    if (c == SC_CHAR_END)
    {
        INTRO_DATA.unk_20C = 0;
        INTRO_DATA.unk_213 = 100;
        ended = TRUE;
    }
    else if (c == SC_CHAR_WAIT_INPUT)
    {
        INTRO_DATA.unk_20C = 0;
        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            INTRO_DATA.unk_213 = 1;

            next = *INTRO_DATA.pText;
            if (next == SC_CHAR_NEW_PAGE)
            {
                INTRO_DATA.unk_218 = 2;
            }
            else if (next == SC_CHAR_END)
            {
                INTRO_DATA.unk_218 = 3;
            }
            else if (next == SC_CHAR_WAIT_INPUT)
            {
                INTRO_DATA.unk_218 = 4;
                INTRO_DATA.pText++;
                if (*INTRO_DATA.pText == SC_CHAR_END)
                    INTRO_DATA.unk_218 = 3;
            }
            else
            {
                INTRO_DATA.unk_218 = 0;
            }
        }
    }
    else if ((c & 0xFF00) == SC_CHAR_DELAY)
    {
        if ((c & 0xFF) <= INTRO_DATA.unk_20C)
        {
            INTRO_DATA.unk_213 = 1;
            INTRO_DATA.unk_20C = 0;
        }
    }
    else if (INTRO_DATA.unk_20C > 2)
    {
        INTRO_DATA.unk_213 = 1;
        INTRO_DATA.unk_20C = 0;
    }

    return ended;
}

/**
 * @brief 97ea8 | d8 | Checks if the ending monologue ended
 *
 * @return boolu32 Ended
 */
boolu32 EndingCheckMonologueEnded(void)
{
    boolu32 ended;
    u16 c;
    u16 next;

    ended = FALSE;
    INTRO_DATA.unk_20C++;

    c = *INTRO_DATA.pText;

    if (c == SC_CHAR_END)
    {
        INTRO_DATA.unk_20C = 0;
        INTRO_DATA.unk_213 = 100;
        ended = TRUE;
    }
    else if (c == SC_CHAR_WAIT_INPUT)
    {
        INTRO_DATA.unk_20C = 0;
        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            INTRO_DATA.unk_213 = 1;

            next = *INTRO_DATA.pText;
            if (next == SC_CHAR_NEW_PAGE)
            {
                INTRO_DATA.unk_218 = 2;
            }
            else if (next == SC_CHAR_END)
            {
                INTRO_DATA.unk_218 = 3;
            }
            else if (next == SC_CHAR_WAIT_INPUT)
            {
                INTRO_DATA.unk_218 = 4;
                INTRO_DATA.pText++;
                if (*INTRO_DATA.pText == SC_CHAR_END)
                    INTRO_DATA.unk_218 = 3;
            }
            else
            {
                INTRO_DATA.unk_218 = 0;
            }
        }
    }
    else if ((c & 0xFF00) == SC_CHAR_DELAY)
    {
        if ((c & 0xFF) <= INTRO_DATA.unk_20C)
        {
            INTRO_DATA.unk_213 = 1;
            INTRO_DATA.unk_20C = 0;
        }
    }
    else if (INTRO_DATA.unk_20C > 3)
    {
        INTRO_DATA.unk_213 = 1;
        INTRO_DATA.unk_20C = 0;
    }

    return ended;
}

/**
 * @brief 97f80 | 1d8 | Processes the monologue text (draws one character)
 *
 */
void SpecialCutsceneProcessMonologue(void)
{
    u16 c;
    u16 i;
    u8* dst;
    u32 width;

    c = *INTRO_DATA.pText;

    if (c == SC_CHAR_END)
        return;

    if (c == SC_CHAR_NEW_LINE)
    {
        // PORT: the index can go past unk_14 (into the 0x110 array) if unk_E > 17, like the original
        for (i = INTRO_DATA.unk_C + 1; i < 28; i++)
            SPECIAL_CUTSCENE_TEXT_STATE((INTRO_DATA.unk_E / 2) * 28 + i) |= 0xFF;

        INTRO_DATA.unk_C = 0;
        INTRO_DATA.unk_E += 2;
        INTRO_DATA.pText++;
        INTRO_DATA.unk_212 = 0;
    }
    else if (c == SC_CHAR_NEW_PAGE)
    {
        DMA3_FILL_32(0, VRAM_BASE, 0x4800);
        INTRO_DATA.unk_12 = 0;
        INTRO_DATA.unk_10 = 0;
        INTRO_DATA.unk_E = 0;
        INTRO_DATA.unk_C = 0;
        INTRO_DATA.pText++;
        INTRO_DATA.unk_212 = 0;

        DMA3_FILL_32(0, &SPECIAL_CUTSCENE_TEXT_STATE(0), 9 * 28);
        DMA3_FILL_32(0, &SPECIAL_CUTSCENE_TEXT_TIMER(0), 9 * 28);
        DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / 4);
    }
    else if (c == SC_CHAR_WAIT_INPUT)
    {
        INTRO_DATA.unk_C++;
    }
    else if ((c & 0xFF00) == SC_CHAR_DELAY)
    {
        INTRO_DATA.pText++;
    }
    else
    {
        dst = (u8*)VRAM_BASE + INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400;
        width = TextGetCharacterWidth(c);
        TextDrawCharacter(*INTRO_DATA.pText, (u32*)dst, width, INTRO_DATA.unk_212, 0);

        if (INTRO_DATA.unk_C < 28)
        {
            SPECIAL_CUTSCENE_TEXT_STATE((INTRO_DATA.unk_E / 2) * 28 + INTRO_DATA.unk_C) = 4;
            INTRO_DATA.unk_212 += width;

            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;
                if (INTRO_DATA.unk_C >= 28)
                    break;

                if (INTRO_DATA.unk_212 != 0)
                    SPECIAL_CUTSCENE_TEXT_STATE((INTRO_DATA.unk_E / 2) * 28 + INTRO_DATA.unk_C) = 4;
            }
        }

        INTRO_DATA.pText++;
    }
}

/**
 * @brief 98158 | 134 | Updates the fading in of the monologue text tiles
 *
 */
void unk_98158(void)
{
    u16 col;
    u16 row;
    u16 limit;
    u32 index;
    u16* pTop;
    u16* pBottom;
    u16 top;
    u16 bottom;

    col = INTRO_DATA.unk_10;

    for (row = INTRO_DATA.unk_12 / 2; row <= INTRO_DATA.unk_E / 2; row++, col = 0)
    {
        if (*INTRO_DATA.pText == SC_CHAR_WAIT_INPUT)
        {
            if (INTRO_DATA.unk_C < 28)
                limit = INTRO_DATA.unk_C + 1;
            else
                limit = 28;
        }
        else if (row == INTRO_DATA.unk_E / 2)
        {
            if (INTRO_DATA.unk_C < 28)
                limit = INTRO_DATA.unk_C;
            else
                limit = 28;
        }
        else
        {
            limit = 28;
        }

        for (; col < limit; col++)
        {
            // PORT: row can go past 8 (index past the 252 bytes arrays) like the original
            index = row * 28 + col;

            if (SPECIAL_CUTSCENE_TEXT_TIMER(index) != 5)
            {
                SPECIAL_CUTSCENE_TEXT_TIMER(index)++;
                continue;
            }

            SPECIAL_CUTSCENE_TEXT_TIMER(index) = 0;
            SPECIAL_CUTSCENE_TEXT_STATE(index)--;

            if ((s8)SPECIAL_CUTSCENE_TEXT_STATE(index) > 0)
            {
                // Decrement the palette of the 2 tiles
                pTop = (u16*)((u8*)VRAM_BASE + 0x4842 + col * 2 + row * 128);
                pBottom = (u16*)((u8*)VRAM_BASE + 0x4882 + col * 2 + row * 128);
                top = *pTop;
                bottom = *pBottom;
                *pTop = (((top >> 12) - 1) << 12) | (top & 0xFFF);
                *pBottom = (((bottom >> 12) - 1) << 12) | (bottom & 0xFFF);
            }
            else if ((s8)SPECIAL_CUTSCENE_TEXT_STATE(index) == 0)
            {
                INTRO_DATA.unk_10 = col;
                INTRO_DATA.unk_12 = row * 2;
            }
            else
            {
                SPECIAL_CUTSCENE_TEXT_STATE(index) |= 0xFF;
                break;
            }
        }
    }
}

/**
 * @brief 9828c | 220 | Processes the Adam text of the ending
 *
 * @return boolu32 Ended
 */
boolu32 EndingProcessAdamText(void)
{
    boolu32 ended;
    u16 c;
    u16 timer;
    u8* dst;
    u32 width;

    ended = FALSE;
    timer = ++INTRO_DATA.unk_20C;
    c = *INTRO_DATA.pText;

    if (c == SC_CHAR_END)
    {
        if (timer > 15)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            ended = TRUE;
        }
    }
    else if (c == SC_CHAR_NEW_LINE)
    {
        if (INTRO_DATA.unk_E < 2)
        {
            if (timer > 5)
            {
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_E = 2;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText++;
            }
        }
        else if (timer > 125)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.pText++;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        }
    }
    else if (c == SC_CHAR_NEW_PAGE)
    {
        if (timer > 15)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText++;
            INTRO_DATA.unk_212 = 0;
        }
    }
    else if (c == SC_CHAR_WAIT_INPUT)
    {
        INTRO_DATA.unk_20C = 0;
        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            c = *INTRO_DATA.pText;
            if (c == SC_CHAR_NEW_PAGE)
                INTRO_DATA.unk_218 = 2;
            else if (c == SC_CHAR_END)
                INTRO_DATA.unk_218 = 3;
            else
                INTRO_DATA.unk_218 = 0;
        }
    }
    else if ((c & 0xFF00) == SC_CHAR_DELAY)
    {
        if ((c & 0xFF) <= timer)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.pText++;
        }
    }
    else if (timer > 5)
    {
        INTRO_DATA.unk_20C = 0;
        dst = (u8*)VRAM_BASE + 0xD000 + INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400;
        width = TextGetCharacterWidth(c);
        TextDrawCharacter(*INTRO_DATA.pText, (u32*)dst, width, INTRO_DATA.unk_212, 0);

        if (*INTRO_DATA.pText != 0x40)
            PlayCharacterAppearingSound(*INTRO_DATA.pText, 1);

        if (INTRO_DATA.unk_C < 32)
        {
            INTRO_DATA.unk_212 += width;
            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;
                if (INTRO_DATA.unk_C >= 32)
                    break;
            }
        }

        INTRO_DATA.pText++;
    }

    return ended;
}

/**
 * @brief Common text processing of IntroProcessText and NewFileIntroProcessAdamText
 *
 * @param playSound Play the character appearing sound
 * @return boolu32 Ended
 */
static boolu32 SpecialCutsceneProcessText(boolu8 playSound)
{
    boolu32 ended;
    u16 c;
    u16 timer;
    u8* dst;
    u32 width;

    ended = FALSE;
    timer = ++INTRO_DATA.unk_20C;
    c = *INTRO_DATA.pText;

    if (c == SC_CHAR_END)
    {
        if (timer > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            ended = TRUE;
        }
    }
    else if (c == SC_CHAR_NEW_LINE)
    {
        if (INTRO_DATA.unk_E < 2)
        {
            if (timer > 2)
            {
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_E = 2;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText++;
            }
        }
        else if (timer > 122)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.pText++;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        }
    }
    else if (c == SC_CHAR_NEW_PAGE)
    {
        if (timer > 12)
        {
            INTRO_DATA.unk_20C = 0;
            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText++;
            INTRO_DATA.unk_212 = 0;
        }
    }
    else if (c == SC_CHAR_WAIT_INPUT)
    {
        INTRO_DATA.unk_20C = 0;
        if (INTRO_DATA.unk_218 == 1)
        {
            INTRO_DATA.pText++;
            c = *INTRO_DATA.pText;
            if (c == SC_CHAR_NEW_PAGE)
            {
                INTRO_DATA.unk_218 = 2;
            }
            else if (c == SC_CHAR_END)
            {
                INTRO_DATA.unk_218 = 3;
            }
            else if (c == SC_CHAR_WAIT_INPUT)
            {
                INTRO_DATA.pText++;
                if (*INTRO_DATA.pText == SC_CHAR_END)
                    INTRO_DATA.unk_218 = 3;
                else
                    INTRO_DATA.unk_218 = 4;
            }
            else
            {
                INTRO_DATA.unk_218 = 0;
            }
        }
    }
    else if ((c & 0xFF00) == SC_CHAR_DELAY)
    {
        if ((c & 0xFF) <= timer)
        {
            INTRO_DATA.unk_20C = 0;
            INTRO_DATA.pText++;
        }
    }
    else if (timer > 2)
    {
        INTRO_DATA.unk_20C = 0;
        dst = (u8*)VRAM_BASE + 0xD000 + INTRO_DATA.unk_C * 32 + INTRO_DATA.unk_E * 0x400;
        width = TextGetCharacterWidth(c);
        TextDrawCharacter(*INTRO_DATA.pText, (u32*)dst, width, INTRO_DATA.unk_212, 0);

        if (playSound && *INTRO_DATA.pText != 0x40)
            PlayCharacterAppearingSound(*INTRO_DATA.pText, 1);

        if (INTRO_DATA.unk_C < 32)
        {
            INTRO_DATA.unk_212 += width;
            while (INTRO_DATA.unk_212 >= 8)
            {
                INTRO_DATA.unk_212 -= 8;
                INTRO_DATA.unk_C++;
                if (INTRO_DATA.unk_C >= 32)
                    break;
            }
        }

        INTRO_DATA.pText++;
    }

    return ended;
}

/**
 * @brief 984ac | 244 | Processes the text of the intro
 *
 * @return boolu32 Ended
 */
boolu32 IntroProcessText(void)
{
    return SpecialCutsceneProcessText(FALSE);
}

/**
 * @brief 986f0 | 250 | Processes the Adam text of the new file intro
 *
 * @return boolu32 Ended
 */
boolu32 NewFileIntroProcessAdamText(void)
{
    return SpecialCutsceneProcessText(TRUE);
}

/**
 * @brief 98940 | 40 | Transfers count blocks of 0x400 bytes (copying size * 32 bytes each), unused
 *
 * @param src Source
 * @param dst Destination
 * @param size Size (in 32 bytes units)
 * @param count Number of blocks
 */
void Dma3Transfer_Unused1(const void* src, void* dst, u32 size, u16 count)
{
    u16 i;
    const u8* s;
    u8* d;

    s = src;
    d = dst;
    for (i = 0; i < count; i++)
    {
        DMA_SET(3, s, d, C_32_2_16(DMA_ENABLE | DMA_32BIT, (size & 0x7FF) * 8));
        s += 0x400;
        d += 0x400;
    }
}

/**
 * @brief 98980 | 3c | Transfers count blocks of 0x40 bytes (copying size halfwords each), unused
 *
 * @param src Source
 * @param dst Destination
 * @param size Size (in halfwords)
 * @param count Number of blocks
 */
void Dma3Transfer_Unused2(const void* src, void* dst, u32 size, u16 count)
{
    u16 i;
    const u8* s;
    u8* d;

    s = src;
    d = dst;
    for (i = 0; i < count; i++)
    {
        DMA_SET(3, s, d, C_32_2_16(DMA_ENABLE | DMA_16BIT, size & 0x7FFF));
        s += 0x40;
        d += 0x40;
    }
}

/**
 * @brief 989bc | 48 | Clears count blocks of 0x400 bytes (size * 32 bytes each), unused
 *
 * @param dst Destination
 * @param size Size (in 32 bytes units)
 * @param count Number of blocks
 */
void Dma3Clear_Unused(void* dst, u32 size, u16 count)
{
    u16 i;
    u8* d;
    vu32 zero;

    d = dst;
    for (i = 0; i < count; i++)
    {
        zero = 0;
        DMA_SET(3, &zero, d, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, (size & 0x7FF) * 8));
        d += 0x400;
    }
}

/**
 * @brief 98a04 | 9c | Updates some intro timers
 *
 */
void unk_98a04(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (SPECIAL_CUTSCENE_INTRO_U8(0x110 + i) <= SPECIAL_CUTSCENE_INTRO_U8(0x12C + i))
        {
            SPECIAL_CUTSCENE_INTRO_U8(0x12C + i) = 0;
            SPECIAL_CUTSCENE_INTRO_U8(0x164 + i) = 1;

            if (SPECIAL_CUTSCENE_INTRO_U8(0x148 + i) < 38)
                SPECIAL_CUTSCENE_INTRO_U8(0x148 + i)++;
            else
                SPECIAL_CUTSCENE_INTRO_U8(0x148 + i) = 0;
        }
        else
        {
            SPECIAL_CUTSCENE_INTRO_U8(0x12C + i)++;
        }
    }

    if (SPECIAL_CUTSCENE_INTRO_U8(0x11A) <= SPECIAL_CUTSCENE_INTRO_U8(0x136))
    {
        SPECIAL_CUTSCENE_INTRO_U8(0x136) = 0;
        SPECIAL_CUTSCENE_INTRO_U8(0x16E) = 1;

        if (SPECIAL_CUTSCENE_INTRO_U8(0x152) < 15)
            SPECIAL_CUTSCENE_INTRO_U8(0x152)++;
        else
            SPECIAL_CUTSCENE_INTRO_U8(0x152) = 0;
    }
    else
    {
        SPECIAL_CUTSCENE_INTRO_U8(0x136)++;
    }
}

/**
 * @brief 98aa0 | 12c | Sets up the window (circle) of the samus getting cured cutscene
 *
 */
void NewFileIntroSamusGettingCuredSetupWindow(void)
{
    s16 i;
    s16 start;
    s32 end;
    u16 tableIndex;
    s16 diff;
    u16* dst;
    const s16* pValues;
    s16 left;
    s16 right;

    DMA3_COPY_32(gSpecialCutsceneWindowValues, gSpecialCutsceneWindowValuesCopy, 0x160 / 4);

    diff = INTRO_DATA.unk_1F5 - INTRO_DATA.unk_1F3;
    end = INTRO_DATA.unk_1F5 + INTRO_DATA.unk_1F3;

    if (diff < 0)
    {
        tableIndex = -diff;
        start = 0;
        if (tableIndex > INTRO_DATA.unk_1F3 * 2)
            start = 161;
    }
    else
    {
        tableIndex = 0;
        start = diff;
    }

    if (end > 159)
        end = 160;

    // PORT: unk_1F3 is not bounds checked (the table has 161 entries), like the original
    pValues = sHaze_PowerBomb_WindowValuesPointers[INTRO_DATA.unk_1F3];
    dst = gSpecialCutsceneWindowValues;

    for (i = 0; i < start; i++)
        *dst++ = 0;

    for (; i <= (s16)end; i++)
    {
        left = INTRO_DATA.unk_1F4 + pValues[tableIndex * 2 + 1];
        right = INTRO_DATA.unk_1F4 + pValues[tableIndex * 2];

        if (left < 0)
            left = 0;

        if (right > 240)
            right = 240;

        *dst++ = (left << 8) | right;
        tableIndex++;
    }

    for (; i < 160; i++)
        *dst++ = 0;
}

/**
 * @brief 98bcc | 20 | Processes and draws the OAM, and fades in
 *
 */
void SpecialCutsceneFadeIn(void)
{
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    if (gWrittenToBldy != 0)
        gWrittenToBldy--;
}

/**
 * @brief 98bec | 20 | Processes and draws the OAM, and fades out
 *
 */
void SpecialCutsceneFadOut(void)
{
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    if (gWrittenToBldy < 16)
        gWrittenToBldy++;
}

/**
 * @brief 98c0c | 2c | Processes the text cursor of the new file intro
 *
 * @param pOam Special cutscene OAM pointer
 */
void NewFileIntroProcessTextCursor(struct SpecialCutsceneOam* pOam)
{
#ifdef PLATFORM_PC
    // Can run before any text is set (pText NULL: the GBA reads the BIOS)
    if (INTRO_DATA.pText != NULL && *INTRO_DATA.pText == SC_CHAR_WAIT_INPUT)
#else
    if (*INTRO_DATA.pText == SC_CHAR_WAIT_INPUT)
#endif
    {
        pOam->xPosition = 235;
        pOam->yPosition = 152;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

/**
 * @brief 98c38 | 34 | Disables the drawing of every special cutscene OAM
 *
 */
void SpecialCutsceneClearOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
        INTRO_DATA.oam[i].unk_18_0 = FALSE;
}

/**
 * @brief 98c6c | 3c | Enables the drawing of every existing special cutscene OAM
 *
 */
void SpecialCutsceneEnableOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type != 0)
            INTRO_DATA.oam[i].unk_18_0 = TRUE;
    }
}

/**
 * @brief 98ca8 | 4c | Destroys the first special cutscene OAM of a type
 *
 * @param type Type
 */
void SpecialCutsceneDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type == type)
        {
            INTRO_DATA.oam[i].type = 0;
            INTRO_DATA.oam[i].unk_18_0 = FALSE;
            break;
        }
    }
}

/**
 * @brief 98cf4 | 58 | Processes every special cutscene OAM
 *
 */
void SpecialCutsceneProcessOam(void)
{
    u8 i;

    INTRO_DATA.unk_215 = 0;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].type != 0)
        {
            ((SpecialCutsceneOamFunc_T)INTRO_DATA.oam[i].pFunction)(&INTRO_DATA.oam[i]);
            INTRO_DATA.unk_215++;
        }
    }
}

/**
 * @brief 98d4c | 54 | Draws every special cutscene OAM
 *
 */
void SpecialCutsceneDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(INTRO_DATA.oam); i++)
    {
        if (INTRO_DATA.oam[i].unk_18_0)
            SpecialCutsceneDrawOam(&INTRO_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
    gUnk_3001238 = 0;
}

/**
 * @brief Applies the common graphics properties of a special cutscene OAM to an OAM entry
 * 
 * @param pOamData OAM entry pointer
 * @param pOam Special cutscene OAM pointer
 */
static void SpecialCutsceneApplyOamProperties(union OamData* pOamData, struct SpecialCutsceneOam* pOam)
{
    pOamData->split.priority = pOam->priority;
    pOamData->split.paletteNum += pOam->unk_1A_4;
    pOamData->split.tileNum += pOam->unk_19 | (pOam->unk_1A_0 << 8);
    pOamData->split.objMode = pOam->unk_18_3;
    pOamData->split.mosaic = pOam->unk_18_5;
}

/**
 * @brief 98da0 | a04 | Draws a special cutscene OAM
 * 
 * @param pOam Special cutscene OAM pointer
 */
void SpecialCutsceneDrawOam(struct SpecialCutsceneOam* pOam)
{
    u16* dst;
    const u16* src;
    const struct FrameData* pFrame;
    s32 partCount;
    s32 i;
    u16 part1;
    u16 part2;
    u8 flags;
    union OamData* pOamData;
    u8 shape;
    u8 size;
    s32 xOffset;
    s32 yOffset;
    u16 xPosition;
    u16 yPosition;
    u16 x;
    u16 y;
    s16 dx;
    s16 dy;
    s16 tmpX;
    s16 tmpY;
    s16 rx;
    s16 ry;
    s32 sine;
    s32 cosine;
    u16 scaleX;
    u16 scaleY;
    s16 scaleXInit;
    u8 flipped;
    u8 doubleMatrix;
    u8 matrix;
    u8 m;

    dst = (u16*)&gOamData[gNextOamSlot];

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame->timer == pOam->animationDurationCounter)
    {
        pOam->currentAnimationFrame++;
        pOam->animationDurationCounter = 0;
        pFrame++;
    }

    if (pFrame->timer == 0)
    {
        pFrame -= pOam->currentAnimationFrame;
        pOam->currentAnimationFrame = 0;
    }

    src = pFrame->pFrame;
    partCount = *src++;
    flags = SPECIAL_CUTSCENE_OAM_FLAGS(pOam);

    if (pOam->affineMode == 0)
    {
        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            *dst++ = part1;
            part2 = *src++;
            *dst++ = part2;
            *dst++ = *src++;

            pOamData = &gOamData[gNextOamSlot + i];

            if (flags & SPECIAL_CUTSCENE_OAM_FLAG_X_FLIP)
            {
                pOamData->split.xFlip ^= TRUE;
                shape = pOamData->split.shape;
                size = pOamData->split.size;
                pOamData->split.y = part1 + pOam->yPosition;
                pOamData->split.x = pOam->xPosition - (part2 + sSpecialCutsceneOamXFlipOffsets[shape][size] * 8);
            }
            else
            {
                pOamData->split.y = part1 + pOam->yPosition;
                pOamData->split.x = part2 + pOam->xPosition;
            }

            SpecialCutsceneApplyOamProperties(pOamData, pOam);
            dst++;
        }
    }
    else if (pOam->affineMode == 1)
    {
        xPosition = pOam->xPosition + 64;
        yPosition = pOam->yPosition + 64;

        scaleX = (flags & SPECIAL_CUTSCENE_OAM_FLAG_X_FLIP) ? -pOam->scaling : pOam->scaling;
        scaleY = (flags & SPECIAL_CUTSCENE_OAM_FLAG_Y_FLIP) ? -pOam->scaling : pOam->scaling;
        scaleXInit = scaleX;
        doubleMatrix = FALSE;

        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            *dst++ = part1;
            part2 = *src++;
            *dst++ = part2;
            *dst++ = *src++;

            pOamData = &gOamData[gNextOamSlot + i];
            shape = pOamData->split.shape;
            size = pOamData->split.size;
            xOffset = sSpecialCutsceneOamXFlipOffsets[shape][size] * 4;
            yOffset = sSpecialCutsceneOamYFlipOffsets[shape][size] * 4;

            y = (part1 + yPosition) & 0xFF;
            x = (part2 + xPosition) & 0x1FF;

            dx = xOffset + (x - xPosition);
            dy = yOffset + (y - yPosition);

            // Apply scaling
            tmpX = ((scaleXInit * dx) >> 8) - dx;
            tmpY = (((s16)scaleY * dy) >> 8) - dy;

            if (pOamData->split.xFlip)
            {
                pOamData->split.xFlip = FALSE;
                doubleMatrix = TRUE;
                flipped = TRUE;
            }
            else
            {
                flipped = FALSE;
            }

            if (pOamData->split.yFlip)
            {
                pOamData->split.yFlip = FALSE;
                scaleY = -scaleY;
            }

            x = (s16)x + tmpX;
            y = (s16)y + tmpY;

            dx = x - xPosition + xOffset;
            dy = y - yPosition + yOffset;

            // Apply rotation
            cosine = COS(pOam->rotation);
            sine = SIN(pOam->rotation);
            rx = (s16)((dx * cosine - dy * sine) >> 8) - xOffset;
            ry = (s16)((dx * sine + dy * cosine) >> 8) - yOffset;

            pOamData->split.y = ry + yPosition - 64;
            pOamData->split.x = (rx + xPosition - 64) & 0x1FF;

            if (flipped == TRUE)
                pOamData->split.x = (pOamData->split.x - 1) & 0x1FF;

            pOamData->split.affineMode = 1;

            m = gUnk_3001238 + flipped;
            if (m & 0x10)
                pOamData->split.yFlip = TRUE;
            if (m & 0x8)
                pOamData->split.xFlip = TRUE;
            pOamData->split.matrixNum = m & 7;

            SpecialCutsceneApplyOamProperties(pOamData, pOam);
            dst++;
        }

        // PORT: the matrix index ((gUnk_3001238 & 0x3F) * 4 + 3) can go past the end of gOamData, like the original
        matrix = gUnk_3001238 << 2;
        gOamData[matrix + 0].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(scaleXInit));
        gOamData[matrix + 1].all.affineParam = FixedMultiplication(SIN(pOam->rotation), FixedInverse(scaleXInit));
        gOamData[matrix + 2].all.affineParam = FixedMultiplication(-SIN(pOam->rotation), FixedInverse(scaleY));
        gOamData[matrix + 3].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(scaleY));
        gUnk_3001238++;

        if (doubleMatrix == TRUE)
        {
            // Matrix with the x scaling negated, for the x flipped parts
            matrix = gUnk_3001238 << 2;
            gOamData[matrix + 0].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(-scaleXInit));
            gOamData[matrix + 1].all.affineParam = FixedMultiplication(SIN(pOam->rotation), FixedInverse(-scaleXInit));
            gOamData[matrix + 2].all.affineParam = FixedMultiplication(-SIN(pOam->rotation), FixedInverse(scaleY));
            gOamData[matrix + 3].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(scaleY));
            gUnk_3001238++;
        }
    }
    else if (pOam->affineMode == 3)
    {
        xPosition = pOam->xPosition + 64;
        yPosition = pOam->yPosition + 64;

        scaleX = (flags & SPECIAL_CUTSCENE_OAM_FLAG_X_FLIP) ? -pOam->scaling : pOam->scaling;
        scaleY = (flags & SPECIAL_CUTSCENE_OAM_FLAG_Y_FLIP) ? -pOam->scaling : pOam->scaling;

        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            *dst++ = part1;
            part2 = *src++;
            *dst++ = part2;
            *dst++ = *src++;

            pOamData = &gOamData[gNextOamSlot + i];
            shape = pOamData->split.shape;
            size = pOamData->split.size;
            xOffset = sSpecialCutsceneOamXFlipOffsets[shape][size] * 4;
            yOffset = sSpecialCutsceneOamYFlipOffsets[shape][size] * 4;

            y = (part1 + yPosition) & 0xFF;
            x = (part2 + xPosition) & 0x1FF;

            dx = xOffset + (x - xPosition);
            dy = yOffset + (y - yPosition);

            // Apply scaling
            tmpX = (((s16)scaleX * dx) >> 8) - dx;
            tmpY = (((s16)scaleY * dy) >> 8) - dy;

            if (pOamData->split.xFlip)
            {
                pOamData->split.xFlip = FALSE;
                scaleX = -scaleX;
            }

            if (pOamData->split.yFlip)
            {
                pOamData->split.yFlip = FALSE;
                scaleY = -scaleY;
            }

            x = (s16)x + tmpX;
            y = (s16)y + tmpY;

            dx = x - xPosition + xOffset;
            dy = y - yPosition + yOffset;

            // Apply rotation
            cosine = COS(pOam->rotation);
            sine = SIN(pOam->rotation);
            rx = (s16)((dx * cosine - dy * sine) >> 8) - xOffset * 2;
            ry = (s16)((dx * sine + dy * cosine) >> 8) - yOffset * 2;

            pOamData->split.y = ry + yPosition - 64;
            pOamData->split.x = (rx + xPosition - 64) & 0x1FF;

            pOamData->split.affineMode = 3;

            m = gUnk_3001238;
            if (m & 0x10)
                pOamData->split.yFlip = TRUE;
            if (m & 0x8)
                pOamData->split.xFlip = TRUE;
            pOamData->split.matrixNum = m & 7;

            SpecialCutsceneApplyOamProperties(pOamData, pOam);
            dst++;
        }

        // PORT: the matrix index ((gUnk_3001238 & 0x3F) * 4 + 3) can go past the end of gOamData, like the original
        matrix = gUnk_3001238 << 2;
        gOamData[matrix + 0].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(scaleX));
        gOamData[matrix + 1].all.affineParam = FixedMultiplication(SIN(pOam->rotation), FixedInverse(scaleX));
        gOamData[matrix + 2].all.affineParam = FixedMultiplication(-SIN(pOam->rotation), FixedInverse(scaleY));
        gOamData[matrix + 3].all.affineParam = FixedMultiplication(COS(pOam->rotation), FixedInverse(scaleY));
        gUnk_3001238++;
    }

    gNextOamSlot += partCount;
    pOam->animationDurationCounter++;
}

/**
 * @brief 997a4 | 108 | Initializes the new file intro
 * 
 */
void NewFileIntroInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    WRITE_16(REG_BLDCNT, 0xFF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

    gNextOamSlot = 0;
    ResetFreeOam();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    DMA3_FILL_32(0x7FFF, PALRAM_BASE, PALRAM_SIZE);
    WRITE_16(PALRAM_BASE, 0);
    DMA3_FILL_32(0, VRAM_BASE, 0x10000);

    WRITE_16(REG_BG3CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0);
    WRITE_16(REG_BG0CNT, 0);
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    WRITE_16(REG_DISPCNT, 0);

    CallbackSetVBlank(NewFileIntroVblank);
}

/**
 * @brief 998ac | 48 | Gets a random number for the special cutscenes
 * 
 * @return u8 Random number
 */
u8 SpecialCutsceneGetRandomNumber(void)
{
    u16 seed;
    u8 value;

    seed = gUnk_3005404;
    seed = seed + seed * 4 + 0x3573 + gFrameCounter8Bit;
    value = sRandomNumberTable[gFrameCounter16Bit & 0x1F] + (seed >> 8);
    gUnk_3005404 = (seed & 0xFF) | (value << 8);

    return value;
}

/**
 * @brief 998f4 | 4c | V-blank for the new file intro
 * 
 */
void NewFileIntroVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 99940 | c | V-blank callback that only updates the audio
 * 
 */
void unk_99940(void)
{
    UpdateAudio();
}

/**
 * @brief 9994c | 78 | Handler for the cutscenes
 * 
 * @return boolu32 Ended
 */
boolu32 CutsceneHandler(void)
{
    boolu32 result;

    result = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            CutsceneInit();
            gSubGameMode1 = 2;
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                gSubGameMode1++;
            break;

        case 2:
            if (CutsceneProcess())
                gSubGameMode1++;
            break;

        case 3:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else
            {
                result = TRUE;
                gSubGameMode1 = 0;
            }
            break;
    }

    return result;
}

/**
 * @brief 999c4 | 120 | Initializes the cutscenes
 * 
 */
void CutsceneInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99af8);

    WRITE_16(REG_BLDCNT, 0xFF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

    // PORT: copies 0x8000 bytes, gCommonSpriteGfxBackup is declared as only 0x4000 bytes
    // (the copy goes on in EWRAM after it, like the original)
    DMA3_COPY_32(VRAM_OBJ, gCommonSpriteGfxBackup, 0x8000 / 4);

    gNextOamSlot = 0;
    ResetFreeOam();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    DMA3_FILL_32(0x7FFF, PALRAM_BASE, PALRAM_SIZE);
    WRITE_16(PALRAM_BASE, 0);
    DMA3_FILL_32(0, VRAM_BASE, 0x10000);

    WRITE_16(REG_BG3CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0);
    WRITE_16(REG_BG0CNT, 0);
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    WRITE_16(REG_DISPCNT, 0);

    CallbackSetVBlank(CutsceneVblank);
}

/**
 * @brief 99ae4 | 14 | V-blank for the cutscenes
 * 
 */
void CutsceneVblank(void)
{
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 99af8 | c | V-blank callback that only updates the audio
 * 
 */
void unk_99af8(void)
{
    UpdateAudio();
}

/**
 * @brief 99b04 | a8 | Processes the current cutscene
 * 
 * @return boolu32 Ended
 */
boolu32 CutsceneProcess(void)
{
    boolu32 ended;
    boolu32 done;

    ended = FALSE;

    switch (gCurrentCutscene)
    {
        case 1:
        case 8:
            done = CutsceneInternalMonologue(0);
            break;

        case 2:
        case 3:
        case 4:
        case 6:
            done = CutsceneElevatorMonologue(0);
            break;

        case 5:
            done = CutsceneElevatorMonologue(1);
            break;

        case 7:
            done = CutsceneFederationMonologue(0);
            break;

        case 9:
            done = CutsceneSecretConversation();
            break;

        case 10:
        case 11:
            done = CutsceneRestrictedLabDetaching();
            break;

        case 12:
            done = CutsceneBslExploding();
            break;

        default:
            return TRUE;
    }

    if (done)
        ended = TRUE;

    return ended;
}
