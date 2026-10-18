#include "file_select.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "callbacks.h"
#include "oam.h"
#include "text.h"
#include "syscalls.h"
#include "init_helpers.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"
#include "audio/track_internal.h"

#include "constants/game_state.h"
#include "structs/save_file.h"

#ifndef PLATFORM_PC
asm(".set gFileSelectFileInfo, 0x03000b94");
#endif

#ifdef FILE_SELECT_EQUIV
// Equivalence testing only: store the original ROM addresses of the callbacks so that
// the RAM written by the C version is identical to the original
void FileSelectProcessSamusHead_Orig(struct FileSelectOam* pOam);
void FileSelectProcessCursor_Orig(struct FileSelectOam* pOam);
void FileSelectProcessDeleteArrow_Orig(struct FileSelectOam* pOam);
void unk_9fddc_Orig(struct FileSelectOam* pOam);
void unk_9ff00_Orig(struct FileSelectOam* pOam);
void FileSelectProcessAudioLogos_Orig(struct FileSelectOam* pOam);
void FileSelectProcessAudioSelect_Orig(struct FileSelectOam* pOam);
void FileSelectProcessFileOverlay_Orig(struct FileSelectOam* pOam);
void unk_a016c_Orig(struct FileSelectOam* pOam);
void unk_a01cc_Orig(struct FileSelectOam* pOam);
void FileSelectProcessFileActionPanel_Orig(struct FileSelectOam* pOam);
void FileSelectProcessCopyFilePanel_Orig(struct FileSelectOam* pOam);
void FileSelectProcessEraseFilePanel_Orig(struct FileSelectOam* pOam);
void unk_a039c_Orig(struct FileSelectOam* pOam);
void unk_a0424_Orig(struct FileSelectOam* pOam);
void unk_a0518_Orig(struct FileSelectOam* pOam);
void FileSelectVblank_Orig(void);
void unk_9eaa4_Orig(void);
void unk_a1478_Orig(void);
asm(".set FileSelectProcessSamusHead_Orig, 0x0809f931");
asm(".set FileSelectProcessCursor_Orig, 0x0809fad5");
asm(".set FileSelectProcessDeleteArrow_Orig, 0x0809fc91");
asm(".set unk_9fddc_Orig, 0x0809fddd");
asm(".set unk_9ff00_Orig, 0x0809ff01");
asm(".set FileSelectProcessAudioLogos_Orig, 0x080a0025");
asm(".set FileSelectProcessAudioSelect_Orig, 0x080a00e5");
asm(".set FileSelectProcessFileOverlay_Orig, 0x080a0145");
asm(".set unk_a016c_Orig, 0x080a016d");
asm(".set unk_a01cc_Orig, 0x080a01cd");
asm(".set FileSelectProcessFileActionPanel_Orig, 0x080a01d1");
asm(".set FileSelectProcessCopyFilePanel_Orig, 0x080a026d");
asm(".set FileSelectProcessEraseFilePanel_Orig, 0x080a0305");
asm(".set unk_a039c_Orig, 0x080a039d");
asm(".set unk_a0424_Orig, 0x080a0425");
asm(".set unk_a0518_Orig, 0x080a0519");
asm(".set FileSelectVblank_Orig, 0x0809e9e1");
asm(".set unk_9eaa4_Orig, 0x0809eaa5");
asm(".set unk_a1478_Orig, 0x080a1479");
#define FUNC_PTR(f) f##_Orig
#else
#define FUNC_PTR(f) f
#endif

/*
 * Typed copies of the pointer tables stored in sBlob_79e868_79eca0 (src/new_file_intro.c),
 * the pointed data is in sBlob_73421e_7478a0.
 * PORT: the struct FrameData tables pointed to still hold GBA ROM pointers (see file_select.h).
 */
static const u16* const sFileSelectTexts_879ea08[25] = { // 0x0879ea08
    (const u16*)BLOB_73421E(0xccea),
    (const u16*)BLOB_73421E(0xcd1c),
    (const u16*)BLOB_73421E(0xcd46),
    (const u16*)BLOB_73421E(0xcd64),
    (const u16*)BLOB_73421E(0xcda6),
    (const u16*)BLOB_73421E(0xcdd6),
    (const u16*)BLOB_73421E(0xce18),
    (const u16*)BLOB_73421E(0xce5a),
    (const u16*)BLOB_73421E(0xce9c),
    (const u16*)BLOB_73421E(0xcede),
    (const u16*)BLOB_73421E(0xcf20),
    (const u16*)BLOB_73421E(0xcf62),
    (const u16*)BLOB_73421E(0xcf78),
    (const u16*)BLOB_73421E(0xcf80),
    (const u16*)BLOB_73421E(0xcf94),
    (const u16*)BLOB_73421E(0xcfbc),
    (const u16*)BLOB_73421E(0xcfdc),
    (const u16*)BLOB_73421E(0xcff0),
    (const u16*)BLOB_73421E(0xd03a),
    (const u16*)BLOB_73421E(0xd062),
    (const u16*)BLOB_73421E(0xd0b0),
    (const u16*)BLOB_73421E(0xd0ce),
    (const u16*)BLOB_73421E(0xd0f0),
    (const u16*)BLOB_73421E(0xd116),
    (const u16*)BLOB_73421E(0xd12e),
};
static const u16* const sFileSelectTexts_879ea6c[25] = { // 0x0879ea6c
    (const u16*)BLOB_73421E(0xd146),
    (const u16*)BLOB_73421E(0xd17a),
    (const u16*)BLOB_73421E(0xd1b0),
    (const u16*)BLOB_73421E(0xd1f2),
    (const u16*)BLOB_73421E(0xd248),
    (const u16*)BLOB_73421E(0xd27e),
    (const u16*)BLOB_73421E(0xd2d8),
    (const u16*)BLOB_73421E(0xd332),
    (const u16*)BLOB_73421E(0xd38c),
    (const u16*)BLOB_73421E(0xd3f0),
    (const u16*)BLOB_73421E(0xd454),
    (const u16*)BLOB_73421E(0xd4b8),
    (const u16*)BLOB_73421E(0xd4ce),
    (const u16*)BLOB_73421E(0xd4ec),
    (const u16*)BLOB_73421E(0xd500),
    (const u16*)BLOB_73421E(0xd528),
    (const u16*)BLOB_73421E(0xd548),
    (const u16*)BLOB_73421E(0xd55c),
    (const u16*)BLOB_73421E(0xd5a6),
    (const u16*)BLOB_73421E(0xd5d0),
    (const u16*)BLOB_73421E(0xd5f6),
    (const u16*)BLOB_73421E(0xd612),
    (const u16*)BLOB_73421E(0xd63c),
    (const u16*)BLOB_73421E(0xd666),
    (const u16*)BLOB_73421E(0xd696),
};
static const u16* const sFileSelectTexts_879ead0[25] = { // 0x0879ead0
    (const u16*)BLOB_73421E(0xd6be),
    (const u16*)BLOB_73421E(0xd6fa),
    (const u16*)BLOB_73421E(0xd728),
    (const u16*)BLOB_73421E(0xd760),
    (const u16*)BLOB_73421E(0xd7b6),
    (const u16*)BLOB_73421E(0xd7f6),
    (const u16*)BLOB_73421E(0xd858),
    (const u16*)BLOB_73421E(0xd8ba),
    (const u16*)BLOB_73421E(0xd91c),
    (const u16*)BLOB_73421E(0xd97a),
    (const u16*)BLOB_73421E(0xd9d8),
    (const u16*)BLOB_73421E(0xda36),
    (const u16*)BLOB_73421E(0xda50),
    (const u16*)BLOB_73421E(0xda72),
    (const u16*)BLOB_73421E(0xda94),
    (const u16*)BLOB_73421E(0xdabe),
    (const u16*)BLOB_73421E(0xdaec),
    (const u16*)BLOB_73421E(0xdb0a),
    (const u16*)BLOB_73421E(0xdb32),
    (const u16*)BLOB_73421E(0xdb64),
    (const u16*)BLOB_73421E(0xdb94),
    (const u16*)BLOB_73421E(0xdbb8),
    (const u16*)BLOB_73421E(0xdbd4),
    (const u16*)BLOB_73421E(0xdc06),
    (const u16*)BLOB_73421E(0xdc2a),
};
static const u16* const sFileSelectTexts_879eb34[25] = { // 0x0879eb34
    (const u16*)BLOB_73421E(0xdc64),
    (const u16*)BLOB_73421E(0xdca6),
    (const u16*)BLOB_73421E(0xdcd0),
    (const u16*)BLOB_73421E(0xdd14),
    (const u16*)BLOB_73421E(0xdd62),
    (const u16*)BLOB_73421E(0xdda0),
    (const u16*)BLOB_73421E(0xde0c),
    (const u16*)BLOB_73421E(0xde78),
    (const u16*)BLOB_73421E(0xdee4),
    (const u16*)BLOB_73421E(0xdf44),
    (const u16*)BLOB_73421E(0xdfa4),
    (const u16*)BLOB_73421E(0xe004),
    (const u16*)BLOB_73421E(0xe026),
    (const u16*)BLOB_73421E(0xe052),
    (const u16*)BLOB_73421E(0xe07e),
    (const u16*)BLOB_73421E(0xe0a2),
    (const u16*)BLOB_73421E(0xe0d4),
    (const u16*)BLOB_73421E(0xe0fa),
    (const u16*)BLOB_73421E(0xe130),
    (const u16*)BLOB_73421E(0xe144),
    (const u16*)BLOB_73421E(0xe168),
    (const u16*)BLOB_73421E(0xe18c),
    (const u16*)BLOB_73421E(0xe1b6),
    (const u16*)BLOB_73421E(0xe1d8),
    (const u16*)BLOB_73421E(0xe202),
};
static const u16* const sFileSelectTexts_879eb98[25] = { // 0x0879eb98
    (const u16*)BLOB_73421E(0xe22e),
    (const u16*)BLOB_73421E(0xe268),
    (const u16*)BLOB_73421E(0xe2a2),
    (const u16*)BLOB_73421E(0xe2e0),
    (const u16*)BLOB_73421E(0xe330),
    (const u16*)BLOB_73421E(0xe368),
    (const u16*)BLOB_73421E(0xe3d4),
    (const u16*)BLOB_73421E(0xe440),
    (const u16*)BLOB_73421E(0xe4ac),
    (const u16*)BLOB_73421E(0xe510),
    (const u16*)BLOB_73421E(0xe574),
    (const u16*)BLOB_73421E(0xe5d8),
    (const u16*)BLOB_73421E(0xe5ee),
    (const u16*)BLOB_73421E(0xe60e),
    (const u16*)BLOB_73421E(0xe622),
    (const u16*)BLOB_73421E(0xe64c),
    (const u16*)BLOB_73421E(0xe680),
    (const u16*)BLOB_73421E(0xe6a6),
    (const u16*)BLOB_73421E(0xe6ec),
    (const u16*)BLOB_73421E(0xe71a),
    (const u16*)BLOB_73421E(0xe746),
    (const u16*)BLOB_73421E(0xe764),
    (const u16*)BLOB_73421E(0xe78e),
    (const u16*)BLOB_73421E(0xe7be),
    (const u16*)BLOB_73421E(0xe7e2),
};
static const u16* const sFileSelectTexts_879ebfc[25] = { // 0x0879ebfc
    (const u16*)BLOB_73421E(0xe80a),
    (const u16*)BLOB_73421E(0xe848),
    (const u16*)BLOB_73421E(0xe870),
    (const u16*)BLOB_73421E(0xe8a2),
    (const u16*)BLOB_73421E(0xe8fa),
    (const u16*)BLOB_73421E(0xe932),
    (const u16*)BLOB_73421E(0xe98c),
    (const u16*)BLOB_73421E(0xe9e6),
    (const u16*)BLOB_73421E(0xea40),
    (const u16*)BLOB_73421E(0xea9c),
    (const u16*)BLOB_73421E(0xeaf8),
    (const u16*)BLOB_73421E(0xeb56),
    (const u16*)BLOB_73421E(0xeb6c),
    (const u16*)BLOB_73421E(0xeb84),
    (const u16*)BLOB_73421E(0xebaa),
    (const u16*)BLOB_73421E(0xebc6),
    (const u16*)BLOB_73421E(0xebda),
    (const u16*)BLOB_73421E(0xebfa),
    (const u16*)BLOB_73421E(0xec2e),
    (const u16*)BLOB_73421E(0xec5e),
    (const u16*)BLOB_73421E(0xec7e),
    (const u16*)BLOB_73421E(0xeca8),
    (const u16*)BLOB_73421E(0xecd0),
    (const u16*)BLOB_73421E(0xecf6),
    (const u16*)BLOB_73421E(0xed24),
};
static const u16* const* const sFileSelectTextPointers[LANGUAGE_COUNT] = { // 0x0879ec68
    sFileSelectTexts_879ea08,
    sFileSelectTexts_879ea08,
    sFileSelectTexts_879ea6c,
    sFileSelectTexts_879ead0,
    sFileSelectTexts_879eb34,
    sFileSelectTexts_879eb98,
    sFileSelectTexts_879ebfc,
};

