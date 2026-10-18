#include "erase_sram.h"

#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "callbacks.h"
#include "init_helpers.h"
#include "sram_misc.h"
#include "syscalls.h"
#include "audio_wrappers.h"
#include "audio/track_internal.h"

/**
 * @brief 809f0 | 11c | Erase SRAM menu handler
 *
 * @return u8 bool, ended
 */
u8 EraseSramMenuHandler(void)
{
    u8 ended;
    s8 result;

    ended = FALSE;
    ERASE_SRAM_DATA.timer++;

    switch (gSubGameMode1)
    {
        case 0:
            EraseSramMenuInit();
            gSubGameMode1++;
            break;

        case 1:
            // Fade in
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy--;
                break;
            }

            ERASE_SRAM_DATA.bldcnt = BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_BG1_FIRST_TARGET_PIXEL |
                BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_BG3_FIRST_TARGET_PIXEL | BLDCNT_OBJ_FIRST_TARGET_PIXEL |
                BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_ALPHA_BLENDING_EFFECT; // 0xEF
            ERASE_SRAM_DATA.targetBldy = 0;
            gSubGameMode1++;
            ERASE_SRAM_DATA.timer = 0;
            break;

        case 2:
            result = EraseSramProcessInput();
            gSubGameMode2 = result;
            if (result == 0)
                break;

            ERASE_SRAM_DATA.timer = 0;
            if (result == 1)
                gSubGameMode1 = 5; // Erase
            else
                gSubGameMode1 = 3; // Don't erase
            break;

        case 3:
            if (ERASE_SRAM_DATA.timer > 40)
            {
                ERASE_SRAM_DATA.bldcnt = 0xFF;
                ERASE_SRAM_DATA.timer = 0;
                gSubGameMode1++;
            }
            break;

        case 4:
            // Fade out, don't erase
            if (gWrittenToBldy <= 15)
                gWrittenToBldy++;
            else
                ended = TRUE;
            break;

        case 5:
            if (ERASE_SRAM_DATA.timer > 40)
            {
                ERASE_SRAM_DATA.bldcnt = 0xBF;
                ERASE_SRAM_DATA.timer = 0;
                gSubGameMode1++;
            }
            break;

        case 6:
            // Fade out, then erase
            if (gWrittenToBldy <= 15)
            {
                gWrittenToBldy++;
            }
            else
            {
                EraseSram();
                ended = TRUE;
            }
            break;
    }

    EraseSramProcessOam();
    ResetFreeOam();
    return ended;
}

/**
 * @brief 80b0c | 50 | Processes the input of the erase SRAM menu
 *
 * @return s8 0 = nothing, 1 = erase, 2 = leave
 */
s8 EraseSramProcessInput(void)
{
    s8 result;

    result = 0;
    if (ERASE_SRAM_DATA.action & ERASE_SRAM_ACTION_PENDING)
        EraseSramApplyInput();
    else
        result = EraseSramCheckForInput();

    if (ERASE_SRAM_DATA.targetBldy != gWrittenToBldy)
    {
        if (ERASE_SRAM_DATA.targetBldy > gWrittenToBldy)
            gWrittenToBldy++;
        else
            gWrittenToBldy--;
    }

    EraseSramUpdateCursorPosition();
    return result;
}

/**
 * @brief 80b5c | 90 | Applies the pending action of the erase SRAM menu
 *
 */
void EraseSramApplyInput(void)
{
    if (ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].oamId == 2)
        return;

    ERASE_SRAM_DATA.action &= ~ERASE_SRAM_ACTION_PENDING;
    ERASE_SRAM_DATA.cursor = ERASE_SRAM_DATA.action;

    switch (ERASE_SRAM_DATA.action)
    {
        case 0:
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].oamId = sEraseSramOptionsOamIds[0];
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].oamId = 0;
            break;

        case 1:
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].oamId = sEraseSramOptionsOamIds[1];
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].oamId = 0;
            break;

        case 2:
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].oamId = sEraseSramOptionsOamIds[2];
            break;

        case 3:
            ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].oamId = sEraseSramOptionsOamIds[3];
            break;
    }

    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].currentAnimationFrame = 0;

    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].oamId = 1;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].currentAnimationFrame = 0;
}

