#include "data/blob_pieces.h"
#include "language_select_eu.h"

#ifdef REGION_EU

#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "callbacks.h"
#include "oam.h"
#include "syscalls.h"
#include "init_helpers.h"
#include "audio_wrappers.h"
#include "audio/track_internal.h"

// port/decomp/sram_files.h (not self-contained)
void SramWrite_Language(void);

#include "constants/audio.h"
#include "constants/game_state.h"

#ifdef LANGUAGE_SELECT_EQUIV
// Equivalence testing only (against the EU ROM): store the original ROM addresses of
// the callbacks so that the RAM written by the C version is identical to the original
void LanguageSelectVBlank_Orig(void);
void LanguageSelectProcessCursorFirstBoot_Orig(struct FileSelectOam* pOam);
void LanguageSelectProcessCursorFromTitle_Orig(struct FileSelectOam* pOam);
void LanguageSelectProcessSelected_Orig(struct FileSelectOam* pOam);
asm(".set LanguageSelectVBlank_Orig, 0x080a1685");
asm(".set LanguageSelectProcessCursorFirstBoot_Orig, 0x080a18ad");
asm(".set LanguageSelectProcessCursorFromTitle_Orig, 0x080a198d");
asm(".set LanguageSelectProcessSelected_Orig, 0x080a1a81");
#define FUNC_PTR(f) f##_Orig
#else
#define FUNC_PTR(f) f
#endif

#define LANGUAGE_SELECT_NBR_LANGUAGES (LANGUAGE_COUNT - LANGUAGE_ENGLISH)

#define LANGUAGE_SELECT_CURSOR_X 86
#define LANGUAGE_SELECT_CURSOR_Y 36
#define LANGUAGE_SELECT_ROW_HEIGHT 16

// Graphics and palette, inside sBlob_73421e_73c274 (also present, unused, in the US ROM)
#define sLanguageSelectObjectsGfx ((const u32*)(&sBlob_73c2e4_7406f8[0x193c])) // EU 0x0873e430, US 0x0873dc20
#define sLanguageSelectObjectsPal ((const u16*)(&sBlob_740d08_7478a0[0x0])) // EU 0x08741518, US 0x08740d08

/*
 * EU only: 2 tables inserted at offset 0x1a0 of &sPointers_79e868[0] (EU 0x0879f23c and 0x0879f250),
 * indexed by the language cursor. The frame data is in sBlob_73421e_73c274 (also in the US ROM).
 * PORT: like the file select frame data, the pointed struct FrameData still hold GBA ROM pointers.
 */
static const struct FrameData* const sLanguageSelectCursorOamPointers[LANGUAGE_SELECT_NBR_LANGUAGES] = {
    ((const struct FrameData*)((const u8*)&sFrameData_7406f8[0])), // English
    ((const struct FrameData*)((const u8*)&sFrameData_740708[0])), // German
    ((const struct FrameData*)((const u8*)&sFrameData_740718[0])), // French
    ((const struct FrameData*)((const u8*)&sFrameData_740728[0])), // Italian
    ((const struct FrameData*)((const u8*)&sFrameData_740738[0])), // Spanish
};

static const struct FrameData* const sLanguageSelectSelectedOamPointers[LANGUAGE_SELECT_NBR_LANGUAGES] = {
    ((const struct FrameData*)((const u8*)&sFrameData_740748[0])), // English
    ((const struct FrameData*)((const u8*)&sFrameData_740760[0])), // German
    ((const struct FrameData*)((const u8*)&sFrameData_740778[0])), // French
    ((const struct FrameData*)((const u8*)&sFrameData_740790[0])), // Italian
    ((const struct FrameData*)((const u8*)&sFrameData_7407a8[0])), // Spanish
};

/**
 * @brief a1490 (EU) | a8 | Language select subroutine (replaces the US stub)
 *
 * @param fromTitleScreen 0 = on boot (skipped if a language is already set), 1 = picked on the title screen
 * @return u32 bool, ended
 */
u32 SetLanguage(u8 fromTitleScreen)
{
    u32 ended;

    ended = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            if (fromTitleScreen == FALSE)
            {
                if (LanguageSelectCheckLanguageSet())
                {
                    ended = TRUE;
                    break;
                }
            }

            LanguageSelectInit(fromTitleScreen);
            gSubGameMode1 = 1;
            break;

        case 1:
            FileSelectDrawAllOam();

            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                gSubGameMode1++;
            break;

        case 2:
            if (fromTitleScreen == FALSE ? LanguageSelectProcessFirstBoot() : LanguageSelectProcessFromTitle())
                gSubGameMode1 = 3;
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                ended = TRUE;
                gSubGameMode1 = 0;
            }

            FileSelectProcessOam();
            FileSelectDrawAllOam();
            break;
    }

    return ended;
}

