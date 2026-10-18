#include "cutscenes_2.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "oam.h"

#include "data/generic_data.h"
#include "data/haze_data.h"

#include "callbacks.h"
#include "dma.h"
#include "fixed_point.h"
#include "init_helpers.h"
#include "music_wrappers.h"
#include "syscalls.h"
#include "text.h"
#include "audio/track_internal.h"

#ifndef PLATFORM_PC
// RAM without a linker.ld name
asm(".set gUnk_3001238, 0x03001238");
#endif

// PORT: these blob regions contain struct FrameData arrays (with 32-bit ROM pointers) and small
// tables; for the native build they must be provided as real typed data at these blob offsets.
#define sCutsceneBslExplodingExplosionOam ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d62c)) // 0x08680ecc
#define sCutsceneBslExplodingBslNearOam ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d75c))   // 0x08680ffc
#define sCutsceneBslExplodingBslFarOam ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d76c))    // 0x0868100c
#define sCutsceneBslExplodingFlashPal ((const u16*)(sBlob_6638a0_682fac + 0x1d77c))                  // 0x0868101c
#define sCutsceneBslExplodingObjPal ((const u16*)(sBlob_6638a0_682fac + 0x1d97c))                    // 0x0868121c
#define sCutsceneBslExplodingBgPal ((const u16*)(sBlob_6638a0_682fac + 0x1ecfc))                     // 0x0868259c
#define sCutsceneBslExplodingObjGfx (sBlob_6638a0_682fac + 0x19f2c)                                  // 0x0867d7cc
#define sCutsceneBslExplodingBgGfx (sBlob_6638a0_682fac + 0x15b80)                                   // 0x08679420
#define sCutsceneBslExplodingTileTable0 (sBlob_6638a0_682fac + 0x1e17c)                              // 0x08681a1c
#define sCutsceneBslExplodingTileTable1 (sBlob_6638a0_682fac + 0x1e804)                              // 0x086820a4
#define sCutsceneBslExplodingTileTable2 (sBlob_6638a0_682fac + 0x1ef08)                              // 0x086827a8
#define sCutsceneBslExplodingTileTable3 (sBlob_6638a0_682fac + 0x1f35c)                              // 0x08682bfc
#define sCutsceneMonologueCursorOam_Moving ((const struct FrameData*)(sBlob_6638a0_682fac + 0x5bc)) // 0x08663e5c
#define sCutsceneMonologueCursorOam_Idle ((const struct FrameData*)(sBlob_6638a0_682fac + 0x5d4))   // 0x08663e74
#define sCutsceneMonologueOamXFlipOffsets ((const u8*)(sBlob_6638a0_682fac + 0x1eefc))              // 0x0868279c [3][4]
#define sCutsceneOamXFlipOffsets ((const u8*)(sBlob_6131c8_63a19c + 0x26fbc))                       // 0x0863a184 [3][4]
#define sCutsceneOamYFlipOffsets ((const u8*)(sBlob_6131c8_63a19c + 0x26fc8))                       // 0x0863a190 [3][4]

#ifdef CUTSCENES_2_EQUIV
// Equivalence testing only: store the original ROM addresses of the callbacks so that
// the RAM written by the C version is identical to the original
void CutsceneBslExplodingProcessScrolling_Orig(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessBslFar_Orig(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessExplosions_Orig(struct CutsceneOam* pOam);
void unk_9db70_Orig(struct CutsceneOam* pOam);
void unk_9c92c_Orig(void);
void CutsceneBslExplodingVblank_Orig(void);
asm(".set CutsceneBslExplodingProcessScrolling_Orig, 0x0809c5f9");
asm(".set CutsceneBslExplodingProcessBslFar_Orig, 0x0809c625");
asm(".set CutsceneBslExplodingProcessExplosions_Orig, 0x0809c681");
asm(".set unk_9db70_Orig, 0x0809db71");
asm(".set unk_9c92c_Orig, 0x0809c92d");
asm(".set CutsceneBslExplodingVblank_Orig, 0x0809c8a9");
#define FUNC_PTR(f) f##_Orig
#else
#define FUNC_PTR(f) f
#endif

/**
 * @brief 9c04c | 34 | Scrolls BG2 horizontally (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9c04c(struct CutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 40)
    {
        pOam->timer = 0;
        if (pOam->xPosition > 0)
            pOam->xPosition--;
    }

    WRITE_16(REG_BG2HOFS, pOam->xPosition);
}

/**
 * @brief 9c080 | 34 | Sets up a restricted lab detaching oam and sets its unk_C
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param unk_C Value for unk_C
 */
void unk_9c080(u8 type, s16 xPosition, s16 yPosition, u16 unk_C)
{
    u8 slot;

    slot = CutsceneRestrictedLabDetachingSetupOam(type, xPosition, yPosition);
    // PORT: slot can be 16 (no free slot), the original then writes past the oam array
    CUTSCENE_DATA.oam[slot].unk_C = unk_C;
}

/**
 * @brief 9c0b4 | 3c | Sets up a restricted lab detaching oam and sets its unk_A and unk_C
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param unk_C Value for unk_C
 * @param unk_A Value for unk_A
 */
void unk_9c0b4(u8 type, s16 xPosition, s16 yPosition, u16 unk_C, u16 unk_A)
{
    u8 slot;

    slot = CutsceneRestrictedLabDetachingSetupOam(type, xPosition, yPosition);
    // PORT: slot can be 16 (no free slot), the original then writes past the oam array
    CUTSCENE_DATA.oam[slot].unk_A = unk_A;
    CUTSCENE_DATA.oam[slot].unk_C = unk_C;
}

/**
 * @brief 9c0f0 | 48 | Gets the position of the first oam of a type
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 */
void CutsceneRestrictedLabDetachingGetPositionOfOamByType(u8 type, s16* pXPosition, s16* pYPosition)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            *pXPosition = CUTSCENE_DATA.oam[i].xPosition;
            *pYPosition = CUTSCENE_DATA.oam[i].yPosition;
            return;
        }
    }

    *pXPosition = 300;
    *pYPosition = 200;
}

