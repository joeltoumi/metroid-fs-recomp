#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "callbacks.h"
#include "syscall_wrappers.h"
#include "syscalls.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"
#include "oam.h"

#include "data/new_file_intro_data.h"
#include "data/sprite_data.h"

#include "cutscenes_2.h"
#include "cutscenes_1.h"

void UpdateAudio(void);

// PORT: the following tables are typed copies of the pointer tables stored in
// sBlob_79c448_79c5a4 (0x879c4a8..0x879c5a4), so they can be used on 64-bit.
// They are indexed by gCurrentCutscene - 1 (9 entries, cutscenes 1..9).

// 0x879c4a8
static const u16* const sMonologueBgPalPointers[9] = {
    (const u16*)(sBlob_6638a0_682fac + 0x20),
    (const u16*)(sBlob_6638a0_682fac + 0x71c8),
    (const u16*)(sBlob_6638a0_682fac + 0x20),
    (const u16*)(sBlob_6638a0_682fac + 0x20),
    (const u16*)(sBlob_6638a0_682fac + 0x71c8),
    (const u16*)(sBlob_6638a0_682fac + 0xe164),
    (const u16*)(sBlob_6638a0_682fac + 0x20),
    (const u16*)(sBlob_6638a0_682fac + 0x20),
    (const u16*)(sBlob_6638a0_682fac + 0x20)
};

// 0x879c4cc
static const u16* const sMonologueObjPalPointers[9] = {
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x7328),
    (const u16*)(sBlob_6638a0_682fac + 0xe2c4),
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x180),
    (const u16*)(sBlob_6638a0_682fac + 0x180)
};

// 0x879c4f0
static const u8* const sMonologueBgGfxPointers[9] = {
    sBlob_64e470_662804 + 0xdff8,
    sBlob_6638a0_682fac + 0x60c,
    sBlob_64e470_662804 + 0xdff8,
    sBlob_64e470_662804 + 0xdff8,
    sBlob_6638a0_682fac + 0x60c,
    sBlob_6638a0_682fac + 0x7c84,
    sBlob_64e470_662804 + 0xdff8,
    sBlob_64e470_662804 + 0xdff8,
    sBlob_64e470_662804 + 0xdff8
};

// 0x879c514
static const u8* const sMonologueObjGfxPointers[9] = {
    sBlob_64e470_662804 + 0x117b4,
    sBlob_64e470_662804 + 0x117b4,
    sBlob_64e470_662804 + 0x117b4,
    sBlob_64e470_662804 + 0x117b4,
    sBlob_6638a0_682fac + 0x4378,
    sBlob_6638a0_682fac + 0xb378,
    sBlob_64e470_662804 + 0x117b4,
    sBlob_64e470_662804 + 0x117b4,
    sBlob_64e470_662804 + 0x117b4
};

// 0x879c538
static const u8* const sMonologueTilemapPointers[9] = {
    sBlob_662cfc_663820 + 0x0,
    sBlob_6638a0_682fac + 0x73e8,
    sBlob_662cfc_663820 + 0x0,
    sBlob_662cfc_663820 + 0x0,
    sBlob_6638a0_682fac + 0x73e8,
    sBlob_6638a0_682fac + 0xe384,
    sBlob_662cfc_663820 + 0x0,
    sBlob_662cfc_663820 + 0x0,
    sBlob_662cfc_663820 + 0x0
};

// 0x879c55c
// PORT: these point to frame data inside a byte blob (4-byte pointers on GBA)
static const struct FrameData* const sMonologueOamPointers[9][2] = {
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x7190), (const struct FrameData*)(sBlob_6638a0_682fac + 0x71b8) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0xe12c), (const struct FrameData*)(sBlob_6638a0_682fac + 0xe154) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) },
    { (const struct FrameData*)(sBlob_6638a0_682fac + 0x530), (const struct FrameData*)(sBlob_6638a0_682fac + 0x558) }
};

// Data inside the blobs, named by their ROM address
#define sMonologueTextGfx_65fb5c (sBlob_64e470_662804 + 0x116ec)
#define sMonologueTextTilemap_663598 (sBlob_662cfc_663820 + 0x89c)
#define sMonologueTextPal_6636a0 ((const u16*)(sBlob_662cfc_663820 + 0x9a4))
#define sMonologueCursorPal_6638a0 ((const u16*)(sBlob_6638a0_682fac + 0x0))
#define sMonologueCursorOam_663e5c ((const struct FrameData*)(sBlob_6638a0_682fac + 0x5bc))
#define sFederationBgGfx_6724c0 (sBlob_6638a0_682fac + 0xec20)
#define sFederationBgPal_674958 ((const u16*)(sBlob_6638a0_682fac + 0x110b8))
#define sFederationTilemap_674ad8 (sBlob_6638a0_682fac + 0x11238)
#define sSecretConversationBgGfx_675098 (sBlob_6638a0_682fac + 0x117f8)
#define sSecretConversationBgPal_677874 ((const u16*)(sBlob_6638a0_682fac + 0x13fd4))
#define sSecretConversationTilemap_677914 (sBlob_6638a0_682fac + 0x14074)
#define sSecretConversationObjPal_677c10 ((const u16*)(sBlob_6638a0_682fac + 0x14370))
#define sSecretConversationObjPal_677c30 ((const u16*)(sBlob_6638a0_682fac + 0x14390))
#define sSecretConversationObjPal_677c50 ((const u16*)(sBlob_6638a0_682fac + 0x143b0))
#define sSecretConversationObjPal_677c70 ((const u16*)(sBlob_6638a0_682fac + 0x143d0))
#define sSecretConversationTilemap_677c90 (sBlob_6638a0_682fac + 0x143f0)
#define sSecretConversationObjGfx_67815c (sBlob_6638a0_682fac + 0x148bc)
#define sSecretConversationObjPal_6788a8 ((const u16*)(sBlob_6638a0_682fac + 0x15008))
#define sSecretConversationOam_679280 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x159e0))
#define sSecretConversationOam_6792a8 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x15a08))
#define sSecretConversationOam_6792d0 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x15a30))
#define sSecretConversationOam_679350 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x15ab0))
#define sSecretConversationOam_6793a0 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x15b00))
#define sSecretConversationOam_6793b0 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x15b10))
#define sRestrictedLabBgGfx_679420 (sBlob_6638a0_682fac + 0x15b80)
#define sRestrictedLabObjGfx_67d7cc (sBlob_6638a0_682fac + 0x19f2c)
#define sRestrictedLabOam_680d54 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d4b4))
#define sRestrictedLabOam_680d64 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d4c4))
#define sRestrictedLabOam_680d74 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d4d4))
#define sRestrictedLabOam_680d84 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d4e4))
#define sRestrictedLabOam_680d94 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d4f4))
#define sRestrictedLabOam_680da4 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d504))
#define sRestrictedLabOam_680dcc ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d52c))
#define sRestrictedLabOam_680e2c ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d58c))
#define sRestrictedLabOam_680e3c ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d59c))
#define sRestrictedLabOam_680f2c ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d68c))
#define sRestrictedLabOam_680f74 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d6d4))
#define sRestrictedLabOam_680f9c ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d6fc))
#define sRestrictedLabOam_680fc4 ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d724))
#define sRestrictedLabOam_680fec ((const struct FrameData*)(sBlob_6638a0_682fac + 0x1d74c))
#define sRestrictedLabFadingPal_68101c ((const u16*)(sBlob_6638a0_682fac + 0x1d77c)) // 16 rows
#define sRestrictedLabObjPal_68121c ((const u16*)(sBlob_6638a0_682fac + 0x1d97c))
#define sRestrictedLabCyclingPal_68141c ((const u16*)(sBlob_6638a0_682fac + 0x1db7c)) // 4 rows
#define sRestrictedLabCyclingPal_68161c ((const u16*)(sBlob_6638a0_682fac + 0x1dd7c)) // 4 rows
#define sRestrictedLabCyclingPal_68181c ((const u16*)(sBlob_6638a0_682fac + 0x1df7c)) // 4 rows
#define sRestrictedLabTilemap_681a1c (sBlob_6638a0_682fac + 0x1e17c)
#define sRestrictedLabTilemap_6820a4 (sBlob_6638a0_682fac + 0x1e804)
#define sRestrictedLabBgPal_68259c ((const u16*)(sBlob_6638a0_682fac + 0x1ecfc))

