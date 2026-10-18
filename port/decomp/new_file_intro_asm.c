#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "callbacks.h"
#include "syscalls.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"

#include "structs/cutscene.h"
#include "structs/intro.h"
#include "structs/audio.h"

#include "data/new_file_intro_data.h"
#include "data/generic_data.h"
#include "data/sprite_data.h"
#include "data/audio.h"

#include "new_file_intro_asm.h"

/**
 * @brief 90d60 | 1f4 | Initializes the landing on BSL cutscene
 *
 */
void NewFileIntroLandingOnBslInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroLandingOnBslObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sIntroLandingOnBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroLandingOnBslBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroLandingOnBslTilemap_60030c, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroLandingOnBslTilemap_5fff08, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroLandingOnBslBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg2XPosition = 0;
    gBg2YPosition = 40;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 40);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, 0, 0));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, 1, 0));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, 3, 0));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    NewFileIntroLandingOnBslSetupOam(1, 120, 0, FALSE);
    NewFileIntroLandingOnBslSetupOam(11, 128, 100 - gBg2YPosition, TRUE);
    NewFileIntroLandingOnBslSetupOam(2, 128, 72 - gBg2YPosition, FALSE);
    NewFileIntroLandingOnBslSetupOam(3, 0, 0, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroLandingOnBslVblank);
}

/**
 * @brief 90f54 | 128 | Processes the landing on BSL cutscene
 *
 * @return boolu32 Finished
 */
