#include "data/blob_pieces.h"
#ifndef PORT_DECOMP_FILE_SELECT_H
#define PORT_DECOMP_FILE_SELECT_H

#include "types.h"
#include "oam.h"

/*
 * File select screen (asm/disasm_0x0809deb4.s, 0x0809e598 - 0x080a13e0) and SetLanguage.
 * US behaviour: the language is always set to LANGUAGE_ENGLISH by SetLanguage, the
 * per-language tables are still kept complete.
 */

#ifndef FILE_SELECT_FILE_INFO_DEFINED
#define FILE_SELECT_FILE_INFO_DEFINED
/* Info about a save file shown on the file select screen, 0x14 bytes (gFileSelectFileInfo, 0x03000b94) */
struct FileSelectFileInfo {
    u8 exists;            // 0x00 (1 = valid file)
    u8 corruptionFlag;    // 0x01 (1 = main copy bad, rewrite main; 2 = rewrite main and backup; 3 = both bad)
    u8 currentArea;       // 0x02
    u8 eventCounter;      // 0x03
    u16 currentEnergy;    // 0x04
    u16 maxEnergy;        // 0x06
    u16 currentMissiles;  // 0x08
    u16 maxMissiles;      // 0x0a
    u8 weaponsStatus;     // 0x0c (gEquipment byte +0xb)
    u8 igtHours;          // 0x0d
    u8 igtMinutes;        // 0x0e
    u8 unk_f;             // 0x0f (copy of save byte 0x1c = 0x03000b90; 0 means 'no started game')
    u8 completedGame;     // 0x10
    u8 introPlayed;       // 0x11
    u8 unk_12[2];         // 0x12
};
#endif /* FILE_SELECT_FILE_INFO_DEFINED */

// IWRAM 0x03000b94, no linker.ld name (bound with .set in file_select.c for the GBA build)
extern struct FileSelectFileInfo gFileSelectFileInfo[3];

struct FileSelectOam;
typedef void (*FileSelectOamFunc_T)(struct FileSelectOam*);

// 0x1C bytes on GBA
struct FileSelectOam {
    u16 xPosition;                  // 0x0
    u16 yPosition;                  // 0x2
    u8 type;                        // 0x4 (0 = free slot)
    u8 drawn;                       // 0x5
    u8 currentAnimationFrame;       // 0x6
    u8 animationDurationCounter;    // 0x7
    u8 unk_8;                       // 0x8
    u8 stage;                       // 0x9
    u8 objMode;                     // 0xA
    u8 priority;                    // 0xB
    u8 xFlip;                       // 0xC
    u8 paletteOffset;               // 0xD
    u16 tileOffset;                 // 0xE
    u8 unk_10[4];                   // 0x10
    const struct FrameData* pOam;   // 0x14
    FileSelectOamFunc_T pFunc;      // 0x18
};

#define FILE_SELECT_OAM_COUNT 23

struct FileSelectData {
    u16 textTileX;                  // 0x0 Current tile of the text being drawn
    u16 textLine;                   // 0x2 Current line (in 8 pixel rows) of the text being drawn
    const u16* pText;               // 0x4 Text being drawn
    u16 textId;                     // 0x8
    s16 stage;                      // 0xA
    u8 timer;                       // 0xC
    u8 fileCursor;                  // 0xD 0-2 = files, 3 = audio, 4 = ?
    u8 actionCursor;                // 0xE 0 = start, 1 = copy, 2 = erase
    u8 copyTarget;                  // 0xF
    u8 yesNoCursor;                 // 0x10
    u8 bgToggle;                    // 0x11 Applied (then cleared) in v-blank
    s8 result;                      // 0x12
    u8 textPixelOffset;             // 0x13
    u8 corruptedFileStage;          // 0x14
    u8 corruptedFile;               // 0x15
    u8 padding_16[2];               // 0x16
    struct FileSelectOam oam[FILE_SELECT_OAM_COUNT]; // 0x18
    struct FileSelectFileInfo emptyFileInfo;         // 0x29C Info shown for a started but never saved file
};

#define FILE_SELECT_DATA (*(struct FileSelectData*)&gNonGameplayRam)