#ifdef CUTSCENES_1_EQUIV
// Equivalence testing only: store the original ROM addresses of the callbacks so that
// the RAM written by the C version is identical to the original
void unk_9a31c_Orig(void);
void CutsceneElevatorMonologueVblank_Orig(void);
void unk_9a63c_Orig(void);
void CutsceneInternalMonologueVblank_Orig(void);
void unk_9a99c_Orig(void);
void CutsceneFederationMonologueVblank_Orig(void);
void unk_9ae0c_Orig(void);
void CutsceneSecretConversationVblank_Orig(void);
void CutsceneProcessElevatorScrolling_Orig(struct CutsceneMonologueOam* pOam);
void unk_9a1a8_Orig(struct CutsceneMonologueOam* pOam);
void CutsceneSecretConversationProcessNavigationPanel_Orig(struct CutsceneOam* pOam);
void CutsceneSecretConversationProcessIncomingDispatch_Orig(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingProcessFallingLab_Orig(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingProcessBslPart_Orig(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingProcessScrolling_Orig(struct CutsceneOam* pOam);
void unk_9ba50_Orig(struct CutsceneOam* pOam);
void unk_9bac0_Orig(struct CutsceneOam* pOam);
void unk_9bb30_Orig(struct CutsceneOam* pOam);
void unk_9bc04_Orig(struct CutsceneOam* pOam);
void unk_9bcdc_Orig(struct CutsceneOam* pOam);
void unk_9bd24_Orig(struct CutsceneOam* pOam);
void unk_9bdf8_Orig(struct CutsceneOam* pOam);
void unk_9be8c_Orig(struct CutsceneOam* pOam);
void unk_9bf54_Orig(struct CutsceneOam* pOam);
void unk_9bfb8_Orig(struct CutsceneOam* pOam);
asm(".set unk_9a31c_Orig, 0x809a31d");
asm(".set CutsceneElevatorMonologueVblank_Orig, 0x809a2c9");
asm(".set unk_9a63c_Orig, 0x809a63d");
asm(".set CutsceneInternalMonologueVblank_Orig, 0x809a605");
asm(".set unk_9a99c_Orig, 0x809a99d");
asm(".set CutsceneFederationMonologueVblank_Orig, 0x809a965");
asm(".set unk_9ae0c_Orig, 0x809ae0d");
asm(".set CutsceneSecretConversationVblank_Orig, 0x809ad65");
asm(".set CutsceneProcessElevatorScrolling_Orig, 0x809a089");
asm(".set unk_9a1a8_Orig, 0x809a1a9");
asm(".set CutsceneSecretConversationProcessNavigationPanel_Orig, 0x809acd5");
asm(".set CutsceneSecretConversationProcessIncomingDispatch_Orig, 0x809acf5");
asm(".set CutsceneRestrictedLabDetachingProcessFallingLab_Orig, 0x809b371");
asm(".set CutsceneRestrictedLabDetachingProcessBslPart_Orig, 0x809b8ad");
asm(".set CutsceneRestrictedLabDetachingProcessScrolling_Orig, 0x809ba25");
asm(".set unk_9ba50_Orig, 0x809ba51");
asm(".set unk_9bac0_Orig, 0x809bac1");
asm(".set unk_9bb30_Orig, 0x809bb31");
asm(".set unk_9bc04_Orig, 0x809bc05");
asm(".set unk_9bcdc_Orig, 0x809bcdd");
asm(".set unk_9bd24_Orig, 0x809bd25");
asm(".set unk_9bdf8_Orig, 0x809bdf9");
asm(".set unk_9be8c_Orig, 0x809be8d");
asm(".set unk_9bf54_Orig, 0x809bf55");
asm(".set unk_9bfb8_Orig, 0x809bfb9");
#define FUNC_PTR(f) f##_Orig
#else
#define FUNC_PTR(f) f
#endif

#define CUTSCENE_DISABLE_HBLANK()                                               \
    {                                                                           \
        WRITE_16(REG_IME, FALSE);                                               \
        WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);       \
        WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);                         \
        WRITE_16(REG_IME, TRUE);                                                \
    }

/* ---------------------------------------------------------------------------
 * Elevator monologue
 * ------------------------------------------------------------------------ */

/**
 * @brief 99bac | 8c | Elevator monologue cutscene subroutine
 *
 * @param secondVariant Uses the scrolling down (instead of up) background part
 * @return u32 bool, ended
 */
u32 CutsceneElevatorMonologue(u8 secondVariant)
{
    u32 ended;

    ended = FALSE;

    switch (MONOLOGUE_DATA.stage)
    {
        case 0:
            MONOLOGUE_DATA.stage = 1;
            CutsceneElevatorMonologueInit(secondVariant);
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneElevatorMonologueProcess())
            {
                MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);
                WRITE_16(REG_BLDCNT, 0xFF);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == 16)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 99c38 | 22c | Initializes the elevator monologue cutscene
 *
 * @param secondVariant Second variant
 */
void CutsceneElevatorMonologueInit(u8 secondVariant)
{
    CUTSCENE_DISABLE_HBLANK();

    CallbackSetVBlank(FUNC_PTR(unk_9a31c));
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sMonologueObjGfxPointers[gCurrentCutscene - 1], VRAM_BASE + 0x12000);
    LZ77UncompVram(sMonologueTextGfx_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sMonologueCursorPal_6638a0, PALRAM_BASE + 0x3E0, 0x20 / 4);
    DMA3_COPY_32(sMonologueObjPalPointers[gCurrentCutscene - 1], PALRAM_BASE + 0x200, 0xC0 / 4);
    LZ77UncompVram(sMonologueBgGfxPointers[gCurrentCutscene - 1], VRAM_BASE);
    LZ77UncompVram(sMonologueTilemapPointers[gCurrentCutscene - 1], VRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    LZ77UncompVram(sMonologueTextTilemap_663598, VRAM_BASE + 0xD800);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / 4);
    DMA3_COPY_32(sMonologueTextPal_6636a0, PALRAM_BASE, 0x200 / 4);
    DMA3_COPY_32(sMonologueBgPalPointers[gCurrentCutscene - 1], PALRAM_BASE, 0x160 / 4);

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, 0x1908);
    WRITE_16(REG_BG1CNT, 0x1B01);
    WRITE_16(REG_BG2CNT, 0x1A03);
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneElevatorMonologueSetupOam(1, 12, 16);
    CutsceneElevatorMonologueSetupOam(2, 120, 120);
    CutsceneElevatorMonologueSetupOam(3, 120, 120);

    if (!secondVariant)
        CutsceneElevatorMonologueSetupOam(4, 120, 104);
    else
        CutsceneElevatorMonologueSetupOam(5, 120, 104);

    MONOLOGUE_DATA.unk_A = gCurrentCutscene - 1;
    MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][MONOLOGUE_DATA.unk_A];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(FUNC_PTR(CutsceneElevatorMonologueVblank));
}