/**
 * @brief a1538 (EU) | 14c | Initializes the language select screen
 *
 * @param fromTitleScreen 0 = on boot, 1 = from the title screen
 */
void LanguageSelectInit(u8 fromTitleScreen)
{
    u32 zero;

    StopAllMusicAndSounds();

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    WRITE_16(REG_DISPCNT, 0);
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    ClearGfxRam();
    gNextOamSlot = 0;
    ResetFreeOam();

    zero = 0;
    DMA_SET(3, &zero, &gNonGameplayRam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, sizeof(gNonGameplayRam) / sizeof(u32)));

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

    LZ77UncompVram(sLanguageSelectObjectsGfx, VRAM_OBJ);
    DMA3_COPY_32(sLanguageSelectObjectsPal, PALRAM_OBJ, 16 * 16 * sizeof(u16) / sizeof(u32));

    FILE_SELECT_DATA.textId = 0;
    FILE_SELECT_DATA.fileCursor = gLanguage - LANGUAGE_ENGLISH;

    if (fromTitleScreen == FALSE)
        LanguageSelectSetupOam(LANGUAGE_SELECT_OAM_TYPE_CURSOR_FIRST_BOOT, LANGUAGE_SELECT_CURSOR_X, LANGUAGE_SELECT_CURSOR_Y);
    else if (fromTitleScreen == TRUE)
        LanguageSelectSetupOam(LANGUAGE_SELECT_OAM_TYPE_CURSOR_FROM_TITLE, LANGUAGE_SELECT_CURSOR_X, LANGUAGE_SELECT_CURSOR_Y);

    FileSelectDrawAllOam();

    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 28, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_OBJ);

    CallbackSetVBlank(FUNC_PTR(LanguageSelectVBlank));
}

/**
 * @brief a1684 (EU) | 2c | V-blank of the language select screen
 *
 */
void LanguageSelectVBlank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

/**
 * @brief a16b0 (EU) | c | Language select, empty v-blank (unused)
 *
 */
void LanguageSelectVBlank_Empty(void)
{
    UpdateAudio();
}

/**
 * @brief a16bc (EU) | 5c | Language select on boot, process
 *
 * @return u32 bool, ended
 */
u32 LanguageSelectProcessFirstBoot(void)
{
    u32 ended;

    ended = FALSE;
    FileSelectProcessOam();

    switch (FILE_SELECT_DATA.stage)
    {
        case 0:
            if (gChangedInput & (KEY_A | KEY_START))
            {
                FILE_SELECT_DATA.stage = 1;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 1:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 16)
            {
                FILE_SELECT_DATA.stage = 100;
                FILE_SELECT_DATA.timer = 0;
                ended = TRUE;
            }
            break;
    }

    FileSelectDrawAllOam();
    return ended;
}

/**
 * @brief a1718 (EU) | 8c | Language select from the title screen, process (B cancels)
 *
 * @return u32 bool, ended
 */
u32 LanguageSelectProcessFromTitle(void)
{
    u32 ended;

    ended = FALSE;

    switch (FILE_SELECT_DATA.stage)
    {
        case 0:
            FileSelectProcessOam();

            if (gChangedInput & (KEY_A | KEY_START))
            {
                FILE_SELECT_DATA.stage = 1;
                FILE_SELECT_DATA.timer = 0;
            }
            else if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 2;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 1:
            FileSelectProcessOam();

            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 16)
            {
                FILE_SELECT_DATA.stage = 100;
                FILE_SELECT_DATA.timer = 0;
                ended = TRUE;
            }
            break;

        case 2:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 4)
            {
                FILE_SELECT_DATA.stage = 100;
                FILE_SELECT_DATA.timer = 0;
                ended = TRUE;
            }
            break;
    }

    FileSelectDrawAllOam();
    return ended;
}

/**
 * @brief a17a4 (EU) | 108 | Sets up a language select OAM object
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @return u8 Allocated slot (FILE_SELECT_OAM_COUNT if none)
 */