/**
 * @brief 9c138 | 84 | V-blank code for the restricted lab detaching cutscene
 *
 */
void CutsceneRestrictedLabDetachingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (CUTSCENE_DATA.unk_A == TRUE)
    {
        CUTSCENE_DATA.unk_A = FALSE;
        DMA3_COPY_32(&sCutsceneBslExplodingFlashPal[CUTSCENE_DATA.unk_C * 16], PALRAM_BASE + 0x120, 16 * sizeof(u16) / sizeof(u32));
    }
}

/**
 * @brief 9c1bc | c | Updates the audio
 *
 */
void unk_9c1bc(void)
{
    UpdateAudio();
}

/**
 * @brief 9c1c8 | 8c | BSL exploding cutscene
 *
 * @return boolu8 bool, ended
 */
boolu8 CutsceneBslExploding(void)
{
    boolu8 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneBslExplodingInit();
            break;

        case 1:
            if (gWrittenToBldy == 16)
                SoundPlay_3b1c(0x247);

            CutsceneFadeIn();
            if (gWrittenToBldy == 0)
                CUTSCENE_DATA.stage++;
            break;

        case 2:
            if (CutsceneBslExplodingProcess())
            {
                CUTSCENE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, 0xBF);
            }
            break;

        case 3:
            CutsceneFadeOut();
            if (gWrittenToBldy == 16)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9c254 | 190 | Initializes the BSL exploding cutscene
 *
 */
void CutsceneBslExplodingInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~0x10);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~2);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(FUNC_PTR(unk_9c92c));
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sCutsceneBslExplodingObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sCutsceneBslExplodingObjPal, PALRAM_OBJ, 0x200 / sizeof(u32));
    LZ77UncompVram(sCutsceneBslExplodingBgGfx, VRAM_BASE);
    LZ77UncompVram(sCutsceneBslExplodingTileTable0, VRAM_BASE + 0xE000);
    LZ77UncompVram(sCutsceneBslExplodingTileTable1, VRAM_BASE + 0xE800);
    LZ77UncompVram(sCutsceneBslExplodingTileTable2, VRAM_BASE + 0xF000);
    LZ77UncompVram(sCutsceneBslExplodingTileTable3, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sCutsceneBslExplodingBgPal, PALRAM_BASE, 0x200 / sizeof(u32));
    SET_BACKDROP_COLOR(COLOR_BLACK);

    WRITE_16(REG_BG0CNT, 0x1C00);
    WRITE_16(REG_BG1CNT, 0x1D03);
    WRITE_16(REG_BG2CNT, 0x1E00);
    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_DISPCNT, 0x1800);

    gWrittenToBldy = 16;
    gWrittenToBldalpha_Eva = 8;
    gWrittenToBldalpha_Evb = 16;

    CutsceneBslExplodingSetupOam(1, 0, 0, FALSE);
    CutsceneBslExplodingSetupOam(0x14, 0x70, 0x58, FALSE);

    CUTSCENE_DATA.unk_A = 0;
    CUTSCENE_DATA.unk_C = 0;
    DMA3_COPY_32(&sCutsceneBslExplodingFlashPal[CUTSCENE_DATA.unk_C * 16], PALRAM_BASE + 0x120, 16 * sizeof(u16) / sizeof(u32));

    CutsceneDrawAllOam();
    CallbackSetVBlank(FUNC_PTR(CutsceneBslExplodingVblank));
}

/**
 * @brief 9c3e4 | 214 | Processes the BSL exploding cutscene
 *
 * @return boolu8 bool, ended
 */
