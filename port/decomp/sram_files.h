#ifndef SRAM_FILES_H
#define SRAM_FILES_H

/*
 * Save files layer: SRAM header, save files (EWRAM copy of the SRAM), most recent file, language
 * (asm/disasm_0x0807e678.s, 0x0807eea4 - 0x080809ec).
 *
 * The EWRAM copy of the SRAM (EWRAM_SRAM, 0x8000 bytes) keeps the exact GBA byte layout so the
 * saves stay compatible with emulators:
 *   0x0000 struct SramFilesHeader (copy 0)
 *   0x0080 struct SramFilesHeader (copy 1)
 *   0x0200 + 0x2400 * n   struct SramFilesSaveFile, file n (main copy)
 *   0x1400 + 0x2400 * n   struct SramFilesSaveFile, file n (backup copy)
 *   0x7000 struct SramFilesSelectBlock "most recent save file"
 *   0x7040 struct SramFilesSelectBlock "language" (copy 0)
 *   0x7080 struct SramFilesSelectBlock "language" (copy 1)
 *   0x7100 struct SramFilesHeader (copy 2)
 * All these structs are pointer free, their sizes are checked below.
 */

#include "types.h"
#include "globals.h"
#include "structs/samus.h"
#include "structs/scroll.h"

/* ---------------------------------------------------------------------------------------------- */
/* Data blobs (static in src/data, externed here)                                                 */
/* ---------------------------------------------------------------------------------------------- */

/* PORT: static in src/data/menus/pause_debug.c (0x0858217b), must be made visible for the native build */
extern const u8 sBlob_58217b_58225c[];
/* PORT: static in src/data/sram_pointers.c (0x08582288), must be made visible for the native build */
extern const u8 sBlob_582288_58b3cc[];

/* 0x085821e8: 16 bytes written to SRAM 0x7fe0 to test the SRAM ("Met4AGB_BackUp01") */
#define sSramTestString (sBlob_58217b_58225c + 0x6D)
/* 0x085821f8: "SAVE_END" (8 bytes), end of the save file data */
#define sSramSaveEndString (sBlob_58217b_58225c + 0x7D)
/* 0x08582200: "MetroidEpisode4A" (16 bytes), start of a save file */
#define sSramSaveStartString (sBlob_58217b_58225c + 0x85)
/* 0x08582248: "MetroidAGB-EUVerE004" (20 bytes), SRAM header version string */
#define sSramHeaderVersionString (sBlob_58217b_58225c + 0xCD)

/* 0x08582288: "SELECTSAVENUMBER" + "ENDDATA_SEL_SAVE" */
#define sSramMostRecentFileStrings (sBlob_582288_58b3cc + 0x0)
/* 0x085822a8: "STARTKEYLANGUAGE" + "ENDKEY_LANGUAGE_" */
#define sSramLanguageStrings (sBlob_582288_58b3cc + 0x20)
/* 0x085822c8: default button assignments */
#define sSramDefaultButtonAssignments (*(const struct ButtonAssignments*)(sBlob_582288_58b3cc + 0x40))
/* 0x085822d4: in game timer of a new file */
#define sSramDefaultInGameTimer (*(const struct InGameTime*)(sBlob_582288_58b3cc + 0x4C))
/* 0x085822e4: default boot debug options */
#define sSramDefaultBootDebugOptions (*(const struct BootDebugOptions*)(sBlob_582288_58b3cc + 0x5C))

/* ---------------------------------------------------------------------------------------------- */
/* Structures                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

/* Compile time size check (works for agbcc and the native compilers) */
#define SRAM_FILES_CHECK_SIZE(name, type, size) typedef char name[(sizeof(type) == (size)) ? 1 : -1]

#define SRAM_FILES_SIZE 0x1200
/* Part of gVisitedMinimapTiles saved/cleared (7 areas of 0x80 bytes, not the whole 0x400 bytes array) */
#define SRAM_FILES_VISITED_MINIMAP_SIZE 0x380