static const u16* const sFileSelectNoDataTexts_879ec60[2] = { // 0x0879ec60
    (const u16*)BLOB_73421E(0xed48),
    (const u16*)BLOB_73421E(0xed5c),
};
static const u16* const* const sFileSelectNoDataTextPointers[LANGUAGE_COUNT] = { // 0x0879ec84
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
    sFileSelectNoDataTexts_879ec60,
};

static const u16* const sFileSelectTextLineOffsets_879e8c8[6] = { // 0x0879e8c8
    (const u16*)BLOB_73421E(0x99ae),
    (const u16*)BLOB_73421E(0x99ba),
    (const u16*)BLOB_73421E(0x99c0),
    (const u16*)BLOB_73421E(0x99c0),
    (const u16*)BLOB_73421E(0x99c0),
    (const u16*)BLOB_73421E(0x99c6),
};
static const u16* const sFileSelectTextLineOffsets_879e8e0[6] = { // 0x0879e8e0
    (const u16*)BLOB_73421E(0x99cc),
    (const u16*)BLOB_73421E(0x99d8),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99e4),
};
static const u16* const sFileSelectTextLineOffsets_879e8f8[6] = { // 0x0879e8f8
    (const u16*)BLOB_73421E(0x99ea),
    (const u16*)BLOB_73421E(0x99d8),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99e4),
};
static const u16* const sFileSelectTextLineOffsets_879e910[6] = { // 0x0879e910
    (const u16*)BLOB_73421E(0x99f6),
    (const u16*)BLOB_73421E(0x99d8),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99de),
    (const u16*)BLOB_73421E(0x99e4),
};
static const u16* const* const sFileSelectTextLineOffsetPointers[LANGUAGE_COUNT] = { // 0x0879e928
    sFileSelectTextLineOffsets_879e8c8,
    sFileSelectTextLineOffsets_879e8c8,
    sFileSelectTextLineOffsets_879e8e0,
    sFileSelectTextLineOffsets_879e8e0,
    sFileSelectTextLineOffsets_879e8f8,
    sFileSelectTextLineOffsets_879e8e0,
    sFileSelectTextLineOffsets_879e910,
};

static const struct FrameData* const sFileSelectAreaNameOamPointers[LANGUAGE_COUNT][7] = { // 0x0879e944
    (const struct FrameData*)BLOB_73421E(0xc81a),
    (const struct FrameData*)BLOB_73421E(0xc7ba),
    (const struct FrameData*)BLOB_73421E(0xc7ca),
    (const struct FrameData*)BLOB_73421E(0xc7da),
    (const struct FrameData*)BLOB_73421E(0xc7ea),
    (const struct FrameData*)BLOB_73421E(0xc7fa),
    (const struct FrameData*)BLOB_73421E(0xc80a),
    (const struct FrameData*)BLOB_73421E(0xc81a),
    (const struct FrameData*)BLOB_73421E(0xc7ba),
    (const struct FrameData*)BLOB_73421E(0xc7ca),
    (const struct FrameData*)BLOB_73421E(0xc7da),
    (const struct FrameData*)BLOB_73421E(0xc7ea),
    (const struct FrameData*)BLOB_73421E(0xc7fa),
    (const struct FrameData*)BLOB_73421E(0xc80a),
    (const struct FrameData*)BLOB_73421E(0xc81a),
    (const struct FrameData*)BLOB_73421E(0xc7ba),
    (const struct FrameData*)BLOB_73421E(0xc7ca),
    (const struct FrameData*)BLOB_73421E(0xc7da),
    (const struct FrameData*)BLOB_73421E(0xc7ea),
    (const struct FrameData*)BLOB_73421E(0xc7fa),
    (const struct FrameData*)BLOB_73421E(0xc80a),
    (const struct FrameData*)BLOB_73421E(0xc9ea),
    (const struct FrameData*)BLOB_73421E(0xc98a),
    (const struct FrameData*)BLOB_73421E(0xc99a),
    (const struct FrameData*)BLOB_73421E(0xc9aa),
    (const struct FrameData*)BLOB_73421E(0xc9ba),
    (const struct FrameData*)BLOB_73421E(0xc9ca),
    (const struct FrameData*)BLOB_73421E(0xc9da),
    (const struct FrameData*)BLOB_73421E(0xca5a),
    (const struct FrameData*)BLOB_73421E(0xc9fa),
    (const struct FrameData*)BLOB_73421E(0xca0a),
    (const struct FrameData*)BLOB_73421E(0xca1a),
    (const struct FrameData*)BLOB_73421E(0xca2a),
    (const struct FrameData*)BLOB_73421E(0xca3a),
    (const struct FrameData*)BLOB_73421E(0xca4a),
    (const struct FrameData*)BLOB_73421E(0xcaca),
    (const struct FrameData*)BLOB_73421E(0xca6a),
    (const struct FrameData*)BLOB_73421E(0xca7a),
    (const struct FrameData*)BLOB_73421E(0xca8a),
    (const struct FrameData*)BLOB_73421E(0xca9a),
    (const struct FrameData*)BLOB_73421E(0xcaaa),
    (const struct FrameData*)BLOB_73421E(0xcaba),
    (const struct FrameData*)BLOB_73421E(0xcada),
    (const struct FrameData*)BLOB_73421E(0xc7ba),
    (const struct FrameData*)BLOB_73421E(0xc7ca),
    (const struct FrameData*)BLOB_73421E(0xc7da),
    (const struct FrameData*)BLOB_73421E(0xc7ea),
    (const struct FrameData*)BLOB_73421E(0xc7fa),
    (const struct FrameData*)BLOB_73421E(0xc80a),
};

static const struct FrameData* const sFileSelectFileOverlayOamPointers[5] = { // 0x0879e890
    (const struct FrameData*)BLOB_73421E(0xc89a),
    (const struct FrameData*)BLOB_73421E(0xc8aa),
    (const struct FrameData*)BLOB_73421E(0xc8ba),
    (const struct FrameData*)BLOB_73421E(0xc6a2),
    (const struct FrameData*)BLOB_73421E(0xc6a2),
};

