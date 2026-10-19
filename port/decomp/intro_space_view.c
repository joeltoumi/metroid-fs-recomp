#include "globals.h"
#include "gba.h"
#include "macros.h"
#include "callbacks.h"
#include "syscalls.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"

#include "structs/cutscene.h"
#include "structs/intro.h"

#include "data/new_file_intro_data.h"
#include "data/generic_data.h"
#include "data/audio.h"

#include "intro_space_view.h"

/*
 * Same content as the ROM table at 0x0879c394 (sBlob_79c394_79c3c8, first 6 entries).
 * PORT: the original indexes that ROM table with pOam->unk_4, which only ever
 * holds 0-5 here; out-of-range indexes would read the following ROM pointers.
 */
static const struct FrameData* const sIntroSpaceViewParticleOamPointers[6] = {
    sIntroSpaceViewOam_60ac08,
    sIntroSpaceViewOam_60ac18,
    sIntroSpaceViewOam_60ac28,
    sIntroSpaceViewOam_60ac38,
    sIntroSpaceViewOam_60ac28,
    sIntroSpaceViewOam_60ac18
};

/**
 * @brief 93980 | 240 | Setup for the intro space view (BSL station in space)
 *
 */
void IntroSpaceViewInit(void)
{
    u16 i;
    u8 x;
    u8 y;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DoSoundAction(0x1000000);
    StopAllMusicAndSounds();

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sBlob_6101b8_612e48, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, sizeof(sPal_612f48) / 4);

    LZ77UncompVram(sIntroBslSpaceBgGfx, VRAM_BASE);
    LZ77UncompWram(sIntroBslTilemap, (u8*)EWRAM_BASE + 0x10000);
    DMA3_COPY_32((u8*)EWRAM_BASE + 0x10000, (u8*)VRAM_BASE + 0xE800, 0x800 / 4);
    DMA3_FILL_16(0x1FF, (u8*)VRAM_BASE + 0xF000, 0x800);
    LZ77UncompVram(sIntroSpaceTilemap, (u8*)VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroBslSpaceBgPal, (u8*)PALRAM_BASE + 0x100, sizeof(sIntroBslSpaceBgPal) / 4);
    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, (u8*)VRAM_BASE + 0xE000);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, 0x1C08);
    WRITE_16(REG_BG2CNT, 0x5D02);
    WRITE_16(REG_BG3CNT, 0x1F03);

    IntroSpaceViewSetupOam(1, 0, 0, TRUE);
    IntroSpaceViewSetupOam(2, -240, -110, TRUE);

    for (i = 0; i < 10; i++)
    {
        x = SpecialCutsceneGetRandomNumber();
        y = SpecialCutsceneGetRandomNumber();
        IntroSpaceViewSetupOam(5, x, y, TRUE);
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, (u8*)VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG2);

    CallbackSetVBlank(IntroSpaceViewVblank);
    PlayMusic(0x60, 0xF);
}

/**
 * @brief 93bc0 | 38c | Processes the intro space view
 *
 * @return boolu32 Finished
 */
