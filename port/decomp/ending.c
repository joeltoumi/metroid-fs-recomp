#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"
#include "callbacks.h"
#include "syscalls.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"

#include "constants/audio.h"
#include "constants/text.h"
#include "constants/game_state.h"

#include "data/generic_data.h"
#include "data/new_file_intro_data.h"
#include "data/audio.h"

#include "structs/audio.h"
#include "structs/cutscene.h"
#include "structs/intro.h"

#include "ending.h"

#define ENDING_IS_ANIM_ENDED(pOam, frame) \
    ((frame)[0].timer == (pOam)->animationDurationCounter && (frame)[1].timer == 0)

/**
 * @brief 94e84 | f0 | Main handler for the ending cutscene
 *
 * @return boolu32 Finished
 */
boolu32 EndingHandler(void)
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
            if (EndingBslCrashing())
                gSubGameMode1 = 2;
            break;

        case 2:
            if (EndingInShip())
            {
                INTRO_DATA.unk_20E = 0;
                gSubGameMode1 = 3;
            }
            break;

        case 3:
            INTRO_DATA.unk_20E++;
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.unk_20E == 1)
                {
                    INTRO_DATA.unk_20E = 0;
                    gWrittenToBldy++;
                }
            }
            else
            {
                if (INTRO_DATA.unk_20E == 1)
                {
                    Sram_ProcessEndingSave(0);
                }
                else if (INTRO_DATA.unk_20E == 2)
                {
                    Sram_ProcessEndingSave(1);
                }
                else if (INTRO_DATA.unk_20E == 3)
                {
                    Sram_ProcessEndingSave(2);
                }
                else if (INTRO_DATA.unk_20E == 4)
                {
                    Sram_ProcessEndingSave(3);
                    INTRO_DATA.unk_20E = 0;
                    result = TRUE;
                }
            }

            SpecialCutsceneDrawAllOam();
            break;
    }

    return result;
}

/**
 * @brief 94f74 | 204 | Setup for the BSL crashing part of the ending
 *
 */
void EndingBslCrashingInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sEndingBslCrashingObjGfx_6238f4, VRAM_OBJ);
    DMA3_COPY_32(sEndingBslCrashingObjPal_636c38, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sEndingBslCrashingBgGfx_62b5f4, VRAM_BASE);
    LZ77UncompVram(sEndingBslCrashingTilemap_638c14, VRAM_BASE + 0xF000);
    LZ77UncompVram(sEndingBslCrashingTilemap_639bc4, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sEndingBslCrashingBgPal_637038, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

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
    WRITE_16(REG_BLDCNT, 0xFF);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 8;
    gWrittenToBldalpha_Evb = 14;

    EndingBslCrashingSetupOam(5, -40, 200, FALSE);
    EndingBslCrashingSetupOam(4, 128, 72, TRUE);
    EndingBslCrashingSetupOam(2, 164, 40, TRUE);
    EndingBslCrashingSetupOam(1, 164, 40, TRUE);
    EndingBslCrashingSetupOam(3, 134, 60, TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingBslCrashingVblank);
}

/**
 * @brief 95178 | 200 | Setup for the ship front view part of the ending
 *
 */
void EndingShipFrontViewInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, INTRO_DATA.unk_14, sizeof(INTRO_DATA.unk_14));
    // Clears unk_110 up to (not including) unk_20C
    DMA3_FILL_16(0, &INTRO_DATA.unk_110, 0xFC);

    LZ77UncompVram(sEndingShipFrontViewBgGfx_626738, VRAM_BASE);
    LZ77UncompVram(sEndingShipFrontViewTilemap_63929c, VRAM_BASE + 0xF000);
    LZ77UncompVram(sEndingShipFrontViewTilemap_6395b8, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sEndingShipFrontViewBgPal_636e38, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = -30;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, 0x1C08);
    WRITE_16(REG_BG2CNT, 0x1E02);
    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_BLDCNT, 0xBF);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 16;
    gWrittenToBldalpha_Evb = 16;
    WRITE_16(REG_BLDALPHA, C_16_2_8(16, 16));

    EndingBslCrashingSetupOam(12, 0, (s16)gBg2YPosition, FALSE);
    EndingBslCrashingSetupOam(10, 120, 106, TRUE);
    EndingBslCrashingSetupOam(11, 120, 64, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingShipFrontViewVblank);
}