boolu32 NewFileIntroLandingOnBslProcess(void)
{
    boolu32 finished;

    finished = FALSE;
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
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
                PlayMusic(0x1E, 13);
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (gBg2YPosition == 0)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 70)
            {
                INTRO_DATA.timer = 0;
                NewFileIntroLandingOnBslSetupOam(12, 128, 50, FALSE);
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (INTRO_DATA.timer == 90)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                    gWrittenToBldy++;
                else
                    finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

/**
 * @brief 9107c | 88 | Handler for the landing on BSL cutscene
 *
 * @return boolu32 Finished
 */
boolu32 NewFileIntroLandingOnBsl(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroLandingOnBslInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroLandingOnBslProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

/**
 * @brief 91104 | 74 | Scrolls the background down while landing on the BSL
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessLandingOnBslScroll(struct SpecialCutsceneOam* pOam)
{
    INTRO_DATA.unk_217 = 0;
    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->yPosition = gBg2YPosition;
        pOam->timer = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        INTRO_DATA.unk_217 = 0;
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            if (pOam->yPosition > 0)
            {
                INTRO_DATA.unk_217 = -1;
                pOam->yPosition--;
                gBg2YPosition = pOam->yPosition;
            }
            else
            {
                INTRO_DATA.unk_217 = 0;
                pOam->type = 0;
            }
        }
    }
    else
    {
        pOam->timer = 0;
    }
}

/**
 * @brief 91178 | a4 | Processes the BSL door
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessBslDoor(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        NewFileIntroLandingOnBslSetupOam(6, 0, 0, FALSE);
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->pOam = sIntroLandingOnBslOam_5fe370;
        SoundPlay_3b1c(0x246);
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (NFIA_OAM_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroLandingOnBslSetupOam(4, pOam->xPosition, pOam->yPosition, TRUE);
        NewFileIntroLandingOnBslSetupOam(5, pOam->xPosition, pOam->yPosition, TRUE);
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }

    pOam->yPosition -= (s8)INTRO_DATA.unk_217;
}

/**
 * @brief 9121c | 7c | Animates the BSL door light palettes
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessBslDoorLight(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;
    if (pOam->unk_A == 8)
    {
        pOam->unk_A = 0;
        INTRO_DATA.unk_110 = 1;
        if (INTRO_DATA.unk_111 < 5)
            INTRO_DATA.unk_111++;
        else
            INTRO_DATA.unk_111 = 0;
    }

    pOam->timer++;
    if (pOam->timer == 8)
    {
        pOam->timer = 0;
        INTRO_DATA.unk_12C = 1;
        if (INTRO_DATA.unk_12D < 7)
            INTRO_DATA.unk_12D++;
        else
            INTRO_DATA.unk_12D = 0;
    }
}

/**
 * @brief 91298 | e8 | Processes the top part of the BSL door
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessBslDoorTop(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;

    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            if (pOam->spawnY < 54)
            {
                pOam->spawnY++;
                pOam->yPosition--;
            }
            else
            {
                pOam->stage = 2;
            }
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(7, &x, &y);
        if (y > 90)
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            if (pOam->spawnY > 0)
            {
                pOam->spawnY--;
                if (pOam->spawnY == 37)
                    NewFileIntroLandingOnBslSetupOam(10, 0, 0, TRUE);
                pOam->yPosition++;
            }
            else
            {
                pOam->stage = 4;
                NewFileIntroLandingOnBslSetupOam(9, pOam->xPosition, pOam->yPosition, TRUE);
            }
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }

    pOam->yPosition -= (s8)INTRO_DATA.unk_217;
}

/**
 * @brief 91380 | c4 | Processes the bottom part of the BSL door
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessBslDoorBottom(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;

    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            if (pOam->spawnY < 54)
            {
                pOam->spawnY++;
                pOam->yPosition++;
            }
            else
            {
                pOam->stage = 2;
            }
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(7, &x, &y);
        if (y > 90)
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            if (pOam->spawnY > 0)
            {
                pOam->spawnY--;
                pOam->yPosition--;
            }
            else
            {
                pOam->stage = 4;
            }
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }

    pOam->yPosition -= (s8)INTRO_DATA.unk_217;
}

/**
 * @brief 91444 | 64 | Animates the landing lights palette (increasing)
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_91444(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        INTRO_DATA_U8_12E(0x148) = 0;
        INTRO_DATA_U8_12E(0x149) = 5;
        pOam->stage = 1;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 75)
    {
        pOam->unk_A = 0;
        INTRO_DATA_U8_12E(0x148) = 1;
        if (INTRO_DATA_U8_12E(0x149) < 9)
            INTRO_DATA_U8_12E(0x149)++;
        else
            pOam->type = 0;
    }
}

/**
 * @brief 914a8 | 334 | Processes Samus' ship landing in the BSL
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_914a8(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;
    u16 timer;
    u8 step;

    pOam->unk_A++;
    timer = pOam->unk_A;

    switch (pOam->stage)
    {
        case 0:
            if (NewFileIntroGetPositionAndSlotOfOamByType_2(4, &x, &y) == ARRAY_SIZE(INTRO_DATA.oam))
                break;

            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 1;
            break;

        case 1:
            NewFileIntroGetPositionAndSlotOfOamByType_2(4, &x, &y);
            pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;
            if (pOam->yPosition - y > 8)
            {
                INTRO_DATA_U8_12E(0x1F0) = 1;
                INTRO_DATA_U8_12E(0x1F1) = 1;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->unk_A = 0;
                pOam->stage = 2;
            }
            break;

        case 2:
            pOam->timer++;
            step = INTRO_DATA_U8_12E(0x1F1);
            if (step <= 6)
            {
                pOam->yPosition = (timer >> 2) + pOam->spawnY;
                if (pOam->timer == 12)
                {
                    pOam->timer = 0;
                    INTRO_DATA_U8_12E(0x1F0) = 1;
                    INTRO_DATA_U8_12E(0x1F1) = step + 1;
                    pOam->spawnX = pOam->xPosition;
                    pOam->spawnY = pOam->yPosition;
                    pOam->unk_A = 0;
                }
            }
            else if (step == 7)
            {
                if (timer == 2)
                {
                    pOam->unk_A = 0;
                    pOam->yPosition++;
                }

                if (pOam->timer == 12)
                {
                    pOam->timer = 0;
                    pOam->pOam = sIntroLandingOnBslOam_5ff628;
                    INTRO_DATA_U8_12E(0x1F0) = 1;
                    INTRO_DATA_U8_12E(0x1F1)++;
                }
            }
            else if (step == 8)
            {
                if (timer == 2)
                {
                    pOam->unk_A = 0;
                    pOam->yPosition++;
                }

                if (pOam->timer == 10)
                {
                    pOam->timer = 0;
                    pOam->priority = 1;
                    INTRO_DATA_U8_12E(0x1F0) = 1;
                    INTRO_DATA_U8_12E(0x1F1)++;
                }
            }
            else if (step <= 13)
            {
                if (timer == 2)
                {
                    pOam->unk_A = 0;
                    pOam->yPosition++;
                }

                if (pOam->timer == 8)
                {
                    pOam->timer = 0;
                    INTRO_DATA_U8_12E(0x1F0) = 1;
                    INTRO_DATA_U8_12E(0x1F1)++;
                }
            }
            else if (step == 14)
            {
                if (timer == 2)
                {
                    pOam->unk_A = 0;
                    pOam->yPosition++;
                }

                if (pOam->timer == 8)
                {
                    pOam->timer = 0;
                    pOam->pOam = sIntroLandingOnBslOam_5ff638;
                    INTRO_DATA_U8_12E(0x1F0) = 1;
                    INTRO_DATA_U8_12E(0x1F1)++;
                    pOam->spawnX = pOam->xPosition;
                    pOam->spawnY = pOam->yPosition;
                    pOam->unk_A = 0;
                    pOam->stage = 3;
                }
            }

            if (pOam->yPosition > 80)
                pOam->yPosition = 80;
            break;

        case 3:
            if (timer == 20)
            {
                pOam->unk_A = 0;
                pOam->stage = 4;
                NewFileIntroLandingOnBslSetupOam(8, pOam->xPosition, 150, FALSE);
            }
            break;

        case 4:
            timer = pOam->unk_8;
            pOam->unk_8 = timer + 1;
            if (pOam->unk_8 > 0xFF)
                pOam->unk_8 = timer - 0xFF;

            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->affineMode = 0;
            pOam->pOam = sIntroLandingOnBslOam_5ff540;
            pOam->stage = 5;
            break;

        case 5:
            pOam->yPosition = (timer >> 4) + pOam->spawnY;
            if (pOam->yPosition > 90 && pOam->currentAnimationFrame == 0 && pOam->animationDurationCounter == 1)
            {
                pOam->pOam = sIntroLandingOnBslOam_5ff4d8;
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 6;
            }
            break;

        case 6:
            pOam->yPosition = (timer >> 4) + pOam->spawnY;
            if (NFIA_OAM_ANIM_ENDED(pOam))
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff5a8;
                pOam->stage = 7;
            }
            break;

        case 7:
            pOam->yPosition = (timer >> 4) + pOam->spawnY;
            if (pOam->yPosition > 103)
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff580;
                pOam->stage = 8;
            }
            break;

        case 8:
            if (NFIA_OAM_ANIM_ENDED(pOam))
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff5a8;
                INTRO_DATA.subStage = 4;
                pOam->stage = 9;
            }
            break;
    }
}

/**
 * @brief 917dc | cc | Processes the smoke of the landing ship
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessShipLandingSmoke(struct SpecialCutsceneOam* pOam)
{
    s16 x;
    s16 y;

    if (pOam->stage == 0)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(12, &x, &y);
        pOam->xPosition = x;
        pOam->yPosition = 150;
        if (y > 100 && NFIA_OAM_ANIM_ENDED(pOam))
        {
            pOam->unk_A = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroLandingOnBslOam_5ff5e8;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        NewFileIntroGetPositionAndSlotOfOamByType_2(12, &x, &y);
        pOam->xPosition = x;
        pOam->yPosition = 150;
        if (y > 103 && NFIA_OAM_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (NFIA_OAM_ANIM_ENDED(pOam))
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

/**
 * @brief 918a8 | 44 | To document
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_918a8(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (NFIA_OAM_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroLandingOnBslOam_5fe430;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 918ec | 64 | Animates the landing lights palette (decreasing) while the ship arms extend
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessExtendingShipArms(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        INTRO_DATA_U8_12E(0x148) = 0;
        INTRO_DATA_U8_12E(0x149) = 9;
        pOam->stage = 1;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 75)
    {
        pOam->unk_A = 0;
        INTRO_DATA_U8_12E(0x148) = 1;
        if (INTRO_DATA_U8_12E(0x149) > 6)
            INTRO_DATA_U8_12E(0x149)--;
        else
            pOam->type = 0;
    }
}

/**
 * @brief 91950 | 1c | Processes the landing lights
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessLandingLights(struct SpecialCutsceneOam* pOam)
{
    pOam->yPosition -= (s8)INTRO_DATA.unk_217;
}

/**
 * @brief 9196c | 208 | Processes the ship landing
 *
 * @param pOam Cutscene OAM pointer
 */
void NewFileIntroProcessShipLanding(struct SpecialCutsceneOam* pOam)
{
    u16 timer;

    pOam->unk_A++;
    timer = pOam->unk_A;

    switch (pOam->stage)
    {
        case 0:
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
            break;

        case 1:
            pOam->yPosition = (timer >> 2) + pOam->spawnY;
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
            break;

        case 2:
            if (pOam->scaling < 0x100)
            {
                pOam->scaling++;
                if (pOam->scaling > 0xFF)
                {
                    pOam->scaling = 0x100;
                    pOam->affineMode = 0;
                }
                else if (pOam->scaling > 0xBF)
                {
                    pOam->priority = 1;
                }
            }

            pOam->yPosition = (pOam->unk_A >> 2) + pOam->spawnY;
            if (pOam->yPosition > 80)
            {
                pOam->yPosition = 80;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = 80;
                pOam->unk_A = 0;

                if (pOam->scaling == 0x100)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame = 0;
                    pOam->pOam = sIntroLandingOnBslOam_5ff530;
                    pOam->stage = 3;
                }
            }
            break;

        case 3:
            if (timer > 4)
            {
                pOam->unk_A = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff540;
                pOam->stage = 4;
                NewFileIntroLandingOnBslSetupOam(8, pOam->xPosition, 150, FALSE);
            }
            break;

        case 4:
            pOam->unk_A = 0;
            if (pOam->currentAnimationFrame == 6)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff530;
                pOam->stage = 5;
            }
            break;

        case 5:
            if (timer > 10)
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 6;
            }
            break;

        case 6:
            pOam->yPosition = (timer >> 3) + pOam->spawnY;
            if (pOam->yPosition > 88)
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff4d8;
                pOam->stage = 7;
            }
            break;

        case 7:
            if (NFIA_OAM_ANIM_ENDED(pOam))
                pOam->animationDurationCounter = 0;

            pOam->yPosition = (pOam->unk_A >> 3) + pOam->spawnY;
            if (pOam->yPosition > 103)
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff580;
                pOam->stage = 8;
            }
            break;

        case 8:
            if (NFIA_OAM_ANIM_ENDED(pOam))
            {
                pOam->unk_A = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroLandingOnBslOam_5ff5a8;
                pOam->stage = 9;
                INTRO_DATA.subStage = 4;
            }
            break;
    }

    pOam->yPosition -= (s8)INTRO_DATA.unk_217;
}

