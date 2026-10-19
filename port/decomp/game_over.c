#include "game_over.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "callbacks.h"
#include "oam.h"
#include "syscalls.h"
#include "init_helpers.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"
#include "audio/track_internal.h"

#include "constants/game_state.h"

#ifdef GAME_OVER_EQUIV
// Equivalence testing only: store the original ROM addresses of the callbacks so that
// the RAM written by the C version is identical to the original
void GameOverProcessCursor_Orig(struct GameOverOam* pOam);
void unk_9e2cc_Orig(struct GameOverOam* pOam);
void GameOverVblank_Orig(void);
void unk_9e58c_Orig(void);
asm(".set GameOverProcessCursor_Orig, 0x0809e205");
asm(".set unk_9e2cc_Orig, 0x0809e2cd");
asm(".set GameOverVblank_Orig, 0x0809e561");
asm(".set unk_9e58c_Orig, 0x0809e58d");
#define FUNC_PTR(f) f##_Orig
#else
#define FUNC_PTR(f) f
#endif

// Text graphics of the game over options, by language (only read for language > LANGUAGE_HIRAGANA)
static const u8* const sGameOverTextGfxPointers[LANGUAGE_COUNT] = {
    [LANGUAGE_JAPANESE] = (&sBlob_73421e_73c274[0x5b3a]), // 0x08739d58
    [LANGUAGE_HIRAGANA] = (&sBlob_73421e_73c274[0x5b3a]),
    [LANGUAGE_ENGLISH] = (&sBlob_73421e_73c274[0x5b3a]),
    [LANGUAGE_GERMAN] = (&sBlob_73421e_73c274[0x6212]),   // 0x0873a430
    [LANGUAGE_FRENCH] = (&sBlob_73421e_73c274[0x690a]),   // 0x0873ab28
    [LANGUAGE_ITALIAN] = (&sBlob_73421e_73c274[0x70ea]),  // 0x0873b308
    [LANGUAGE_SPANISH] = (&sBlob_73421e_73c274[0x788e]),  // 0x0873baac
};

// Original table at 0x0879e868 : cursor idle, continue selected, quit selected
static const struct FrameData* const sGameOverCursorOamPointers[3] = {
    sGameOverOam_Cursor,
    sGameOverOam_CursorSelected,
    sGameOverOam_CursorSelected,
};

/**
 * @brief 9deb4 | a4 | Game over main loop
 *
 * @return u8 0 = running, 1 = continue, 2 = quit
 */
u8 GameOverHandler(void)
{
    u8 result;

    result = 0;

    switch (gSubGameMode1)
    {
        case 0:
            GameOverInit();
            gSubGameMode1 = 1;
            break;

        case 1:
            GameOverDrawAllOam();
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
                break;
            }

            PlayMusic(3, 0);
            gSubGameMode1++;
            break;

        case 2:
            if (GameOverAfterOptionDelay())
            {
                WRITE_16(REG_BLDCNT, 0xFF);
                gSubGameMode1++;
            }
            break;

        case 3:
            GameOverDrawAllOam();
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
                break;
            }

            if (GAME_OVER_DATA.selectedOption == 1)
                result = 1;
            else if (GAME_OVER_DATA.selectedOption == 2)
                result = 2;

            gSubGameMode1 = 0;
            break;
    }

    return result;
}

/**
 * @brief 9df58 | 1cc | Initializes the game over screen
 *
 */