/**
 * @brief 95378 | 2c4 | Processes the BSL crashing part of the ending
 *
 * @return boolu32 Finished
 */
boolu32 EndingBslCrashingProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == BLDY_MAX_VALUE)
                    SoundPlay_3b1c(0x24B);

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
                INTRO_DATA.unk_110 = TRUE;
                INTRO_DATA.unk_111 = 0;
            }
            else if (INTRO_DATA.timer == 2)
            {
                WRITE_16(REG_BLDCNT, 0x842);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
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
                    INTRO_DATA.unk_110 = TRUE;
                    INTRO_DATA.unk_111++;
                }
            }
            else if (INTRO_DATA.timer == 20)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
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
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }
            break;

        case 5:
            if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
                EndingShipFrontViewInit();
            }
            return finished;

        case 6:
            WRITE_16(REG_BLDCNT, 0xC40);
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 7;
            break;

        case 7:
            if (INTRO_DATA.timer == 168)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 2;
                INTRO_DATA.subStage = 8;
            }
            break;

        case 8:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldalpha_Eva != 0)
                {
                    gWrittenToBldalpha_Eva--;
                    if (gWrittenToBldalpha_Eva == 0)
                        SpecialCutsceneDestroyOamOfType(10);
                }
                else
                {
                    WRITE_16(REG_BLDCNT, 0xFF);
                    INTRO_DATA.subStage = 9;
                }
            }
            break;

        case 9:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 4)
                {
                    gWrittenToBldy++;
                    INTRO_DATA.timer = 0;
                }
            }
            else if (INTRO_DATA.timer == 90)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }
            break;

        default:
            return finished;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    return finished;
}

/**
 * @brief 9563c | 88 | Handler for the BSL crashing part of the ending
 *
 * @return boolu32 Finished
 */