/* struct SamusEnvironmentalEffect as stored in a save file (the GBA struct with a 32 bit OAM pointer) */
struct SramFilesEnvironmentalEffect {
    u8 effect;
    u8 animationDurationCounter;
    u8 currentAnimationFrame;
    u8 externalTimer;
    u8 timer1;
    u8 timer2;
    u8 unk_6;
    u8 padding_7;
    u16 xPosition;
    u16 yPosition;
    u32 pOamFrame; // GBA address of a const u16 OAM frame
};

/*
 * gCamera as stored in a save file, 0x14 bytes: struct Camera (explicit layout, agbcc rounds
 * sizeof(struct Camera) up to 16) followed by the 6 bytes at 0x03000132 that struct Camera doesn't describe
 */
struct SramFilesCamera {
    u16 xPosition;
    u16 prevXPosition;
    u16 yPosition;
    s8 xVelocity;
    s8 yVelocity;
    s8 frontWideDirection;
    s8 ladderFrontWideDirection;
    s8 frontWideXVelocity;
    u8 padding_B;
    u16 frontWideTargetXPosition;
    u8 unk_E[6]; // 0x03000132
};

/* Music state stored in a save file (fields of gMusicInfo) */
struct SramFilesMusicInfo {
    u16 musicTrack;
    u16 unk_1E;
    u8 unk_20;
    u8 priority;
    u16 unk_2;
};

/* A save file, 0x1200 bytes */
struct SramFilesSaveFile {
    /* 0x000 */ u8 startString[16]; // "MetroidEpisode4A"
    /* 0x010 */ u32 checksum; // Sum of the 0x480 words of the file (with checksum = 0 and notChecksum = -1)
    /* 0x014 */ u32 notChecksum;
    /* 0x018 */ s8 completedGame; // gGameCompletion
    /* 0x019 */ s8 introPlayed;
    /* 0x01A */ u8 unk_1A; // 0x03000016
    /* 0x01B */ u8 unk_1B; // 0x03000017
    /* 0x01C */ u8 unk_1C; // 0x03000b90, set when the file has been saved in game
    /* 0x01D */ u8 currentArea;
    /* 0x01E */ u8 currentRoom;
    /* 0x01F */ u8 lastDoorUsed;
    /* 0x020 */ u8 abilityCount;
    /* 0x021 */ u8 eventCounter;
    /* 0x022 */ u8 previousNavigationConversation;
    /* 0x023 */ u8 previousCutscene;
    /* 0x024 */ u8 minimapX;
    /* 0x025 */ u8 minimapY;
    /* 0x026 */ u16 soundEventCounter;
    /* 0x028 */ u16 previousSoundEvent;
    /* 0x02A */ u8 unk_2A; // 0x0300004d
    /* 0x02B */ u8 securityHatchLevelBackup;
    /* 0x02C */ struct SramFilesCamera camera;
    /* 0x040 */ u16 bg0XPosition;
    /* 0x042 */ u16 bg0YPosition;
    /* 0x044 */ u16 bg1XPosition;
    /* 0x046 */ u16 bg1YPosition;
    /* 0x048 */ u16 bg2XPosition;
    /* 0x04A */ u16 bg2YPosition;
    /* 0x04C */ u16 bg3XPosition;
    /* 0x04E */ u16 bg3YPosition;
    /* 0x050 */ u8 numberOfNeverReformBlocks[8];
    /* 0x058 */ u8 numberOfCollectedTanks[8];
    /* 0x060 */ struct SamusData samusData;
    /* 0x08C */ struct SamusAnimationInfo samusAnimationInfo;
    /* 0x098 */ struct SamusEcho samusEcho;
    /* 0x0A4 */ struct SramFilesEnvironmentalEffect samusEnvironmentalEffects[2];
    /* 0x0C4 */ struct Equipment equipment;
    /* 0x0D4 */ u16 preventMovementTimer;
    /* 0x0D6 */ u8 disableDrawingSamusAndScrollingFlag;
    /* 0x0D7 */ u8 padding_D7;
    /* 0x0D8 */ u16 atmosphericStabilizersOnline;
    /* 0x0DA */ u16 missileGeronsDestroyed;
    /* 0x0DC */ u16 superMissileGeronsDestroyed;
    /* 0x0DE */ u16 powerBombGeronsDestroyed;
    /* 0x0E0 */ u16 gadorasDestroyed;
    /* 0x0E2 */ u8 missileHatchDestroyed;
    /* 0x0E3 */ u8 waterLowered;
    /* 0x0E4 */ struct InGameTime inGameTimer;
    /* 0x0E8 */ struct SramFilesMusicInfo musicInfo;
    /* 0x0F0 */ u8 endString[8]; // "SAVE_END"
    /* 0x0F8 */ u8 unk_F8[0x208];
    /*
     * 0x300: world data:
     *   0x000 visited minimap tiles (0x380 bytes)
     *   0x380 never reform blocks of each area, packed (gNumberOfNeverReformBlocks[i] * 3 bytes rounded to 4)
     *   0xC80 collected tanks of each area, packed (gNumberOfCollectedTanks[i] * 4 bytes)
     */
    /* 0x300 */ u8 worldData[0xF00];
};