/**
 * @brief 91b74 | 388 | Spawns an OAM for the landing on BSL cutscene
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search a free slot from the end
 * @return u8 Slot (20 if none)
 */
u8 NewFileIntroLandingOnBslSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
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
            return ARRAY_SIZE(INTRO_DATA.oam);
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return ARRAY_SIZE(INTRO_DATA.oam);
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessLandingOnBslScroll;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5fe430;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoor;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorLight;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5fe410;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorTop;
    }
    else if (type == 5)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5fe420;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslDoorBottom;
    }
    else if (type == 6)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_91444;
    }
    else if (type == 7)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5ff618;
        INTRO_DATA.oam[slot].pFunction = unk_914a8;
    }
    else if (type == 8)
    {
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5ff5b8;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessShipLandingSmoke;
    }
    else if (type == 9)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5fe3c0;
        INTRO_DATA.oam[slot].pFunction = unk_918a8;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessExtendingShipArms;
    }
    else if (type == 11)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5ff6c0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessLandingLights;
    }
    else if (type == 12)
    {
        INTRO_DATA.oam[slot].scaling = 2;
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroLandingOnBslOam_5ff638;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessShipLanding;
    }

    return slot;
}

/**
 * @brief 91efc | 13c | V-blank code for the landing on BSL cutscene
 *
 */
void NewFileIntroLandingOnBslVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;
        DMA3_COPY_32(sIntroLandingOnBslLightPals + INTRO_DATA.unk_111 * PAL_ROW_SIZE,
            PALRAM_BASE + 0x340, PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA.unk_12C == 1)
    {
        INTRO_DATA.unk_12C = 0;
        DMA3_COPY_32(sIntroLandingOnBslDoorLightPals + INTRO_DATA.unk_12D * PAL_ROW_SIZE,
            PALRAM_BASE + 0x300, PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA_U8_12E(0x148) == 1)
    {
        INTRO_DATA_U8_12E(0x148) = 0;
        DMA3_COPY_32(sIntroLandingOnBslLightPals + INTRO_DATA_U8_12E(0x149) * PAL_ROW_SIZE,
            PALRAM_BASE + 0x320, PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(sIntroLandingOnBslLightPals + INTRO_DATA_U8_12E(0x149) * PAL_ROW_SIZE,
            PALRAM_BASE + 0x160, PAL_ROW_SIZE / sizeof(u32));
    }
}

/**
 * @brief 92038 | 60 | Returns slot, X and Y position of an intro OAM
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot (20 if not found)
 */
u8 NewFileIntroGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition)
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
 * @brief 92098 | 4 | Empty function
 *
 */
void unk_92098(void)
{
    return;
}

/**
 * @brief 9209c | 1a0 | Initializes the Samus in ship cutscene
 *
 */
void unk_9209c(void)
{
    u16 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    for (i = 0; i < 5; i++)
        LZ77UncompVram(sIntroSamusSittingBgGfxPointers[i], VRAM_BASE + 0x8000 + i * 0x1000);

    LZ77UncompVram(sIntroSamusInShipTilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusInShipPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 8;
    gBg2YPosition = 8;
    gBg3XPosition = 8;
    gBg3YPosition = 8;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, 0, 0));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 29, 0, 0));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Eva = 0;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
    WRITE_16(REG_BLDALPHA, C_16_2_8(BLDALPHA_MAX_VALUE, 0));

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_OBJ);

    CallbackSetVBlank(unk_93884);
}

/**
 * @brief 9223c | 294 | Processes the Samus in ship cutscene
 *
 * @return boolu32 Finished
 */