/**
 * @brief 80bec | 10c | Checks for input on the erase SRAM menu
 *
 * @return u8 0 = nothing, 1 = erase, 2 = leave
 */
u8 EraseSramCheckForInput(void)
{
    u8 result;
    u8 sound;
    u8 confirm;

    result = 0;
    sound = 0;
    confirm = FALSE;

    switch (ERASE_SRAM_DATA.cursor)
    {
        case 0:
            if (gChangedInput & KEY_RIGHT)
            {
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 1;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                // Don't erase
                result = 2;
                sound = 1;
                confirm = TRUE;
            }
            break;

        case 1:
            if (gChangedInput & KEY_LEFT)
            {
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 0;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                // Go to the confirmation
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 2;
                sound = 1;
                ERASE_SRAM_DATA.targetBldy = 4;
            }
            break;

        case 2:
            if (gChangedInput & KEY_RIGHT)
            {
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 3;
                sound = 4;
            }
            else if (gChangedInput & (KEY_A | KEY_B))
            {
                // Back to the first question
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 0;
                ERASE_SRAM_DATA.targetBldy = 0;
                if (gChangedInput & KEY_A)
                    sound = 1;
                else
                    sound = 3;
            }
            break;

        case 3:
            if (gChangedInput & KEY_LEFT)
            {
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 2;
                sound = 4;
            }
            else if (gChangedInput & KEY_A)
            {
                // Erase
                result = 1;
                sound = 2;
                confirm = TRUE;
            }
            else if (gChangedInput & KEY_B)
            {
                ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 0;
                sound = 3;
                ERASE_SRAM_DATA.targetBldy = 0;
            }
            break;
    }

    if (confirm)
    {
        ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].oamId = 2;
        ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].animationDurationCounter = 0;
        ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].currentAnimationFrame = 0;
    }

    if (sEraseSramSounds[sound] != 0)
        SoundPlay(sEraseSramSounds[sound]);

    return result;
}

/**
 * @brief 80cf8 | 200 | Initializes the erase SRAM menu
 *
 */
void EraseSramMenuInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(EraseSramLoadingVBlank);

    WRITE_16(REG_BLDCNT, BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_BG1_FIRST_TARGET_PIXEL |
        BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_BG3_FIRST_TARGET_PIXEL | BLDCNT_OBJ_FIRST_TARGET_PIXEL |
        BLDCNT_BACKDROP_FIRST_TARGET_PIXEL | BLDCNT_BRIGHTNESS_INCREASE_EFFECT); // 0xBF
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

    ERASE_SRAM_DATA.language = gLanguage;
    if ((u8)(gLanguage - 2) > 4)
    {
        ERASE_SRAM_DATA.language = 2;
        gLanguage = 0;
    }

    // Wait for v-blank
    while ((u16)(READ_16(REG_VCOUNT) - 21) < 140) {}

    DMA3_COPY_16(sEraseSramBgPal, PALRAM_BASE, 0x100);
    DMA3_COPY_16(sEraseSramObjPal, PALRAM_OBJ, 0x70);

    LZ77UncompVram(sEraseSramBgGfx, VRAM_BASE + 0x1000);
    LZ77UncompVram(sEraseSramObjGfx, VRAM_BASE + 0x12000);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][0], VRAM_BASE);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][1], VRAM_BASE + 0x11000);
    LZ77UncompVram(sEraseSramTextGfxPointers[ERASE_SRAM_DATA.language][0], VRAM_BASE + 0x10000);
    LZ77UncompVram(sEraseSramBg1Tilemap, VRAM_BASE + 0xD000);
    LZ77UncompVram(sEraseSramBg3Tilemap, VRAM_BASE + 0xF000);

    WRITE_16(REG_BG0CNT, 0);
    WRITE_16(REG_BG2CNT, 0);
    WRITE_16(REG_BG1CNT, 0x1A01);
    WRITE_16(REG_BG3CNT, 0x1E03);

    gWrittenToBldalpha_Evb = 0;
    WRITE_16(REG_BLDALPHA, 0);

    gUnk_3000be3 = FALSE;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    EraseSramResetOam();
    EraseSramProcessOam();

    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG3 | DCNT_OBJ);
    CallbackSetVBlank(EraseSramVBlank);
}