/* SRAM header, 0x80 bytes (3 copies) */
struct SramFilesHeader {
    /* 0x00 */ u32 checksum; // Sum of the 0x20 words (with checksum = 0 and notChecksum = -1)
    /* 0x04 */ u32 notChecksum;
    /* 0x08 */ u8 unk_8; // '0'
    /* 0x09 */ u8 unk_9; // '1'
    /* 0x0A */ u8 unk_A; // 0x03000010
    /* 0x0B */ u8 unk_B; // 2
    /* 0x0C */ u8 versionString[20];
    /* 0x20 */ u8 unk_20[0x60];
};

/* Small checked block (most recent save file and language), 0x40 bytes */
struct SramFilesSelectBlock {
    /* 0x00 */ u8 magic; // 0x1e most recent save file, 0x1f language
    /* 0x01 */ u8 writeCounter;
    /* 0x02 */ u16 checksum; // Sum of the 0x20 halfwords (with checksum = 0 and notChecksum = 0xffff)
    /* 0x04 */ u16 notChecksum;
    /* 0x06 */ u8 startString[16];
    /* 0x16 */ u8 value;
    /* 0x17 */ u8 endString[16];
    /* 0x27 */ u8 unk_27[0x19];
};

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

SRAM_FILES_CHECK_SIZE(SramFilesCheck_EnvEffect, struct SramFilesEnvironmentalEffect, 0x10);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_Camera, struct SramFilesCamera, 0x14);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_MusicInfo, struct SramFilesMusicInfo, 0x8);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_SaveFile, struct SramFilesSaveFile, SRAM_FILES_SIZE);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_Header, struct SramFilesHeader, 0x80);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_SelectBlock, struct SramFilesSelectBlock, 0x40);
SRAM_FILES_CHECK_SIZE(SramFilesCheck_FileInfo, struct FileSelectFileInfo, 0x14);

/* EWRAM copy of the SRAM */
#define SRAM_FILES_HEADER_0 ((struct SramFilesHeader*)(EWRAM_SRAM + 0x0))
#define SRAM_FILES_HEADER_1 ((struct SramFilesHeader*)(EWRAM_SRAM + 0x80))
#define SRAM_FILES_HEADER_2 ((struct SramFilesHeader*)(EWRAM_SRAM + 0x7100))
#define SRAM_FILES_MOST_RECENT ((struct SramFilesSelectBlock*)(EWRAM_SRAM + 0x7000))
#define SRAM_FILES_LANGUAGE(copy) ((struct SramFilesSelectBlock*)sUnk_582280[(copy)])
#define SRAM_FILES_SAVE(file) ((struct SramFilesSaveFile*)sSaveDataEwramPointers[(file)])
#define SRAM_FILES_SAVE_BACKUP(file) ((struct SramFilesSaveFile*)sSaveDataEwramBackupPointers[(file)])
#define SRAM_FILES_WORLD_DATA(file) ((u8*)sUnk_582274[(file)])