static const struct FrameData* const sFileSelectCopyArrowOamPointers[3][3] = { // 0x0879e8a4
    (const struct FrameData*)BLOB_73421E(0xc5e2),
    (const struct FrameData*)BLOB_73421E(0xc5e2),
    (const struct FrameData*)BLOB_73421E(0xc602),
    (const struct FrameData*)BLOB_73421E(0xc622),
    (const struct FrameData*)BLOB_73421E(0xc622),
    (const struct FrameData*)BLOB_73421E(0xc8ca),
    (const struct FrameData*)BLOB_73421E(0xc8ea),
    (const struct FrameData*)BLOB_73421E(0xc90a),
    (const struct FrameData*)BLOB_73421E(0xc90a),
};


#define FILE_SELECT_TEXT_CURSOR_NORMALIZE()             \
{                                                       \
    while (FILE_SELECT_DATA.textPixelOffset > 7)        \
    {                                                   \
        FILE_SELECT_DATA.textPixelOffset -= 8;          \
        FILE_SELECT_DATA.textTileX++;                   \
    }                                                   \
}

#define FILE_SELECT_ANIM_ENDED(pOam) \
    ((pOam)->pOam[(pOam)->currentAnimationFrame].timer == (pOam)->animationDurationCounter && \
    (pOam)->pOam[(pOam)->currentAnimationFrame + 1].timer == 0)

#define FILE_SELECT_FILE_IS_STARTED(pInfo) \
    ((s8)(pInfo)->completedGame == TRUE || (s8)(pInfo)->introPlayed == TRUE || (pInfo)->exists == TRUE)

/**
 * @brief 9e598 | 1b8 | File select main loop
 *
 * @return s8 Result of the file select (0 = running)
 */
s8 FileSelectHandler(void)
{
    s8 result;

    result = 0;

    switch (gSubGameMode1)
    {
        case 0:
            FileSelectInit();
            if (gFileSelectFileInfo[0].corruptionFlag == 0 && gFileSelectFileInfo[1].corruptionFlag == 0 &&
                gFileSelectFileInfo[2].corruptionFlag == 0)
            {
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_SAMUS_HEAD, 0xF, (s16)(gMostRecentSaveFile * 16 + 0x31), 0);
                WRITE_16(REG_BG1HOFS, 2);
                gSubGameMode1 = 1;
            }
            else
            {
                WRITE_16(REG_BG1HOFS, 0xFFD0);
                WRITE_16(REG_BG1VOFS, 0x30);
                gSubGameMode1 = 5;
            }
            break;

        case 1:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDrawText(1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectDrawFileInfo(0);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FileSelectDrawFileInfo(1);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                FileSelectDrawFileInfo(2);
                FILE_SELECT_DATA.timer = 0;
                gWrittenToBldy = 14;
                gSubGameMode1 = 2;
            }
            break;

        case 2:
            FileSelectDrawAllOam();
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                gSubGameMode1++;
            break;

        case 3:
            FILE_SELECT_DATA.result = FileSelectInput();
            if ((u8)FILE_SELECT_DATA.result != 0)
            {
                gSubGameMode1++;
                FadeMusic(20);
            }
            break;

        case 4:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else
            {
                result = FILE_SELECT_DATA.result;
                gSubGameMode1 = 0;
            }
            break;

        case 5:
            if (FileSelectProcessCorruptedFile())
            {
                WRITE_16(REG_BG1HOFS, 2);
                WRITE_16(REG_BG1VOFS, 0xFFFA);
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_SAMUS_HEAD, 0xF, (s16)(gMostRecentSaveFile * 16 + 0x31), 0);
                gSubGameMode1 = 3;
            }
            break;
    }

    return result;
}

/**
 * @brief 9e750 | 290 | Initializes the file select
 *
 */
void FileSelectInit(void)
{
    u32 zero;
    u32 i;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(FUNC_PTR(unk_9eaa4));
    WRITE_16(REG_DISPCNT, 0);

    WRITE_16(REG_BLDCNT, 0xFF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

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
    WRITE_16(REG_BG1VOFS, 0xFFFA);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    LZ77UncompVram(sFileSelectBgGfx, VRAM_BASE);
    LZ77UncompVram(sFileSelectBg3TileTable, VRAM_BASE + 0xF800);
    DMA3_COPY_32(sFileSelectBgPal, PALRAM_BASE, 0x200 / sizeof(u32));
    LZ77UncompVram(sFileSelectBg2TileTable, VRAM_BASE + 0xE000);

    // The BG1 tile table is decompressed in EWRAM (also used as a source for the action panel)
    LZ77UncompVram(sFileSelectBg1TileTable, EWRAM_BASE);
    DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xE800, 0x800 / sizeof(u32));
    LZ77UncompVram(sFileSelectBg0TileTable, VRAM_BASE + 0xF000);

    DMA3_COPY_32(sFileSelectBgPalRow0, PALRAM_BASE, 0x20 / sizeof(u32));
    DMA3_COPY_32(sFileSelectBgPalOverride, PALRAM_BASE, 8 / sizeof(u32));
    DMA3_COPY_32(sFileSelectBgPalOverride + 8, PALRAM_BASE + 0x1C, 4 / sizeof(u32));
    WRITE_16(PALRAM_BASE, 0);

    // Copy of the action panel tile table with palette 1
    for (i = 0; i < 0x100; i += 2)
        *(u16*)((u8*)EWRAM_BASE + 0x800 + i) = (*(u16*)((u8*)EWRAM_BASE + 0x340 + i) & 0xFFF) | 0x1000;

    LZ77UncompVram(sFileSelectObjGfx, VRAM_OBJ);
    DMA3_COPY_32(sFileSelectObjPal, PALRAM_OBJ, 0x200 / sizeof(u32));

    FILE_SELECT_DATA.textId = 0;
    FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][0];

    Sram_WriteFileInfo();
    FILE_SELECT_DATA.fileCursor = gMostRecentSaveFile;

    FileSelectSetupOam(FILE_SELECT_OAM_TYPE_AUDIO_SELECT, 0x66, 0x74, 1);
    FileSelectSetupOam(FILE_SELECT_OAM_TYPE_AUDIO_LOGOS, 0x8E, 0x74, 1);
    FileSelectSetupOam(FILE_SELECT_OAM_TYPE_FILE_OVERLAY, 0x84, 0x30, 1);
    FileSelectDrawAllOam();

    WRITE_16(REG_BG3CNT, 0x1F03);
    WRITE_16(REG_BG2CNT, 0x1C0A);
    WRITE_16(REG_BG1CNT, 0x1D09);
    WRITE_16(REG_BG0CNT, 0x1E08);
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(FUNC_PTR(FileSelectVblank));
}

/**
 * @brief 9e9e0 | c4 | V-blank code of the file select
 *
 */
void FileSelectVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    switch (FILE_SELECT_DATA.bgToggle)
    {
        case 0:
            break;

        case 1:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            FILE_SELECT_DATA.bgToggle = 0;
            break;

        case 3:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            FILE_SELECT_DATA.bgToggle = 0;
            break;

        case 2:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
            FILE_SELECT_DATA.bgToggle = 0;
            break;

        case 4:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
            FILE_SELECT_DATA.bgToggle = 0;
            break;

        case 5:
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1));
            FILE_SELECT_DATA.bgToggle = 0;
            break;

        default:
            FILE_SELECT_DATA.bgToggle = 0;
            break;
    }
}

/**
 * @brief 9eaa4 | c | V-blank code of the file select during init
 *
 */
void unk_9eaa4(void)
{
    UpdateAudio();
}

static void FileSelectClearTextBg(void)
{
    u32 zero;

    zero = 0;
    DMA_SET(3, &zero, VRAM_BASE + 0xC800, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x1800 / sizeof(u32)));
}

/**
 * @brief 9eab0 | a68 | Handles the file select menus
 *
 * @return u8 0 = running, 1 = start a saved game, 2 = start a new game, 3 = back to the title
 */