/**
 * @brief 80ef8 | 5c | Resets the objects of the erase SRAM menu
 *
 */
void EraseSramResetOam(void)
{
    ERASE_SRAM_DATA.cursor = 0;
    ERASE_SRAM_DATA.action = ERASE_SRAM_ACTION_PENDING | 0;

    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].oamId = sEraseSramOptionsOamIds[0];
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].yPosition = sEraseSramQuestionsPositions[0][1];
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_1].xPosition = sEraseSramQuestionsPositions[0][0];

    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].oamId = 1;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].currentAnimationFrame = 0;

    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].oamId = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].animationDurationCounter = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].currentAnimationFrame = 0;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].yPosition = sEraseSramQuestionsPositions[1][1];
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_QUESTION_2].xPosition = sEraseSramQuestionsPositions[1][0];

    EraseSramUpdateCursorPosition();
}

/**
 * @brief 80f54 | 4c | Updates the position of the cursor of the erase SRAM menu
 *
 */
void EraseSramUpdateCursorPosition(void)
{
    u8 question;

    question = ERASE_SRAM_DATA.cursor / 2;
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].yPosition =
        sEraseSramQuestionsPositions[question][1] + sEraseSramCursorOffsets[ERASE_SRAM_DATA.cursor][1];
    ERASE_SRAM_DATA.oam[ERASE_SRAM_OBJECT_CURSOR].xPosition =
        sEraseSramQuestionsPositions[question][0] + sEraseSramCursorOffsets[ERASE_SRAM_DATA.cursor][0];
}

/**
 * @brief 80fa0 | 78 | V-blank code of the erase SRAM menu
 *
 */
void EraseSramVBlank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (ERASE_SRAM_DATA.bldcnt != 0)
    {
        WRITE_16(REG_BLDCNT, ERASE_SRAM_DATA.bldcnt);
        ERASE_SRAM_DATA.bldcnt = 0;
    }
}

/**
 * @brief 81018 | c | V-blank code while the erase SRAM menu loads
 *
 */
void EraseSramLoadingVBlank(void)
{
    UpdateAudio();
}

/**
 * @brief 81024 | 148 | Processes the objects of the erase SRAM menu
 *
 */
void EraseSramProcessOam(void)
{
    s32 i;
    s32 j;
    struct MenuOam* pOam;
    const struct FrameData* pAnim;
    const u16* pFrame;
    u16* dst;
    union OamData* pData;
    s32 prevSlot;
    s32 nextSlot;
    u16 yPosition;
    s16 xPosition;
    u16 part;

    gNextOamSlot = 0;
    dst = (u16*)gOamData;
    nextSlot = 0;
    prevSlot = 0;
    // PORT: the original keeps the animation pointer of the previous object for an oam id above 6
    // (and an undefined one for the first object), oam ids are always 0-6
    pAnim = sEraseSramOam[0];

    for (i = 0; i < ERASE_SRAM_OBJECT_END; i++)
    {
        pOam = &ERASE_SRAM_DATA.oam[i];
        if (pOam->oamId == 0)
            continue;

        if (pOam->oamId <= 6)
        {
            pAnim = sEraseSramOam[pOam->oamId];

            // Update animation
            if (pOam->animationDurationCounter >= pAnim[pOam->currentAnimationFrame].timer)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame++;
                if (pAnim[pOam->currentAnimationFrame].timer == 0)
                    pOam->currentAnimationFrame = 0;
            }
        }

        pOam->animationDurationCounter++;

        yPosition = pOam->yPosition - gBg1YPosition;
        xPosition = pOam->xPosition - gBg1XPosition;

        pFrame = pAnim[pOam->currentAnimationFrame].pFrame;
        nextSlot += *pFrame++;

        if (prevSlot < nextSlot)
        {
            pData = &gOamData[prevSlot];
            for (j = nextSlot - prevSlot; j != 0; j--)
            {
                part = *pFrame++;
                *dst++ = part;
                pData->split.y = part + yPosition;

                part = *pFrame++;
                *dst++ = part;
                pData->split.x = part + xPosition;

                *dst = *pFrame++;
                pData->split.priority = 1;

                dst += 2;
                pData++;
            }

            prevSlot = nextSlot;
        }
    }

    gNextOamSlot = nextSlot;
}