void GameOverInit(void)
{
    u32 zero;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(FUNC_PTR(unk_9e58c));
    WRITE_16(REG_DISPCNT, 0);

    zero = 0;
    DMA_SET(3, &zero, &gNonGameplayRam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, sizeof(gNonGameplayRam) / sizeof(u32)));

    WRITE_16(REG_BLDCNT, 0xBF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

    // Back up the sprite graphics (0x8000 bytes)
    // PORT: this covers gCommonSpriteGfxBackup and the gRoomSpriteGfxBackup right after it in EWRAM
    DMA3_COPY_32(VRAM_OBJ, gCommonSpriteGfxBackup, 0x8000 / sizeof(u32));

    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

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

    LZ77UncompVram(sGameOverObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sGameOverObjPal, PALRAM_OBJ, 0x200 / sizeof(u32));
    LZ77UncompVram(sGameOverBgGfx, VRAM_BASE);

    if (gLanguage > LANGUAGE_HIRAGANA)
    {
        // PORT: the original reads past the table for gLanguage >= LANGUAGE_COUNT
        LZ77UncompVram(sGameOverTextGfxPointers[gLanguage], VRAM_BASE);
    }

    LZ77UncompVram(sGameOverBg3TileTable, VRAM_BASE + 0xF800);
    LZ77UncompVram(sGameOverBg1TileTable, VRAM_BASE + 0xF000);
    DMA3_COPY_32(sGameOverBgPal, PALRAM_BASE, 0x200 / sizeof(u32));

    WRITE_16(REG_BG1CNT, 0x1E02);
    WRITE_16(REG_BG3CNT, 0x1F03);

    GameOverSetupOam(GAME_OVER_OAM_TYPE_CURSOR, 0x2B, 0x6F);
    GameOverDrawAllOam();

    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG3 | DCNT_OBJ);
    CallbackSetVBlank(FUNC_PTR(GameOverVblank));
}

/**
 * @brief 9e124 | 34 | Processes the game over and waits a bit after an option was chosen
 *
 * @return u8 bool, delay ended
 */
u8 GameOverAfterOptionDelay(void)
{
    u8 ended;

    ended = FALSE;

    GameOverProcessOam();
    GameOverDrawAllOam();

    if (GAME_OVER_DATA.optionChosen == TRUE)
    {
        GAME_OVER_DATA.afterChoiceTimer++;
        if (GAME_OVER_DATA.afterChoiceTimer == 30)
        {
            GAME_OVER_DATA.afterChoiceTimer = 0;
            ended = TRUE;
        }
    }

    return ended;
}

/**
 * @brief 9e158 | ac | Sets up a new game over OAM object
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot used (3 if none free)
 */
u8 GameOverSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;
    struct GameOverOam* pOam;

    for (i = 0; GAME_OVER_DATA.oam[i].type != 0; )
    {
        i++;
        if (i > 2)
            return 3;
    }

    if (i > 2)
        return 3;

    GameOverResetOam(i);

    pOam = &GAME_OVER_DATA.oam[i];
    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->drawn = TRUE;

    if (type == GAME_OVER_OAM_TYPE_CURSOR)
    {
        pOam->priority = 3;
        pOam->pOam = sGameOverCursorOamPointers[0];
        pOam->pFunc = FUNC_PTR(GameOverProcessCursor);
    }
    else if (type == GAME_OVER_OAM_TYPE_FOLLOW_CURSOR)
    {
        pOam->priority = 3;
        pOam->pOam = sGameOverOam_Cursor;
        pOam->pFunc = FUNC_PTR(unk_9e2cc);
    }

    return i;
}

/**
 * @brief 9e204 | c8 | Handles the game over cursor (Samus head)
 *
 * @param pOam Game over OAM object
 */
void GameOverProcessCursor(struct GameOverOam* pOam)
{
    if (pOam->stage != 0)
        return;

    if (gChangedInput & KEY_UP)
    {
        if (pOam->yPosition != 0x6F)
        {
            pOam->yPosition = 0x6F;
            SoundPlay(0x1F9);
        }
    }
    else if (gChangedInput & KEY_DOWN)
    {
        if (pOam->yPosition != 0x88)
        {
            pOam->yPosition = 0x88;
            SoundPlay(0x1F9);
        }
    }

    if (gChangedInput & (KEY_A | KEY_START))
    {
        if (pOam->yPosition == 0x6F)
        {
            SoundPlay(0x1FE);
            FadeMusic(10);
            pOam->pOam = sGameOverCursorOamPointers[1];
            GAME_OVER_DATA.selectedOption = 1;
        }
        else if (pOam->yPosition == 0x88)
        {
            SoundPlay(0x1FE);
            FadeMusic(10);
            pOam->pOam = sGameOverCursorOamPointers[2];
            GAME_OVER_DATA.selectedOption = 2;
        }

        GAME_OVER_DATA.optionChosen = TRUE;
        pOam->currentAnimationFrame = 0;
        pOam->animationDurationCounter = 0;
        pOam->stage = 1;
    }
}