enum FileSelectOamType {
    FILE_SELECT_OAM_TYPE_NONE,
    FILE_SELECT_OAM_TYPE_SAMUS_HEAD,
    FILE_SELECT_OAM_TYPE_ACTION_CURSOR,
    FILE_SELECT_OAM_TYPE_COPY_ARROW,
    FILE_SELECT_OAM_TYPE_COPY_YES_NO_CURSOR,
    FILE_SELECT_OAM_TYPE_ERASE_YES_NO_CURSOR,
    FILE_SELECT_OAM_TYPE_AUDIO_LOGOS,
    FILE_SELECT_OAM_TYPE_FILE_OVERLAY,
    FILE_SELECT_OAM_TYPE_8,
    FILE_SELECT_OAM_TYPE_AUDIO_SELECT,
    FILE_SELECT_OAM_TYPE_CORRUPTED_PANEL,
    FILE_SELECT_OAM_TYPE_FILE_ACTION_PANEL,
    FILE_SELECT_OAM_TYPE_COPY_FILE_PANEL,
    FILE_SELECT_OAM_TYPE_ERASE_FILE_PANEL,
    FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_A,  // 0xE + file
    FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_B,
    FILE_SELECT_OAM_TYPE_AREA_NAME_FILE_C,
    FILE_SELECT_OAM_TYPE_CORRUPTED_TEXT,
    FILE_SELECT_OAM_TYPE_12,
    FILE_SELECT_OAM_TYPE_13,
    FILE_SELECT_OAM_TYPE_COMPLETED_FILE_A,  // 0x14 + file
    FILE_SELECT_OAM_TYPE_COMPLETED_FILE_B,
    FILE_SELECT_OAM_TYPE_COMPLETED_FILE_C,
    FILE_SELECT_OAM_TYPE_NEW_GAME_PANEL,
    FILE_SELECT_OAM_TYPE_NEW_GAME_YES_NO_CURSOR,
};

// Static data blob of src/data/sa_x_close_up.c (sBlob_73421e_73c274, ROM 0x0873421e)
#define BLOB_73421E(off) (&sBlob_73421e_73c274[(off)])
// src/data/text_data.c
extern const u8 sCharactersGfx[192 * 1024];

// PORT: the frame data below lives inside a raw binary blob and holds GBA ROM pointers,
// it must be decoded into real struct FrameData arrays for a native build.
#define FS_FRAME(off) ((const struct FrameData*)BLOB_73421E(off))
#define sFileSelectOam_AudioStereoIdle      FS_FRAME(0xc5a2) // 0x087407c0
#define sFileSelectOam_AudioStereoActive    FS_FRAME(0xc5b2) // 0x087407d0
#define sFileSelectOam_AudioLogos           FS_FRAME(0xc5c2) // 0x087407e0
#define sFileSelectOam_AudioLogosActive     FS_FRAME(0xc5d2) // 0x087407f0
#define sFileSelectOam_CorruptedPanel       FS_FRAME(0xc662) // 0x08740880
#define sFileSelectOam_Type8Selected        FS_FRAME(0xc6b2) // 0x087408d0
#define sFileSelectOam_Type8                FS_FRAME(0xc6c2) // 0x087408e0
#define sFileSelectOam_AudioSelect          FS_FRAME(0xc6d2) // 0x087408f0
#define sFileSelectOam_PanelOpening         FS_FRAME(0xc6fa) // 0x08740918
#define sFileSelectOam_ActionPanelIdle      FS_FRAME(0xc722) // 0x08740940
#define sFileSelectOam_ActionPanelClosing   FS_FRAME(0xc732) // 0x08740950
#define sFileSelectOam_SmallPanelOpening    FS_FRAME(0xc75a) // 0x08740978
#define sFileSelectOam_SmallPanelIdle       FS_FRAME(0xc782) // 0x087409a0
#define sFileSelectOam_SmallPanelClosing    FS_FRAME(0xc792) // 0x087409b0
#define sFileSelectOam_SamusHead            FS_FRAME(0xc82a) // 0x08740a48
#define sFileSelectOam_SamusHeadSelected    FS_FRAME(0xc852) // 0x08740a70
#define sFileSelectOam_CopyArrow            FS_FRAME(0xc89a) // 0x08740ab8
#define sFileSelectOam_Cursor               FS_FRAME(0xc92a) // 0x08740b48
#define sFileSelectOam_CursorSelected       FS_FRAME(0xc952) // 0x08740b70
#define sFileSelectOam_CompletedStar        FS_FRAME(0xc97a) // 0x08740b98

#define sFileSelectOamXWidthTable           BLOB_73421E(0x9986) // 0x0873dba4, u8[3][4] width in tiles by shape/size
#define sFileSelectCopyYesNoXPositions      BLOB_73421E(0x9992) // 0x0873dbb0, u8[LANGUAGE_COUNT][2] (no, yes)
#define sFileSelectEraseYesNoXPositions     BLOB_73421E(0x99a0) // 0x0873dbbe, u8[LANGUAGE_COUNT][2] (no, yes)