boolu32 EndingBslCrashing(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            EndingBslCrashingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (EndingBslCrashingProcess())
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
 * @brief 956c4 | d8 | Processes the falling BSL (and its debris)
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessFallingBsl(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

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
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
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
            pOam->pOam = sEndingOam_6362b8;
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
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 9579c | 30 | Destroys the OAM once its animation ended
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_9579c(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 957cc | 64 | Processes the small ship leaving
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessLeavingSmallShip(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;

        if (pOam->unk_A == 150)
        {
            pOam->unk_A = 0;
            pOam->unk_18_0 = TRUE;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX - pOam->unk_A * 4;
        pOam->yPosition = pOam->spawnY + pOam->unk_A / 3;

        if (pOam->xPosition < 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 95830 | 64 | Processes the big ship leaving
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessLeavingBigShip(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;

        if (pOam->unk_A == 240)
        {
            pOam->unk_A = 0;
            pOam->unk_18_0 = TRUE;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX + pOam->unk_A * 4;
        pOam->yPosition = pOam->spawnY - pOam->unk_A * 3;

        if (pOam->xPosition > 280)
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 95894 | 34 | Processes the thrusters of the front facing ship (follows the ship)
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessFrontFacingShipThrusters(struct SpecialCutsceneOam* pOam)
{
    s16 xPosition;
    s16 yPosition;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    EndingGetPositionAndSlotOfOamByType(12, &xPosition, &yPosition);
    pOam->yPosition = pOam->spawnY - yPosition;
}

/**
 * @brief 958c8 | 90 | Processes the front facing ship (bobbing, scrolls BG2)
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessFrontFacingShip(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->timer = 4;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (sSineTable[pOam->timer] >> 3) + pOam->spawnY;

        if (pOam->timer == 64)
        {
            pOam->stage = 2;
            pOam->unk_A = 0;
        }
    }
    else if (pOam->stage == 2)
    {
        if (pOam->unk_A == 2)
        {
            pOam->unk_A = 0;
            pOam->timer++;
        }

        pOam->yPosition = (sSineTable[pOam->timer] >> 3) + pOam->spawnY;
    }

    gBg2YPosition = pOam->yPosition;
}

/**
 * @brief 95958 | 2fc | Spawns an OAM for the BSL crashing / ship front view parts
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search a free slot from the end
 * @return u8 Slot (20 if none)
 */
u8 EndingBslCrashingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;
    struct SpecialCutsceneOam* pOam;

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

    pOam = &INTRO_DATA.oam[slot];
    DMA3_FILL_32(0, pOam, sizeof(struct SpecialCutsceneOam));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->unk_18_0 = TRUE;

    if (type == 1)
    {
        pOam->scaling = Q_8_8(1.f);
        pOam->priority = 2;
        pOam->affineMode = 1;
        pOam->pOam = sEndingOam_636020;
        pOam->pFunction = EndingProcessFallingBsl;
    }
    else if (type == 2)
    {
        pOam->scaling = Q_8_8(2.f);
        pOam->unk_18_3 = 1;
        pOam->priority = 2;
        pOam->affineMode = 1;
        pOam->pOam = sEndingOam_636038;
        pOam->pFunction = EndingProcessFallingBsl;
    }
    else if (type == 3)
    {
        pOam->priority = 2;
        pOam->pOam = sEndingOam_636050;
        pOam->pFunction = unk_9579c;
    }
    else if (type == 4)
    {
        pOam->unk_18_0 = FALSE;
        pOam->priority = 2;
        pOam->pOam = sEndingOam_636288;
        pOam->pFunction = EndingProcessLeavingSmallShip;
    }
    else if (type == 5)
    {
        pOam->unk_18_0 = FALSE;
        pOam->pOam = sEndingOam_6362a0;
        pOam->pFunction = EndingProcessLeavingBigShip;
    }
    else if (type == 10)
    {
        pOam->unk_18_3 = 1;
        pOam->priority = 3;
        pOam->pOam = sEndingOam_6363a0;
        pOam->pFunction = unk_95e20;
    }
    else if (type == 11)
    {
        pOam->priority = 3;
        pOam->pOam = sEndingOam_6363b8;
        pOam->pFunction = EndingProcessFrontFacingShipThrusters;
    }
    else if (type == 12)
    {
        pOam->unk_18_0 = FALSE;
        pOam->pOam = sEndingOam_6363a0;
        pOam->pFunction = EndingProcessFrontFacingShip;
    }

    return slot;
}

/**
 * @brief 95c54 | d8 | V-blank for the BSL crashing part of the ending
 *
 */
void EndingBslCrashingVblank(void)
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

    if (INTRO_DATA.unk_110 == TRUE)
    {
        INTRO_DATA.unk_110 = FALSE;
        DMA3_COPY_32(&sEndingBslFlashPal_636a38[INTRO_DATA.unk_111 * PAL_ROW],
            PALRAM_BASE + 0x120, PAL_ROW_SIZE / sizeof(u32));
    }
}

/**
 * @brief 95d2c | 94 | V-blank for the ship front view part of the ending
 *
 */
void EndingShipFrontViewVblank(void)
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
 * @brief 95dc0 | 60 | Returns slot, X and Y position of an ending OAM
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot (20 if not found)
 */
u8 EndingGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition)
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
 * @brief 95e20 | 4 | Empty OAM process function
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_95e20(struct SpecialCutsceneOam* pOam)
{
    return;
}

/**
 * @brief 95e24 | 200 | Setup for the Samus monologue (in ship) part of the ending
 *
 */
void EndingMonologueInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sEndingMonologueObjGfx_6150e8, VRAM_OBJ);
    DMA3_COPY_32(sEndingMonologueObjPal_636638, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sEndingMonologueBgGfx_6186a4, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingMonologueBgTilemap_6377f8, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sEndingMonologueBgPal_636438, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / sizeof(u32));
    DMA3_FILL_32(0, VRAM_BASE, 0x4800);
    DMA3_COPY_32(sIntroPal_663820, PALRAM_BASE + 0x180, 4 * PAL_ROW_SIZE / sizeof(u32));

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, 0x900);
    WRITE_16(REG_BG1CNT, 0x1E01);
    WRITE_16(REG_BG3CNT, 0x1F0B);
    WRITE_16(REG_BLDCNT, 0xFF);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 0;
    gWrittenToBldalpha_Evb = 16;

    EndingDialogueSetupOam(1, 260, 180, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingMonologueVblank);
}

/**
 * @brief 96024 | 204 | Setup for the Adam conversation part of the ending
 *
 */
void EndingAdamConversationInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, INTRO_DATA.unk_14, sizeof(INTRO_DATA.unk_14));
    // Clears unk_110 up to (not including) unk_20C
    DMA3_FILL_16(0, &INTRO_DATA.unk_110, 0xFC);

    LZ77UncompVram(sEndingAdamBgGfx_6131c8, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingAdamBgTilemap_637238, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    DMA3_COPY_32(sEndingMonologueBgPal_636438, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    gBg0XPosition = -8;
    gBg0YPosition = 8;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 8);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, 0x1C08);
    WRITE_16(REG_BG3CNT, 0x1F0B);
    WRITE_16(REG_BLDCNT, 0xFF);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 16;
    gWrittenToBldalpha_Evb = 16;
    WRITE_16(REG_BLDALPHA, C_16_2_8(16, 16));

    EndingDialogueSetupOam(2, 112, 80, TRUE);
    EndingDialogueSetupOam(3, 112, 80, TRUE);
    EndingDialogueSetupOam(4, 112, 80, TRUE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingConversationAndAnimalsVblank);
}