/**
 * @brief 99e64 | 3c | Processes the elevator monologue cutscene
 *
 * @return u32 bool, ended
 */
u32 CutsceneElevatorMonologueProcess(void)
{
    u32 ended;

    ended = CutsceneMonologueProcessSpecialTextCharacters();

    if (MONOLOGUE_DATA.unk_17 == 0)
    {
        MONOLOGUE_DATA.unk_17 = 100;
    }
    else if (MONOLOGUE_DATA.unk_17 == 1)
    {
        MONOLOGUE_DATA.unk_17 = 100;
        CutsceneMonologueProcessText();
    }

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    return ended;
}

/**
 * @brief 99ea0 | 1e8 | Sets up an elevator monologue oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (5 if none free)
 */
u8 CutsceneElevatorMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < CUTSCENE_MONOLOGUE_OAM_COUNT; i++)
    {
        if (MONOLOGUE_DATA.oam[i].process == 0)
            break;
    }

    if (i > CUTSCENE_MONOLOGUE_OAM_COUNT - 1)
        return CUTSCENE_MONOLOGUE_OAM_COUNT;

    CutsceneMonologueResetOam(i);

    MONOLOGUE_DATA.oam[i].xPosition = xPosition;
    MONOLOGUE_DATA.oam[i].yPosition = yPosition;
    MONOLOGUE_DATA.oam[i].process = type;
    MONOLOGUE_DATA.oam[i].draw = TRUE;

    if (type == 1)
    {
        MONOLOGUE_DATA.oam[i].paletteOffset = 15;
        MONOLOGUE_DATA.oam[i].tileOffset = 0x3E0;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueCursorOam_663e5c;
        MONOLOGUE_DATA.oam[i].pFunction = CutsceneMonologueProcessCursor;
    }
    else if (type == 2)
    {
        MONOLOGUE_DATA.oam[i].priority = 3;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueOamPointers[gCurrentCutscene - 1][0];
        MONOLOGUE_DATA.oam[i].pFunction = unk_9d09c;
    }
    else if (type == 3)
    {
        MONOLOGUE_DATA.oam[i].objMode = 2;
        MONOLOGUE_DATA.oam[i].priority = type;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueOamPointers[gCurrentCutscene - 1][0];
        MONOLOGUE_DATA.oam[i].pFunction = unk_9d09c;
    }
    else if (type == 4)
    {
        MONOLOGUE_DATA.oam[i].priority = 3;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueOamPointers[gCurrentCutscene - 1][1];
        MONOLOGUE_DATA.oam[i].pFunction = FUNC_PTR(CutsceneProcessElevatorScrolling);
    }
    else if (type == 5)
    {
        MONOLOGUE_DATA.oam[i].priority = 3;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueOamPointers[gCurrentCutscene - 1][1];
        MONOLOGUE_DATA.oam[i].pFunction = FUNC_PTR(unk_9a1a8);
    }

    return i;
}

/**
 * @brief 9a088 | 120 | Processes the elevator scrolling (going up)
 *
 * @param pOam Cutscene monologue oam pointer
 */
void CutsceneProcessElevatorScrolling(struct CutsceneMonologueOam* pOam)
{
    pOam->yPosition += 2;

    MONOLOGUE_DATA.unk_12--;
    WRITE_16(REG_BG2VOFS, MONOLOGUE_DATA.unk_12);

    if (pOam->stage == 0)
    {
        if (gWrittenToBldy == 0)
        {
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = 16;
            WRITE_16(REG_WININ, 0);
            WRITE_16(REG_WINOUT, 0x331D);
            MONOLOGUE_DATA.unk_14 = 0;
            WRITE_16(REG_BG1VOFS, 0);
            WRITE_16(REG_BLDALPHA, 16 << 8);
            WRITE_16(REG_BLDCNT, 0x1042);
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1 | DCNT_WINOBJ);
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (gWrittenToBldalpha_Eva == 10)
        {
            pOam->stage = 2;
            pOam->timer = 0;
        }
        else if (pOam->timer > 3)
        {
            pOam->timer = 0;
            gWrittenToBldalpha_Eva++;
        }
        else
        {
            pOam->timer++;
        }

        MONOLOGUE_DATA.unk_14 -= 3;
        WRITE_16(REG_BG1VOFS, MONOLOGUE_DATA.unk_14);
    }
    else
    {
        if (gWrittenToBldalpha_Eva == 4)
        {
            pOam->stage = 1;
            pOam->timer = 0;
        }
        else if (pOam->timer > 3)
        {
            pOam->timer = 0;
            gWrittenToBldalpha_Eva--;
        }
        else
        {
            pOam->timer++;
        }

        MONOLOGUE_DATA.unk_14 -= 3;
        WRITE_16(REG_BG1VOFS, MONOLOGUE_DATA.unk_14);
    }
}

/**
 * @brief 9a1a8 | 120 | Processes the elevator scrolling (going down)
 *
 * @param pOam Cutscene monologue oam pointer
 */
void unk_9a1a8(struct CutsceneMonologueOam* pOam)
{
    pOam->yPosition -= 2;

    MONOLOGUE_DATA.unk_12++;
    WRITE_16(REG_BG2VOFS, MONOLOGUE_DATA.unk_12);

    if (pOam->stage == 0)
    {
        if (gWrittenToBldy == 0)
        {
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = 16;
            WRITE_16(REG_WININ, 0);
            WRITE_16(REG_WINOUT, 0x331D);
            MONOLOGUE_DATA.unk_14 = 0;
            WRITE_16(REG_BG1VOFS, 0);
            WRITE_16(REG_BLDALPHA, 16 << 8);
            WRITE_16(REG_BLDCNT, 0x1042);
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1 | DCNT_WINOBJ);
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (gWrittenToBldalpha_Eva == 10)
        {
            pOam->stage = 2;
            pOam->timer = 0;
        }
        else if (pOam->timer > 3)
        {
            pOam->timer = 0;
            gWrittenToBldalpha_Eva++;
        }
        else
        {
            pOam->timer++;
        }

        MONOLOGUE_DATA.unk_14 += 3;
        WRITE_16(REG_BG1VOFS, MONOLOGUE_DATA.unk_14);
    }
    else
    {
        if (gWrittenToBldalpha_Eva == 4)
        {
            pOam->stage = 1;
            pOam->timer = 0;
        }
        else if (pOam->timer > 3)
        {
            pOam->timer = 0;
            gWrittenToBldalpha_Eva--;
        }
        else
        {
            pOam->timer++;
        }

        MONOLOGUE_DATA.unk_14 += 3;
        WRITE_16(REG_BG1VOFS, MONOLOGUE_DATA.unk_14);
    }
}