/*
 * PORT: the OAM frame pointer of the environmental effects is saved as a 32 bit GBA address.
 * On the native build the port must provide the conversion between ROM data pointers and GBA addresses.
 */
#ifdef PLATFORM_PC
u32 PortPointerToGbaAddress(const void* ptr);
const void* PortGbaAddressToPointer(u32 address);
#define SRAM_FILES_PTR_TO_SAVE(ptr) PortPointerToGbaAddress((ptr))
#define SRAM_FILES_SAVE_TO_PTR(value) ((const u16*)PortGbaAddressToPointer((value)))
#else
#define SRAM_FILES_PTR_TO_SAVE(ptr) ((u32)(ptr))
#define SRAM_FILES_SAVE_TO_PTR(value) ((const u16*)(value))
#endif

/* ---------------------------------------------------------------------------------------------- */
/* RAM without a linker.ld name                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/* 0x03000010, SRAM header byte 0xa */
extern u8 gUnk_3000010;
/* 0x03000016 and 0x03000017, the 2 bytes after gGameCompletion (saved with it) */
extern u8 gUnk_3000016;
extern u8 gUnk_3000017;
/* 0x0300004c (named by navigation.h) */
extern u8 gNavigationTargetLocation;
/* 0x0300004d */
extern u8 gUnk_300004d;
/* 0x03000132, the 6 bytes after struct Camera in gCamera (saved with it) */
extern u8 gUnk_3000132[6];
/* 0x03000b8e, SRAM test failed (the SRAM isn't read) */
extern u8 gUnk_3000b8e;
/* 0x03000b90, set by Sram_QuickSave */
extern u8 gUnk_3000b90;
/* 0x03000b94 */
extern struct FileSelectFileInfo gFileSelectFileInfo[3];

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

void Sram_ReadAll(void);
void Sram_WriteHeader(void);
void Sram_ReadHeader(void);
u32 Sram_VerifyHeader(u8 headerId);
void Sram_ProcessIntroSave(u8 stage);
void Sram_WriteHeaderAndGameInfo(void);
void Sram_ProcessEndingSave(u8 stage);
void Sram_CopyGameCompletion(void);
void Sram_QuickSave(u8 stage);
void SramWrite_ToEwram(void);
void SramRead_FromEwram(void);
void Sram_StringCopy_MetroidEpisode4A(u8* dst, const u8* src);
void Sram_StringCopy_SAVE_END(u8* dst, const u8* src);
void SramTestFlash(void);
void Sram_BackupCurrentFile_Unused(void);
void unk_7fb84(void);
void unk_7fd10(void);
u32 unk_7fdb0(u8 useBackup);
void SramLoad_CurrentSave(void);
void SramLoad_CurrentSave_Unused(void);
void SramWrite_WorldData(void);
void SramRead_WorldData(void);
void SramWrite_MostRecentSaveFile(void);
void SramRead_MostRecentSaveFile(void);
void SramWrite_Language(void);
void SramRead_Language(void);
void Sram_InitSaveFile(void);
void Sram_ResetForDemo(void);
void Sram_CheckLoadSaveFile(void);
void Sram_EraseFile(u8 stage);
void Sram_CopyFile(u8 dstFile, u8 stage);
void Sram_WriteFileInfo(void);
void Sram_LoadingfileVblank(void);
void Sram_AfterLoadingFileVblank(void);
s8 Sram_ChecLoadSaveFileWithBlank(void);
void Sram_SetCurrentFile(u8 file);

#endif /* SRAM_FILES_H */