boolu8 CutsceneBslExplodingProcess(void)
{
    boolu8 ended;

    ended = FALSE;
    CUTSCENE_DATA.timer++;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer = 0;
            CUTSCENE_DATA.subStage = 1;
            break;

        case 1:
            if (CUTSCENE_DATA.timer == 15)
            {
                WRITE_16(REG_BLDCNT, 0x1C44);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | 0x400);
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 2;
            }
            break;

        case 2:
            if (gWrittenToBldalpha_Eva < 16)
            {
                if (CUTSCENE_DATA.timer == 1)
                {
                    CUTSCENE_DATA.timer = 0;
                    gWrittenToBldalpha_Eva += 2;
                }
                gWrittenToBldy = 16;
            }
            else if (CUTSCENE_DATA.timer == 40)
            {
                WRITE_16(REG_BLDCNT, 0xFF);
                WRITE_16(REG_DISPCNT, 0x1200);
                CutsceneDestroyOamOfType(1);
                CutsceneDestroyOamOfType(0x14);
                CutsceneBslExplodingSetupOam(0x15, 0x78, 0x5A, TRUE);
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 3;
            }
            break;

        case 3:
            if (CUTSCENE_DATA.timer == 1)
            {
                gWrittenToBldy = 0;
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 4;
            }
            break;

        case 4:
            if (CUTSCENE_DATA.timer == 60)
            {
                WRITE_16(REG_BLDCNT, 0x1E41);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | 0x100);
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 5;
            }
            break;

        case 5:
            if (CUTSCENE_DATA.unk_C < 15)
            {
                if (CUTSCENE_DATA.timer == 4)
                {
                    CUTSCENE_DATA.timer = 0;
                    CUTSCENE_DATA.unk_A = TRUE;
                    CUTSCENE_DATA.unk_C++;

                    if (CUTSCENE_DATA.unk_C == 1)
                    {
                        CutsceneBslExplodingSetupOam(0x16, 0x78, 0x60, FALSE);
                        CutsceneBslExplodingSetupOam(0x16, 0x5F, 0x50, FALSE);
                        CutsceneBslExplodingSetupOam(0x16, 0x8C, 0x69, FALSE);
                    }
                    else if (CUTSCENE_DATA.unk_C == 2)
                    {
                        CutsceneBslExplodingSetupOam(0x16, 0x78, 0x54, FALSE);
                        CutsceneBslExplodingSetupOam(0x16, 0x91, 0x55, FALSE);
                    }
                    else if (CUTSCENE_DATA.unk_C == 3)
                    {
                        CutsceneBslExplodingSetupOam(0x16, 0x60, 0x6A, FALSE);
                    }
                }
            }
            else if (CUTSCENE_DATA.timer == 15)
            {
                CUTSCENE_DATA.timer = 0;
                gWrittenToBldy = 16;
                CUTSCENE_DATA.subStage = 6;
            }
            break;

        case 6:
            if (gWrittenToBldalpha_Eva < 16)
            {
                if (CUTSCENE_DATA.timer == 6)
                {
                    CUTSCENE_DATA.timer = 0;
                    gWrittenToBldalpha_Eva++;
                }
            }
            else
            {
                WRITE_16(REG_BLDCNT, 0xBF);
                if (CUTSCENE_DATA.timer == 16)
                {
                    CUTSCENE_DATA.timer = 0;
                    ended = TRUE;
                }
            }
            break;
    }

    CutsceneProcessOam();
    CutsceneDrawAllOam();

    return ended;
}

/**
 * @brief 9c5f8 | 2c | Scrolls BG3 horizontally (BSL exploding)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneBslExplodingProcessScrolling(struct CutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 30)
    {
        pOam->timer = 0;
        pOam->xPosition--;
    }

    WRITE_16(REG_BG3HOFS, pOam->xPosition);
}

/**
 * @brief 9c624 | 5c | Processes the BSL (far) oam
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneBslExplodingProcessBslFar(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (CUTSCENE_DATA.subStage == 5 && CUTSCENE_DATA.unk_C == 5)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sCutsceneBslExplodingExplosionOam;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (pOam->pOam[pOam->currentAnimationFrame].timer == pOam->animationDurationCounter &&
            pOam->pOam[pOam->currentAnimationFrame + 1].timer == 0)
        {
            pOam->type = 0;
            pOam->exists = FALSE;
        }
    }
}

/**
 * @brief 9c680 | 2c | Processes an explosion oam
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneBslExplodingProcessExplosions(struct CutsceneOam* pOam)
{
    if (pOam->pOam[pOam->currentAnimationFrame].timer == pOam->animationDurationCounter &&
        pOam->pOam[pOam->currentAnimationFrame + 1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9c6ac | 1a4 | Sets up a BSL exploding oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param fromEnd Search a free slot starting from the end
 * @return u8 Slot (16 if none)
 */