boolu32 IntroSpaceViewPartProcess(void)
{
    boolu32 result;
    u8 x;
    u8 y;
    u16 timer;

    result = FALSE;
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
            }

            if (SpecialCutsceneGetRandomNumber() < 64 && INTRO_DATA.unk_215 < 14)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                IntroSpaceViewSetupOam(5, x, y, TRUE);
            }
            break;

        case 1:
            if (INTRO_DATA.timer == 30)
            {
                INTRO_DATA.timer = 0;
                IntroSpaceViewSetupOam(4, 120, 74, FALSE);
                INTRO_DATA.subStage = 2;
            }
            goto spawn_particle;

        case 2:
            if (INTRO_DATA.timer == 480)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
            goto spawn_particle;

        case 3:
            if (INTRO_DATA.timer == 30)
            {
                SoundPlay(0x1E9);
            }
            else if (INTRO_DATA.timer == 1050)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 5;
            }

        spawn_particle:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
            {
                y = SpecialCutsceneGetRandomNumber();
                IntroSpaceViewSetupOam(5, 0, y, TRUE);
            }
            break;

        case 4:
            if (gWrittenToBldy < 16)
            {
                if (gWrittenToBldy == 0)
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[0x1EB].trackGroupNumber].pTrack, 10);

                gWrittenToBldy += 2;
            }
            else
            {
                result = TRUE;
            }
            break;

        case 5:
            timer = INTRO_DATA.timer;
            if (timer <= 5)
            {
                // PORT: timer is always 1-5 here (reset to 0 then incremented)
                LZ77UncompVram(sIntroSamusSittingBgGfxPointers[timer - 1], (u8*)VRAM_BASE + 0x8000 + (timer - 1) * 0x1000);
            }
            else if (timer == 6)
            {
                LZ77UncompVram(sIntroSpaceView_658be0, (u8*)VRAM_BASE + 0xE000);
                DMA3_COPY_32(sIntroSpaceViewPal_6591e4, PALRAM_BASE, 0x100 / 4);
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = 16;
                WRITE_16(REG_BG1HOFS, 0);
                WRITE_16(REG_BG1VOFS, 0);
                WRITE_16(REG_BG1CNT, 0x1C08);
            }
            else if (timer == 7)
            {
                WRITE_16(REG_BLDCNT, 0x3C42);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }
            break;

        case 6:
            if (INTRO_DATA.timer != 4)
                break;

            INTRO_DATA.timer = 0;
            if (gWrittenToBldalpha_Eva < 16)
            {
                if (gWrittenToBldalpha_Eva == 0)
                {
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[0x1E9].trackGroupNumber].pTrack, 60);
                    ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[0x1EA].trackGroupNumber].pTrack, 60);
                    PlayFadingSound(0x1EB, 60);
                }

                gWrittenToBldalpha_Eva++;
                gWrittenToBldalpha_Evb--;
            }
            else
            {
                DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                INTRO_DATA.subStage = 7;
                gWrittenToBldy = 0;
            }
            break;

        case 7:
            if (INTRO_DATA.timer == 150)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                WRITE_16(REG_BLDCNT, 0xFF);
            }
            // Doesn't process the OAM
            goto process_text;

        default:
            goto process_text;
    }

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

process_text:
    IntroProcessText();
    return result;
}

/**
 * @brief 93f4c | 1c8 | Setup for the intro flying view
 *
 */
void IntroFlyingViewInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    LZ77UncompVram(sBlob_6101b8_612e48, VRAM_OBJ);
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 0x200 / 4);

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, (u8*)VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, (u8*)VRAM_BASE + 0xE000);

    // PORT: copies 0x200 bytes from sPal_609020 (declared 0x100 bytes), the
    // second half is the data that follows it in ROM (sTitleScreenSpaceBackgroundPal)
    DMA3_COPY_32(sPal_609020, PALRAM_BASE, 0x200 / 4);
    DMA3_COPY_32(sPal_598a8c, (u8*)PALRAM_BASE + 0x1E0, sizeof(sPal_598a8c) / 4);
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, 0x1C08);
    WRITE_16(REG_BG3CNT, 0x1F03);

    IntroSpaceViewSetupOam(10, 145, 140, FALSE);
    IntroSpaceViewSetupOam(11, 140, 80, FALSE);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, (u8*)VRAM_BASE + 0xD000, 0x1000);

    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG0);

    CallbackSetVBlank(IntroSpaceViewVblank);
}

/**
 * @brief 94114 | f0 | Processes the intro flying view
 *
 * @return boolu32 Finished
 */
boolu32 IntroFlyingViewProcess(void)
{
    boolu32 result;
    u8 x;
    u8 y;

    result = FALSE;
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy == 16)
                {
                    PlayFadingSound(0x1EC, 0);
                    PlayFadingSound(0x1ED, 0);
                }
                gWrittenToBldy -= 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 10)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                IntroSpaceViewSetupOam(16, x, y, FALSE);
            }

            if (INTRO_DATA.timer == 300)
            {
                INTRO_DATA.timer = 0;
                result = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (gWrittenToBldy < 16)
                gWrittenToBldy++;
            else
                result = TRUE;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();
    return result;
}

/**
 * @brief 94204 | 124 | Main handler for the intro space view
 *
 * @return boolu32 Finished
 */