/**
 * @brief 96228 | 220 | Setup for the animals part of the ending
 *
 */
void EndingAnimalsInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    DMA3_FILL_16(0, INTRO_DATA.unk_14, sizeof(INTRO_DATA.unk_14));
    // Clears unk_110 up to (not including) unk_20C
    DMA3_FILL_16(0, &INTRO_DATA.unk_110, 0xFC);

    LZ77UncompVram(sEndingAnimalsBgGfx_61b89c, VRAM_BASE);
    LZ77UncompVram(sEndingAnimalsBgGfx_6217a8, VRAM_BASE + 0x8000);
    LZ77UncompVram(sEndingAnimalsBg2Tilemap_638654, VRAM_BASE + 0xF000);
    LZ77UncompVram(sEndingAnimalsBg3Tilemap_637db8, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sEndingAnimalsBgPal_636838, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    DMA3_FILL_16(0x2FF, VRAM_BASE + 0xF500, 0x300);

    gBg0XPosition = 0;
    gBg0YPosition = 0;
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg3XPosition = 0;
    gBg2YPosition = -30;
    gBg3YPosition = 226;

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 226);

    WRITE_16(REG_BG2CNT, 0x1E0A);
    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_BLDCNT, 0xFF);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 16;
    gWrittenToBldalpha_Evb = 16;
    WRITE_16(REG_BLDALPHA, C_16_2_8(16, 16));

    EndingDialogueSetupOam(20, 0, 0, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(EndingConversationAndAnimalsVblank);
}

/**
 * @brief 96448 | 4e0 | Processes the in ship part of the ending (monologue, Adam, animals)
 *
 * @return boolu32 Finished
 */