u8 CutsceneBslExplodingSetupOam(u8 type, u16 xPosition, u16 yPosition, boolu8 fromEnd)
{
    s8 i;
    struct CutsceneOam* pOam;

    if (!fromEnd)
    {
        for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
        {
            if (CUTSCENE_DATA.oam[i].type == 0)
                break;
        }

        if (i >= CUTSCENE_OAM_COUNT)
            return CUTSCENE_OAM_COUNT;
    }
    else
    {
        for (i = CUTSCENE_OAM_COUNT - 1; i >= 0; i--)
        {
            if (CUTSCENE_DATA.oam[i].type == 0)
                break;
        }

        if (i < 0)
            return CUTSCENE_OAM_COUNT;
    }

    pOam = &CUTSCENE_DATA.oam[i];
    DMA3_FILL_32(0, pOam, sizeof(struct CutsceneOam));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->exists = TRUE;

    if (type == 1)
    {
        pOam->exists = FALSE;
        pOam->pFunction = FUNC_PTR(CutsceneBslExplodingProcessScrolling);
    }
    else if (type == 0x14)
    {
        pOam->priority = 2;
        pOam->pOam = sCutsceneBslExplodingBslNearOam;
        pOam->pFunction = FUNC_PTR(unk_9db70);
    }
    else if (type == 0x15)
    {
        pOam->priority = 2;
        pOam->pOam = sCutsceneBslExplodingBslFarOam;
        pOam->pFunction = FUNC_PTR(CutsceneBslExplodingProcessBslFar);
    }
    else if (type == 0x16)
    {
        pOam->priority = 2;
        pOam->pOam = sCutsceneBslExplodingExplosionOam;
        pOam->pFunction = FUNC_PTR(CutsceneBslExplodingProcessExplosions);
    }

    return i;
}

/**
 * @brief 9c850 | 58 | Gets the position, scaling and slot of the first oam of a type
 *
 * @param type Type
 * @param pXPosition X position pointer
 * @param pYPosition Y position pointer
 * @param pScaling Scaling pointer
 * @return u8 Slot (0 if not found)
 */
u8 CutsceneBslExplodingGetOamInfoByType(u8 type, s16* pXPosition, s16* pYPosition, s16* pScaling)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            *pXPosition = CUTSCENE_DATA.oam[i].xPosition;
            *pYPosition = CUTSCENE_DATA.oam[i].yPosition;
            *pScaling = CUTSCENE_DATA.oam[i].scaling;
            return i;
        }
    }

    *pXPosition = 300;
    *pYPosition = 200;
    *pScaling = Q_8_8(1.f);
    return 0;
}

/**
 * @brief 9c8a8 | 84 | V-blank code for the BSL exploding cutscene
 *
 */
void CutsceneBslExplodingVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (CUTSCENE_DATA.unk_A == TRUE)
    {
        CUTSCENE_DATA.unk_A = FALSE;
        DMA3_COPY_32(&sCutsceneBslExplodingFlashPal[CUTSCENE_DATA.unk_C * 16], PALRAM_BASE + 0x120, 16 * sizeof(u16) / sizeof(u32));
    }
}

/**
 * @brief 9c92c | c | Updates the audio
 *
 */
void unk_9c92c(void)
{
    UpdateAudio();
}

/**
 * @brief 9c938 | c0 | Processes the monologue text cursor
 *
 * @param pOam Cutscene monologue oam pointer
 */
void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam)
{
    u16 character;

    character = *MONOLOGUE_DATA.pText;

    if (character == 0xFF00)
    {
        pOam->process = FALSE;
        pOam->draw = FALSE;
        return;
    }

    if (character == 0xFC00)
    {
        if (pOam->stage == 0)
        {
            if (gChangedInput & KEY_A)
            {
                pOam->xPosition = 0x122;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
            }
            else
            {
                pOam->pOam = sCutsceneMonologueCursorOam_Idle;
                pOam->xPosition = 0x76;
                pOam->yPosition = MONOLOGUE_DATA.line * 8 + 24;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 1;
            }
            return;
        }

        if (pOam->stage != 1)
            return;

        if (!(gChangedInput & KEY_A))
            return;

        character = 0xFD00;
    }

    if (character == 0xFD00)
    {
        pOam->pOam = sCutsceneMonologueCursorOam_Moving;
        pOam->xPosition = 0x122;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->stage = 0;
        return;
    }

    pOam->xPosition = MONOLOGUE_DATA.column * 8 + (MONOLOGUE_DATA.indent + 12);
    pOam->yPosition = MONOLOGUE_DATA.line * 8 + 12;
}

/**
 * @brief 9c9f8 | a4 | Processes the special text characters (waits) of a monologue
 *
 * @return boolu8 bool, text ended
 */
boolu8 CutsceneMonologueProcessSpecialTextCharacters(void)
{
    boolu8 ended;
    u16 character;

    ended = FALSE;

    if (gButtonInput & KEY_A)
        MONOLOGUE_DATA.timer += 2;
    else
        MONOLOGUE_DATA.timer++;

    character = *MONOLOGUE_DATA.pText;

    if (character == 0xFF00)
    {
        MONOLOGUE_DATA.timer = 0;
        MONOLOGUE_DATA.unk_17 = 100;
        ended = TRUE;
    }
    else if (character == 0xFC00)
    {
        if (gChangedInput & KEY_A)
            MONOLOGUE_DATA.unk_17 = 1;
        MONOLOGUE_DATA.timer = 0;
    }
    else if ((character & 0xFF00) == 0xE100)
    {
        if ((character & 0xFF) <= MONOLOGUE_DATA.timer)
        {
            MONOLOGUE_DATA.unk_17 = 1;
            MONOLOGUE_DATA.timer = 0;
        }
    }
    else if (MONOLOGUE_DATA.timer > 2)
    {
        MONOLOGUE_DATA.unk_17 = 1;
        MONOLOGUE_DATA.timer = 0;
    }

    return ended;
}