u8 FileSelectInput(void)
{
    u8 result;
    struct FileSelectFileInfo* pInfo;

    result = 0;
    FileSelectProcessOam();

    switch (FILE_SELECT_DATA.stage)
    {
        case 0:
            if (gChangedInput & (KEY_A | KEY_START))
            {
                if (FILE_SELECT_DATA.fileCursor == 3)
                    break;

                if (FILE_SELECT_DATA.fileCursor == 4)
                {
                    FILE_SELECT_DATA.stage = 34;
                    break;
                }

                FILE_SELECT_DATA.stage = 1;
                break;
            }

            if (gChangedInput & KEY_B)
                FILE_SELECT_DATA.stage = 34;
            break;

        case 1:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.textId = 1;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][1];
                FileSelectDrawText(2);
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_FILE_ACTION_PANEL, 0x52, 0x76, 1);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                pInfo = &gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor];
                if (FILE_SELECT_FILE_IS_STARTED(pInfo))
                {
                    DMA3_COPY_32((u8*)EWRAM_BASE + 0x340, VRAM_BASE + 0xEB40, 0x100 / sizeof(u32));
                    FILE_SELECT_DATA.stage = 3;
                }
                else
                {
                    DMA3_COPY_32((u8*)EWRAM_BASE + 0x800, VRAM_BASE + 0xEB40, 0x100 / sizeof(u32));
                    FILE_SELECT_DATA.stage = 2;
                }

                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.actionCursor = 0;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_ACTION_CURSOR, 0x16, 0x67, 1);
                FILE_SELECT_DATA.bgToggle = 3;
            }
            break;

        case 2:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 4;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            if ((s8)gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].completedGame == TRUE)
                FILE_SELECT_DATA.stage = 9;
            else
                FILE_SELECT_DATA.stage = 5;
            break;

        case 3:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 4;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            if (FILE_SELECT_DATA.actionCursor == 0)
            {
                pInfo = &gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor];
                if (pInfo->exists == FALSE)
                {
                    if ((s8)pInfo->completedGame == TRUE)
                        FILE_SELECT_DATA.stage = 9;
                    else if ((s8)pInfo->introPlayed == TRUE)
                        FILE_SELECT_DATA.stage = 5;
                }
                else if (pInfo->exists == TRUE)
                {
                    if ((s8)pInfo->completedGame == TRUE)
                        FILE_SELECT_DATA.stage = 9;
                    else
                        FILE_SELECT_DATA.stage = 7;
                }
            }
            else if (FILE_SELECT_DATA.actionCursor == 1)
            {
                FILE_SELECT_DATA.stage = 16;
                FILE_SELECT_DATA.timer = 0;
            }
            else if (FILE_SELECT_DATA.actionCursor == 2)
            {
                FILE_SELECT_DATA.stage = 27;
            }
            break;

        case 4:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ACTION_CURSOR);
                FILE_SELECT_DATA.bgToggle = 4;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 0;
            }
            break;

        case 5:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.stage = 6;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 7:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.stage = 8;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 6:
        case 15:
            gMostRecentSaveFile = FILE_SELECT_DATA.fileCursor;
            Sram_CheckLoadSaveFile();
            result = 1;
            break;

        case 8:
        case 14:
            gMostRecentSaveFile = FILE_SELECT_DATA.fileCursor;
            Sram_CheckLoadSaveFile();
            result = 2;
            break;

        case 9:
            // Start over on a completed file
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_NEW_GAME_PANEL, 0x9C, 0x78, 1);
                FILE_SELECT_DATA.bgToggle = 2;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.textId = 24;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][24];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 10;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_NEW_GAME_YES_NO_CURSOR, 0x66, 0x69, 1);
                FILE_SELECT_DATA.bgToggle = 1;
            }
            break;

        case 10:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 11;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            if (FILE_SELECT_DATA.yesNoCursor == 0)
                FILE_SELECT_DATA.stage = 12;
            else
                FILE_SELECT_DATA.stage = 13;
            break;

        case 11:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_NEW_GAME_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 2;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.stage = 3;
            }
            break;

        case 12:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.timer = 0;
                if (gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].exists == TRUE)
                    FILE_SELECT_DATA.stage = 14;
                else
                    FILE_SELECT_DATA.stage = 15;
            }
            break;

        case 13:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].exists = FALSE;
                gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].introPlayed = FALSE;
            }
            else if (FILE_SELECT_DATA.timer == 42)
            {
                FILE_SELECT_DATA.stage = 15;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 16:
            // Copy
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.bgToggle = 2;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_COPY_FILE_PANEL, 0x9C, 0x78, 1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.textId = 2;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][2];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.stage = 17;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.copyTarget = 0;
                if (FILE_SELECT_DATA.fileCursor == 0)
                    FILE_SELECT_DATA.copyTarget = 1;

                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_COPY_ARROW, 0x84, 0x30, 1);
                FILE_SELECT_DATA.bgToggle = 1;
            }
            break;

        case 17:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 18;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            pInfo = &gFileSelectFileInfo[FILE_SELECT_DATA.copyTarget];
            if (FILE_SELECT_FILE_IS_STARTED(pInfo))
                FILE_SELECT_DATA.stage = 19;
            else
                FILE_SELECT_DATA.stage = 20;
            break;

        case 18:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_COPY_ARROW);
                FILE_SELECT_DATA.bgToggle = 2;
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 3;
            }
            break;

        case 19:
            // Copy over an existing file, confirm
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.bgToggle = 2;
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FILE_SELECT_DATA.textId = 3;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][3];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                FILE_SELECT_DATA.bgToggle = 1;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 22;
                FILE_SELECT_DATA.yesNoCursor = 1;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_COPY_YES_NO_CURSOR,
                    sFileSelectCopyYesNoXPositions[gLanguage * 2 + 1], 0x91, 1);
            }
            break;

        case 20:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.fileCursor;
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 3);
            }
            else if (FILE_SELECT_DATA.timer == 6)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.copyTarget);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 21;
            }
            break;

        case 21:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FILE_SELECT_DATA.bgToggle = 5;
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ACTION_CURSOR);
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_COPY_ARROW);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.copyTarget = 0;
                FILE_SELECT_DATA.actionCursor = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 0;
            }
            break;

        case 22:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 23;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            if (FILE_SELECT_DATA.yesNoCursor == 0)
                FILE_SELECT_DATA.stage = 25;
            else
                FILE_SELECT_DATA.stage = 24;
            break;

        case 23:
        case 24:
            // Back to the copy target selection (24 : with a delay)
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == (FILE_SELECT_DATA.stage == 23 ? 1 : 9))
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_COPY_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 2;
            }
            else if (FILE_SELECT_DATA.timer == (FILE_SELECT_DATA.stage == 23 ? 2 : 10))
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == (FILE_SELECT_DATA.stage == 23 ? 3 : 11))
            {
                FILE_SELECT_DATA.textId = 2;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][2];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.bgToggle = 1;
                FILE_SELECT_DATA.stage = 17;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.yesNoCursor = 0;
            }
            break;

        case 25:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.fileCursor;
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_CopyFile(FILE_SELECT_DATA.copyTarget, 3);
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.copyTarget);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.stage = 26;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 26:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ACTION_CURSOR);
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_COPY_ARROW);
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_COPY_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 5;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.copyTarget = 0;
                FILE_SELECT_DATA.actionCursor = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 0;
            }
            break;

        case 27:
            // Erase
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_ERASE_FILE_PANEL, 0x9C, 0x78, 1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                FILE_SELECT_DATA.textId = 4;
                FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][4];
                FileSelectDrawText(3);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.yesNoCursor = 1;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR,
                    sFileSelectEraseYesNoXPositions[gLanguage * 2 + 1], 0x91, 1);
                FILE_SELECT_DATA.bgToggle = 1;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 28;
            }
            break;

        case 28:
            if (gChangedInput & KEY_B)
            {
                FILE_SELECT_DATA.stage = 29;
                break;
            }

            if (!(gChangedInput & (KEY_A | KEY_START)))
                break;

            if (FILE_SELECT_DATA.yesNoCursor == 0)
                FILE_SELECT_DATA.stage = 32;
            else
                FILE_SELECT_DATA.stage = 30;
            break;

        case 29:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 2;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.stage = 3;
            }
            break;

        case 30:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 8)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 2;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.stage = 31;
            }
            break;

        case 31:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 6)
            {
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.stage = 3;
            }
            break;

        case 32:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                gMostRecentSaveFile = FILE_SELECT_DATA.fileCursor;
                Sram_EraseFile(0);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                Sram_EraseFile(1);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                Sram_EraseFile(2);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                Sram_EraseFile(3);
            }
            else if (FILE_SELECT_DATA.timer == 11)
            {
                FileSelectDrawFileInfo(FILE_SELECT_DATA.fileCursor);
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.stage = 33;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 33:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ACTION_CURSOR);
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR);
                FILE_SELECT_DATA.bgToggle = 5;
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                FileSelectClearTextBg();
            }
            else if (FILE_SELECT_DATA.timer == 12)
            {
                FILE_SELECT_DATA.yesNoCursor = 0;
                FILE_SELECT_DATA.copyTarget = 0;
                FILE_SELECT_DATA.actionCursor = 0;
                FILE_SELECT_DATA.timer = 0;
                FILE_SELECT_DATA.stage = 0;
            }
            break;

        case 34:
            result = 3;
            break;
    }

    FileSelectDrawAllOam();
    return result;
}

/**
 * @brief 9f518 | 418 | Sets up a new file select OAM object
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param unused Unused
 * @return u8 Slot used (23 if none free)
 */