boolu32 EndingInShipProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == 7)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldy != 0)
                {
                    gWrittenToBldy--;
                }
                else
                {
                    PlayMusic(MUSIC_EPILOGUE, 14);
                    INTRO_DATA.subStage = 1;
                }
            }
            break;

        case 1:
            if (INTRO_DATA.timer == 70)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
                INTRO_DATA.unk_12 = 0;
                INTRO_DATA.unk_10 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][7];
                INTRO_DATA.subStage = 2;
            }
            break;

        case 2:
            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
                INTRO_DATA.unk_218 = 1;

            INTRO_DATA.timer = 0;

            if (INTRO_DATA.unk_218 == 2)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 3;
            }

            if (EndingCheckMonologueEnded())
            {
                INTRO_DATA.subStage = 3;
                INTRO_DATA.unk_218 = 0;
            }

            if (INTRO_DATA.unk_213 == 0)
            {
                INTRO_DATA.unk_213 = 100;
            }
            else if (INTRO_DATA.unk_213 == 1)
            {
                INTRO_DATA.unk_213 = 100;
                SpecialCutsceneProcessMonologue();
            }
            break;

        case 3:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Evb = 0;
                gWrittenToBldalpha_Eva = 16;
            }
            else if (INTRO_DATA.timer == 20)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, 0x1841);
                INTRO_DATA.subStage = 4;
            }
            break;

        case 4:
            if (INTRO_DATA.timer == 4)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Evb < 16)
                    gWrittenToBldalpha_Evb++;

                if (gWrittenToBldalpha_Eva != 0)
                    gWrittenToBldalpha_Eva--;

                if (gWrittenToBldalpha_Evb == 16 && gWrittenToBldalpha_Eva == 0)
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                    INTRO_DATA.subStage = 5;
                }
            }
            break;

        case 5:
            if (INTRO_DATA.timer == 10)
            {
                EndingDialogueSetupOam(30, 120, 80, TRUE);
            }
            else if (INTRO_DATA.timer == 39)
            {
                gWrittenToBldy = BLDY_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 40)
            {
                WRITE_16(REG_BLDCNT, 0xFF);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }
            break;

        case 6:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 7;
            }
            break;

        case 7:
            INTRO_DATA.timer = 0;
            EndingAdamConversationInit();
            INTRO_DATA.subStage = 8;
            return finished;

        case 8:
            gWrittenToBldy = 0;
            INTRO_DATA.timer = 0;
            SoundPlay(SOUND_24C);
            INTRO_DATA.subStage = 9;
            break;

        case 9:
            if (INTRO_DATA.timer != 10 && INTRO_DATA.timer == 40)
            {
                EndingDialogueSetupOam(0xFF, 0, 0, FALSE);
                EndingDialogueSetupOam(6, 20, 192, FALSE);
                EndingDialogueSetupOam(7, 128, 192, FALSE);
                EndingDialogueSetupOam(9, 128, 192, FALSE);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 10;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            EndingProcessAdamText();
            return finished;

        case 10:
            INTRO_DATA.timer = 0;

            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
                INTRO_DATA.unk_218 = 1;

            if (INTRO_DATA.unk_218 == 2)
            {
                INTRO_DATA.unk_218 = 0;
                SoundPlay(SOUND_203);
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                INTRO_DATA.unk_218 = 0;
                SoundPlay(SOUND_203);
                FadeMusic(10);
                INTRO_DATA.subStage = 11;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            EndingProcessAdamText();
            return finished;

        case 11:
            INTRO_DATA.timer = 0;
            break;

        case 12:
            if (INTRO_DATA.timer == 1)
            {
                ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[SOUND_24C].trackGroupNumber].pTrack, 0);
            }
            else if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.subStage = 13;
            }
            break;

        case 13:
            EndingAnimalsInit();
            INTRO_DATA.timer = 0;
            gWrittenToBldy = 0;
            INTRO_DATA.subStage = 14;
            return finished;

        case 14:
            if (INTRO_DATA.timer == 1)
            {
                PlayMusic(MUSIC_EPILOGUE_END, 14);
            }
            else if (INTRO_DATA.timer == 640)
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                INTRO_DATA.subStage = 15;
            }
            break;

        case 15:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    INTRO_DATA.subStage = 0;
                    finished = TRUE;
                }
            }
            break;

        default:
            return finished;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    return finished;
}

/**
 * @brief 96928 | 88 | Handler for the in ship part of the ending
 *
 * @return boolu32 Finished
 */