/**
 * @brief 9ca9c | 1b0 | Processes (draws) the next monologue text character
 *
 */
void CutsceneMonologueProcessText(void)
{
    u16 character;
    u16 i;
    u32* dst;
    u32 width;

    character = *MONOLOGUE_DATA.pText;

    if (character == 0xFF00)
        return;

    if (character == 0xFE00)
    {
        // New line, mark the rest of the line as done
        // PORT: the row index (line / 2) isn't bounds checked, same flat indexing as the original
        for (i = MONOLOGUE_DATA.column + 1; i < CUTSCENE_MONOLOGUE_TEXT_COLUMNS; i++)
            MONOLOGUE_DATA.unk_1C[MONOLOGUE_DATA.line / 2][i] |= 0xFF;

        MONOLOGUE_DATA.column = 0;
        MONOLOGUE_DATA.line += 2;
        MONOLOGUE_DATA.pText++;
        MONOLOGUE_DATA.indent = 0;
        return;
    }

    if (character == 0xFD00)
    {
        // New page
        DMA3_FILL_32(0, VRAM_BASE + 0x8000, 0x4800);
        MONOLOGUE_DATA.unk_6 = 0;
        MONOLOGUE_DATA.unk_4 = 0;
        MONOLOGUE_DATA.line = 0;
        MONOLOGUE_DATA.column = 0;
        MONOLOGUE_DATA.pText++;
        MONOLOGUE_DATA.indent = 0;
        DMA3_FILL_32(0, MONOLOGUE_DATA.unk_1C, sizeof(MONOLOGUE_DATA.unk_1C));
        DMA3_FILL_32(0, MONOLOGUE_DATA.unk_118, sizeof(MONOLOGUE_DATA.unk_118));
        DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / sizeof(u32));
        return;
    }

    if (character == 0xFC00 || (character & 0xFF00) == 0xE100)
    {
        MONOLOGUE_DATA.pText++;
        return;
    }

    dst = (u32*)(VRAM_BASE + 0x8000 + MONOLOGUE_DATA.column * 32 + MONOLOGUE_DATA.line * 0x400);
    width = TextGetCharacterWidth(character);
    TextDrawCharacter(*MONOLOGUE_DATA.pText, dst, width, MONOLOGUE_DATA.indent, 0);

    if (MONOLOGUE_DATA.column < CUTSCENE_MONOLOGUE_TEXT_COLUMNS)
    {
        MONOLOGUE_DATA.unk_1C[MONOLOGUE_DATA.line / 2][MONOLOGUE_DATA.column] = 4;
        MONOLOGUE_DATA.indent += width;

        while (MONOLOGUE_DATA.indent >= 8)
        {
            MONOLOGUE_DATA.indent -= 8;
            MONOLOGUE_DATA.column++;
            if (MONOLOGUE_DATA.column >= CUTSCENE_MONOLOGUE_TEXT_COLUMNS)
                break;

            if (MONOLOGUE_DATA.indent != 0)
                MONOLOGUE_DATA.unk_1C[MONOLOGUE_DATA.line / 2][MONOLOGUE_DATA.column] = 4;
        }
    }

    MONOLOGUE_DATA.pText++;
}

/**
 * @brief 9cc4c | 134 | Updates the monologue text reveal effect (tile palettes)
 *
 */
void unk_9cc4c(void)
{
    u16 column;
    u16 row;
    u16 end;
    u8* pTimer;
    u8* pCounter;
    s8 counter;
    vu16* pTop;
    vu16* pBottom;
    u16 top;
    u16 bottom;

    column = MONOLOGUE_DATA.unk_4;
    row = MONOLOGUE_DATA.unk_6 / 2;

    for (; row <= MONOLOGUE_DATA.line / 2; row++, column = 0)
    {
        if (*MONOLOGUE_DATA.pText == 0xFC00)
        {
            if (MONOLOGUE_DATA.column < CUTSCENE_MONOLOGUE_TEXT_COLUMNS)
                end = MONOLOGUE_DATA.column + 1;
            else
                end = CUTSCENE_MONOLOGUE_TEXT_COLUMNS;
        }
        else if (row == MONOLOGUE_DATA.line / 2)
        {
            end = CUTSCENE_MONOLOGUE_TEXT_COLUMNS;
            if (MONOLOGUE_DATA.column < CUTSCENE_MONOLOGUE_TEXT_COLUMNS)
                end = MONOLOGUE_DATA.column;
        }
        else
        {
            end = CUTSCENE_MONOLOGUE_TEXT_COLUMNS;
        }

        for (; column < end; column++)
        {
            // PORT: row isn't bounds checked, same flat indexing as the original
            pTimer = &MONOLOGUE_DATA.unk_118[row][column];
            if (*pTimer != 5)
            {
                (*pTimer)++;
                continue;
            }

            *pTimer = 0;
            pCounter = &MONOLOGUE_DATA.unk_1C[row][column];
            counter = *pCounter - 1;
            *pCounter = counter;

            if (counter > 0)
            {
                pTop = (vu16*)(VRAM_BASE + 0xC842 + column * 2 + row * 128);
                pBottom = (vu16*)(VRAM_BASE + 0xC882 + column * 2 + row * 128);
                top = *pTop;
                bottom = *pBottom;
                *pTop = (((top >> 12) - 1) << 12) | (top & 0xFFF);
                *pBottom = (((bottom >> 12) - 1) << 12) | (bottom & 0xFFF);
            }
            else if (counter == 0)
            {
                MONOLOGUE_DATA.unk_6 = row * 2;
                MONOLOGUE_DATA.unk_4 = column;
            }
            else
            {
                *pCounter = counter | 0xFF;
                break;
            }
        }
    }
}