u8 FileSelectSetupOam(u8 type, u16 xPosition, u16 yPosition, u8 unused)
{
    s8 i;
    u32 zero;
    struct FileSelectOam* pOam;

    // Find a free slot, starting from the end
    for (i = FILE_SELECT_OAM_COUNT - 1; FILE_SELECT_DATA.oam[i].type != 0; )
    {
        i--;
        if (i < 0)
            return FILE_SELECT_OAM_COUNT;
    }

    if (i < 0)
        return FILE_SELECT_OAM_COUNT;

    pOam = &FILE_SELECT_DATA.oam[i];

    zero = 0;
    DMA_SET(3, &zero, pOam, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x1C / sizeof(u32)));

    pOam->xPosition = xPosition;
    pOam->yPosition = yPosition;
    pOam->type = type;
    pOam->drawn = TRUE;

    switch (type)
    {
        case FILE_SELECT_OAM_TYPE_SAMUS_HEAD:
            pOam->pOam = sFileSelectOam_SamusHead;
            pOam->pFunc = FUNC_PTR(FileSelectProcessSamusHead);
            break;

        case FILE_SELECT_OAM_TYPE_ACTION_CURSOR:
            pOam->pOam = sFileSelectOam_Cursor;
            pOam->pFunc = FUNC_PTR(FileSelectProcessCursor);
            break;

        case FILE_SELECT_OAM_TYPE_COPY_ARROW:
            pOam->priority = 1;
            pOam->drawn = FALSE;
            pOam->pOam = sFileSelectOam_CopyArrow;
            pOam->pFunc = FUNC_PTR(FileSelectProcessDeleteArrow);
            break;

        case FILE_SELECT_OAM_TYPE_COPY_YES_NO_CURSOR:
            pOam->pOam = sFileSelectOam_Cursor;
            pOam->pFunc = FUNC_PTR(unk_9fddc);
            break;

        case FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR:
            pOam->pOam = sFileSelectOam_Cursor;
            pOam->pFunc = FUNC_PTR(unk_9ff00);
            break;

        case FILE_SELECT_OAM_TYPE_AUDIO_LOGOS:
            pOam->priority = 3;
            pOam->pOam = sFileSelectOam_AudioLogos;
            pOam->pFunc = FUNC_PTR(FileSelectProcessAudioLogos);
            break;

        case FILE_SELECT_OAM_TYPE_FILE_OVERLAY:
            pOam->priority = 2;
            // PORT: the original reads past the table if gMostRecentSaveFile > 4
            pOam->pOam = sFileSelectFileOverlayOamPointers[gMostRecentSaveFile];
            pOam->pFunc = FUNC_PTR(FileSelectProcessFileOverlay);
            break;

        case FILE_SELECT_OAM_TYPE_8:
            pOam->priority = 2;
            pOam->pOam = sFileSelectOam_Type8;
            pOam->pFunc = FUNC_PTR(unk_a016c);
            break;

        case FILE_SELECT_OAM_TYPE_AUDIO_SELECT:
            pOam->drawn = FALSE;
            pOam->priority = 3;
            pOam->pOam = sFileSelectOam_AudioSelect;
            pOam->pFunc = FUNC_PTR(FileSelectProcessAudioSelect);
            break;

        case FILE_SELECT_OAM_TYPE_CORRUPTED_PANEL:
            pOam->pOam = sFileSelectOam_CorruptedPanel;
            pOam->pFunc = FUNC_PTR(unk_a01cc);
            break;

        case FILE_SELECT_OAM_TYPE_FILE_ACTION_PANEL:
            SoundPlay(0x1FC);
            pOam->priority = 2;
            pOam->pOam = sFileSelectOam_PanelOpening;
            pOam->pFunc = FUNC_PTR(FileSelectProcessFileActionPanel);
            break;

        case FILE_SELECT_OAM_TYPE_COPY_FILE_PANEL:
            SoundPlay(0x1FC);
            pOam->priority = 1;
            pOam->pOam = sFileSelectOam_SmallPanelOpening;
            pOam->pFunc = FUNC_PTR(FileSelectProcessCopyFilePanel);
            break;

        case FILE_SELECT_OAM_TYPE_ERASE_FILE_PANEL:
            SoundPlay(0x1FC);
            pOam->priority = 1;
            pOam->pOam = sFileSelectOam_SmallPanelOpening;
            pOam->pFunc = FUNC_PTR(FileSelectProcessEraseFilePanel);
            break;

        case FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_A:
        case FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_B:
        case FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_C:
            // Frame data set by FileSelectSetUpAreaNameOam
            pOam->priority = 3;
            pOam->pFunc = FUNC_PTR(unk_a0518);
            break;

        case FILE_SELECT_OAM_TYPE_CORRUPTED_TEXT:
            pOam->priority = 2;
            pOam->pOam = sFileSelectOam_SmallPanelIdle;
            pOam->pFunc = FUNC_PTR(unk_a0518);
            break;

        case FILE_SELECT_OAM_TYPE_COMPLETED_FILE_A:
        case FILE_SELECT_OAM_TYPE_COMPLETED_FILE_B:
        case FILE_SELECT_OAM_TYPE_COMPLETED_FILE_C:
            pOam->priority = 3;
            pOam->pOam = sFileSelectOam_CompletedStar;
            pOam->pFunc = FUNC_PTR(unk_a0518);
            break;

        case FILE_SELECT_OAM_TYPE_NEW_GAME_PANEL:
            SoundPlay(0x1FC);
            pOam->priority = 1;
            pOam->pOam = sFileSelectOam_SmallPanelOpening;
            pOam->pFunc = FUNC_PTR(unk_a039c);
            break;

        case FILE_SELECT_OAM_TYPE_NEW_GAME_YES_NO_CURSOR:
            pOam->pOam = sFileSelectOam_Cursor;
            pOam->pFunc = FUNC_PTR(unk_a0424);
            break;
    }

    return i;
}

/**
 * @brief 9f930 | 1a4 | Handles the Samus head (file cursor)
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessSamusHead(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (gChangedInput & KEY_UP)
        {
            if (FILE_SELECT_DATA.fileCursor == 3)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition -= 0x25;
                FILE_SELECT_DATA.fileCursor--;
                SoundPlay(0x1F9);
            }
            else if (FILE_SELECT_DATA.fileCursor == 4)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition -= 0x28;
                FILE_SELECT_DATA.fileCursor--;
                SoundPlay(0x1F9);
            }
            else if (FILE_SELECT_DATA.fileCursor < 3 && FILE_SELECT_DATA.fileCursor >= 1)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition -= 0x10;
                FILE_SELECT_DATA.fileCursor--;
                SoundPlay(0x1F9);
            }
        }
        else if (gChangedInput & KEY_DOWN)
        {
            if (FILE_SELECT_DATA.fileCursor == 2)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition += 0x25;
                FILE_SELECT_DATA.fileCursor++;
                SoundPlay(0x1F9);
            }
            else if (FILE_SELECT_DATA.fileCursor == 3)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition += 0x28;
                FILE_SELECT_DATA.fileCursor++;
                SoundPlay(0x1F9);
            }
            else if (FILE_SELECT_DATA.fileCursor < 2)
            {
                pOam->xPosition = 0xF;
                pOam->yPosition += 0x10;
                FILE_SELECT_DATA.fileCursor++;
                SoundPlay(0x1F9);
            }
        }

        if (FILE_SELECT_DATA.fileCursor != 3 && gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
            SoundPlay(0x1FB);
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 100;
        }

        if (FILE_SELECT_DATA.timer == 11)
            pOam->stage = 100;
    }
    else if (pOam->stage == 100)
    {
        if (FILE_SELECT_DATA.stage == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SamusHead;
            pOam->stage = 0;
        }
        else if (FILE_SELECT_DATA.stage == 5 || FILE_SELECT_DATA.stage == 7 || FILE_SELECT_DATA.stage == 12 ||
            FILE_SELECT_DATA.stage == 13)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SamusHeadSelected;
            pOam->stage = 200;
        }
    }
    else
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 9fad4 | 1bc | Handles the action cursor (start/copy/erase)
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessCursor(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_DATA.stage == 2)
        {
            if (gChangedInput & KEY_B)
            {
                pOam->stage = 100;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                if ((s8)gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].completedGame == TRUE)
                    SoundPlay(0x1FB);
                else
                    SoundPlay(0x1FE);

                FILE_SELECT_DATA.actionCursor = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectOam_CursorSelected;
                pOam->stage = 100;
            }
        }
        else if (FILE_SELECT_DATA.stage == 3)
        {
            if (gChangedInput & KEY_UP)
            {
                if (FILE_SELECT_DATA.actionCursor != 0)
                {
                    FILE_SELECT_DATA.actionCursor--;
                    pOam->yPosition -= 0x10;
                    SoundPlay(0x1F9);
                }
            }
            else if (gChangedInput & KEY_DOWN)
            {
                if (FILE_SELECT_DATA.actionCursor < 2)
                {
                    FILE_SELECT_DATA.actionCursor++;
                    pOam->yPosition += 0x10;
                    SoundPlay(0x1F9);
                }
            }

            if (gChangedInput & KEY_B)
            {
                pOam->stage = 100;
            }
            else if (gChangedInput & (KEY_A | KEY_START))
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sFileSelectOam_CursorSelected;

                if (FILE_SELECT_DATA.actionCursor == 0)
                {
                    pOam->stage = 100;
                    if ((s8)gFileSelectFileInfo[FILE_SELECT_DATA.fileCursor].completedGame == TRUE)
                        SoundPlay(0x1FB);
                    else
                        SoundPlay(0x1FE);
                }
                else
                {
                    SoundPlay(0x1FB);
                    pOam->stage = 1;
                }
            }
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 100;
        }

        if (FILE_SELECT_DATA.timer == 11)
            pOam->stage = 100;
    }
    else
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.stage == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_Cursor;
            pOam->stage = 0;
        }
    }
}

/**
 * @brief 9fc90 | 14c | Handles the arrow selecting the destination file of a copy
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessDeleteArrow(struct FileSelectOam* pOam)
{
    u8 selectSound;
    u8 moveSound;
    struct FileSelectFileInfo* pInfo;

    selectSound = 0;
    moveSound = FALSE;

    if (pOam->stage == 0)
    {
        pOam->drawn = TRUE;

        if (gChangedInput & KEY_UP)
        {
            if (FILE_SELECT_DATA.copyTarget != 0)
            {
                FILE_SELECT_DATA.copyTarget--;
                moveSound = TRUE;
            }

            if (FILE_SELECT_DATA.fileCursor == FILE_SELECT_DATA.copyTarget)
            {
                // Skip the source file
                if (FILE_SELECT_DATA.fileCursor == 0)
                {
                    FILE_SELECT_DATA.copyTarget++;
                    moveSound = FALSE;
                }
                else
                {
                    FILE_SELECT_DATA.copyTarget--;
                    moveSound = TRUE;
                }
            }
        }
        else if (gChangedInput & KEY_DOWN)
        {
            if (FILE_SELECT_DATA.copyTarget < 2)
            {
                FILE_SELECT_DATA.copyTarget++;
                moveSound = TRUE;
            }

            if (FILE_SELECT_DATA.fileCursor == FILE_SELECT_DATA.copyTarget)
            {
                // Skip the source file
                if (FILE_SELECT_DATA.fileCursor == 2)
                {
                    FILE_SELECT_DATA.copyTarget--;
                    moveSound = FALSE;
                }
                else
                {
                    FILE_SELECT_DATA.copyTarget++;
                    moveSound = TRUE;
                }
            }
        }

        // PORT: the original reads past the table if fileCursor or copyTarget > 2
        pOam->pOam = sFileSelectCopyArrowOamPointers[FILE_SELECT_DATA.fileCursor][FILE_SELECT_DATA.copyTarget];

        if (gChangedInput & KEY_B)
        {
            pOam->stage = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 1;

            pInfo = &gFileSelectFileInfo[FILE_SELECT_DATA.copyTarget];
            if (FILE_SELECT_FILE_IS_STARTED(pInfo))
                selectSound = 1;
            else
                selectSound = 2;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.timer == 11)
            pOam->stage = 100;
    }
    else
    {
        if (FILE_SELECT_DATA.stage == 17)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 0;
        }
    }

    if (moveSound)
        SoundPlay(0x1F9);

    if (selectSound == 1)
        SoundPlay(0x1FB);
    else if (selectSound == 2)
        SoundPlay(0x207);
}

/**
 * @brief 9fddc | 124 | Handles the yes/no cursor of the copy confirmation
 *
 * @param pOam File select OAM object
 */