boolu32 IntroSamusInShipProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer <= 5)
            {
                // PORT: timer is never 0 here in practice (index -1 otherwise, as in the original)
                LZ77UncompVram(sIntroSamusSittingBgGfxPointers[INTRO_DATA.timer - 1],
                    VRAM_BASE + 0x8000 + (INTRO_DATA.timer - 1) * 0x1000);
            }
            else if (INTRO_DATA.timer == 6)
            {
                LZ77UncompVram(sIntroSamusInShipTilemap, VRAM_BASE + 0xE800);
                DMA3_COPY_32(sIntroSamusInShipPal, PALRAM_BASE, 8 * PAL_ROW_SIZE / sizeof(u32));
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                WRITE_16(REG_BG1HOFS, 0);
                WRITE_16(REG_BG1VOFS, 0);
                WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 29, 0, 0));
            }
            else if (INTRO_DATA.timer == 7)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT |
                    BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
            break;

        case 1:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldalpha_Evb == 0)
                {
                    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                    INTRO_DATA.subStage = 2;
                }
                else
                {
                    if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE)
                    {
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[492].trackGroupNumber].pTrack, 10);
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[493].trackGroupNumber].pTrack, 10);
                    }
                    gWrittenToBldalpha_Evb -= 2;
                }
            }
            break;

        case 2:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                {
                    if (gWrittenToBldalpha_Eva == 0)
                        PlayFadingSound(0x1EB, 0);
                    gWrittenToBldalpha_Eva++;
                }
                else
                {
                    INTRO_DATA.subStage = 3;
                }
            }
            break;

        case 3:
            if (INTRO_DATA.timer == 40)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                gWrittenToBldy = 0;
            }
            break;

        case 4:
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 5;
            break;

        case 5:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 6;
            }
            break;

        case 6:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            goto end;

        default:
            goto end;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

end:
    IntroProcessText();
    return finished;
}

/**
 * @brief 924d0 | 270 | Initializes the ship alert cutscene
 *
 */
void IntroShipAlertInit(void)
{
    u16 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    for (i = 0; i < 6; i++)
        LZ77UncompVram(sIntroShipAlertObjGfxPointers[i], VRAM_OBJ + i * 0x1000);

    DMA3_COPY_32(sIntroShipAlertObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    for (i = 0; i < 5; i++)
        LZ77UncompVram(sIntroShipAlertBgGfxPointers[i], VRAM_BASE + i * 0x1000);

    LZ77UncompVram(sIntroShipAlertTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroShipAlertPal, PALRAM_BASE, 8 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, 0, 0));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 30, 1, 0));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 31, 2, 0));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Evb = 0;
    gWrittenToBldalpha_Eva = 0;
    WRITE_16(REG_BLDALPHA, 0);

    IntroSetupOam(19, 96, 128, FALSE);
    IntroSetupOam(20, 128, 96, FALSE);
    IntroSetupOam(21, 128, 128, FALSE);
    IntroSetupOam(22, 200, 38, FALSE);
    IntroSetupOam(23, 210, 88, FALSE);

    IntroSetupBigNumberOam(24, 210, 88, 210);
    IntroSetupBigNumberOam(25, 67, 151, 200);
    IntroSetupBigNumberOam(26, 44, 152, 200);
    IntroSetupBigNumberOam(27, 37, 152, 200);
    IntroSetupBigNumberOam(28, 69, 125, 200);
    IntroSetupBigNumberOam(29, 62, 125, 200);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_OBJ);

    CallbackSetVBlank(IntroShipAlertAndDraftingVblank);
}

/**
 * @brief 92740 | f0 | Processes the ship alert cutscene
 *
 * @return boolu32 Finished
 */
boolu32 IntroShipAlertProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            IntroShipAlertInit();
            INTRO_DATA.subStage = 1;
            INTRO_DATA.timer = 0;
            break;

        case 1:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.subStage = 2;
                INTRO_DATA.timer = 0;
            }
            break;

        case 2:
            if (INTRO_DATA.timer == 399)
            {
                gWrittenToBldy = 0;
            }
            else if (INTRO_DATA.timer == 400)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (gWrittenToBldy == 0)
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[491].trackGroupNumber].pTrack, 10);
                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }
            break;

        default:
            goto end;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

end:
    IntroProcessText();
    return finished;
}

/**
 * @brief 92830 | 1d0 | Initializes the Samus drifting out cutscene
 *
 */
void IntroSamusDriftingOutInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    LZ77UncompVram(sBlob_6101b8_612e48, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    // PORT: copies 16 rows from an 8 row palette (sPal_609020 is followed by sTitleScreenSpaceBackgroundPal)
    DMA3_COPY_32(sPal_609020, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    SET_BACKDROP_COLOR(COLOR_BLACK);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, 0, 0));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, 3, 0));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gWrittenToBldalpha_Evb = 0;
    gWrittenToBldalpha_Eva = 0;
    WRITE_16(REG_BLDALPHA, 0);

    IntroSetupOam(10, 145, 140, FALSE);
    IntroSetupOam(11, 140, 80, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(IntroShipAlertAndDraftingVblank);
}

/**
 * @brief Spawns a depth particle at a random position (50% chance, if there's less than 10 OAM)
 *
 */
static void IntroSamusDriftingOutTrySpawnParticle(void)
{
    u8 x;
    u8 y;

    if ((s8)SpecialCutsceneGetRandomNumber() >= 0 && INTRO_DATA.unk_215 < 10)
    {
        x = SpecialCutsceneGetRandomNumber();
        y = SpecialCutsceneGetRandomNumber();
        IntroSetupOam(16, x, y, TRUE);
    }
}

/**
 * @brief 92a00 | 1f4 | Processes the Samus drifting out cutscene
 *
 * @return boolu32 Finished
 */
boolu32 IntroSamusDriftingOutProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            IntroSamusDriftingOutInit();
            INTRO_DATA.subStage = 1;
            INTRO_DATA.timer = 0;
            break;

        case 1:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == BLDY_MAX_VALUE)
                {
                    PlayFadingSound(0x1EC, 0);
                    PlayFadingSound(0x1ED, 0);
                }
                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.subStage = 2;
                INTRO_DATA.timer = 0;
            }

            IntroSamusDriftingOutTrySpawnParticle();
            break;

        case 2:
            if (INTRO_DATA.timer == 140)
                PlayMusic(0x49, 15);

            IntroSamusDriftingOutTrySpawnParticle();
            break;

        case 3:
            IntroSamusDriftingOutTrySpawnParticle();

            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 3)
                {
                    INTRO_DATA.timer = 0;
                    if (gWrittenToBldy == 0)
                        ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[492].trackGroupNumber].pTrack, 30);
                    gWrittenToBldy++;
                }
            }
            else if (INTRO_DATA.timer == 8)
            {
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }
            break;

        default:
            goto end;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

end:
    IntroProcessText();
    return finished;
}

/**
 * @brief 92bf4 | 118 | Handler for the Samus' ship crashing part of the intro
 *
 * @return boolu32 Finished
 */