/**
 * @brief 9cd80 | 58 | Monologue fade in (slows down near the end)
 *
 */
void CutsceneMonologueFadeIn(void)
{
    u16 bldy;

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    bldy = gWrittenToBldy;
    if (bldy == 0)
        return;

    if (bldy > 11)
    {
        MONOLOGUE_DATA.unk_16++;
        if (MONOLOGUE_DATA.unk_16 != 3)
            return;
        MONOLOGUE_DATA.unk_16 = 0;
    }
    else if (bldy > 6)
    {
        MONOLOGUE_DATA.unk_16++;
        if (MONOLOGUE_DATA.unk_16 != 2)
            return;
        MONOLOGUE_DATA.unk_16 = 0;
    }

    gWrittenToBldy = bldy - 1;
}

/**
 * @brief 9cdd8 | 58 | Monologue fade out (slow at the start)
 *
 */
void CutsceneMonologueFadeOut(void)
{
    u16 bldy;

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    bldy = gWrittenToBldy;
    if (bldy >= 16)
        return;

    if (bldy <= 5)
    {
        MONOLOGUE_DATA.unk_16++;
        if (MONOLOGUE_DATA.unk_16 != 3)
            return;
        MONOLOGUE_DATA.unk_16 = 0;
    }
    else if (bldy <= 10)
    {
        MONOLOGUE_DATA.unk_16++;
        if (MONOLOGUE_DATA.unk_16 != 2)
            return;
        MONOLOGUE_DATA.unk_16 = 0;
    }

    gWrittenToBldy = bldy + 1;
}

/**
 * @brief 9ce30 | 44 | Processes the monologue oam
 *
 */
void CutsceneMonologueProcessOam(void)
{
    u8 i;

    for (i = 0; i < CUTSCENE_MONOLOGUE_OAM_COUNT; i++)
    {
        if (MONOLOGUE_DATA.oam[i].process)
            MONOLOGUE_DATA.oam[i].pFunction(&MONOLOGUE_DATA.oam[i]);
    }
}

/**
 * @brief 9ce74 | 4c | Draws the monologue oam
 *
 */
void CutsceneMonologueDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < CUTSCENE_MONOLOGUE_OAM_COUNT; i++)
    {
        if (MONOLOGUE_DATA.oam[i].draw)
            CutsceneMnologueDrawOam(&MONOLOGUE_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief 9cec0 | 188 | Draws a monologue oam
 *
 * @param pOam Cutscene monologue oam pointer
 */
void CutsceneMnologueDrawOam(struct CutsceneMonologueOam* pOam)
{
    u16* dst;
    const struct FrameData* pFrame;
    const u16* src;
    s32 partCount;
    s32 i;
    u16 part1;
    u16 part2;
    u32 slot;
    u16 x;
    u16 y;
    u8 offset;

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
        part1 = *src++;
        part2 = *src++;
        *dst++ = part1;
        *dst++ = part2;
        *dst++ = *src++;

        slot = gNextOamSlot + i;

        if (pOam->xFlip == TRUE)
        {
            gOamData[slot].split.xFlip ^= TRUE;
            offset = sCutsceneMonologueOamXFlipOffsets[gOamData[slot].split.shape * 4 + gOamData[slot].split.size];
            x = MOD_AND(pOam->xPosition - (part2 + offset * 8), 512);
            y = MOD_AND(part1 + pOam->yPosition, 256);
        }
        else
        {
            y = MOD_AND(part1 + pOam->yPosition, 256);
            x = MOD_AND(part2 + pOam->xPosition, 512);
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
 * @brief 9d048 | 54 | Resets a monologue oam
 *
 * @param slot Oam slot
 */
void CutsceneMonologueResetOam(u8 slot)
{
    MONOLOGUE_DATA.oam[slot].currentAnimationFrame = 0;
    MONOLOGUE_DATA.oam[slot].animationDurationCounter = 0;
    MONOLOGUE_DATA.oam[slot].stage = 0;
    MONOLOGUE_DATA.oam[slot].objMode = 0;
    MONOLOGUE_DATA.oam[slot].priority = 0;
    MONOLOGUE_DATA.oam[slot].xFlip = 0;
    MONOLOGUE_DATA.oam[slot].paletteOffset = 0;
    MONOLOGUE_DATA.oam[slot].tileOffset = 0;
}

/**
 * @brief 9d09c | 4 | Empty monologue oam process
 *
 * @param pOam Cutscene monologue oam pointer
 */
void unk_9d09c(struct CutsceneMonologueOam* pOam)
{
    return;
}

/**
 * @brief 9d0a0 | 124 | Computes the circular window values (WIN0H per scanline)
 *
 */
void unk_9d0a0(void)
{
    u16* dst;
    const s16* src;
    s16 i;
    s16 top;
    s16 bottom;
    u16 subSlice;
    u16 right;
    u16 left;

    DMA3_COPY_32(EWRAM_BASE + 0x1000, EWRAM_BASE + 0x2000, 0x150 / sizeof(u32));

    top = CUTSCENE_DATA.unk_E - CUTSCENE_DATA.unk_A;
    bottom = CUTSCENE_DATA.unk_E + CUTSCENE_DATA.unk_A;

    if (top < 0)
    {
        subSlice = -top;
        top = 0;
        if (subSlice > CUTSCENE_DATA.unk_A * 2)
            top = SCREEN_SIZE_Y + 1;
    }
    else
    {
        subSlice = 0;
    }

    if (bottom >= SCREEN_SIZE_Y)
        bottom = SCREEN_SIZE_Y;

    src = sHaze_PowerBomb_WindowValuesPointers[CUTSCENE_DATA.unk_A];
    dst = (u16*)(EWRAM_BASE + 0x1000);

    for (i = 0; i < top; i++)
        *dst++ = 0;

    for (; i <= bottom; i++, subSlice++)
    {
        right = (u16)CUTSCENE_DATA.unk_C + (u16)src[subSlice * 2 + 0];
        left = (u16)CUTSCENE_DATA.unk_C + (u16)src[subSlice * 2 + 1];

        if ((s16)left < 0)
            left = 0;

        if ((s16)right > SCREEN_SIZE_X)
            right = SCREEN_SIZE_X;

        *dst++ = (s16)right | (left << 8);
    }

    for (; i < SCREEN_SIZE_Y; i++)
        *dst++ = 0;
}

/**
 * @brief 9d1c4 | 20 | H-blank code, applies the window values of the current scanline
 *
 */
void unk_9d1c4(void)
{
    WRITE_16(REG_WIN0H, ((u16*)(EWRAM_BASE + 0x2000))[(s16)READ_16(REG_VCOUNT)]);
}

/**
 * @brief 9d1e4 | 44 | Destroys the first cutscene oam of a type
 *
 * @param type Type
 */
void CutsceneMonologueDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            CUTSCENE_DATA.oam[i].type = 0;
            CUTSCENE_DATA.oam[i].exists = FALSE;
            break;
        }
    }
}

/**
 * @brief 9d228 | 20 | Cutscene fade in
 *
 */
void CutsceneFadeIn(void)
{
    CutsceneProcessOam();
    CutsceneDrawAllOam();

    if (gWrittenToBldy != 0)
        gWrittenToBldy--;
}

/**
 * @brief 9d248 | 20 | Cutscene fade out
 *
 */
void CutsceneFadeOut(void)
{
    CutsceneProcessOam();
    CutsceneDrawAllOam();

    if (gWrittenToBldy < 16)
        gWrittenToBldy++;
}

/**
 * @brief 9d268 | 44 | Destroys the first cutscene oam of a type
 *
 * @param type Type
 */
void CutsceneDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == type)
        {
            CUTSCENE_DATA.oam[i].type = 0;
            CUTSCENE_DATA.oam[i].exists = FALSE;
            break;
        }
    }
}

/**
 * @brief 9d2ac | 48 | Processes the cutscene oam
 *
 */
void CutsceneProcessOam(void)
{
    u8 i;

    CUTSCENE_DATA.oamCount = 0;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type != 0)
        {
            CUTSCENE_DATA.oam[i].pFunction(&CUTSCENE_DATA.oam[i]);
            CUTSCENE_DATA.oamCount++;
        }
    }
}

/**
 * @brief 9d2f4 | 4c | Draws the cutscene oam
 *
 */
void CutsceneDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].exists)
            CutsceneDrawOam(&CUTSCENE_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
    gUnk_3001238 = 0;
}