/**
 * @brief 9a2c8 | 54 | V-blank code for the elevator monologue cutscene
 *
 */
void CutsceneElevatorMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);
    unk_9cc4c();
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a31c | c | V-blank code during the elevator monologue init
 *
 */
void unk_9a31c(void)
{
    UpdateAudio();
}

/* ---------------------------------------------------------------------------
 * Internal monologue
 * ------------------------------------------------------------------------ */

/**
 * @brief 9a328 | 84 | Internal monologue cutscene subroutine
 *
 * @param unused Unused (passed to the init in the original code, which ignores it)
 * @return u32 bool, ended
 */
u32 CutsceneInternalMonologue(u8 unused)
{
    u32 ended;

    ended = FALSE;

    switch (MONOLOGUE_DATA.stage)
    {
        case 0:
            MONOLOGUE_DATA.stage = 1;
            CutsceneInternalMonologueInit();
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneInternalMonologueProcess())
            {
                MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, 0xFF);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == 16)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9a3ac | 13c | Initializes the internal monologue cutscene
 *
 */
void CutsceneInternalMonologueInit(void)
{
    CUTSCENE_DISABLE_HBLANK();

    CallbackSetVBlank(FUNC_PTR(unk_9a63c));
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sMonologueTextGfx_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sMonologueCursorPal_6638a0, PALRAM_BASE + 0x3E0, 0x20 / 4);
    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / 4);
    DMA3_COPY_32(sMonologueTextPal_6636a0, PALRAM_BASE, 0x200 / 4);
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, 0x1908);
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneInternalMonologueSetupOam(1, 12, 16);

    MONOLOGUE_DATA.unk_A = gCurrentCutscene - 1;
    MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][MONOLOGUE_DATA.unk_A];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(FUNC_PTR(CutsceneInternalMonologueVblank));
}

/**
 * @brief 9a4e8 | 3c | Processes the internal monologue cutscene
 *
 * @return u32 bool, ended
 */
u32 CutsceneInternalMonologueProcess(void)
{
    u32 ended;

    ended = CutsceneMonologueProcessSpecialTextCharacters();

    if (MONOLOGUE_DATA.unk_17 == 0)
    {
        MONOLOGUE_DATA.unk_17 = 100;
    }
    else if (MONOLOGUE_DATA.unk_17 == 1)
    {
        MONOLOGUE_DATA.unk_17 = 100;
        CutsceneMonologueProcessText();
    }

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    return ended;
}

/**
 * @brief 9a524 | e0 | Sets up an internal monologue oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (5 if none free)
 */
u8 CutsceneInternalMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < CUTSCENE_MONOLOGUE_OAM_COUNT; i++)
    {
        if (MONOLOGUE_DATA.oam[i].process == 0)
            break;
    }

    if (i > CUTSCENE_MONOLOGUE_OAM_COUNT - 1)
        return CUTSCENE_MONOLOGUE_OAM_COUNT;

    CutsceneMonologueResetOam(i);

    MONOLOGUE_DATA.oam[i].xPosition = xPosition;
    MONOLOGUE_DATA.oam[i].yPosition = yPosition;
    MONOLOGUE_DATA.oam[i].process = type;
    MONOLOGUE_DATA.oam[i].draw = TRUE;

    if (type == 1)
    {
        MONOLOGUE_DATA.oam[i].priority = 2;
        MONOLOGUE_DATA.oam[i].paletteOffset = 15;
        MONOLOGUE_DATA.oam[i].tileOffset = 0x3E0;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueCursorOam_663e5c;
        MONOLOGUE_DATA.oam[i].pFunction = CutsceneMonologueProcessCursor;
    }

    return i;
}

/**
 * @brief 9a604 | 38 | V-blank code for the internal monologue cutscene
 *
 */
void CutsceneInternalMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);
    unk_9cc4c();
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a63c | c | V-blank code during the internal monologue init
 *
 */
void unk_9a63c(void)
{
    UpdateAudio();
}

/* ---------------------------------------------------------------------------
 * Federation monologue
 * ------------------------------------------------------------------------ */

/**
 * @brief 9a648 | 84 | Federation monologue cutscene subroutine
 *
 * @param unused Unused (passed to the init in the original code, which ignores it)
 * @return u32 bool, ended
 */
u32 CutsceneFederationMonologue(u8 unused)
{
    u32 ended;

    ended = FALSE;

    switch (MONOLOGUE_DATA.stage)
    {
        case 0:
            MONOLOGUE_DATA.stage = 1;
            CutsceneFederationMonologueInit();
            break;

        case 1:
            CutsceneMonologueFadeIn();
            if (gWrittenToBldy == 0)
                MONOLOGUE_DATA.stage++;
            break;

        case 2:
            if (CutsceneFederationMonologueProcess())
            {
                MONOLOGUE_DATA.stage = 3;
                WRITE_16(REG_BLDCNT, 0xFF);
            }
            break;

        case 3:
            CutsceneMonologueFadeOut();
            if (gWrittenToBldy == 16)
                ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9a6cc | 17c | Initializes the federation monologue cutscene
 *
 */
void CutsceneFederationMonologueInit(void)
{
    CUTSCENE_DISABLE_HBLANK();

    CallbackSetVBlank(FUNC_PTR(unk_9a99c));
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sMonologueTextGfx_65fb5c, VRAM_BASE + 0x17C00);
    DMA3_COPY_32(sMonologueCursorPal_6638a0, PALRAM_BASE + 0x3E0, 0x20 / 4);
    LZ77UncompVram(sFederationBgGfx_6724c0, VRAM_BASE);
    LZ77UncompVram(sFederationTilemap_674ad8, VRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xC800, 0x800 / 4);
    DMA3_COPY_32(sFederationBgPal_674958, PALRAM_BASE, 0x180 / 4);
    DMA3_COPY_32(sIntroPal_663820, PALRAM_BASE + 0x180, 0x80 / 4);
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG0VOFS, 4);
    WRITE_16(REG_BG0CNT, 0x1908);
    WRITE_16(REG_BG2CNT, 0x1A03);
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneFederationMonologueSetupOam(1, 12, 16);

    MONOLOGUE_DATA.unk_A = gCurrentCutscene - 1;
    MONOLOGUE_DATA.pText = sMonologueTextPointers[gLanguage][MONOLOGUE_DATA.unk_A];

    CutsceneMonologueDrawAllOam();
    CallbackSetVBlank(FUNC_PTR(CutsceneFederationMonologueVblank));
}

/**
 * @brief 9a848 | 3c | Processes the federation monologue cutscene
 *
 * @return u32 bool, ended
 */
u32 CutsceneFederationMonologueProcess(void)
{
    u32 ended;

    ended = CutsceneMonologueProcessSpecialTextCharacters();

    if (MONOLOGUE_DATA.unk_17 == 0)
    {
        MONOLOGUE_DATA.unk_17 = 100;
    }
    else if (MONOLOGUE_DATA.unk_17 == 1)
    {
        MONOLOGUE_DATA.unk_17 = 100;
        CutsceneMonologueProcessText();
    }

    CutsceneMonologueProcessOam();
    CutsceneMonologueDrawAllOam();

    return ended;
}

/**
 * @brief 9a884 | e0 | Sets up a federation monologue oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (5 if none free)
 */