void unk_9fddc(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_DATA.yesNoCursor == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                FILE_SELECT_DATA.yesNoCursor = 1;
                pOam->xPosition = sFileSelectCopyYesNoXPositions[gLanguage * 2 + 1];
                SoundPlay(0x1FA);
            }
        }
        else if (FILE_SELECT_DATA.yesNoCursor == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.yesNoCursor = 0;
                pOam->xPosition = sFileSelectCopyYesNoXPositions[gLanguage * 2];
                SoundPlay(0x1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->stage = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;

            if (FILE_SELECT_DATA.yesNoCursor == 0)
                SoundPlay(0x207);
            else
                SoundPlay(0x1FB);

            pOam->pOam = sFileSelectOam_CursorSelected;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
        }
    }
    else
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief 9ff00 | 124 | Handles the yes/no cursor of the erase confirmation
 *
 * @param pOam File select OAM object
 */
void unk_9ff00(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_DATA.yesNoCursor == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                FILE_SELECT_DATA.yesNoCursor = 1;
                pOam->xPosition = sFileSelectEraseYesNoXPositions[gLanguage * 2 + 1];
                SoundPlay(0x1FA);
            }
        }
        else if (FILE_SELECT_DATA.yesNoCursor == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                FILE_SELECT_DATA.yesNoCursor = 0;
                pOam->xPosition = sFileSelectEraseYesNoXPositions[gLanguage * 2];
                SoundPlay(0x1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->stage = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;

            if (FILE_SELECT_DATA.yesNoCursor == 0)
                SoundPlay(0x208);
            else
                SoundPlay(0x1FB);

            pOam->pOam = sFileSelectOam_CursorSelected;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
        }
    }
    else
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief a0024 | c0 | Handles the stereo/mono logos
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessAudioLogos(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.fileCursor == 3)
    {
        if (pOam->stage == 0)
        {
            pOam->pOam = sFileSelectOam_AudioStereoIdle;
            if (gChangedInput & KEY_RIGHT)
            {
                pOam->stage = 1;
                pOam->pOam = sFileSelectOam_AudioStereoActive;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                DoSoundAction(0x2000000);
                SoundPlay(0x206);
            }
        }
        else if (pOam->stage == 1)
        {
            pOam->pOam = sFileSelectOam_AudioStereoActive;
            if (gChangedInput & KEY_LEFT)
            {
                pOam->stage = 0;
                pOam->pOam = sFileSelectOam_AudioStereoIdle;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                DoSoundAction(0x1000000);
                SoundPlay(0x1FA);
            }
        }
    }
    else
    {
        if (pOam->stage == 0)
        {
            pOam->pOam = sFileSelectOam_AudioLogos;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
        else if (pOam->stage == 1)
        {
            pOam->pOam = sFileSelectOam_AudioLogosActive;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
}

/**
 * @brief a00e4 | 60 | Handles the audio (stereo/mono) selection cursor
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessAudioSelect(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.fileCursor == 3)
    {
        pOam->drawn = TRUE;
        if (pOam->stage == 0)
        {
            if (gChangedInput & KEY_RIGHT)
            {
                pOam->stage = 1;
                pOam->xPosition = 0xAA;
            }
        }
        else if (pOam->stage == 1)
        {
            if (gChangedInput & KEY_LEFT)
            {
                pOam->stage = 0;
                pOam->xPosition = 0x66;
            }
        }
    }
    else
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->drawn = FALSE;
    }
}

/**
 * @brief a0144 | 28 | Handles the overlay of the selected file
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessFileOverlay(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.stage == 0)
    {
        // PORT: the original reads past the table if fileCursor > 4
        pOam->pOam = sFileSelectFileOverlayOamPointers[FILE_SELECT_DATA.fileCursor];
    }
}

/**
 * @brief a016c | 60 | To document
 *
 * @param pOam File select OAM object
 */
void unk_a016c(struct FileSelectOam* pOam)
{
    if (FILE_SELECT_DATA.stage != 0)
        return;

    pOam->pOam = sFileSelectOam_Type8;

    if (FILE_SELECT_DATA.fileCursor > 2)
    {
        pOam->drawn = FALSE;
        return;
    }

    pOam->drawn = TRUE;
    if (FILE_SELECT_DATA.fileCursor == 0)
        pOam->yPosition = 0x31;
    else if (FILE_SELECT_DATA.fileCursor == 1)
        pOam->yPosition = 0x41;
    else if (FILE_SELECT_DATA.fileCursor == 2)
        pOam->yPosition = 0x51;

    if (gChangedInput & (KEY_A | KEY_START))
        pOam->pOam = sFileSelectOam_Type8Selected;
}

/**
 * @brief a01cc | 4 | Empty OAM function
 *
 * @param pOam File select OAM object
 */
void unk_a01cc(struct FileSelectOam* pOam)
{
    return;
}

/**
 * @brief a01d0 | 9c | Handles the file action panel
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessFileActionPanel(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_ActionPanelIdle;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.stage == 21 || FILE_SELECT_DATA.stage == 4 || FILE_SELECT_DATA.stage == 26 ||
            FILE_SELECT_DATA.stage == 33)
        {
            SoundPlay(0x1FD);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_ActionPanelClosing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->type = 0;
            pOam->drawn = FALSE;
        }
    }
}

/**
 * @brief a026c | 98 | Handles the copy file panel
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessCopyFilePanel(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelIdle;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.stage == 21 || FILE_SELECT_DATA.stage == 18 || FILE_SELECT_DATA.stage == 26)
        {
            SoundPlay(0x1FD);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelClosing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->type = 0;
            pOam->drawn = FALSE;
        }
    }
}

/**
 * @brief a0304 | 98 | Handles the erase file panel
 *
 * @param pOam File select OAM object
 */
void FileSelectProcessEraseFilePanel(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelIdle;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.stage == 31 || FILE_SELECT_DATA.stage == 29 || FILE_SELECT_DATA.stage == 33)
        {
            SoundPlay(0x1FD);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelClosing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->type = 0;
            pOam->drawn = FALSE;
        }
    }
}

/**
 * @brief a039c | 88 | Handles the new game (completed file) panel
 *
 * @param pOam File select OAM object
 */
void unk_a039c(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelIdle;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_DATA.stage == 11)
        {
            SoundPlay(0x1FD);
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sFileSelectOam_SmallPanelClosing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
        {
            pOam->type = 0;
            pOam->drawn = FALSE;
        }
    }
}

/**
 * @brief a0424 | f4 | Handles the yes/no cursor of the new game panel
 *
 * @param pOam File select OAM object
 */
void unk_a0424(struct FileSelectOam* pOam)
{
    if (pOam->stage == 0)
    {
        if (FILE_SELECT_DATA.yesNoCursor == 0)
        {
            if (gChangedInput & KEY_DOWN)
            {
                FILE_SELECT_DATA.yesNoCursor = 1;
                pOam->yPosition = 0x79;
                SoundPlay(0x1FA);
            }
        }
        else if (FILE_SELECT_DATA.yesNoCursor == 1)
        {
            if (gChangedInput & KEY_UP)
            {
                FILE_SELECT_DATA.yesNoCursor = 0;
                pOam->yPosition = 0x69;
                SoundPlay(0x1FA);
            }
        }

        if (gChangedInput & KEY_B)
        {
            pOam->stage = 100;
        }
        else if (gChangedInput & (KEY_A | KEY_START))
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            SoundPlay(0x1FE);
            pOam->pOam = sFileSelectOam_CursorSelected;
            pOam->stage = 100;
        }
    }
    else if (pOam->stage == 1)
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;

        if (FILE_SELECT_DATA.timer == 11)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 100;
        }
    }
    else
    {
        if (FILE_SELECT_ANIM_ENDED(pOam))
            pOam->animationDurationCounter = 0;
    }
}

/**
 * @brief a0518 | 4 | Empty OAM function
 *
 * @param pOam File select OAM object
 */
void unk_a0518(struct FileSelectOam* pOam)
{
    return;
}

static u8* FileSelectGetFileInfoGfxAddress(u8 file)
{
    if (file == 0)
        return VRAM_BASE + 0x88C0;
    else if (file == 1)
        return VRAM_BASE + 0x90C0;
    else
        return VRAM_BASE + 0x98C0;
}

/**
 * @brief a051c | 520 | Draws the info of a file (energy, time, area)
 *
 * @param file File number
 */