boolu32 EndingInShip(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            EndingMonologueInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (EndingInShipProcess())
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
 * @brief 969b0 | 30 | Processes the monologue cursor
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessMonologueCursor(struct SpecialCutsceneOam* pOam)
{
    // EndingMonologueInit draws once before setting pText: the GBA then
    // reads the BIOS at address 0 (not the arrow character).
    if (INTRO_DATA.pText != NULL && *INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        pOam->xPosition = 118;
        pOam->yPosition = INTRO_DATA.unk_E * 8 + 24;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

/**
 * @brief 969e0 | 28 | Resets the animation counter once the animation ended
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_969e0(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 96a08 | 34 | Processes the SR388 radar view
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessSr388RadarView(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_633ec4;
            pOam->stage = 1;
        }
    }
}

/**
 * @brief 96a3c | 34 | Processes the Samus view radar view
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessSamusViewRadarView(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_633f0c;
            pOam->stage = 1;
        }
    }
}

/**
 * @brief 96a70 | 9c | Processes a popup (opening, waiting, closing)
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_96a70(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
            SoundPlay(SOUND_11C);

        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;

        if (INTRO_DATA.subStage == 11)
        {
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_633244;
            SoundPlay(SOUND_11D);
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
        {
            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 96b0c | 8c | Processes the Adam text cursor
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessAdamTextCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        pOam->xPosition = 290;
    }
    else if (*INTRO_DATA.pText != CHAR_NEW_LINE)
    {
        if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
        {
            pOam->xPosition = 290;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_633e8c;
        }
        else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
        {
            pOam->xPosition = SCREEN_X_MIDDLE;
            pOam->yPosition = 154;
            pOam->pOam = sEndingOam_633e64;
        }
        else
        {
            pOam->xPosition = INTRO_DATA.unk_C * 8 + INTRO_DATA.unk_212 + 14;
            pOam->yPosition = INTRO_DATA.unk_E * 8 + 132;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    else
    {
        pOam->xPosition = INTRO_DATA.unk_C * 8 + INTRO_DATA.unk_212 + 14;
        pOam->yPosition = INTRO_DATA.unk_E * 8 + 132;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}

/**
 * @brief 96b98 | 1a8 | Processes the Adam panel (frame and background)
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessAdamPanel(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;

        if (pOam->yPosition > 128)
        {
            pOam->yPosition -= 8;
            return;
        }

        pOam->yPosition = 128;

        if (pOam->type == 7)
            SoundPlay(SOUND_20A);

        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter)
        {
            if (frame[1].timer == 0)
            {
                pOam->animationDurationCounter = 0;
                pOam->stage = 2;
            }

            if (pOam->type != 7)
                return;

            if (pOam->currentAnimationFrame == 10)
                EndingDialogueSetupOam(8, pOam->xPosition, pOam->yPosition, FALSE);
        }

        if (pOam->type == 7 && pOam->currentAnimationFrame == 11 && pOam->animationDurationCounter == 15)
        {
            INTRO_DATA.unk_212 = 0;
            INTRO_DATA.unk_E = 0;
            INTRO_DATA.unk_C = 0;
            INTRO_DATA.pText = sEndingAdamTextPointers[gLanguage][112];
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->animationDurationCounter = 0;
        pOam->timer++;
        if (pOam->timer == 1)
        {
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->animationDurationCounter = 0;

        if (INTRO_DATA.subStage == 11)
        {
            pOam->currentAnimationFrame = 0;

            if (pOam->type == 7)
            {
                pOam->pOam = sEndingOam_6332fc;
                SoundPlay(SOUND_20B);
            }
            else if (pOam->type == 9)
            {
                pOam->pOam = sEndingOam_6333cc;
            }

            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        if (pOam->currentAnimationFrame == 11 && pOam->animationDurationCounter == 3)
        {
            if (pOam->type == 7)
                SpecialCutsceneDestroyOamOfType(8);

            pOam->animationDurationCounter = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->animationDurationCounter = 0;

        if (pOam->yPosition < 192)
        {
            pOam->yPosition += 8;
        }
        else
        {
            if (pOam->type == 7)
                INTRO_DATA.subStage = 12;

            pOam->type = 0;
            pOam->unk_18_0 = FALSE;
        }
    }
}

/**
 * @brief 96d40 | 88 | Processes the Adam icon
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessAdamIcon(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_6338a4;
            pOam->stage = 1;
        }

        if (INTRO_DATA.subStage == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_63345c;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 1)
    {
        if (INTRO_DATA.subStage == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sEndingOam_63345c;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (ENDING_IS_ANIM_ENDED(pOam, frame))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 96dc8 | 138 | Processes the scrolling of the animals part (BG2/BG3 and VRAM clearing)
 *
 * @param pOam Cutscene OAM pointer
 */
void EndingProcessAnimalsScrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->xPosition = gBg2XPosition;
        pOam->yPosition = gBg2YPosition;
        pOam->spawnX = gBg3XPosition;
        pOam->spawnY = gBg3YPosition;

        if (pOam->yPosition < -32)
        {
            pOam->unk_A = 0x4000;
            DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x1000);
        }
        else
        {
            pOam->unk_A = 0x5000;
        }

        pOam->timer = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->timer == 10)
        {
            pOam->timer = 0;
            pOam->stage = 2;
        }
    }
    else
    {
        if (INTRO_DATA.subStage != 14)
        {
            pOam->timer = 0;
            return;
        }

        if (pOam->timer == 2)
        {
            pOam->timer = 0;

            if (pOam->yPosition > -160)
            {
                pOam->yPosition--;
                pOam->unk_8++;
            }

            if (pOam->spawnY > 0)
                pOam->spawnY--;

            gBg2YPosition = pOam->yPosition;
            gBg3YPosition = pOam->spawnY;
        }

        if (pOam->unk_8 == 9)
        {
            pOam->unk_8 = 0;
            if (pOam->unk_A != 0)
            {
                pOam->unk_A -= 0x400;
                DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x400);
            }
        }
    }
}