u8 CutsceneFederationMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < CUTSCENE_MONOLOGUE_OAM_COUNT; i++)
    {
        if (MONOLOGUE_DATA.oam[i].process == 0)
            break;
    }

    if (i > CUTSCENE_MONOLOGUE_OAM_COUNT - 1)
        return CUTSCENE_MONOLOGUE_OAM_COUNT;

    CutsceneMonologueResetOam(i);

    MONOLOGUE_DATA.oam[i].xPosition = xPosition;
    MONOLOGUE_DATA.oam[i].yPosition = yPosition;
    MONOLOGUE_DATA.oam[i].process = type;
    MONOLOGUE_DATA.oam[i].draw = TRUE;

    if (type == 1)
    {
        MONOLOGUE_DATA.oam[i].priority = 0;
        MONOLOGUE_DATA.oam[i].paletteOffset = 15;
        MONOLOGUE_DATA.oam[i].tileOffset = 0x3E0;
        MONOLOGUE_DATA.oam[i].pOam = sMonologueCursorOam_663e5c;
        MONOLOGUE_DATA.oam[i].pFunction = CutsceneMonologueProcessCursor;
    }

    return i;
}

/**
 * @brief 9a964 | 38 | V-blank code for the federation monologue cutscene
 *
 */
void CutsceneFederationMonologueVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);
    unk_9cc4c();
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief 9a99c | c | V-blank code during the federation monologue init
 *
 */
void unk_9a99c(void)
{
    UpdateAudio();
}

/* ---------------------------------------------------------------------------
 * Secret conversation
 * ------------------------------------------------------------------------ */

/**
 * @brief 9a9a8 | 84 | Secret conversation cutscene subroutine
 *
 * @return u32 bool, ended
 */
u32 CutsceneSecretConversation(void)
{
    u32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneSecretConversationInit();
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                CUTSCENE_DATA.stage = 2;
            break;

        case 2:
            if (CutsceneSecretConversationProcess())
            {
                CUTSCENE_DATA.stage = 3;
                WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG2 | DCNT_OBJ);
                WRITE_16(REG_BLDCNT, 0xFF);
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
 * @brief 9aa2c | 138 | Initializes the secret conversation cutscene
 *
 */
void CutsceneSecretConversationInit(void)
{
    CUTSCENE_DISABLE_HBLANK();

    CallbackSetVBlank(FUNC_PTR(unk_9ae0c));
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sSecretConversationObjGfx_67815c, VRAM_BASE + 0x14000);
    DMA3_COPY_32(sSecretConversationObjPal_6788a8, PALRAM_BASE + 0x300, 0x40 / 4);
    LZ77UncompVram(sSecretConversationBgGfx_675098, VRAM_BASE + 0x800);
    LZ77UncompVram(sSecretConversationTilemap_677914, VRAM_BASE + 0xC000);
    LZ77UncompVram(sSecretConversationTilemap_677c90, VRAM_BASE + 0xC800);
    DMA3_COPY_32(sSecretConversationBgPal_677874, PALRAM_BASE, 0xA0 / 4);
    DMA3_COPY_32(sSecretConversationObjPal_677c10, PALRAM_BASE + 0x1E0, 0x20 / 4);

    CutsceneSecretConversationSetupOam(1, 120, 128);
    CutsceneSecretConversationSetupOam(2, 120, 128);
    CutsceneSecretConversationSetupOam(3, 120, 128);

    WRITE_16(REG_BG1CNT, 0x1802);
    WRITE_16(REG_BG2CNT, 0x1903);
    WRITE_16(REG_DISPCNT, DCNT_BG1 | DCNT_BG2 | DCNT_OBJ);

    gWrittenToBldy--;

    CutsceneDrawAllOam();
    CallbackSetVBlank(FUNC_PTR(CutsceneSecretConversationVblank));
}

/**
 * @brief 9ab64 | 64 | Processes the secret conversation cutscene
 *
 * @return u32 bool, ended
 */
u32 CutsceneSecretConversationProcess(void)
{
    u32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer > 29)
            {
                CUTSCENE_DATA.subStage = 1;
                CUTSCENE_DATA.timer = 0;
                CutsceneSecretConversationSetupOam(4, 120, 68);
                CutsceneProcessOam();
            }
            CutsceneDrawAllOam();
            break;

        case 1:
            CutsceneProcessOam();
            CutsceneDrawAllOam();
            break;

        case 2:
            CutsceneProcessOam();
            CutsceneDrawAllOam();
            ended = TRUE;
            break;
    }

    return ended;
}

/**
 * @brief 9abc8 | 10c | Sets up a secret conversation oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (16 if none free)
 */
u8 CutsceneSecretConversationSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == 0)
            break;
    }

    if (i > CUTSCENE_OAM_COUNT - 1)
        return CUTSCENE_OAM_COUNT;

    DMA3_FILL_32(0, &CUTSCENE_DATA.oam[i], sizeof(CUTSCENE_DATA.oam[i]));

    CUTSCENE_DATA.oam[i].xPosition = xPosition;
    CUTSCENE_DATA.oam[i].yPosition = yPosition;
    CUTSCENE_DATA.oam[i].type = type;
    CUTSCENE_DATA.oam[i].exists = TRUE;

    if (type == 1)
    {
        CUTSCENE_DATA.oam[i].pOam = sSecretConversationOam_6793b0;
        CUTSCENE_DATA.oam[i].pFunction = unk_9db70;
    }
    else if (type == 2)
    {
        CUTSCENE_DATA.oam[i].pOam = sSecretConversationOam_679280;
        CUTSCENE_DATA.oam[i].pFunction = FUNC_PTR(CutsceneSecretConversationProcessNavigationPanel);
    }
    else if (type == 3)
    {
        CUTSCENE_DATA.oam[i].pOam = sSecretConversationOam_6793a0;
        CUTSCENE_DATA.oam[i].pFunction = unk_9db70;
    }
    else if (type == 4)
    {
        CUTSCENE_DATA.oam[i].pOam = sSecretConversationOam_6792d0;
        CUTSCENE_DATA.oam[i].pFunction = FUNC_PTR(CutsceneSecretConversationProcessIncomingDispatch);
    }

    return i;
}

/**
 * @brief 9acd4 | 20 | Processes the navigation panel (secret conversation)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneSecretConversationProcessNavigationPanel(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->stage = 1;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->pOam = sSecretConversationOam_6792a8;
    }
}

/**
 * @brief 9acf4 | 70 | Processes the incoming dispatch message (secret conversation)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneSecretConversationProcessIncomingDispatch(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    if (pOam->stage == 0)
    {
        pFrame = &pOam->pOam[pOam->currentAnimationFrame];

        if (pOam->timer == 0)
        {
            SoundPlay(0x22F);
            pOam->timer = 1;
        }

        if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
        {
            pOam->stage = 1;
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sSecretConversationOam_679350;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        if (pOam->timer == 180)
        {
            pOam->stage = 2;
            pOam->timer = 0;
            CUTSCENE_DATA.subStage = 2;
        }
    }
}

/**
 * @brief 9ad64 | a8 | V-blank code for the secret conversation cutscene
 *
 */
void CutsceneSecretConversationVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);
    WRITE_16(REG_BLDY, gWrittenToBldy);

    CUTSCENE_DATA.unk_11++;
    switch (CUTSCENE_DATA.unk_11)
    {
        case 7:
            DMA3_COPY_32(sSecretConversationObjPal_677c30, PALRAM_BASE + 0x1E0, 0x20 / 4);
            break;

        case 14:
            DMA3_COPY_32(sSecretConversationObjPal_677c50, PALRAM_BASE + 0x1E0, 0x20 / 4);
            break;

        case 21:
            DMA3_COPY_32(sSecretConversationObjPal_677c70, PALRAM_BASE + 0x1E0, 0x20 / 4);
            break;

        case 28:
            DMA3_COPY_32(sSecretConversationObjPal_677c10, PALRAM_BASE + 0x1E0, 0x20 / 4);
            CUTSCENE_DATA.unk_11 = 0;
            break;
    }
}

/**
 * @brief 9ae0c | c | V-blank code during the secret conversation init
 *
 */
void unk_9ae0c(void)
{
    UpdateAudio();
}

/* ---------------------------------------------------------------------------
 * Restricted lab detaching
 * ------------------------------------------------------------------------ */

/**
 * @brief 9ae18 | 8c | Restricted lab detaching cutscene subroutine
 *
 * @return u32 bool, ended
 */
u32 CutsceneRestrictedLabDetaching(void)
{
    u32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.stage)
    {
        case 0:
            CUTSCENE_DATA.stage = 1;
            CutsceneRestrictedLabDetachingInit();
            break;

        case 1:
            if (gWrittenToBldy == 16)
                SoundPlay_3b1c(0x248);

            CutsceneFadeIn();
            if (gWrittenToBldy == 0)
                CUTSCENE_DATA.stage++;
            break;

        case 2:
            if (CutsceneRestrictedLabDetachingProcess())
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
 * @brief 9aea4 | 15c | Initializes the restricted lab detaching cutscene
 *
 */
void CutsceneRestrictedLabDetachingInit(void)
{
    CUTSCENE_DISABLE_HBLANK();

    CallbackSetVBlank(unk_9c1bc);
    unk_36c4();
    WRITE_16(REG_DISPCNT, 0);

    LZ77UncompVram(sRestrictedLabObjGfx_67d7cc, VRAM_OBJ);
    DMA3_COPY_32(sRestrictedLabObjPal_68121c, PALRAM_BASE + 0x200, 0x200 / 4);
    LZ77UncompVram(sRestrictedLabBgGfx_679420, VRAM_BASE);
    LZ77UncompVram(sRestrictedLabTilemap_6820a4, VRAM_BASE + 0xE000);
    LZ77UncompVram(sRestrictedLabTilemap_681a1c, VRAM_BASE + 0xE800);
    DMA3_COPY_32(sRestrictedLabBgPal_68259c, PALRAM_BASE, 0x200 / 4);
    WRITE_16(PALRAM_BASE, 0);

    WRITE_16(REG_BG1CNT, 0x1D00);
    WRITE_16(REG_BG3CNT, 0x1C03);
    WRITE_16(REG_DISPCNT, DCNT_BG3 | DCNT_OBJ);

    gWrittenToBldy = 16;

    CutsceneRestrictedLabDetachingSetupOam(1, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(3, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(2, 150, 90);
    CutsceneRestrictedLabDetachingSetupOam(4, 120, 0);

    CutsceneProcessOam();
    CutsceneDrawAllOam();

    CUTSCENE_DATA.unk_A = 0;
    CUTSCENE_DATA.unk_C = 0;
    DMA3_COPY_32(sRestrictedLabFadingPal_68101c + CUTSCENE_DATA.unk_C * 16, PALRAM_BASE + 0x120, 0x20 / 4);

    CallbackSetVBlank(CutsceneRestrictedLabDetachingVblank);
}

/**
 * @brief 9b000 | 370 | Processes the restricted lab detaching cutscene
 *
 * @return u32 bool, ended
 */
u32 CutsceneRestrictedLabDetachingProcess(void)
{
    s16 xPosition;
    s16 yPosition;
    u32 ended;

    ended = FALSE;

    switch (CUTSCENE_DATA.subStage)
    {
        case 0:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 1;
            }
            break;

        case 1:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(0x11, xPosition - 20, yPosition - 20, -2, 6);
                unk_9c0b4(0x11, xPosition - 70, yPosition - 26, -1, 4);
            }
            else if (CUTSCENE_DATA.timer == 16)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(0x11, xPosition - 30, yPosition - 30, -2, 8);
                unk_9c0b4(0x11, xPosition - 50, yPosition - 8, -1, 8);
            }
            else if (CUTSCENE_DATA.timer == 20)
            {
                CutsceneRestrictedLabDetachingGetPositionOfOamByType(2, &xPosition, &yPosition);
                unk_9c0b4(0x11, xPosition - 80, yPosition - 14, -3, 6);
                unk_9c0b4(0x11, xPosition - 10, yPosition - 18, -2, 2);
            }
            else if (CUTSCENE_DATA.timer == 170)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 2;
                gWrittenToBldy = 0;
            }
            break;

        case 2:
            if (gWrittenToBldy > 15)
            {
                gWrittenToBldy = 16;
                DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
                CUTSCENE_DATA.subStage = 5;
            }
            else
            {
                gWrittenToBldy += 2;
            }
            break;

        case 5:
            if (gWrittenToBldy <= 15)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
                CUTSCENE_DATA.timer = 0;
                CutsceneRestrictedLabDetachingSetupOam(4, 0, 0);
                CutsceneRestrictedLabDetachingSetupOam(0x1E, 205, 10);
                CutsceneRestrictedLabDetachingSetupOam(0xC, 140, 80);
                WRITE_16(REG_BG2HOFS, 0);
                WRITE_16(REG_BG2VOFS, 0);
                CUTSCENE_DATA.subStage = 6;
            }
            break;

        case 6:
            if (gWrittenToBldy != 0)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                gWrittenToBldy = 0;
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 7;
            }
            break;

        case 7:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 149)
            {
                gWrittenToBldalpha_Eva = 10;
                gWrittenToBldalpha_Evb = 10;
            }
            else if (CUTSCENE_DATA.timer == 150)
            {
                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 8;
            }
            break;

        case 8:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, 0x1C42);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);

                CutsceneRestrictedLabDetachingGetPositionOfOamByType(0xC, &xPosition, &yPosition);
                CutsceneDestroyOamOfType(0xC);
                unk_9c0b4(0x10, xPosition, yPosition, 0, 0);

                CUTSCENE_DATA.timer = 0;
                CUTSCENE_DATA.subStage = 9;
            }
            break;

        case 9:
            CUTSCENE_DATA.timer++;
            if (CUTSCENE_DATA.unk_C <= 14)
            {
                if (CUTSCENE_DATA.timer == 4)
                {
                    CUTSCENE_DATA.timer = 0;
                    CUTSCENE_DATA.unk_A = 1;
                    CUTSCENE_DATA.unk_C++;
                }
            }
            else if (CUTSCENE_DATA.timer == 15)
            {
                CUTSCENE_DATA.timer = 0;
                gWrittenToBldy = 16;
                CUTSCENE_DATA.subStage = 10;
            }
            break;

        case 10:
            CUTSCENE_DATA.timer++;
            if (gWrittenToBldalpha_Eva <= 15)
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
                    DMA3_FILL_32(0, CUTSCENE_DATA.oam, sizeof(CUTSCENE_DATA.oam));
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
 * @brief 9b370 | cc | Processes the falling restricted lab
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneRestrictedLabDetachingProcessFallingLab(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_E++;
        pOam->xPosition = (pOam->unk_E >> 1) + pOam->unk_6;
        pOam->yPosition = pOam->unk_8 - (pOam->unk_E >> 2);
    }

    pOam->timer++;
    if (pOam->timer == 10)
    {
        pOam->timer = 0;

        if (pOam->unk_E < 220)
            pOam->scaling += 2;
        else if (pOam->unk_E < 440)
            pOam->scaling += 4;
        else
            pOam->scaling += 6;

        if (pOam->scaling > 0x1FF)
            pOam->scaling = 0x200;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 6)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 15)
            pOam->unk_C = 0;
    }

    if ((u16)(pOam->xPosition + 16) > 306 || pOam->yPosition < -50 || pOam->yPosition > 176)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}