boolu32 IntroSpaceView(void)
{
    boolu32 result;

    result = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            IntroSpaceViewInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (gWrittenToBldy == 0)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (IntroSpaceViewPartProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < 16)
                gWrittenToBldy++;
            else
                INTRO_DATA.stage = 4;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            // Falls through (original behaviour, stage is set to 6 right away)

        case 4:
            IntroFlyingViewInit();
            INTRO_DATA.stage = 6;
            break;

        case 5:
            INTRO_DATA.stage = 6;
            break;

        case 6:
            if (IntroFlyingViewProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 0;
                result = TRUE;
            }
            break;

        case 7:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                result = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return result;
}

/**
 * @brief 94328 | 28 | Scrolls the space background
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessSpaceViewScrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 30)
    {
        pOam->animationDurationCounter = 0;
        gBg3XPosition--;
    }
}

/**
 * @brief 94350 | 23c | Processes the BSL ship seen from the side (BG2)
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessBslShipSideways(struct SpecialCutsceneOam* pOam)
{
    s16 xPosition;
    s32 cos;
    s32 sin;
    u8 offset;

    xPosition = pOam->xPosition;
    pOam->unk_4 = xPosition;

    if (pOam->stage == 0)
    {
        pOam->spawnX = xPosition;
        pOam->spawnY = pOam->yPosition;

        if (INTRO_DATA.subStage == 3)
            pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 780)
            IntroSpaceViewSetupOam(3, 260, 110, FALSE);

        pOam->xPosition = (((60 - pOam->spawnX) * (pOam->unk_A * 2)) >> 11) + pOam->spawnX;
        pOam->yPosition = (((10 - pOam->spawnY) * (pOam->unk_A * 2)) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 29)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 1)
        {
            pOam->unk_A = 0;
            pOam->spawnY = 4;
            pOam->unk_4 = xPosition;
            pOam->unk_8 = pOam->yPosition;
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        cos = pOam->spawnX * COS(pOam->timer);
        sin = pOam->spawnY * SIN(pOam->timer);

        pOam->xPosition = (pOam->unk_A >> 2) + pOam->spawnX;
        pOam->yPosition = ((cos * SIN(0) + sin * COS(0)) >> 16) + pOam->unk_8;

        pOam->timer++;
        pOam->unk_A++;

        if (pOam->unk_A != 60 && pOam->unk_A == 30000)
        {
            pOam->unk_A = 0;
            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->stage = 5;
        pOam->spawnX = xPosition;
        pOam->spawnY = pOam->yPosition;
    }
    else if (pOam->stage == 5)
    {
        pOam->unk_A++;
        pOam->xPosition = (((520 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((100 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;

        if (pOam->xPosition > 519)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;

    if (pOam->xPosition < -120)
        return;

    // Scroll the tilemap column by column (currentAnimationFrame = sub-tile pixels, animationDurationCounter = column)
    pOam->currentAnimationFrame += (u8)pOam->xPosition - (u8)pOam->unk_4;

    if (pOam->unk_1A_4 == 0)
    {
        if (pOam->currentAnimationFrame > 7)
        {
            pOam->currentAnimationFrame -= 8;
            offset = pOam->animationDurationCounter;
            Dma3Transfer_Unused2((u8*)EWRAM_BASE + 0x10800 + offset * 2, (u8*)VRAM_BASE + 0xF000 + offset * 2, 1, 20);

            pOam->animationDurationCounter++;
            if (pOam->animationDurationCounter == 32)
            {
                pOam->animationDurationCounter = 0;
                pOam->unk_1A_4 = 1;
            }
        }
    }
    else if (pOam->unk_1A_4 == 1)
    {
        if (pOam->currentAnimationFrame > 7)
        {
            pOam->currentAnimationFrame -= 8;

            pOam->animationDurationCounter++;
            if (pOam->animationDurationCounter == 32)
            {
                pOam->animationDurationCounter = 0;
                pOam->unk_1A_4 = 10;
            }
        }
    }
}

/**
 * @brief 9458c | 14c | Processes Samus' ship entering the view
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessSamusSHipEntering(struct SpecialCutsceneOam* pOam)
{
    s32 cos;
    s32 sin;
    s32 x;
    s32 y;

    if (pOam->stage == 0)
    {
        pOam->spawnX = 100;
        pOam->spawnY = 30;
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition - 30;
        pOam->timer = 64;
        pOam->stage = 1;
        SoundPlay(0x1EA);
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->scaling -= 2;

        if (pOam->timer == 128)
        {
            pOam->stage = 2;
            pOam->scaling = Q_8_8(1);
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->spawnX = 0;
        pOam->spawnY = 8;
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 128;
        pOam->stage = 3;
    }
    else if (pOam->stage == 3)
    {
        pOam->timer += 2;
        if (pOam->timer == 192)
            pOam->stage = 4;
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->unk_A++;
        if (pOam->unk_A == 8)
        {
            pOam->unk_A = 0;
            pOam->unk_4--;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->spawnX = 280 - pOam->xPosition;
        pOam->spawnY = 60;
        pOam->unk_4 = pOam->xPosition + pOam->spawnX;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 128;
        pOam->stage = 6;
    }
    else if (pOam->stage == 6)
    {
        pOam->timer++;
        if (pOam->timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }

    cos = pOam->spawnX * COS(pOam->timer);
    sin = pOam->spawnY * SIN(pOam->timer);

    x = cos * COS(0) - sin * SIN(0);
    y = cos * SIN(0) + sin * COS(0);

    pOam->xPosition = (x >> 16) + pOam->unk_4;
    pOam->yPosition = (y >> 16) + pOam->unk_8;
}

/**
 * @brief 946d8 | 2c | Processes the splash text, kills it when its animation ended
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessSplashText(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

/**
 * @brief 94704 | b4 | Processes a horizontal space particle
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessSpaceViewParticle(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_8 = (SpecialCutsceneGetRandomNumber() & 7) + 1;
        pOam->unk_4 = SpecialCutsceneGetRandomNumber() & 3;
        pOam->pOam = sIntroSpaceViewParticleOamPointers[pOam->unk_4];
        pOam->spawnX = pOam->xPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = ((pOam->unk_8 * pOam->unk_A) >> 4) + pOam->spawnX;

        pOam->timer++;
        if (pOam->timer == 8)
        {
            pOam->timer = 0;

            if (pOam->unk_4 < 5)
                pOam->unk_4++;
            else
                pOam->unk_4 = 0;

            pOam->pOam = sIntroSpaceViewParticleOamPointers[pOam->unk_4];
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }

    if (pOam->xPosition >= SCREEN_SIZE_X || pOam->yPosition >= SCREEN_SIZE_Y)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

/**
 * @brief 947b8 | 40 | Processes the idle ship seen from the back (floating up and down)
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessIdleShipBackview(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (SIN(pOam->timer) >> 5) + pOam->spawnY;
    }
}

/**
 * @brief 947f8 | 64 | Spawns the 4 parts of the BSL ship seen from the back
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessBslShipSpawning_2(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        IntroSpaceViewSetupOam(12, pOam->xPosition + 122, pOam->yPosition, FALSE);
        IntroSpaceViewSetupOam(13, pOam->xPosition + 50, pOam->yPosition + 1, FALSE);
        IntroSpaceViewSetupOam(14, pOam->xPosition + 36, pOam->yPosition, FALSE);
        IntroSpaceViewSetupOam(15, pOam->xPosition, pOam->yPosition, FALSE);
        pOam->type = 0;
    }
}

/**
 * @brief 9485c | d8 | Processes a part of the BSL ship seen from the back
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessBslShipBackview(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 20)
        {
            pOam->spawnX++;
            pOam->timer = 0;

            if (pOam->unk_A == 4)
                pOam->unk_A = 0;

            if (pOam->unk_A < 2)
                pOam->yPosition++;
            else if (pOam->unk_A < 4)
                pOam->yPosition--;

            if (pOam->spawnX == 300)
            {
                pOam->stage = 1;
                pOam->timer = 0;
            }

            pOam->unk_A++;
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
 * @brief 94934 | c4 | Processes a particle coming towards the camera
 *
 * @param pOam Cutscene oam pointer
 */