boolu32 IntroSamusShipCrashing(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                INTRO_DATA.stage = 2;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (IntroSamusInShipProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (IntroShipAlertProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 4;
            }
            break;

        case 4:
            if (IntroSamusDriftingOutProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 5;
            }
            break;

        case 5:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

/**
 * @brief 92d0c | 148 | Randomly shakes the background (Samus drifting out)
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_92d0c(struct SpecialCutsceneOam* pOam)
{
    u8 xStep;
    u8 yStep;

    xStep = sRandomNumberTable[gFrameCounter16Bit % ARRAY_SIZE(sRandomNumberTable)] / 4;
    yStep = sRandomNumberTable[(gFrameCounter16Bit + 7) % ARRAY_SIZE(sRandomNumberTable)] / 4;

    if (pOam->unk_8 == 0)
    {
        pOam->timer++;
        if (pOam->timer != 0)
        {
            pOam->timer = 0;
            if (pOam->yPosition < 16)
            {
                pOam->yPosition += yStep;
                if (pOam->yPosition > 15)
                {
                    pOam->yPosition = 16;
                    pOam->unk_8 = 1;
                }
            }
        }
    }
    else
    {
        pOam->timer++;
        if (pOam->timer != 0)
        {
            pOam->timer = 0;
            if (pOam->yPosition > 0)
            {
                pOam->yPosition -= yStep;
                if (pOam->yPosition <= 0)
                {
                    pOam->yPosition = 0;
                    pOam->unk_8 = 0;
                }
            }
        }
    }

    if (pOam->unk_4 == 0)
    {
        pOam->unk_A++;
        if (pOam->unk_A != 0)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition < 16)
            {
                pOam->xPosition += xStep;
                if (pOam->xPosition > 15)
                {
                    pOam->xPosition = 16;
                    pOam->unk_4 = 1;
                }
            }
        }
    }
    else
    {
        pOam->unk_A++;
        if (pOam->unk_A != 0)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition > 0)
            {
                pOam->xPosition -= xStep;
                if (pOam->xPosition <= 0)
                {
                    pOam->xPosition = 0;
                    pOam->unk_4 = 0;
                }
            }
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;

    if (INTRO_DATA.subStage == 4)
    {
        pOam->rotation++;
        if (pOam->rotation == 2)
        {
            pOam->rotation = 0;
            if (gWrittenToBldalpha_Eva != 0)
                gWrittenToBldalpha_Eva--;
            if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                gWrittenToBldalpha_Evb++;
        }
    }
}

/**
 * @brief 92e54 | 26c | Processes Samus' ship drifting
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessDriftingShip(struct SpecialCutsceneOam* pOam)
{
    u16 timer;

    pOam->unk_A++;
    timer = pOam->unk_A;

    switch (pOam->stage)
    {
        case 0:
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 1;
            break;

        case 1:
            pOam->timer++;
            pOam->yPosition = (sSineTable[pOam->timer] >> 7) + pOam->spawnY;
            if (pOam->timer > 52)
            {
                pOam->unk_4++;
                if (pOam->unk_4 == 12)
                {
                    pOam->rotation--;
                    pOam->xPosition--;
                    pOam->unk_4 = 0;
                }

                pOam->unk_8++;
                if (pOam->unk_8 == 10)
                {
                    pOam->unk_8 = 0;
                    pOam->scaling--;
                }
            }

            if ((s8)pOam->timer < 0)
            {
                pOam->unk_8 = 0;
                pOam->unk_A = 0;
                pOam->unk_4 = 0;
                pOam->timer = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 2;
                SoundPlay(0x1F2);
            }
            break;

        case 2:
            pOam->timer++;
            pOam->xPosition = pOam->spawnX - (timer >> 2);
            pOam->yPosition = pOam->spawnY - (timer >> 3) + (sSineTable[pOam->timer] >> 7);

            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->unk_4 = 0;
            }

            pOam->unk_8++;
            if (pOam->unk_8 == 2)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }

            if (pOam->timer == 0)
            {
                pOam->unk_8 = 0;
                pOam->unk_A = 0;
                pOam->unk_4 = 0;
                pOam->timer = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 3;
            }
            break;

        case 3:
            pOam->timer++;
            pOam->xPosition = pOam->spawnX - (timer >> 2);
            pOam->yPosition = pOam->spawnY - (timer >> 3);

            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->unk_4 = 0;
            }

            pOam->unk_8++;
            if (pOam->unk_8 == 1)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }

            if (pOam->timer == 0)
            {
                pOam->unk_8 = 0;
                pOam->unk_A = 0;
                pOam->unk_4 = 0;
                pOam->timer = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 4;
            }

            if (pOam->scaling <= 2)
            {
                pOam->unk_8 = 0;
                pOam->unk_A = 0;
                pOam->unk_4 = 0;
                pOam->timer = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 5;
            }
            break;

        case 4:
            pOam->timer++;
            pOam->xPosition = pOam->spawnX - (timer >> 1);
            pOam->yPosition = pOam->spawnY - (timer >> 2);

            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->unk_4 = 0;
            }

            pOam->unk_8++;
            if (pOam->unk_8 == 1)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }

            if (pOam->scaling <= 2)
            {
                pOam->unk_8 = 0;
                pOam->unk_A = 0;
                pOam->unk_4 = 0;
                pOam->timer = 0;
                pOam->spawnX = pOam->xPosition;
                pOam->spawnY = pOam->yPosition;
                pOam->stage = 5;
            }
            break;

        case 5:
            pOam->unk_A = 0;
            pOam->scaling = Q_8_8(1);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->affineMode = 0;
            pOam->pOam = sIntroDriftingOutOam_60ad48;
            pOam->stage = 6;
            SoundPlay_3b1c(0x1F3);
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 3;
            break;

        case 6:
            if (NFIA_OAM_ANIM_ENDED(pOam))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
            break;
    }
}

/**
 * @brief 930c0 | 64 | Spawns the 4 parts of the BSL ship (back view)
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessBslShipSpawning(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        IntroSetupOam(12, pOam->xPosition + 122, pOam->yPosition, FALSE);
        IntroSetupOam(13, pOam->xPosition + 50, pOam->yPosition + 1, FALSE);
        IntroSetupOam(14, pOam->xPosition + 36, pOam->yPosition, FALSE);
        IntroSetupOam(15, pOam->xPosition, pOam->yPosition, FALSE);
        pOam->type = 0;
    }
}

/**
 * @brief 93124 | d4 | Processes a part of the BSL ship (back view)
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessBslShipBack(struct SpecialCutsceneOam* pOam)
{
    u16 counter;

    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 20)
        {
            pOam->spawnX++;
            pOam->timer = 0;

            if (pOam->unk_A == 4)
                pOam->unk_A = 0;

            counter = pOam->unk_A;
            if (counter <= 1)
                pOam->yPosition++;
            else if (counter <= 3)
                pOam->yPosition--;

            if (pOam->spawnX == 30)
            {
                pOam->stage = 1;
                pOam->timer = 0;
            }

            pOam->unk_A = counter + 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->unk_A++;
            pOam->timer = 0;
        }

        pOam->xPosition = (((900 - pOam->spawnX) * pOam->unk_A) >> 12) + pOam->spawnX;
        pOam->yPosition = (((pOam->unk_4 - pOam->spawnY) * pOam->unk_A) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 320)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
}

/**
 * @brief 931f8 | c4 | Processes a depth particle
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessDepthParticle(struct SpecialCutsceneOam* pOam)
{
    s32 depth;
    s32 x;

    pOam->unk_4 = pOam->unk_A;

    if (pOam->stage == 0)
    {
        pOam->spawnX = (pOam->xPosition - 120) * 100;
        pOam->spawnY = (pOam->yPosition - 80) * 100;
        pOam->stage = 1;
    }
    else if ((s16)pOam->unk_A < 100)
    {
        if ((s16)pOam->unk_A == 25)
            pOam->pOam = sIntroDriftingOutOam_60ac18;
        else if ((s16)pOam->unk_A == 50)
            pOam->pOam = sIntroDriftingOutOam_60ac28;
        else if ((s16)pOam->unk_A == 70)
            pOam->pOam = sIntroDriftingOutOam_60ac38;

        depth = 100 - pOam->unk_4;
        x = pOam->spawnX / depth;
        pOam->xPosition = x + 120;
        pOam->yPosition = pOam->spawnY / depth + 80;

        if ((u16)(x + 128) > 256 || pOam->yPosition > 168 || pOam->yPosition < -8)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
    else
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }

    pOam->unk_A++;
}

/**
 * @brief 932bc | 20 | Plays the time and distance sound
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessTimeAndDistanceOam(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0 && pOam->currentAnimationFrame == 1)
    {
        SoundPlay(0x1EE);
        pOam->stage = 1;
    }
}

/**
 * @brief 932dc | 24 | Plays the asteroids pop up sound
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroProcessAsteroidsPopUp(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0 && pOam->currentAnimationFrame == 1)
    {
        SoundPlay(0x1EF);
        pOam->stage = 1;
    }
}

/**
 * @brief 93300 | 34 | Shows an OAM after a delay, with a sound
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_93300(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_A++;
        if (pOam->unk_A == pOam->unk_8)
        {
            pOam->unk_18_0 = 1;
            pOam->stage = 1;
            SoundPlay(0x1F1);
        }
    }
}

/**
 * @brief 93334 | 48 | Plays a sound on the second frame and kills the OAM when the animation ends
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_93334(struct SpecialCutsceneOam* pOam)
{
    if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
        SoundPlay(0x1F0);

    if (NFIA_OAM_ANIM_ENDED(pOam))
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

/**
 * @brief 9337c | 2c | Shows a big changing number after a delay
 *
 * @param pOam Cutscene OAM pointer
 */
void IntroOamProcessBigChangingNumber(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_A++;
        if (pOam->unk_A == pOam->unk_8)
        {
            pOam->unk_18_0 = 1;
            pOam->stage = 1;
        }
    }
}

/**
 * @brief 933a8 | 4a0 | Spawns an OAM for the ship alert/drifting out cutscenes
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search a free slot from the end
 * @return u8 Slot (20 if none)
 */
u8 IntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
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
            return ARRAY_SIZE(INTRO_DATA.oam);
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }

        if (slot < 0)
            return ARRAY_SIZE(INTRO_DATA.oam);
    }

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_92d0c;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60acd0;
        INTRO_DATA.oam[slot].pFunction = IntroProcessDriftingShip;
    }
    else if (type == 11)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60acd0;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipSpawning;
    }
    else if (type == 12)
    {
        INTRO_DATA.oam[slot].unk_4 = -40;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60ad28;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 13)
    {
        INTRO_DATA.oam[slot].unk_4 = -30;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60ad18;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 14)
    {
        INTRO_DATA.oam[slot].unk_4 = -20;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60ad08;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 15)
    {
        INTRO_DATA.oam[slot].unk_4 = -10;
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60acf8;
        INTRO_DATA.oam[slot].pFunction = IntroProcessBslShipBack;
    }
    else if (type == 16)
    {
        INTRO_DATA.oam[slot].pOam = sIntroDriftingOutOam_60ac08;
        INTRO_DATA.oam[slot].pFunction = IntroProcessDepthParticle;
    }
    else if (type == 19)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65bb38;
        INTRO_DATA.oam[slot].pFunction = IntroProcessTimeAndDistanceOam;
    }
    else if (type == 20)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65bd00;
        INTRO_DATA.oam[slot].pFunction = unk_9397c;
    }
    else if (type == 21)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65bd48;
        INTRO_DATA.oam[slot].pFunction = unk_9397c;
    }
    else if (type == 22)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65bd60;
        INTRO_DATA.oam[slot].pFunction = IntroProcessAsteroidsPopUp;
    }
    else if (type == 23)
    {
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65be00;
        INTRO_DATA.oam[slot].pFunction = unk_93334;
    }
    else if (type == 24)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65bf10;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 25)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65c0d0;
        INTRO_DATA.oam[slot].pFunction = unk_93300;
    }
    else if (type == 26)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65c128;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 27)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65c180;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 28)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65c1d8;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }
    else if (type == 29)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sIntroShipAlertOam_65c230;
        INTRO_DATA.oam[slot].pFunction = IntroOamProcessBigChangingNumber;
    }

    return slot;
}

/**
 * @brief 93848 | 3c | Spawns a big number OAM that appears after a delay
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param delay Delay before appearing
 */
void IntroSetupBigNumberOam(u8 type, s16 xPosition, s16 yPosition, u16 delay)
{
    u8 slot;

    slot = IntroSetupOam(type, xPosition, yPosition, FALSE);
    // PORT: if no slot is free, slot is 20 and this writes in INTRO_DATA.hBlankCode (as the original)
    INTRO_DATA.oam[slot].unk_8 = delay;
}

/**
 * @brief 93884 | 7c | V-blank code for the Samus in ship cutscene
 *
 */
void unk_93884(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

/**
 * @brief 93900 | 7c | V-blank code for the ship alert and drifting out cutscenes
 *
 */
void IntroShipAlertAndDraftingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

/**
 * @brief 9397c | 4 | Empty OAM handler
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_9397c(struct SpecialCutsceneOam* pOam)
{
    return;
}