/**
 * @brief 9d340 | 830 | Draws a cutscene oam (normal, or rotated/scaled)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneDrawOam(struct CutsceneOam* pOam)
{
    u16* dst;
    const struct FrameData* pFrame;
    const u16* src;
    u16 partCount;
    s32 i;
    u16 part1;
    u16 part2;
    union OamData* pData;
    u32 slot;
    u8 shapeSize;
    u8 mode;
    u16 x;
    u16 y;
    u16 xPosition;
    u16 yPosition;
    u16 scaleX;
    u16 scaleY;
    s16 sx;
    s16 sy;
    s32 xOffset;
    s32 yOffset;
    s16 tmpX;
    s16 tmpY;
    u16 dx;
    u16 dy;
    s16 cos;
    s16 sin;
    s32 rx;
    s32 ry;
    u8 flags;
    u8 matrix;

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

    mode = pOam->affineMode;

    if (mode == 0)
    {
        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            part2 = *src++;
            *dst++ = part1;
            *dst++ = part2;
            *dst++ = *src++;

            slot = gNextOamSlot + i;

            if (pOam->xFlip == TRUE)
            {
                gOamData[slot].split.xFlip ^= TRUE;
                shapeSize = gOamData[slot].split.shape * 4 + gOamData[slot].split.size;
                x = MOD_AND(pOam->xPosition - (part2 + sCutsceneOamXFlipOffsets[shapeSize] * 8), 512);
                y = MOD_AND(part1 + pOam->yPosition, 256);
            }
            else
            {
                y = MOD_AND(part1 + pOam->yPosition, 256);
                x = MOD_AND(part2 + pOam->xPosition, 512);
            }

            gOamData[slot].split.y = y;
            gOamData[slot].split.x = x;
            gOamData[slot].split.priority = pOam->priority;
            gOamData[slot].split.paletteNum += pOam->paletteOffset;
            gOamData[slot].split.tileNum += C_16_2_8(pOam->tileOffsetHigh, pOam->tileOffsetLow);
            gOamData[slot].split.objMode = pOam->objMode;

            dst++;
        }
    }
    else if (mode == OAM_AFFINE_MODE_AFFINE || mode == OAM_AFFINE_MODE_DOUBLE_SIZED)
    {
        xPosition = pOam->xPosition + 0x40;
        yPosition = pOam->yPosition + 0x40;

        if (pOam->xFlip)
            scaleX = -pOam->scaling;
        else
            scaleX = pOam->scaling;

        if (pOam->yFlip)
            scaleY = -pOam->scaling;
        else
            scaleY = pOam->scaling;

        for (i = 0; i < partCount; i++)
        {
            part1 = *src++;
            part2 = *src++;
            *dst++ = part1;
            *dst++ = part2;
            *dst++ = *src++;

            slot = gNextOamSlot + i;
            pData = &gOamData[slot];

            flags = ((u8*)pData)[3];
            shapeSize = pData->split.shape * 4 + pData->split.size;
            // Half size of the object, in pixels
            xOffset = sCutsceneOamXFlipOffsets[shapeSize] * 4;
            yOffset = sCutsceneOamYFlipOffsets[shapeSize] * 4;

            y = MOD_AND(part1 + yPosition, 256);
            x = MOD_AND(part2 + xPosition, 512);

            // Apply scaling
            tmpX = xOffset + (x - xPosition);
            tmpY = yOffset + (y - yPosition);
            sx = scaleX;
            dx = ((tmpX * sx) >> 8) - tmpX;
            sy = scaleY;
            dy = ((tmpY * sy) >> 8) - tmpY;

            // Flips are done by negating the scaling (for the next parts and the matrix)
            if (flags & 0x10)
            {
                ((u8*)pData)[3] = flags & ~0x10;
                scaleX = -sx;
            }

            if (pData->split.yFlip)
            {
                pData->split.yFlip = FALSE;
                scaleY = -sy;
            }

            x = (s16)x + (s16)dx;
            y = (s16)y + (s16)dy;

            // Apply rotation
            tmpX = (x - xPosition) + xOffset;
            tmpY = (y - yPosition) + yOffset;

            cos = COS(pOam->rotation);
            sin = SIN(pOam->rotation);

            rx = (s32)((u32)(tmpX * cos - tmpY * sin) << 8);
            ry = (s32)((u32)(tmpX * sin + tmpY * cos) << 8);

            if (mode == OAM_AFFINE_MODE_AFFINE)
            {
                rx = (rx >> 16) - xOffset;
                ry = (ry >> 16) - yOffset;
            }
            else
            {
                rx = (rx >> 16) - xOffset * 2;
                ry = (ry >> 16) - yOffset * 2;
            }

            pData->split.y = (u8)((u16)ry + yPosition - 0x40);
            pData->split.x = MOD_AND((s16)rx + xPosition - 0x40, 512);
            pData->split.affineMode = mode;

            if (gUnk_3001238 & 0x10)
                pData->split.yFlip = TRUE;
            if (gUnk_3001238 & 8)
                pData->split.xFlip = TRUE;
            pData->split.matrixNum = gUnk_3001238 & 7;

            pData->split.priority = pOam->priority;
            pData->split.paletteNum += pOam->paletteOffset;
            pData->split.tileNum += C_16_2_8(pOam->tileOffsetHigh, pOam->tileOffsetLow);
            pData->split.objMode = pOam->objMode;

            dst++;
        }

        // Affine matrix
        // PORT: the matrix index isn't bounds checked (gUnk_3001238 >= 40 writes past gOamData)
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
 * @brief 9db70 | 4 | Empty cutscene oam process
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9db70(struct CutsceneOam* pOam)
{
    return;
}