/**
 * @brief 9e2cc | 28 | Copies the position of the cursor
 *
 * @param pOam Game over OAM object
 */
void unk_9e2cc(struct GameOverOam* pOam)
{
    u16 position[2];

    GameOverGetPositionAndSlotOfOamByType(GAME_OVER_OAM_TYPE_CURSOR, &position[0], &position[1]);
    pOam->xPosition = position[0];
    pOam->yPosition = position[1];
}

/**
 * @brief 9e2f4 | 28 | Resets the animation/drawing fields of a game over OAM object
 *
 * @param slot Slot
 */
void GameOverResetOam(u8 slot)
{
    struct GameOverOam* pOam;

    pOam = &GAME_OVER_DATA.oam[slot];
    pOam->currentAnimationFrame = 0;
    pOam->animationDurationCounter = 0;
    pOam->unk_8 = 0;
    pOam->stage = 0;
    pOam->objMode = 0;
    pOam->priority = 0;
    pOam->xFlip = 0;
    pOam->paletteOffset = 0;
    pOam->tileOffset = 0;
}

/**
 * @brief 9e31c | 38 | Calls the functions of the game over OAM objects
 *
 */
void GameOverProcessOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(GAME_OVER_DATA.oam); i++)
    {
        if (GAME_OVER_DATA.oam[i].type != 0)
            GAME_OVER_DATA.oam[i].pFunc(&GAME_OVER_DATA.oam[i]);
    }
}

/**
 * @brief 9e354 | 40 | Draws all the game over OAM objects
 *
 */
void GameOverDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(GAME_OVER_DATA.oam); i++)
    {
        if (GAME_OVER_DATA.oam[i].drawn)
            GameOverDrawOam(&GAME_OVER_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief 9e394 | 188 | Draws a game over OAM object
 *
 * @param pOam Game over OAM object
 */
void GameOverDrawOam(struct GameOverOam* pOam)
{
    u16* dst;
    const u16* src;
    const struct FrameData* pFrame;
    s32 partCount;
    s32 i;
    u16 part0;
    u16 part1;
    u32 slot;
    u32 x;
    u32 y;

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

    for (i = 0; i < partCount; i++)
    {
        part0 = *src++;
        part1 = *src++;
        *dst++ = part0;
        *dst++ = part1;
        *dst++ = *src++;

        slot = gNextOamSlot + i;

        if (pOam->xFlip == TRUE)
        {
            gOamData[slot].split.xFlip ^= TRUE;
            x = pOam->xPosition - (sGameOverOamXWidthTable[gOamData[slot].split.shape * 4 + gOamData[slot].split.size] * 8 + part1);
            y = part0 + pOam->yPosition;
        }
        else
        {
            y = part0 + pOam->yPosition;
            x = part1 + pOam->xPosition;
        }

        gOamData[slot].split.y = y;
        gOamData[slot].split.x = x;
        gOamData[slot].split.priority = pOam->priority;
        gOamData[slot].split.paletteNum += pOam->paletteOffset;
        gOamData[slot].split.tileNum += pOam->tileOffset;
        gOamData[slot].split.objMode = pOam->objMode;

        dst++;
    }

    gNextOamSlot += partCount;
    pOam->animationDurationCounter++;
}

/**
 * @brief 9e51c | 44 | Gets the position of the first game over OAM object of a type
 *
 * @param type Type
 * @param pX X position destination (300 if not found)
 * @param pY Y position destination (200 if not found)
 */
void GameOverGetPositionAndSlotOfOamByType(u8 type, u16* pX, u16* pY)
{
    u8 i;

    for (i = 0; i < ARRAY_SIZE(GAME_OVER_DATA.oam); i++)
    {
        if (GAME_OVER_DATA.oam[i].type == type)
        {
            *pX = GAME_OVER_DATA.oam[i].xPosition;
            *pY = GAME_OVER_DATA.oam[i].yPosition;
            return;
        }
    }

    *pX = 300;
    *pY = 200;
}

/**
 * @brief 9e560 | 2c | V-blank code of the game over
 *
 */
void GameOverVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9e58c | c | V-blank code of the game over during init
 *
 */
void unk_9e58c(void)
{
    UpdateAudio();
}