#define sFileSelectEnergyTankFullGfx        BLOB_73421E(0x9946) // 0x0873db64
#define sFileSelectEnergyTankHalfFullGfx    BLOB_73421E(0x98e6) // 0x0873db04, half full, last tank
#define sFileSelectEnergyTankHalfGfx        BLOB_73421E(0x9926) // 0x0873db44, half full, more tanks after
#define sFileSelectEnergyTankEmptyGfx       BLOB_73421E(0x9906) // 0x0873db24
#define sFileSelectEnergyTankHalfEmptyGfx   BLOB_73421E(0x98c6) // 0x0873dae4

#define sFileSelectBgGfx                    BLOB_73421E(0xed96)  // 0x08742fb4 (LZ77)
#define sFileSelectBg3TileTable             BLOB_73421E(0x12ec2) // 0x087470e0 (LZ77)
#define sFileSelectBgPal                    BLOB_73421E(0x13482) // 0x087476a0
#define sFileSelectBg2TileTable             BLOB_73421E(0x8d8e)  // 0x0873cfac (LZ77)
#define sFileSelectBg1TileTable             BLOB_73421E(0x9162)  // 0x0873d380 (LZ77)
#define sFileSelectBg0TileTable             BLOB_73421E(0x93ce)  // 0x0873d5ec (LZ77)
#define sFileSelectBgPalRow0                BLOB_73421E(0x9966)  // 0x0873db84
#define sFileSelectBgPalOverride            BLOB_73421E(0x98a6)  // 0x0873dac4
#define sFileSelectObjGfx                   BLOB_73421E(0x9a02)  // 0x0873dc20 (LZ77)
#define sFileSelectObjPal                   BLOB_73421E(0xcaea)  // 0x08740d08

s8 FileSelectHandler(void);
void FileSelectInit(void);
void FileSelectVblank(void);
void unk_9eaa4(void);
u8 FileSelectInput(void);
u8 FileSelectSetupOam(u8 type, u16 xPosition, u16 yPosition, u8 unused);
void FileSelectProcessSamusHead(struct FileSelectOam* pOam);
void FileSelectProcessCursor(struct FileSelectOam* pOam);
void FileSelectProcessDeleteArrow(struct FileSelectOam* pOam);
void unk_9fddc(struct FileSelectOam* pOam);
void unk_9ff00(struct FileSelectOam* pOam);
void FileSelectProcessAudioLogos(struct FileSelectOam* pOam);
void FileSelectProcessAudioSelect(struct FileSelectOam* pOam);
void FileSelectProcessFileOverlay(struct FileSelectOam* pOam);
void unk_a016c(struct FileSelectOam* pOam);
void unk_a01cc(struct FileSelectOam* pOam);
void FileSelectProcessFileActionPanel(struct FileSelectOam* pOam);
void FileSelectProcessCopyFilePanel(struct FileSelectOam* pOam);
void FileSelectProcessEraseFilePanel(struct FileSelectOam* pOam);
void unk_a039c(struct FileSelectOam* pOam);
void unk_a0424(struct FileSelectOam* pOam);
void unk_a0518(struct FileSelectOam* pOam);
void FileSelectDrawFileInfo(u8 file);
void FileSelectDrawText(u8 destination);
u8 FileSelectProcessCorruptedFile(void);
void FileSelectDrawFileCorruptedText(u8 file);
void FileSelectDrawCorruptionText(u8 destination);
void FileSelectDestroyOamOfType(u8 type);
void FileSelectSetUpAreaNameOam(u8 type, s16 xPosition, s16 yPosition, u16 area);
void FileSelectProcessOam(void);
void FileSelectDrawAllOam(void);
void FileSelectDrawOam(struct FileSelectOam* pOam);
u32 SetLanguage(u8 unused);
void unk_a13e0(void);
void unk_a1478(void);
u32 unk_a147c(void);

// Still asm (disasm_0x0807e678.s), same prototypes as port/decomp/sram_files.h
void Sram_CheckLoadSaveFile(void);
void Sram_EraseFile(u8 stage);
void Sram_CopyFile(u8 dstFile, u8 stage);
void Sram_WriteFileInfo(void);
void Sram_SetCurrentFile(u8 file);

#endif /* PORT_DECOMP_FILE_SELECT_H */