void FileSelectDrawFileInfo(u8 file)
{
    struct FileSelectFileInfo* pInfo;
    u8* start;
    u8* dst;
    u8* tankDst;
    const u16* pText;
    const u8* src;
    u32 zero;
    u8 i;
    s32 width;
    s32 timeDigits[2];
    s32 energyDigits[4];
    s32 tanks[4];

    pInfo = &gFileSelectFileInfo[file];
    start = dst = FileSelectGetFileInfoGfxAddress(file);

    FILE_SELECT_DATA.textTileX = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    if (pInfo->exists == FALSE)
    {
        if ((s8)gFileSelectFileInfo[file].completedGame == TRUE || (s8)gFileSelectFileInfo[file].introPlayed == TRUE)
        {
            // Started but never saved, display a full energy tank
            FILE_SELECT_DATA.emptyFileInfo.currentEnergy = 99;
            pInfo = &FILE_SELECT_DATA.emptyFileInfo;
        }
        else
        {
            // Empty file
            FileSelectDestroyOamOfType(file + FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_A);
            FileSelectDestroyOamOfType(file + FILE_SELECT_OAM_TYPE_COMPLETED_FILE_A);

            zero = 0;
            DMA_SET(3, &zero, dst, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x300 / sizeof(u32)));
            zero = 0;
            DMA_SET(3, &zero, dst + 0x400, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x300 / sizeof(u32)));

            pText = sFileSelectNoDataTextPointers[gLanguage][0];
            FILE_SELECT_DATA.textTileX = 8;

            while (*pText != 0xFF00)
            {
                if (*pText == 0x5A)
                    width = TextGetCharacterWidth(*pText) + 2;
                else if (*pText == 0x40)
                    width = 8 - FILE_SELECT_DATA.textPixelOffset;
                else
                    width = 8;

                dst = start + FILE_SELECT_DATA.textTileX * 32;
                TextDrawCharacter(*pText, (u32*)dst, width, FILE_SELECT_DATA.textPixelOffset, 0);
                FILE_SELECT_DATA.textPixelOffset += width;
                FILE_SELECT_TEXT_CURSOR_NORMALIZE();
                pText++;
            }
            return;
        }
    }

    // Energy
    energyDigits[0] = pInfo->currentEnergy / 1000;
    energyDigits[1] = tanks[0] = pInfo->currentEnergy / 100;
    energyDigits[1] = tanks[1] = energyDigits[1] % 10;
    energyDigits[2] = pInfo->currentEnergy / 10 % 10;
    energyDigits[3] = pInfo->currentEnergy % 10;

    for (i = 2; i < 4; i++)
    {
        src = &sCharactersGfx[(energyDigits[i] + 0x50) * 32];
        DMA3_COPY_32(src, dst, 32 / sizeof(u32));
        DMA3_COPY_32(src + 0x400, dst + 0x400, 32 / sizeof(u32));
        dst += 32;
    }

    // Energy tanks
    zero = 0;
    DMA_SET(3, &zero, dst, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x200 / sizeof(u32)));
    zero = 0;
    DMA_SET(3, &zero, dst + 0x400, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x200 / sizeof(u32)));

    tanks[1] = tanks[1] % 2;
    tanks[2] = pInfo->maxEnergy / 100;
    tanks[3] = tanks[2] % 10;
    tanks[3] = tanks[3] % 2;

    tankDst = dst + 0x400;
    i = 0;
    while (i < tanks[0] - tanks[1])
    {
        if (i == 10)
            tankDst -= 0x4A0;
        DMA3_COPY_32(sFileSelectEnergyTankFullGfx, tankDst, 32 / sizeof(u32));
        tankDst += 32;
        i += 2;
    }

    if (tanks[1] == 1)
    {
        if (i == 10)
            tankDst -= 0x4A0;

        if (tanks[2] == tanks[0])
        {
            DMA3_COPY_32(sFileSelectEnergyTankHalfFullGfx, tankDst, 32 / sizeof(u32));
        }
        else
        {
            DMA3_COPY_32(sFileSelectEnergyTankHalfGfx, tankDst, 32 / sizeof(u32));
        }

        i += 2;
        tankDst += 32;
    }

    while (i < tanks[2] - tanks[3])
    {
        if (i == 10)
            tankDst -= 0x4A0;
        DMA3_COPY_32(sFileSelectEnergyTankEmptyGfx, tankDst, 32 / sizeof(u32));
        tankDst += 32;
        i += 2;
    }

    if (tanks[3] == 1 && i < tanks[2])
    {
        if (i == 10)
            tankDst -= 0x4A0;
        DMA3_COPY_32(sFileSelectEnergyTankHalfEmptyGfx, tankDst, 32 / sizeof(u32));
    }

    // Hours
    dst += 0xC0;
    timeDigits[0] = pInfo->igtHours / 10 % 10;
    timeDigits[1] = pInfo->igtHours % 10;

    for (i = 0; i < 2; i++)
    {
        src = &sCharactersGfx[(timeDigits[i] + 0x50) * 32];
        DMA3_COPY_32(src, dst, 32 / sizeof(u32));
        DMA3_COPY_32(src + 0x400, dst + 0x400, 32 / sizeof(u32));
        dst += 32;
    }

    // Colon
    FILE_SELECT_DATA.textTileX = 10;
    dst = start + 10 * 32;
    width = TextGetCharacterWidth(0x5A) + 3;
    TextDrawCharacter(0x5A, (u32*)dst, width, FILE_SELECT_DATA.textPixelOffset, 0);
    FILE_SELECT_DATA.textPixelOffset += width;
    FILE_SELECT_TEXT_CURSOR_NORMALIZE();

    // Minutes
    timeDigits[0] = pInfo->igtMinutes / 10 % 10;
    timeDigits[1] = pInfo->igtMinutes % 10;

    for (i = 0; i < 2; i++)
    {
        dst = start + FILE_SELECT_DATA.textTileX * 32;
        TextDrawCharacter(timeDigits[i] + 0x50, (u32*)dst, 8, FILE_SELECT_DATA.textPixelOffset, 0);
        FILE_SELECT_DATA.textPixelOffset += 8;
        FILE_SELECT_TEXT_CURSOR_NORMALIZE();
    }

    FileSelectDestroyOamOfType(file + FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_A);
    FileSelectSetUpAreaNameOam(file + FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_A, 0x9D, file * 16 + 0x20, pInfo->currentArea);

    FileSelectDestroyOamOfType(file + FILE_SELECT_OAM_TYPE_COMPLETED_FILE_A);
    if ((s8)gFileSelectFileInfo[file].completedGame == TRUE)
        FileSelectSetupOam(file + FILE_SELECT_OAM_TYPE_COMPLETED_FILE_A, 0xDC, file * 16 + 0x28, 1);
}

/**
 * @brief a0a3c | 148 | Draws the current text (FILE_SELECT_DATA.pText)
 *
 * @param destination Destination (1 = file header, 2 = action panel, 3 = small panel)
 */
void FileSelectDrawText(u8 destination)
{
    const u16* pLineOffsets;
    u8* base;
    u8* dst;
    u8 color;
    u32 width;

    FILE_SELECT_DATA.textLine = 0;
    FILE_SELECT_DATA.textTileX = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    if (FILE_SELECT_DATA.textId == 24)
        pLineOffsets = sFileSelectTextLineOffsetPointers[gLanguage][5];
    else
        pLineOffsets = sFileSelectTextLineOffsetPointers[gLanguage][FILE_SELECT_DATA.textId];

    // PORT: base and color are left uninitialized by the original for any other destination
    base = VRAM_BASE + 0xC800;
    color = 0;
    if (destination == 1)
    {
        base = VRAM_BASE + 0x8000;
        color = 6;
    }
    else if (destination == 2)
    {
        base = VRAM_BASE + 0xB000;
        color = 0;
    }
    else if (destination == 3)
    {
        base = VRAM_BASE + 0xC800;
        color = 0;
    }

    while (*FILE_SELECT_DATA.pText != 0xFF00)
    {
        if (*FILE_SELECT_DATA.pText == 0xFE00)
        {
            // New line
            FILE_SELECT_DATA.textTileX = 0;
            FILE_SELECT_DATA.textLine += 2;
            FILE_SELECT_DATA.textPixelOffset = 0;
            pLineOffsets++;
            color = 0;
        }
        else
        {
            dst = base + FILE_SELECT_DATA.textTileX * 32 + FILE_SELECT_DATA.textLine * 0x400 + *pLineOffsets * 32;
            width = TextGetCharacterWidth(*FILE_SELECT_DATA.pText);
            TextDrawCharacter(*FILE_SELECT_DATA.pText, (u32*)dst, width, FILE_SELECT_DATA.textPixelOffset, color);
            FILE_SELECT_DATA.textPixelOffset += width;
            FILE_SELECT_TEXT_CURSOR_NORMALIZE();
        }

        FILE_SELECT_DATA.pText++;
    }
}

/**
 * @brief a0b84 | 280 | Handles the corrupted files message on boot
 *
 * @return u8 bool, ended
 */