/**
 * @brief 9b43c | 470 | Sets up a restricted lab detaching oam
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Slot (16 if none free)
 */
u8 CutsceneRestrictedLabDetachingSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;
    struct CutsceneOam* pOam;

    for (i = 0; i < CUTSCENE_OAM_COUNT; i++)
    {
        if (CUTSCENE_DATA.oam[i].type == 0)
            break;
    }

    if (i > CUTSCENE_OAM_COUNT - 1)
        return CUTSCENE_OAM_COUNT;

    DMA3_FILL_32(0, &CUTSCENE_DATA.oam[i], sizeof(CUTSCENE_DATA.oam[i]));

    pOam = &CUTSCENE_DATA.oam[i];
    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->exists = TRUE;

    switch (type)
    {
        case 1:
            pOam->priority = 1;
            pOam->scaling = 0x180;
            pOam->affineMode = 3;
            pOam->pOam = sRestrictedLabOam_680d54;
            pOam->pFunction = FUNC_PTR(CutsceneRestrictedLabDetachingProcessBslPart);
            break;

        case 2:
            pOam->priority = 1;
            pOam->scaling = 0x180;
            pOam->affineMode = 3;
            pOam->pOam = sRestrictedLabOam_680d64;
            pOam->pFunction = FUNC_PTR(CutsceneRestrictedLabDetachingProcessBslPart);
            break;

        case 3:
            pOam->priority = 1;
            pOam->scaling = 0x180;
            pOam->affineMode = 3;
            pOam->pOam = sRestrictedLabOam_680d74;
            pOam->pFunction = FUNC_PTR(CutsceneRestrictedLabDetachingProcessBslPart);
            break;

        case 4:
            pOam->exists = FALSE;
            pOam->pFunction = FUNC_PTR(CutsceneRestrictedLabDetachingProcessScrolling);
            break;

        case 5:
            pOam->pOam = sRestrictedLabOam_680e2c;
            pOam->pFunction = FUNC_PTR(unk_9ba50);
            break;

        case 6:
            pOam->priority = 1;
            pOam->pOam = sRestrictedLabOam_680e3c;
            pOam->pFunction = FUNC_PTR(unk_9ba50);
            break;

        case 7:
            pOam->priority = 1;
            pOam->pOam = sRestrictedLabOam_680da4;
            pOam->pFunction = FUNC_PTR(unk_9bac0);
            break;

        case 8:
            pOam->priority = 1;
            pOam->pOam = sRestrictedLabOam_680d94;
            pOam->pFunction = FUNC_PTR(unk_9bb30);
            break;

        case 9:
            pOam->scaling = 0x100;
            pOam->priority = 1;
            pOam->affineMode = 1;
            pOam->pOam = sRestrictedLabOam_680d84;
            pOam->pFunction = FUNC_PTR(unk_9bc04);
            break;

        case 10:
            pOam->exists = FALSE;
            pOam->pFunction = FUNC_PTR(unk_9bcdc);
            break;

        case 11:
            pOam->pOam = sRestrictedLabOam_680dcc;
            pOam->pFunction = FUNC_PTR(unk_9bac0);
            break;

        case 12:
            pOam->scaling = 0x100;
            pOam->priority = 1;
            pOam->affineMode = 1;
            pOam->pOam = sRestrictedLabOam_680fec;
            pOam->pFunction = FUNC_PTR(unk_9bd24);
            break;

        case 13:
            pOam->scaling = 0x100;
            pOam->priority = 1;
            pOam->affineMode = 1;
            pOam->pOam = sRestrictedLabOam_680fc4;
            pOam->pFunction = FUNC_PTR(unk_9bdf8);
            break;

        case 14:
            pOam->exists = FALSE;
            pOam->pFunction = FUNC_PTR(unk_9be8c);
            break;

        case 15:
            pOam->exists = FALSE;
            pOam->pFunction = FUNC_PTR(unk_9bf54);
            break;

        case 16:
            pOam->objMode = 1;
            pOam->priority = 1;
            pOam->pOam = sRestrictedLabOam_680f9c;
            pOam->pFunction = FUNC_PTR(unk_9bfb8);
            break;

        case 17:
            pOam->pOam = sRestrictedLabOam_680f74;
            pOam->pFunction = FUNC_PTR(unk_9bfb8);
            break;

        case 18:
            pOam->exists = FALSE;
            pOam->pFunction = unk_9c04c;
            break;

        case 30:
            pOam->scaling = 0x1A0;
            pOam->priority = 1;
            pOam->affineMode = 3;
            pOam->pOam = sRestrictedLabOam_680f2c;
            pOam->pFunction = FUNC_PTR(CutsceneRestrictedLabDetachingProcessFallingLab);
            break;
    }

    return i;
}