/**
 * @brief 96f00 | 8 | Kills the OAM
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_96f00(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

/**
 * @brief 96f08 | 380 | Spawns an OAM for the monologue / Adam conversation / animals parts
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search a free slot from the end
 * @return u8 Slot (20 if none)
 */
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;
    struct SpecialCutsceneOam* pOam;

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

    pOam = &INTRO_DATA.oam[slot];
    DMA3_FILL_32(0, pOam, sizeof(struct SpecialCutsceneOam));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->unk_18_0 = TRUE;

    if (type == 1)
    {
        pOam->pOam = sEndingOam_633e64;
        pOam->pFunction = EndingProcessMonologueCursor;
    }
    else if (type == 2)
    {
        pOam->priority = 2;
        pOam->pOam = sEndingOam_6338d4;
        pOam->pFunction = unk_969e0;
    }
    else if (type == 3)
    {
        pOam->priority = 2;
        pOam->pOam = sEndingOam_6339d4;
        pOam->pFunction = EndingProcessSr388RadarView;
    }
    else if (type == 4)
    {
        pOam->priority = 2;
        pOam->pOam = sEndingOam_633c4c;
        pOam->pFunction = EndingProcessSamusViewRadarView;
    }
    else if (type == 5)
    {
        pOam->priority = 2;
        pOam->pOam = sEndingOam_6331ec;
        pOam->pFunction = unk_96a70;
    }
    else if (type == 6)
    {
        pOam->pOam = sEndingOam_633e8c;
        pOam->pFunction = EndingProcessAdamTextCursor;
    }
    else if (type == 7)
    {
        pOam->priority = 1;
        pOam->pOam = sEndingOam_633294;
        pOam->pFunction = EndingProcessAdamPanel;
    }
    else if (type == 8)
    {
        pOam->priority = 1;
        pOam->pOam = sEndingOam_633434;
        pOam->pFunction = EndingProcessAdamIcon;
    }
    else if (type == 9)
    {
        pOam->priority = 1;
        pOam->pOam = sEndingOam_633364;
        pOam->pFunction = EndingProcessAdamPanel;
    }
    else if (type == 20)
    {
        pOam->unk_18_0 = FALSE;
        pOam->pFunction = EndingProcessAnimalsScrolling;
    }
    else if (type == 30)
    {
        SoundPlay(SOUND_12D);
        pOam->priority = 1;
        pOam->pOam = sEndingOam_633f24;
        pOam->pFunction = unk_97418;
    }
    else if (type == 0xFF)
    {
        pOam->unk_18_0 = FALSE;
        pOam->pOam = sEndingOam_6331ec;
        pOam->pFunction = unk_96f00;
    }

    return slot;
}

/**
 * @brief 97288 | 9c | V-blank for the monologue part of the ending
 *
 */
void EndingMonologueVblank(void)
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

    unk_98158();
}

/**
 * @brief 97324 | 94 | V-blank for the Adam conversation and animals parts of the ending
 *
 */
void EndingConversationAndAnimalsVblank(void)
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
 * @brief 973b8 | 60 | Returns slot, X and Y position of an ending OAM (duplicate)
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @return u8 Slot (20 if not found)
 */
u8 EndingGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition)
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
 * @brief 97418 | 4 | Empty OAM process function
 *
 * @param pOam Cutscene OAM pointer
 */
void unk_97418(struct SpecialCutsceneOam* pOam)
{
    return;
}