u8 FileSelectProcessCorruptedFile(void)
{
    u8 ended;
    u8 file;
    u32 zero;

    ended = FALSE;
    FileSelectProcessOam();

    switch (FILE_SELECT_DATA.corruptedFileStage)
    {
        case 0:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                FileSelectDrawText(1);
            }
            else if (FILE_SELECT_DATA.timer == 2)
            {
                if (gFileSelectFileInfo[0].corruptionFlag == 0)
                    FileSelectDrawFileInfo(0);
                else
                    FileSelectDrawFileCorruptedText(0);
            }
            else if (FILE_SELECT_DATA.timer == 3)
            {
                if (gFileSelectFileInfo[1].corruptionFlag == 0)
                    FileSelectDrawFileInfo(1);
                else
                    FileSelectDrawFileCorruptedText(1);
            }
            else if (FILE_SELECT_DATA.timer == 4)
            {
                if (gFileSelectFileInfo[2].corruptionFlag == 0)
                    FileSelectDrawFileInfo(2);
                else
                    FileSelectDrawFileCorruptedText(2);

                FILE_SELECT_DATA.timer = 0;
                gWrittenToBldy = 14;
                FILE_SELECT_DATA.corruptedFileStage = 1;
            }
            break;

        case 1:
            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                FILE_SELECT_DATA.corruptedFileStage = 2;
            break;

        case 2:
            // Find the next corrupted file
            while (FILE_SELECT_DATA.corruptedFile < 3)
            {
                if (gFileSelectFileInfo[FILE_SELECT_DATA.corruptedFile].corruptionFlag != 0)
                {
                    FILE_SELECT_DATA.corruptedFileStage = 3;
                    break;
                }
                FILE_SELECT_DATA.corruptedFile++;
            }

            if (FILE_SELECT_DATA.corruptedFile == 3)
                FILE_SELECT_DATA.corruptedFileStage = 7;
            break;

        case 3:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 10)
            {
                FILE_SELECT_DATA.corruptedFileStage = 4;
                FILE_SELECT_DATA.timer = 0;
                FileSelectSetupOam(FILE_SELECT_OAM_TYPE_CORRUPTED_TEXT, 0x7A, 0x44, 0);
            }
            break;

        case 4:
            file = FILE_SELECT_DATA.corruptedFile;
            if (gFileSelectFileInfo[file].corruptionFlag == 1)
                FILE_SELECT_DATA.textId = file + 5;
            else
                FILE_SELECT_DATA.textId = file + 8;

            FILE_SELECT_DATA.pText = sFileSelectTextPointers[gLanguage][FILE_SELECT_DATA.textId];
            FileSelectDrawCorruptionText(2);
            FileSelectSetupOam(FILE_SELECT_OAM_TYPE_CORRUPTED_PANEL, 0x78, 0x64, 0);
            FILE_SELECT_DATA.bgToggle = 3;
            FILE_SELECT_DATA.corruptedFileStage = 5;
            break;

        case 5:
            if (gChangedInput & (KEY_A | KEY_B))
            {
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_CORRUPTED_PANEL);
                FileSelectDestroyOamOfType(FILE_SELECT_OAM_TYPE_CORRUPTED_TEXT);
                SoundPlay(0x1FB);
                FILE_SELECT_DATA.bgToggle = 4;
                Sram_SetCurrentFile(FILE_SELECT_DATA.corruptedFile);
                FileSelectDrawFileInfo(FILE_SELECT_DATA.corruptedFile);
                FILE_SELECT_DATA.corruptedFileStage = 6;
            }
            break;

        case 6:
            FILE_SELECT_DATA.timer++;
            if (FILE_SELECT_DATA.timer == 1)
            {
                zero = 0;
                DMA_SET(3, &zero, VRAM_BASE + 0xB000, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x1800 / sizeof(u32)));
            }
            else if (FILE_SELECT_DATA.timer == 10)
            {
                FILE_SELECT_DATA.corruptedFileStage = 2;
                FILE_SELECT_DATA.timer = 0;
            }
            break;

        case 7:
            FILE_SELECT_DATA.timer = 0;
            ended = TRUE;
            break;
    }

    FileSelectDrawAllOam();
    return ended;
}

/**
 * @brief a0e04 | 114 | Draws the "corrupted" text in place of the file info
 *
 * @param file File number
 */
void FileSelectDrawFileCorruptedText(u8 file)
{
    u8* start;
    u8* dst;
    const u16* pText;
    u32 zero;
    s32 width;

    start = FileSelectGetFileInfoGfxAddress(file);

    FILE_SELECT_DATA.textTileX = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    zero = 0;
    DMA_SET(3, &zero, start, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x300 / sizeof(u32)));
    zero = 0;
    DMA_SET(3, &zero, start + 0x400, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x300 / sizeof(u32)));

    pText = sFileSelectNoDataTextPointers[gLanguage][0];
    FILE_SELECT_DATA.textTileX = 8;

    while (*pText != 0xFF00)
    {
        if (*pText == 0x5A)
            width = TextGetCharacterWidth(*pText) + 3;
        else if (*pText == 0x40)
            width = 8 - FILE_SELECT_DATA.textPixelOffset;
        else
            width = 8;

        dst = start + FILE_SELECT_DATA.textTileX * 32;
        TextDrawCharacter(*pText, (u32*)dst, width, FILE_SELECT_DATA.textPixelOffset, 0);
        FILE_SELECT_DATA.textPixelOffset += width;
        FILE_SELECT_TEXT_CURSOR_NORMALIZE();
        pText++;
    }
}

/**
 * @brief a0f18 | f0 | Draws the current text (FILE_SELECT_DATA.pText), no line offsets
 *
 * @param destination Destination (1 = file header, 2 = action panel, 3 = small panel)
 */
void FileSelectDrawCorruptionText(u8 destination)
{
    u8* base;
    u8* dst;
    u32 width;

    FILE_SELECT_DATA.textLine = 0;
    FILE_SELECT_DATA.textTileX = 0;
    FILE_SELECT_DATA.textPixelOffset = 0;

    // PORT: base is left uninitialized by the original for any other destination
    base = VRAM_BASE + 0xB000;
    if (destination == 1)
        base = VRAM_BASE + 0x8000;
    else if (destination == 2)
        base = VRAM_BASE + 0xB000;
    else if (destination == 3)
        base = VRAM_BASE + 0xC800;

    while (*FILE_SELECT_DATA.pText != 0xFF00)
    {
        if (*FILE_SELECT_DATA.pText == 0xFE00)
        {
            // New line
            FILE_SELECT_DATA.textTileX = 0;
            FILE_SELECT_DATA.textLine += 2;
            FILE_SELECT_DATA.textPixelOffset = 0;
        }
        else
        {
            dst = base + FILE_SELECT_DATA.textTileX * 32 + FILE_SELECT_DATA.textLine * 0x400;
            width = TextGetCharacterWidth(*FILE_SELECT_DATA.pText);
            TextDrawCharacter(*FILE_SELECT_DATA.pText, (u32*)dst, width, FILE_SELECT_DATA.textPixelOffset, 0);
            FILE_SELECT_DATA.textPixelOffset += width;
            FILE_SELECT_TEXT_CURSOR_NORMALIZE();
        }

        FILE_SELECT_DATA.pText++;
    }
}

/**
 * @brief a1008 | 34 | Destroys the first file select OAM object of a type
 *
 * @param type Type
 */
void FileSelectDestroyOamOfType(u8 type)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].type == type)
        {
            FILE_SELECT_DATA.oam[i].type = 0;
            FILE_SELECT_DATA.oam[i].drawn = FALSE;
            return;
        }
    }
}

/**
 * @brief a103c | 190 | Sets up the OAM object of the area name of a file
 *
 * @param type Type
 * @param xPosition X position
 * @param yPosition Y position
 * @param area Area
 */
void FileSelectSetUpAreaNameOam(u8 type, s16 xPosition, s16 yPosition, u16 area)
{
    u8 slot;
    s32 index;

    slot = FileSelectSetupOam(type, xPosition, yPosition, 1);

    index = (s16)area;
    if (index < 1 || index > 6)
        index = 0;

    // PORT: if no slot was free (slot == 23), the original writes right after the OAM array
    // (into emptyFileInfo/the following RAM)
    FILE_SELECT_DATA.oam[slot].pOam = sFileSelectAreaNameOamPointers[gLanguage][index];
}

/**
 * @brief a11cc | 3c | Calls the functions of the file select OAM objects
 *
 */
void FileSelectProcessOam(void)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].type != 0)
            FILE_SELECT_DATA.oam[i].pFunc(&FILE_SELECT_DATA.oam[i]);
    }
}

/**
 * @brief a1208 | 40 | Draws all the file select OAM objects
 *
 */
void FileSelectDrawAllOam(void)
{
    u8 i;

    for (i = 0; i < FILE_SELECT_OAM_COUNT; i++)
    {
        if (FILE_SELECT_DATA.oam[i].drawn)
            FileSelectDrawOam(&FILE_SELECT_DATA.oam[i]);
    }

    ResetFreeOam();
    gNextOamSlot = 0;
}

/**
 * @brief a1248 | 188 | Draws a file select OAM object
 *
 * @param pOam File select OAM object
 */
void FileSelectDrawOam(struct FileSelectOam* pOam)
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
            x = pOam->xPosition - (sFileSelectOamXWidthTable[gOamData[slot].split.shape * 4 + gOamData[slot].split.size] * 8 + part1);
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
 * @brief a13d0 | 10 | Sets the language (US : always english)
 *
 * @param unused Unused
 * @return u32 bool, always TRUE
 */
u32 SetLanguage(u8 unused)
{
    gLanguage = LANGUAGE_ENGLISH;
    return TRUE;
}

/**
 * @brief a13e0 | 98 | Resets the display registers
 *
 */
void unk_a13e0(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    WRITE_16(REG_DISPCNT, 0);
    WRITE_16(REG_BLDCNT, 0xFF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);

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
    CallbackSetVBlank(FUNC_PTR(unk_a1478));
}

/**
 * @brief a1478 | 4 | Empty v-blank code
 *
 */
void unk_a1478(void)
{
    return;
}

/**
 * @brief a147c | 4 | Returns TRUE
 *
 * @return u32 TRUE
 */
u32 unk_a147c(void)
{
    return TRUE;
}