u8 LanguageSelectSetupOam(u8 type, u16 xPosition, u16 yPosition)
{
    u8 i;
    u32 zero;
    struct FileSelectOam* pOam;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].type == LANGUAGE_SELECT_OAM_TYPE_NONE)
            break;
    }

    if (i >= FILE_SELECT_OAM_COUNT)
        return FILE_SELECT_OAM_COUNT;

    pOam = &FILE_SELECT_DATA.oam[i];

    zero = 0;
    DMA_SET(3, &zero, pOam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x1C / sizeof(u32)));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->drawn = TRUE;

    if (type == LANGUAGE_SELECT_OAM_TYPE_CURSOR_FIRST_BOOT)
    {
        pOam->priority = 1;
        pOam->pOam = sLanguageSelectCursorOamPointers[FILE_SELECT_DATA.fileCursor];
        pOam->pFunc = FUNC_PTR(LanguageSelectProcessCursorFirstBoot);
    }
    else if (type == LANGUAGE_SELECT_OAM_TYPE_SELECTED)
    {
        pOam->pOam = sLanguageSelectSelectedOamPointers[FILE_SELECT_DATA.fileCursor];
        pOam->pFunc = FUNC_PTR(LanguageSelectProcessSelected);
    }
    else if (type == LANGUAGE_SELECT_OAM_TYPE_CURSOR_FROM_TITLE)
    {
        pOam->priority = 1;
        pOam->pOam = sLanguageSelectCursorOamPointers[FILE_SELECT_DATA.fileCursor];
        pOam->pFunc = FUNC_PTR(LanguageSelectProcessCursorFromTitle);
    }

    return i;
}

/**
 * @brief Moves the language cursor and applies the language when A/Start is pressed
 * (shared start of the two cursor objects)
 *
 * @param pOam Cursor object
 * @return u32 bool, a language was picked
 */
static u32 LanguageSelectMoveCursorAndPick(struct FileSelectOam* pOam)
{
    if (gChangedInput & KEY_UP)
    {
        if (FILE_SELECT_DATA.fileCursor != 0)
        {
            FILE_SELECT_DATA.fileCursor--;
            SoundPlay(SOUND_1F9);
        }
    }
    else if (gChangedInput & KEY_DOWN)
    {
        if (FILE_SELECT_DATA.fileCursor < LANGUAGE_SELECT_NBR_LANGUAGES - 1)
        {
            FILE_SELECT_DATA.fileCursor++;
            SoundPlay(SOUND_1F9);
        }
    }

    pOam->pOam = sLanguageSelectCursorOamPointers[FILE_SELECT_DATA.fileCursor];

    if (gChangedInput & (KEY_A | KEY_START))
    {
        gLanguage = FILE_SELECT_DATA.fileCursor + LANGUAGE_ENGLISH;
        SramWrite_Language();

        LanguageSelectSetupOam(LANGUAGE_SELECT_OAM_TYPE_SELECTED, LANGUAGE_SELECT_CURSOR_X,
            (s16)(FILE_SELECT_DATA.fileCursor * LANGUAGE_SELECT_ROW_HEIGHT + LANGUAGE_SELECT_CURSOR_Y));

        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        SoundPlay(SOUND_1FB);
        pOam->stage = 1;
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief a18ac (EU) | e0 | Processes the language cursor (on boot)
 *
 * @param pOam Cursor object
 */
void LanguageSelectProcessCursorFirstBoot(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        LanguageSelectMoveCursorAndPick(pOam);
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.timer == 15)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
        }
    }
    else
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}

/**
 * @brief a198c (EU) | f4 | Processes the language cursor (from the title screen, B cancels)
 *
 * @param pOam Cursor object
 */
void LanguageSelectProcessCursorFromTitle(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (!LanguageSelectMoveCursorAndPick(pOam))
        {
            if (gChangedInput & KEY_B)
                pOam->stage = 10;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.timer == 15)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
        }
    }
    else if (pOam->stage != 10)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}

/**
 * @brief a1a80 (EU) | 38 | Processes the "language selected" object
 *
 * @param pOam Selected object
 */
void LanguageSelectProcessSelected(struct FileSelectOam* pOam)
{
    pOam->unk_8++;

    if (pOam->stage == 0)
    {
        if (pOam->unk_8 == 3)
        {
            pOam->unk_8 = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (pOam->unk_8 == 3)
        {
            pOam->unk_8 = 0;
            pOam->stage = 0;
        }
    }
}

/**
 * @brief a1ab8 (EU) | 24 | Checks if a valid language is set, defaults to english if not
 *
 * @return u32 bool, language already set
 */
u32 LanguageSelectCheckLanguageSet(void)
{
    u32 set;

    set = FALSE;

    if (gLanguage > LANGUAGE_HIRAGANA)
        set = TRUE;
    else
        gLanguage = LANGUAGE_ENGLISH;

    return set;
}

#endif /* REGION_EU */