void IntroProcessIdleDepthParticle(struct SpecialCutsceneOam* pOam)
{
    s32 x;
    s32 y;
    s32 divisor;

    pOam->unk_4 = pOam->unk_A;

    if (pOam->stage == 0)
    {
        pOam->spawnX = (pOam->xPosition - SCREEN_X_MIDDLE) * 100;
        pOam->spawnY = (pOam->yPosition - SCREEN_Y_MIDDLE) * 100;
        pOam->stage = 1;
    }
    else
    {
        if ((s16)pOam->unk_A < 100)
        {
            if ((s16)pOam->unk_A == 25)
                pOam->pOam = sIntroSpaceViewOam_60ac18;
            else if ((s16)pOam->unk_A == 50)
                pOam->pOam = sIntroSpaceViewOam_60ac28;
            else if ((s16)pOam->unk_A == 70)
                pOam->pOam = sIntroSpaceViewOam_60ac38;

            divisor = -pOam->unk_4 + 100;
            x = pOam->spawnX / divisor;
            pOam->xPosition = x + SCREEN_X_MIDDLE;
            y = pOam->spawnY / divisor + SCREEN_Y_MIDDLE;
            pOam->yPosition = y;

            if ((u16)(x + 128) > 256 || (s16)y > 168 || (s16)y < -8)
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
    }

    pOam->unk_A++;
}

/**
 * @brief 949f8 | 3f4 | Sets up a cutscene oam for the intro space view
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param descendingSearchOrder Search a free slot from the end
 * @return u8 Slot (20 if none free)
 */
u8 IntroSpaceViewSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
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

    pOam = &INTRO_DATA.oam[slot];
    DMA3_FILL_32(0, pOam, sizeof(*pOam));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->unk_18_0 = 1;

    switch (type)
    {
        case 1:
            pOam->unk_18_0 = 0;
            pOam->pFunction = IntroProcessSpaceViewScrolling;
            break;

        case 2:
            pOam->unk_18_0 = 0;
            pOam->pFunction = IntroProcessBslShipSideways;
            break;

        case 3:
            pOam->scaling = 0x180;
            pOam->priority = 1;
            pOam->affineMode = 3;
            pOam->pOam = sIntroSpaceViewOam_60ac98;
            pOam->pFunction = IntroProcessSamusSHipEntering;
            break;

        case 4:
            pOam->pOam = sIntroSpaceViewOam_60af10;
            pOam->pFunction = IntroProcessSplashText;
            break;

        case 5:
            pOam->priority = 3;
            pOam->pOam = sIntroSpaceViewOam_60ac38;
            pOam->pFunction = IntroProcessSpaceViewParticle;
            break;

        case 10:
            pOam->spawnX = xPosition;
            pOam->spawnY = yPosition;
            pOam->scaling = Q_8_8(1);
            pOam->priority = 1;
            pOam->affineMode = 1;
            pOam->pOam = sIntroSpaceViewOam_60acd0;
            pOam->pFunction = IntroProcessIdleShipBackview;
            break;

        case 11:
            pOam->unk_18_0 = 0;
            pOam->pOam = sIntroSpaceViewOam_60acd0;
            pOam->pFunction = IntroProcessBslShipSpawning_2;
            break;

        case 12:
            pOam->unk_4 = -40;
            pOam->priority = 1;
            pOam->pOam = sIntroSpaceViewOam_60ad28;
            pOam->pFunction = IntroProcessBslShipBackview;
            break;

        case 13:
            pOam->unk_4 = -30;
            pOam->priority = 1;
            pOam->pOam = sIntroSpaceViewOam_60ad18;
            pOam->pFunction = IntroProcessBslShipBackview;
            break;

        case 14:
            pOam->unk_4 = -20;
            pOam->priority = 1;
            pOam->pOam = sIntroSpaceViewOam_60ad08;
            pOam->pFunction = IntroProcessBslShipBackview;
            break;

        case 15:
            pOam->unk_4 = -10;
            pOam->priority = 1;
            pOam->pOam = sIntroSpaceViewOam_60acf8;
            pOam->pFunction = IntroProcessBslShipBackview;
            break;

        case 16:
            pOam->priority = 2;
            pOam->pOam = sIntroSpaceViewOam_60ac08;
            pOam->pFunction = IntroProcessIdleDepthParticle;
            break;
    }

    return slot;
}

/**
 * @brief 94dec | 94 | V-blank for the intro space view
 *
 */
void IntroSpaceViewVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

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
 * @brief 94e80 | 4 | Empty function
 *
 */
void unk_94e80(void)
{
    return;
}