/**
 * @brief 9b8ac | 178 | Processes a part of the BSL (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneRestrictedLabDetachingProcessBslPart(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 9)
        {
            pOam->timer = 0;
            pOam->xPosition--;
        }

        pOam->unk_E++;
        switch (pOam->unk_6)
        {
            case 0:
                if (pOam->unk_E == 4)
                {
                    pOam->unk_E = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x17F)
                        pOam->unk_6 = 1;
                }
                break;

            case 1:
                if (pOam->unk_E == 5)
                {
                    pOam->unk_E = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x19F)
                        pOam->unk_6 = 2;
                }
                break;

            case 2:
                if (pOam->unk_E == 6)
                {
                    pOam->unk_E = 0;
                    pOam->scaling += 2;
                    if (pOam->scaling > 0x1BF)
                        pOam->unk_6 = 3;
                }
                break;

            default:
                if (pOam->unk_E == 7)
                {
                    pOam->unk_E = 0;
                    pOam->scaling += 2;
                }
        }

        if (pOam->scaling > 0x200)
            pOam->scaling = 0x200;

        if (CUTSCENE_DATA.subStage == 1)
        {
            pOam->stage = 1;
            pOam->timer = 0;
            pOam->unk_6 = 0;
            pOam->unk_E = 0;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        if (pOam->timer == 9)
        {
            pOam->timer = 0;
            pOam->xPosition--;
        }

        if (pOam->type == 3)
        {
            pOam->yPosition += 6;
            pOam->unk_8 = pOam->yPosition;
        }

        pOam->unk_E = 0;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 9)
        {
            pOam->timer = 0;
            pOam->xPosition--;
        }

        pOam->unk_A++;
        if (pOam->unk_A == 7)
        {
            pOam->unk_A = 0;
            pOam->scaling += 2;
            if (pOam->scaling > 0x200)
                pOam->scaling = 0x200;
        }

        pOam->unk_E++;
        if (pOam->type == 3)
            pOam->yPosition = ((s32)((u32)pOam->unk_E * pOam->unk_E) >> 10) + pOam->unk_8;
    }
}

/**
 * @brief 9ba24 | 2c | Processes the background scrolling (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void CutsceneRestrictedLabDetachingProcessScrolling(struct CutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 30)
    {
        pOam->timer = 0;
        pOam->xPosition--;
    }

    WRITE_16(REG_BG3HOFS, pOam->xPosition);
}

// Moves in a straight line using unk_C/unk_A as velocity, and dies when off screen
#define CUTSCENE_LINEAR_MOVEMENT(pOam)                                              \
    {                                                                               \
        if ((pOam)->stage == 0)                                                     \
        {                                                                           \
            (pOam)->unk_6 = (pOam)->xPosition;                                      \
            (pOam)->unk_8 = (pOam)->yPosition;                                      \
            (pOam)->stage = 1;                                                      \
        }                                                                           \
        else if ((pOam)->stage == 1)                                                \
        {                                                                           \
            (pOam)->unk_E++;                                                        \
            (pOam)->xPosition = (((pOam)->unk_C * (pOam)->unk_E) >> 6) + (pOam)->unk_6; \
            (pOam)->yPosition = (((pOam)->unk_A * (pOam)->unk_E) >> 6) + (pOam)->unk_8; \
        }                                                                           \
    }

#define CUTSCENE_KILL_IF_OFF_SCREEN(pOam)                                           \
    {                                                                               \
        if ((u16)((pOam)->xPosition + 16) > 272 || (pOam)->yPosition < -16 || (pOam)->yPosition > 176) \
        {                                                                           \
            (pOam)->type = 0;                                                       \
            (pOam)->exists = FALSE;                                                 \
        }                                                                           \
    }

/**
 * @brief 9ba50 | 70 | Processes a linearly moving debris (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9ba50(struct CutsceneOam* pOam)
{
    CUTSCENE_LINEAR_MOVEMENT(pOam);
    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9bac0 | 70 | Processes a linearly moving debris (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bac0(struct CutsceneOam* pOam)
{
    CUTSCENE_LINEAR_MOVEMENT(pOam);
    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9bb30 | d4 | Processes a moving and shrinking object (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bb30(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_E++;
        pOam->xPosition = pOam->unk_6 - ((u32)(pOam->unk_E * 3) >> 4);
        pOam->yPosition = (pOam->unk_E >> 3) + pOam->unk_8;
    }

    pOam->timer++;
    if (pOam->timer == 12)
    {
        pOam->timer = 0;
        pOam->scaling -= 2;
        if (pOam->scaling <= 0)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 16)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(sRestrictedLabCyclingPal_68161c + pOam->unk_C * 16, PALRAM_BASE + 0x220, 0x20 / 4);
    }

    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9bc04 | d8 | Processes a moving and shrinking object (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bc04(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_E++;
        pOam->xPosition = ((u32)(pOam->unk_E * 11) >> 6) + pOam->unk_6;
        pOam->yPosition = pOam->unk_8 - ((pOam->unk_E * 9) >> 6);
    }

    pOam->timer++;
    if (pOam->timer == 12)
    {
        pOam->timer = 0;
        pOam->scaling -= 2;
        if (pOam->scaling <= 0)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 6)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(sRestrictedLabCyclingPal_68141c + pOam->unk_C * 16, PALRAM_BASE + 0x200, 0x20 / 4);
    }

    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9bcdc | 48 | Processes the BG2 horizontal scrolling (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bcdc(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        WRITE_16(REG_BG2HOFS, pOam->xPosition);
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_E++;
        WRITE_16(REG_BG2HOFS, ((pOam->unk_C * pOam->unk_E) >> 7) + pOam->xPosition);
    }
}

/**
 * @brief 9bd24 | d4 | Processes a moving and shrinking object (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bd24(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->unk_6 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_E++;
        pOam->xPosition = pOam->unk_6 - (pOam->unk_E >> 3);
        pOam->yPosition = (pOam->unk_E >> 4) + pOam->unk_8;
    }

    pOam->timer++;
    if (pOam->timer == 3)
    {
        pOam->timer = 0;
        pOam->scaling -= 4;
        if (pOam->scaling <= 2)
            pOam->scaling = 2;
    }

    pOam->unk_A++;
    if (pOam->unk_A == 15)
    {
        pOam->unk_A = 0;
        pOam->unk_C++;
        if (pOam->unk_C > 3)
            pOam->unk_C = 0;

        DMA3_COPY_32(sRestrictedLabCyclingPal_68181c + pOam->unk_C * 16, PALRAM_BASE + 0x260, 0x20 / 4);
    }

    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9bdf8 | 94 | Processes a linearly moving and shrinking object (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bdf8(struct CutsceneOam* pOam)
{
    CUTSCENE_LINEAR_MOVEMENT(pOam);

    pOam->timer++;
    if (pOam->timer == 5)
    {
        pOam->timer = 0;
        pOam->scaling -= 4;
        if (pOam->scaling <= 2)
            pOam->scaling = 2;
    }

    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);
}

/**
 * @brief 9be8c | c8 | Processes the palette fading (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9be8c(struct CutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        DMA3_COPY_32(sRestrictedLabFadingPal_68101c, PALRAM_BASE + 0x120, 0x20 / 4);
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        if (pOam->timer == 8)
        {
            pOam->timer = 0;
            pOam->unk_C++;
            if (pOam->unk_C > 14)
            {
                pOam->unk_C = 15;
                pOam->stage = 2;
            }

            DMA3_COPY_32(sRestrictedLabFadingPal_68101c + pOam->unk_C * 16, PALRAM_BASE + 0x120, 0x20 / 4);
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 6)
        {
            pOam->timer = 0;
            if (gWrittenToBldalpha_Eva <= 15)
            {
                gWrittenToBldalpha_Eva++;
                if (gWrittenToBldalpha_Eva <= 15)
                    gWrittenToBldalpha_Evb++;
            }
        }
    }
}

/**
 * @brief 9bf54 | 64 | Processes the BG1 shaking (restricted lab detaching)
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bf54(struct CutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 1)
    {
        pOam->timer = 0;
        CUTSCENE_DATA.unk_A += 2;
        if (CUTSCENE_DATA.unk_A > 160)
            CUTSCENE_DATA.unk_A = 160;
    }

    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == ARRAY_SIZE(sRandomNumberTable))
        pOam->animationDurationCounter = 0;

    WRITE_16(REG_BG1HOFS, sRandomNumberTable[pOam->animationDurationCounter]);
    WRITE_16(REG_BG1VOFS, sRandomNumberTable[pOam->animationDurationCounter]);
}

/**
 * @brief 9bfb8 | 94 | Processes a linearly moving animated object, dies at the end of its animation
 *
 * @param pOam Cutscene oam pointer
 */
void unk_9bfb8(struct CutsceneOam* pOam)
{
    const struct FrameData* pFrame;

    CUTSCENE_LINEAR_MOVEMENT(pOam);
    CUTSCENE_KILL_IF_OFF_SCREEN(pOam);

    pFrame = &pOam->pOam[pOam->currentAnimationFrame];
    if (pFrame[0].timer == pOam->animationDurationCounter && pFrame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->exists = FALSE;
    }
}
