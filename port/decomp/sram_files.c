#include "sram_files.h"

#include "gba.h"
#include "macros.h"
#include "globals.h"
#include "dma.h"
#include "callbacks.h"
#include "event.h"
#include "minimap.h"
#include "sram_misc.h"
#include "sram/sram.h"
#include "audio/track_internal.h"

#include "data/sram_pointers.h"

#include "structs/audio.h"
#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/minimap.h"
#include "structs/samus.h"
#include "structs/save_file.h"
#include "structs/scroll.h"
#include "structs/sprite.h"
#include "structs/menus/boot_debug.h"

#ifndef PLATFORM_PC
// RAM without a linker.ld name, bound to its GBA address (native definitions are generated elsewhere)
asm(".set gUnk_3000010, 0x03000010");
asm(".set gUnk_3000016, 0x03000016");
asm(".set gUnk_3000017, 0x03000017");
asm(".set gNavigationTargetLocation, 0x0300004c");
asm(".set gUnk_300004d, 0x0300004d");
asm(".set gUnk_3000132, 0x03000132");
asm(".set gUnk_3000b8e, 0x03000b8e");
asm(".set gUnk_3000b90, 0x03000b90");
asm(".set gFileSelectFileInfo, 0x03000b94");
#endif

// Not in a decomp header
extern const struct Door* sAreaDoorPointers[];
#ifdef PLATFORM_PC
#include <string.h>
#else
void* memset(void* dst, int value, unsigned long size);
#endif

#define SRAM_FILES_SAVE_FILE_WORDS (sizeof(struct SramFilesSaveFile) / sizeof(u32))
#define SRAM_FILES_HEADER_WORDS (sizeof(struct SramFilesHeader) / sizeof(u32))
#define SRAM_FILES_BLOCK_HALFWORDS (sizeof(struct SramFilesSelectBlock) / sizeof(u16))

/**
 * @brief Computes the checksum (sum of the words) of a save file
 *
 * @param pFile Save file
 * @return u32 Checksum
 */
static u32 SramFilesSaveChecksum(struct SramFilesSaveFile* pFile)
{
    u32* pData;
    u32 sum;
    s32 i;

    pData = (u32*)pFile;
    sum = 0;
    for (i = 0; i < SRAM_FILES_SAVE_FILE_WORDS; i++)
        sum += pData[i];

    return sum;
}

/**
 * @brief Computes the checksum (sum of the words) of a SRAM header
 *
 * @param pHeader Header
 * @return u32 Checksum
 */
static u32 SramFilesHeaderChecksum(struct SramFilesHeader* pHeader)
{
    u32* pData;
    u32 sum;
    s32 i;

    pData = (u32*)pHeader;
    sum = 0;
    for (i = 0; i < SRAM_FILES_HEADER_WORDS; i++)
        sum += pData[i];

    return sum;
}

/**
 * @brief Computes the checksum (sum of the halfwords) of a select block
 *
 * @param pBlock Block
 * @return u16 Checksum
 */
static u16 SramFilesBlockChecksum(struct SramFilesSelectBlock* pBlock)
{
    u16* pData;
    u16 sum;
    s32 i;

    pData = (u16*)pBlock;
    sum = 0;
    for (i = 0; i < SRAM_FILES_BLOCK_HALFWORDS; i++)
        sum += pData[i];

    return sum;
}

/**
 * @brief Checks the strings of a select block
 *
 * @param pBlock Block
 * @param pStrings Start string (16 bytes) followed by the end string (16 bytes)
 * @return u32 bool, the strings are correct
 */
static u32 SramFilesBlockCheckStrings(struct SramFilesSelectBlock* pBlock, const u8* pStrings)
{
    s32 i;

    for (i = 0; i < 16; i++)
    {
        if (pBlock->startString[i] != pStrings[i])
            return FALSE;
        if (pBlock->endString[i] != pStrings[16 + i])
            return FALSE;
    }

    return TRUE;
}

/**
 * @brief 7eea4 | 18 | Reads everything from the SRAM
 *
 */
void Sram_ReadAll(void)
{
    Sram_ReadHeader();
    unk_7fb84();
    SramRead_MostRecentSaveFile();
    SramRead_Language();
}

/**
 * @brief 7eebc | 6c | Writes the SRAM header
 *
 */
void Sram_WriteHeader(void)
{
    struct SramFilesHeader* pHeader;
    s32 i;
    u32 checksum;

    pHeader = SRAM_FILES_HEADER_0;
    pHeader->unk_8 = '0';
    pHeader->unk_9 = '1';
    pHeader->unk_A = gUnk_3000010;
    pHeader->unk_B = 2;

    for (i = 0; i < ARRAY_SIZE(pHeader->versionString); i++)
        pHeader->versionString[i] = sSramHeaderVersionString[i];

    pHeader->checksum = 0;
    pHeader->notChecksum = -1;
    checksum = SramFilesHeaderChecksum(pHeader);
    pHeader->checksum = checksum;
    pHeader->notChecksum = ~checksum;

    unk_c98();
}

/**
 * @brief 7ef28 | 150 | Reads and verifies the SRAM header
 *
 */
void Sram_ReadHeader(void)
{
    u32 error0;
    u32 error1;
    u32 error2;

    SramTestFlash();
    if (!gUnk_3000b8e)
        ReadSramHeaderToEwram();

    error0 = Sram_VerifyHeader(0);
    error1 = Sram_VerifyHeader(1);
    error2 = Sram_VerifyHeader(2);

    if (error0)
    {
        DMA3_FILL_16(USHORT_MAX, SRAM_FILES_HEADER_0, sizeof(struct SramFilesHeader));

        if (error2)
        {
            DMA3_FILL_16(USHORT_MAX, SRAM_FILES_HEADER_2, sizeof(struct SramFilesHeader));

            if (error1)
            {
                DMA3_FILL_16(USHORT_MAX, SRAM_FILES_HEADER_1, sizeof(struct SramFilesHeader));
            }
            else
            {
                // Restore from header 1
                DMA3_COPY_16(SRAM_FILES_HEADER_1, SRAM_FILES_HEADER_0, sizeof(struct SramFilesHeader) / 2);
                error0 = 0;
                unk_c98();
            }
        }
        else
        {
            // Restore from header 2
            DMA3_COPY_16(SRAM_FILES_HEADER_2, SRAM_FILES_HEADER_0, sizeof(struct SramFilesHeader) / 2);
            error0 = 0;
            unk_c98();

            if (error1)
            {
                DMA3_COPY_16(SRAM_FILES_HEADER_0, SRAM_FILES_HEADER_1, sizeof(struct SramFilesHeader) / 2);
                unk_cd8();
            }
        }
    }
    else
    {
        DMA3_COPY_16(SRAM_FILES_HEADER_0, SRAM_FILES_HEADER_1, sizeof(struct SramFilesHeader) / 2);
        unk_cd8();

        if (error2)
        {
            DMA3_COPY_16(SRAM_FILES_HEADER_0, SRAM_FILES_HEADER_2, sizeof(struct SramFilesHeader) / 2);
            unk_cf0();
        }
    }

    if (!error0)
    {
        gUnk_3000010 = 0;
    }
    else
    {
        // Every header is corrupted
        EraseSram();
        gUnk_3000010 = 0;
        Sram_WriteHeader();
    }
}

/**
 * @brief 7f078 | 80 | Verifies a SRAM header
 *
 * @param headerId Header id (0, 1 or 2)
 * @return u32 Error flags (1 = checksum, 2 = version string, 4 = not checksum)
 */
u32 Sram_VerifyHeader(u8 headerId)
{
    struct SramFilesHeader* pHeader;
    u32 error;
    u32 checksum;
    s32 i;

    error = 0;

    if (headerId == 2)
        pHeader = SRAM_FILES_HEADER_2;
    else if (headerId == 1)
        pHeader = SRAM_FILES_HEADER_1;
    else
        pHeader = SRAM_FILES_HEADER_0;

    checksum = SramFilesHeaderChecksum(pHeader);
    if (pHeader->checksum != checksum)
        error |= 1;

    for (i = 0; i < ARRAY_SIZE(pHeader->versionString); i++)
    {
        if (pHeader->versionString[i] != sSramHeaderVersionString[i])
            error |= 2;
    }

    if (pHeader->checksum != ~pHeader->notChecksum)
        error |= 4;

    return error;
}

/**
 * @brief 7f0f8 | 138 | Saves after the intro of a new file
 *
 * @param stage Stage
 */
void Sram_ProcessIntroSave(u8 stage)
{
    struct FileSelectFileInfo* pInfo;

    pInfo = &gFileSelectFileInfo[gMostRecentSaveFile];

    if (pInfo->unk_f)
    {
        switch (stage)
        {
            case 0:
                gDisableSoftReset = TRUE;
                gGameCompletion.introPlayed = TRUE;
                pInfo->introPlayed = TRUE;
                return;

            case 1:
            case 2:
                return;

            case 3:
                DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
                    sizeof(struct SramFilesSaveFile), 16);
                break;
        }
    }
    else
    {
        switch (stage)
        {
            case 0:
                gDisableSoftReset = TRUE;
                gGameCompletion.introPlayed = TRUE;
                pInfo->introPlayed = TRUE;
                gGameCompletion.completedGame = gFileSelectFileInfo[gMostRecentSaveFile].completedGame;
                BitFill(3, 0, SRAM_FILES_SAVE(gMostRecentSaveFile), 0x300, 16);
                return;

            case 1:
                Sram_WriteHeaderAndGameInfo();
                return;

            case 2:
                WriteMostRecentFileToSram();
                return;

            case 3:
                DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
                    sizeof(struct SramFilesSaveFile), 16);
                break;
        }
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 7f230 | 84 | Writes the start of the current save file (strings, game completion, checksum)
 *
 */
void Sram_WriteHeaderAndGameInfo(void)
{
    struct SramFilesSaveFile* pFile;
    u32 checksum;

    pFile = SRAM_FILES_SAVE(gMostRecentSaveFile);
    Sram_StringCopy_MetroidEpisode4A(pFile->startString, sSramSaveStartString);
    pFile->checksum = 0;
    pFile->notChecksum = -1;
    pFile->introPlayed = gGameCompletion.introPlayed;
    pFile->completedGame = gGameCompletion.completedGame;
    Sram_StringCopy_SAVE_END(pFile->endString, sSramSaveEndString);

    checksum = SramFilesSaveChecksum(SRAM_FILES_SAVE(gMostRecentSaveFile));
    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f2b4 | 90 | Saves after the ending
 *
 * @param stage Stage
 */
void Sram_ProcessEndingSave(u8 stage)
{
    switch (stage)
    {
        case 0:
            ReadMostRecentFileToEwram();
            break;

        case 1:
            gGameCompletion.completedGame = TRUE;
            Sram_CopyGameCompletion();
            break;

        case 2:
            WriteMostRecentFileToSram();
            gFileSelectFileInfo[gMostRecentSaveFile].completedGame = gGameCompletion.completedGame;
            break;

        case 3:
            DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
                sizeof(struct SramFilesSaveFile), 16);
            break;
    }
}

/**
 * @brief 7f344 | 68 | Copies the game completion to the current save file
 *
 */
void Sram_CopyGameCompletion(void)
{
    struct SramFilesSaveFile* pFile;
    u32 checksum;

    pFile = SRAM_FILES_SAVE(gMostRecentSaveFile);
    pFile->checksum = 0;
    pFile->notChecksum = -1;
    pFile->completedGame = gGameCompletion.completedGame;

    checksum = SramFilesSaveChecksum(SRAM_FILES_SAVE(gMostRecentSaveFile));
    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f3ac | a4 | Saves the game (save room/message banner)
 *
 * @param stage Stage
 */
void Sram_QuickSave(u8 stage)
{
    switch (stage)
    {
        case 0:
            gDisableSoftReset = TRUE;
            gUnk_3000b90 = TRUE;
            WriteMostRecentFileBackupToSram();
            return;

        case 1:
            SramWrite_WorldData();
            SramWrite_ToEwram();
            return;

        case 2:
            WriteMostRecentFileToSram();
            gFileSelectFileInfo[gMostRecentSaveFile].exists = TRUE;
            return;

        case 3:
            DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
                sizeof(struct SramFilesSaveFile), 16);
            break;
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 7f450 | 370 | Writes the game state to the current save file (EWRAM)
 *
 */
void SramWrite_ToEwram(void)
{
    struct SramFilesSaveFile* pFile;
    s32 i;
    u32 checksum;

    pFile = SRAM_FILES_SAVE(gMostRecentSaveFile);
    Sram_StringCopy_MetroidEpisode4A(pFile->startString, sSramSaveStartString);
    pFile->checksum = 0;
    pFile->notChecksum = -1;

    pFile->completedGame = gGameCompletion.completedGame;
    pFile->introPlayed = gGameCompletion.introPlayed;
    pFile->unk_1A = gUnk_3000016;
    pFile->unk_1B = gUnk_3000017;
    pFile->unk_1C = gUnk_3000b90;

    pFile->currentArea = gCurrentArea;
    pFile->currentRoom = gCurrentRoom;
    pFile->lastDoorUsed = gLastDoorUsed;
    pFile->abilityCount = gAbilityCount;
    pFile->eventCounter = gEventCounter;
    pFile->previousNavigationConversation = gPreviousNavigationConversation;
    pFile->previousCutscene = gPreviousCutscene;
    pFile->minimapX = gMinimapX;
    pFile->minimapY = gMinimapY;
    pFile->soundEventCounter = gSoundEventCounter;
    pFile->previousSoundEvent = gPreviousSoundEvent;
    pFile->unk_2A = gUnk_300004d;
    pFile->securityHatchLevelBackup = gSecurityHatchLevelBackup;

    pFile->camera.xPosition = gCamera.xPosition;
    pFile->camera.prevXPosition = gCamera.prevXPosition;
    pFile->camera.yPosition = gCamera.yPosition;
    pFile->camera.xVelocity = gCamera.xVelocity;
    pFile->camera.yVelocity = gCamera.yVelocity;
    pFile->camera.frontWideDirection = gCamera.frontWideDirection;
    pFile->camera.ladderFrontWideDirection = gCamera.ladderFrontWideDirection;
    pFile->camera.frontWideXVelocity = gCamera.frontWideXVelocity;
    pFile->camera.padding_B = ((u8*)&gCamera)[0xB];
    pFile->camera.frontWideTargetXPosition = gCamera.frontWideTargetXPosition;
    for (i = 0; i < ARRAY_SIZE(pFile->camera.unk_E); i++)
        pFile->camera.unk_E[i] = gUnk_3000132[i];

    pFile->bg0XPosition = gBg0XPosition;
    pFile->bg0YPosition = gBg0YPosition;
    pFile->bg1XPosition = gBg1XPosition;
    pFile->bg1YPosition = gBg1YPosition;
    pFile->bg2XPosition = gBg2XPosition;
    pFile->bg2YPosition = gBg2YPosition;
    pFile->bg3XPosition = gBg3XPosition;
    pFile->bg3YPosition = gBg3YPosition;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        pFile->numberOfNeverReformBlocks[i] = gNumberOfNeverReformBlocks[i];

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        pFile->numberOfCollectedTanks[i] = gNumberOfCollectedTanks[i];

    pFile->samusData = gSamusData;
    pFile->samusAnimationInfo = gSamusAnimationInfo;
    pFile->samusEcho = gSamusEcho;

    for (i = 0; i < 2; i++)
    {
        pFile->samusEnvironmentalEffects[i].effect = gSamusEnvironmentalEffects[i].effect;
        pFile->samusEnvironmentalEffects[i].animationDurationCounter = gSamusEnvironmentalEffects[i].animationDurationCounter;
        pFile->samusEnvironmentalEffects[i].currentAnimationFrame = gSamusEnvironmentalEffects[i].currentAnimationFrame;
        pFile->samusEnvironmentalEffects[i].externalTimer = gSamusEnvironmentalEffects[i].externalTimer;
        pFile->samusEnvironmentalEffects[i].timer1 = gSamusEnvironmentalEffects[i].timer1;
        pFile->samusEnvironmentalEffects[i].timer2 = gSamusEnvironmentalEffects[i].timer2;
        pFile->samusEnvironmentalEffects[i].unk_6 = gSamusEnvironmentalEffects[i].unk_6;
        // PORT: the GBA copies the padding byte too, it is never used
        pFile->samusEnvironmentalEffects[i].padding_7 = ((u8*)&gSamusEnvironmentalEffects[i])[7];
        pFile->samusEnvironmentalEffects[i].xPosition = gSamusEnvironmentalEffects[i].xPosition;
        pFile->samusEnvironmentalEffects[i].yPosition = gSamusEnvironmentalEffects[i].yPosition;
        pFile->samusEnvironmentalEffects[i].pOamFrame = SRAM_FILES_PTR_TO_SAVE(gSamusEnvironmentalEffects[i].pOamFrame);
    }

    pFile->equipment = gEquipment;
    pFile->preventMovementTimer = gPreventMovementTimer;
    pFile->disableDrawingSamusAndScrollingFlag = gDisableDrawingSamusAndScrollingFlag;
    pFile->atmosphericStabilizersOnline = gAtmosphericStabilizersOnline;
    pFile->missileGeronsDestroyed = gMissileGeronsDestroyed;
    pFile->superMissileGeronsDestroyed = gSuperMissileGeronsDestroyed;
    pFile->powerBombGeronsDestroyed = gPowerBombGeronsDestroyed;
    pFile->gadorasDestroyed = gGadorasDestroyed;
    pFile->missileHatchDestroyed = gMissileHatchDestroyed;
    pFile->waterLowered = gWaterLowered;
    pFile->inGameTimer = gInGameTimer;

    pFile->musicInfo.musicTrack = gMusicInfo.musicTrack;
    pFile->musicInfo.unk_1E = gMusicInfo.unk_1E;
    pFile->musicInfo.unk_20 = gMusicInfo.unk_20;
    pFile->musicInfo.priority = gMusicInfo.priority;
    pFile->musicInfo.unk_2 = gMusicInfo.unk_2;

    Sram_StringCopy_SAVE_END(pFile->endString, sSramSaveEndString);

    checksum = SramFilesSaveChecksum(SRAM_FILES_SAVE(gMostRecentSaveFile));
    pFile->checksum = checksum;
    pFile->notChecksum = ~checksum;
}

/**
 * @brief 7f7c0 | 2e8 | Reads the game state from the current save file (EWRAM)
 *
 */
void SramRead_FromEwram(void)
{
    struct SramFilesSaveFile* pFile;
    s32 i;

    pFile = SRAM_FILES_SAVE(gMostRecentSaveFile);

    gGameCompletion.completedGame = pFile->completedGame;
    gGameCompletion.introPlayed = pFile->introPlayed;
    gUnk_3000016 = pFile->unk_1A;
    gUnk_3000017 = pFile->unk_1B;
    gUnk_3000b90 = pFile->unk_1C;

    gCurrentArea = pFile->currentArea;
    gCurrentRoom = pFile->currentRoom;
    gLastDoorUsed = pFile->lastDoorUsed;
    gAbilityCount = pFile->abilityCount;
    gEventCounter = pFile->eventCounter;
    gPreviousNavigationConversation = pFile->previousNavigationConversation;
    gPreviousCutscene = pFile->previousCutscene;
    gMinimapX = pFile->minimapX;
    gMinimapY = pFile->minimapY;
    gSoundEventCounter = pFile->soundEventCounter;
    gPreviousSoundEvent = pFile->previousSoundEvent;
    gUnk_300004d = pFile->unk_2A;
    gSecurityHatchLevelBackup = pFile->securityHatchLevelBackup;

    gCamera.xPosition = pFile->camera.xPosition;
    gCamera.prevXPosition = pFile->camera.prevXPosition;
    gCamera.yPosition = pFile->camera.yPosition;
    gCamera.xVelocity = pFile->camera.xVelocity;
    gCamera.yVelocity = pFile->camera.yVelocity;
    gCamera.frontWideDirection = pFile->camera.frontWideDirection;
    gCamera.ladderFrontWideDirection = pFile->camera.ladderFrontWideDirection;
    gCamera.frontWideXVelocity = pFile->camera.frontWideXVelocity;
    ((u8*)&gCamera)[0xB] = pFile->camera.padding_B;
    gCamera.frontWideTargetXPosition = pFile->camera.frontWideTargetXPosition;
    for (i = 0; i < ARRAY_SIZE(pFile->camera.unk_E); i++)
        gUnk_3000132[i] = pFile->camera.unk_E[i];

    gBg0XPosition = pFile->bg0XPosition;
    gBg0YPosition = pFile->bg0YPosition;
    gBg1XPosition = pFile->bg1XPosition;
    gBg1YPosition = pFile->bg1YPosition;
    gBg2XPosition = pFile->bg2XPosition;
    gBg2YPosition = pFile->bg2YPosition;
    gBg3XPosition = pFile->bg3XPosition;
    gBg3YPosition = pFile->bg3YPosition;

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        gNumberOfNeverReformBlocks[i] = pFile->numberOfNeverReformBlocks[i];

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
        gNumberOfCollectedTanks[i] = pFile->numberOfCollectedTanks[i];

    gSamusData = pFile->samusData;
    gSamusAnimationInfo = pFile->samusAnimationInfo;
    gSamusEcho = pFile->samusEcho;

    for (i = 0; i < 2; i++)
    {
        gSamusEnvironmentalEffects[i].effect = pFile->samusEnvironmentalEffects[i].effect;
        gSamusEnvironmentalEffects[i].animationDurationCounter = pFile->samusEnvironmentalEffects[i].animationDurationCounter;
        gSamusEnvironmentalEffects[i].currentAnimationFrame = pFile->samusEnvironmentalEffects[i].currentAnimationFrame;
        gSamusEnvironmentalEffects[i].externalTimer = pFile->samusEnvironmentalEffects[i].externalTimer;
        gSamusEnvironmentalEffects[i].timer1 = pFile->samusEnvironmentalEffects[i].timer1;
        gSamusEnvironmentalEffects[i].timer2 = pFile->samusEnvironmentalEffects[i].timer2;
        gSamusEnvironmentalEffects[i].unk_6 = pFile->samusEnvironmentalEffects[i].unk_6;
        // PORT: the GBA copies the padding byte too, it is never used
        ((u8*)&gSamusEnvironmentalEffects[i])[7] = pFile->samusEnvironmentalEffects[i].padding_7;
        gSamusEnvironmentalEffects[i].xPosition = pFile->samusEnvironmentalEffects[i].xPosition;
        gSamusEnvironmentalEffects[i].yPosition = pFile->samusEnvironmentalEffects[i].yPosition;
        gSamusEnvironmentalEffects[i].pOamFrame = SRAM_FILES_SAVE_TO_PTR(pFile->samusEnvironmentalEffects[i].pOamFrame);
    }

    gEquipment = pFile->equipment;
    gPreventMovementTimer = pFile->preventMovementTimer;
    gDisableDrawingSamusAndScrollingFlag = pFile->disableDrawingSamusAndScrollingFlag;
    gAtmosphericStabilizersOnline = pFile->atmosphericStabilizersOnline;
    gMissileGeronsDestroyed = pFile->missileGeronsDestroyed;
    gSuperMissileGeronsDestroyed = pFile->superMissileGeronsDestroyed;
    gPowerBombGeronsDestroyed = pFile->powerBombGeronsDestroyed;
    gGadorasDestroyed = pFile->gadorasDestroyed;
    gMissileHatchDestroyed = pFile->missileHatchDestroyed;
    gWaterLowered = pFile->waterLowered;
    gInGameTimer = pFile->inGameTimer;

    gMusicInfo.musicTrack = pFile->musicInfo.musicTrack;
    gMusicInfo.unk_1E = pFile->musicInfo.unk_1E;
    gMusicInfo.unk_20 = pFile->musicInfo.unk_20;
    gMusicInfo.priority = pFile->musicInfo.priority;
    gMusicInfo.unk_2 = pFile->musicInfo.unk_2;
}

/**
 * @brief 7faa8 | 1c | Copies the 16 bytes start string of a save file
 *
 * @param dst Destination
 * @param src Source
 */
void Sram_StringCopy_MetroidEpisode4A(u8* dst, const u8* src)
{
    s32 i;

    for (i = 0; i < 16; i++)
        dst[i] = src[i];
}

/**
 * @brief 7fac4 | 1c | Copies the 8 bytes end string of a save file
 *
 * @param dst Destination
 * @param src Source
 */
void Sram_StringCopy_SAVE_END(u8* dst, const u8* src)
{
    s32 i;

    for (i = 0; i < 8; i++)
        dst[i] = src[i];
}

/**
 * @brief 7fae0 | 68 | Tests if the SRAM can be written
 *
 */
void SramTestFlash(void)
{
    u8 buffer[16];
    u32 error;
    s32 i;

    gUnk_3000b8e = FALSE;

    error = SramWriteChecked((u8*)sSramTestString, (u8*)SRAM_BASE + 0x7FE0, sizeof(buffer)) != NULL;

    // Read it back, change it and write it again
    SramWriteUnchecked((u8*)SRAM_BASE + 0x7FE0, buffer, sizeof(buffer));
    for (i = 0; i < 16; i++)
        buffer[i]++;

    if (SramWriteChecked(buffer, (u8*)SRAM_BASE + 0x7FE0, sizeof(buffer)) != NULL)
        error |= 2;

    gUnk_3000b8e = error != 0;
}

/**
 * @brief 7fb48 | 3c | Backs up the current file (unused)
 *
 */
void Sram_BackupCurrentFile_Unused(void)
{
    DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
        sizeof(struct SramFilesSaveFile), 16);
    WriteMostRecentFileBackupToSram();
}

/**
 * @brief 7fb84 | 18c | Reads and verifies every save file
 *
 */
void unk_7fb84(void)
{
    struct FileSelectFileInfo empty;
    s32 i;

    memset(&empty, 0, sizeof(empty));
    for (i = 0; i < ARRAY_SIZE(gFileSelectFileInfo); i++)
        gFileSelectFileInfo[i] = empty;

    gMostRecentSaveFile = 0;
    gIsLoadingFile = FALSE;

    if (!gUnk_3000b8e)
        ReadAllFilesToEwram();

    for (i = 0; i < ARRAY_SIZE(gFileSelectFileInfo); i++)
    {
        gMostRecentSaveFile = i;
        unk_7fd10();

        switch (gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag)
        {
            case 0:
                // Main copy is fine, update the backup
                DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile),
                    sizeof(struct SramFilesSaveFile), 16);
                WriteMostRecentFileBackupToSram();
                gFileSelectFileInfo[i].exists = TRUE;
                break;

            case 1:
                // Main copy is corrupted, restore it from the backup
                DmaTransfer(3, SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile), SRAM_FILES_SAVE(gMostRecentSaveFile),
                    sizeof(struct SramFilesSaveFile), 16);
                gFileSelectFileInfo[i].exists = TRUE;
                break;

            case 2:
                BitFill(3, USHORT_MAX, SRAM_FILES_SAVE(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
                BitFill(3, USHORT_MAX, SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
                break;

            case 3:
                BitFill(3, USHORT_MAX, SRAM_FILES_SAVE(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
                WriteMostRecentFileToSram();
                BitFill(3, USHORT_MAX, SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
                WriteMostRecentFileBackupToSram();
                gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 0;
                break;

            default:
                while (TRUE) {}
        }
    }

    gMostRecentSaveFile = 0;
}

/**
 * @brief 7fd10 | a0 | Verifies both copies of the current save file and sets its corruption flag
 *
 */
void unk_7fd10(void)
{
    u32 mainError;
    u32 backupError;

    mainError = unk_7fdb0(FALSE);
    backupError = unk_7fdb0(TRUE);

    if (mainError == 0)
    {
        gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 0;
    }
    else if (mainError == 1)
    {
        gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 1;
        if (backupError != 0)
            gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 2;
    }
    else
    {
        gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 3;
        if (backupError == 0)
            gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 1;
        else if (backupError == 1)
            gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 2;
    }
}

/**
 * @brief 7fdb0 | b0 | Verifies a copy of the current save file, erases it if it isn't a save file
 *
 * @param useBackup Verify the backup copy
 * @return u32 0 = fine, 1 = bad checksum or bad start string, 2 = both
 */
u32 unk_7fdb0(u8 useBackup)
{
    struct SramFilesSaveFile* pFile;
    u32 error;
    u32 stringError;
    u32 checksum;
    s32 i;

    error = 0;
    stringError = 0;

    if (!useBackup)
        pFile = SRAM_FILES_SAVE(gMostRecentSaveFile);
    else
        pFile = SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile);

    checksum = SramFilesSaveChecksum(pFile);
    if (pFile->checksum != checksum || pFile->checksum != ~pFile->notChecksum)
        error |= 1;

    for (i = 0; i < ARRAY_SIZE(pFile->startString); i++)
    {
        if (sSramSaveStartString[i] != pFile->startString[i])
            stringError |= 1;
    }

    error += stringError;
    if (error > 1)
        BitFill(3, USHORT_MAX, pFile, sizeof(struct SramFilesSaveFile), 16);

    return error;
}

/**
 * @brief 7fe60 | 34 | Loads the current save file if a file is being loaded
 *
 */
void SramLoad_CurrentSave(void)
{
    if (gIsLoadingFile == TRUE)
    {
        SramRead_FromEwram();
        SramRead_WorldData();

        gSamusData.pose = 0x3D;
        gSamusData.animationDurationCounter = 0;
        gSamusData.currentAnimationFrame = 0;
    }
}

/**
 * @brief 7fe94 | 10 | Loads the current save file (unused)
 *
 */
void SramLoad_CurrentSave_Unused(void)
{
    SramRead_FromEwram();
    SramRead_WorldData();
}

/**
 * @brief 7fea4 | d8 | Writes the world data (minimap, never reform blocks, tanks) to the current save file
 *
 */
void SramWrite_WorldData(void)
{
    u8* pWorld;
    s32 i;
    s32 size;
    s32 offset;

    pWorld = SRAM_FILES_WORLD_DATA(gMostRecentSaveFile);
    DmaTransfer(3, gVisitedMinimapTiles, pWorld, SRAM_FILES_VISITED_MINIMAP_SIZE, 16);

    offset = SRAM_FILES_VISITED_MINIMAP_SIZE;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfNeverReformBlocks[i] * 3;
        if (size & 3)
            size = (size & 0xFFFC) + 4;

        if (size != 0)
        {
            // PORT: the area slots are 0, 2, 3, ..., 8; slot 8 is past the end of gNeverReformBlocks[8]
            // (the EWRAM buffer has room for 9 slots)
            DmaTransfer(3, gNeverReformBlocks[0] + (i != 0 ? i + 1 : 0) * NEVER_REFORM_BLOCKS_SIZE,
                pWorld + offset, size, 16);
            offset += size;
        }
    }

    offset = 0xC80;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfCollectedTanks[i] * 4;
        if (size != 0)
        {
            // PORT: same slot layout as above, slot 8 is past the end of gCollectedTanks[8]
            DmaTransfer(3, gCollectedTanks[0] + (i != 0 ? i + 1 : 0) * COLLECTED_TANKS_SIZE,
                pWorld + offset, size, 16);
            offset += size;
        }
    }
}

/**
 * @brief 7ff7c | ec | Reads the world data (minimap, never reform blocks, tanks) from the current save file
 *
 */
void SramRead_WorldData(void)
{
    u8* pWorld;
    s32 i;
    s32 size;
    s32 offset;

    pWorld = SRAM_FILES_WORLD_DATA(gMostRecentSaveFile);
    DmaTransfer(3, pWorld, gVisitedMinimapTiles, SRAM_FILES_VISITED_MINIMAP_SIZE, 16);
    // Clears gNeverReformBlocks and gCollectedTanks (9 slots each)
    BitFill(3, USHORT_MAX, gNeverReformBlocks, (MAX_AMOUNT_OF_AREAS + 1) * (NEVER_REFORM_BLOCKS_SIZE + COLLECTED_TANKS_SIZE), 16);

    offset = SRAM_FILES_VISITED_MINIMAP_SIZE;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfNeverReformBlocks[i] * 3;
        if (size & 3)
            size = (size & 0xFFFC) + 4;

        if (size != 0)
        {
            // PORT: see SramWrite_WorldData
            DmaTransfer(3, pWorld + offset,
                gNeverReformBlocks[0] + (i != 0 ? i + 1 : 0) * NEVER_REFORM_BLOCKS_SIZE, size, 16);
            offset += size;
        }
    }

    offset = 0xC80;
    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        size = gNumberOfCollectedTanks[i] * 4;
        if (size != 0)
        {
            // PORT: see SramWrite_WorldData
            DmaTransfer(3, pWorld + offset,
                gCollectedTanks[0] + (i != 0 ? i + 1 : 0) * COLLECTED_TANKS_SIZE, size, 16);
            offset += size;
        }
    }
}

/**
 * @brief 80068 | 8c | Writes the most recent save file number to the SRAM
 *
 */
void SramWrite_MostRecentSaveFile(void)
{
    struct SramFilesSelectBlock* pBlock;
    s32 i;
    u16 checksum;

    pBlock = SRAM_FILES_MOST_RECENT;
    pBlock->magic = 0x1E;
    pBlock->writeCounter++;
    pBlock->checksum = 0;
    pBlock->notChecksum = USHORT_MAX;
    pBlock->value = gMostRecentSaveFile;

    for (i = 0; i < 16; i++)
    {
        pBlock->startString[i] = sSramMostRecentFileStrings[i];
        pBlock->endString[i] = sSramMostRecentFileStrings[16 + i];
    }

    checksum = SramFilesBlockChecksum(pBlock);
    pBlock->checksum = checksum;
    pBlock->notChecksum = USHORT_MAX - checksum;

    unk_dd4();
}

/**
 * @brief 800f4 | e0 | Reads the most recent save file number
 *
 */
void SramRead_MostRecentSaveFile(void)
{
    struct SramFilesSelectBlock* pBlock;
    u32 error;

    pBlock = SRAM_FILES_MOST_RECENT;
    error = pBlock->magic != 0x1E;

    if (!error)
    {
        if (pBlock->checksum != SramFilesBlockChecksum(pBlock))
            error = 2;
    }

    if (!error)
    {
        if (!SramFilesBlockCheckStrings(pBlock, sSramMostRecentFileStrings))
            error = 3;
    }

    if (!error)
    {
        gMostRecentSaveFile = pBlock->value;
    }
    else
    {
        DMA3_FILL_16(USHORT_MAX, pBlock, sizeof(struct SramFilesSelectBlock));
        gMostRecentSaveFile = 0;
    }
}

/**
 * @brief 801d4 | 90 | Writes the language to the SRAM
 *
 */
void SramWrite_Language(void)
{
    struct SramFilesSelectBlock* pBlock;
    s32 i;
    u16 checksum;

    pBlock = SRAM_FILES_LANGUAGE(0);
    pBlock->magic = 0x1F;
    pBlock->writeCounter++;
    pBlock->checksum = 0;
    pBlock->notChecksum = USHORT_MAX;
    pBlock->value = gLanguage;

    for (i = 0; i < 16; i++)
    {
        pBlock->startString[i] = sSramLanguageStrings[i];
        pBlock->endString[i] = sSramLanguageStrings[16 + i];
    }

    checksum = SramFilesBlockChecksum(pBlock);
    pBlock->checksum = checksum;
    pBlock->notChecksum = USHORT_MAX - checksum;

    unk_dec(0);
}

/**
 * @brief 80264 | 180 | Reads the language
 *
 */
void SramRead_Language(void)
{
    struct SramFilesSelectBlock* pBlock;
    u32 error;
    s32 i;

    for (i = 0; i < 2; i++)
    {
        pBlock = SRAM_FILES_LANGUAGE(i);
        error = pBlock->magic != 0x1F;

        if (!error)
        {
            if (pBlock->checksum != SramFilesBlockChecksum(pBlock))
                error = 2;
        }

        if (!error)
        {
            if (!SramFilesBlockCheckStrings(pBlock, sSramLanguageStrings))
                error = 3;
        }

        if (i == 0)
        {
            if (!error)
            {
                // First copy is fine, update the second one
                DMA3_COPY_16(SRAM_FILES_LANGUAGE(0), SRAM_FILES_LANGUAGE(1), sizeof(struct SramFilesSelectBlock) / 2);
                unk_dec(1);
                break;
            }
        }
        else
        {
            if (!error)
            {
                // Second copy is fine, restore the first one
                DMA3_COPY_16(SRAM_FILES_LANGUAGE(1), SRAM_FILES_LANGUAGE(0), sizeof(struct SramFilesSelectBlock) / 2);
                unk_dec(0);
            }
            else
            {
                // Both corrupted, clear them
                DMA3_FILL_16(0, SRAM_FILES_LANGUAGE(0), sizeof(struct SramFilesSelectBlock));
                unk_dec(0);
                DMA3_FILL_16(0, SRAM_FILES_LANGUAGE(1), sizeof(struct SramFilesSelectBlock));
                unk_dec(1);
            }
        }
    }

    if (!error)
        gLanguage = pBlock->value;
    else
        gLanguage = 0;
}

/**
 * @brief 803e4 | 14c | Initializes the game state for a new file
 *
 */
void Sram_InitSaveFile(void)
{
    s32 i;
    const struct Door* pDoor;

    BitFill(3, 0, gVisitedMinimapTiles, SRAM_FILES_VISITED_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, (MAX_AMOUNT_OF_AREAS + 1) * NEVER_REFORM_BLOCKS_SIZE, 16);
    BitFill(3, USHORT_MAX, gCollectedTanks, (MAX_AMOUNT_OF_AREAS + 1) * COLLECTED_TANKS_SIZE, 16);

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        gNumberOfNeverReformBlocks[i] = 0;
        gNumberOfCollectedTanks[i] = 0;
    }

    gInGameTimer = sSramDefaultInGameTimer;
    gDisableDrawingSamusAndScrollingFlag = TRUE;
    EventSet(0);
    gPreviousNavigationConversation = UCHAR_MAX;
    gPreviousSoundEvent = UCHAR_MAX;
    gEquipment.securityHatchLevel |= UCHAR_MAX;
    gSecurityHatchLevel = UCHAR_MAX;
    gSecurityHatchLevelBackup = UCHAR_MAX;
    gEquipment.downloadedMaps = 0;
    gAbilityCount = 0;
    gCurrentArea = 0;
    gPreviousArea = 0;
    gCurrentRoom = 0;
    gLastDoorUsed = 0;
    gNavigationTargetLocation = 0;
    gUnk_300004d = 0;

    // Start at the first door of the first area
    pDoor = sAreaDoorPointers[0];
    gSamusData.xPosition = gPreviousXPosition = pDoor->xStart * 64 + (pDoor->xExit + 8) * 4;
    gSamusData.yPosition = gPreviousYPosition = (pDoor->yEnd + 1) * 64 + pDoor->yExit * 4 - 1;

    MinimapLoadInitial();
    gIsLoadingFile = FALSE;
}

/**
 * @brief 80530 | 134 | Resets the game state for a demo
 *
 */
void Sram_ResetForDemo(void)
{
    s32 i;

    gBootDebugOptions = sSramDefaultBootDebugOptions;
    gButtonAssignments = sSramDefaultButtonAssignments;

    BitFill(3, USHORT_MAX, gVisitedMinimapTiles, SRAM_FILES_VISITED_MINIMAP_SIZE, 16);
    BitFill(3, USHORT_MAX, gNeverReformBlocks, (MAX_AMOUNT_OF_AREAS + 1) * NEVER_REFORM_BLOCKS_SIZE, 16);
    BitFill(3, USHORT_MAX, gCollectedTanks, (MAX_AMOUNT_OF_AREAS + 1) * COLLECTED_TANKS_SIZE, 16);

    for (i = 0; i < MAX_AMOUNT_OF_AREAS; i++)
    {
        gNumberOfNeverReformBlocks[i] = 0;
        gNumberOfCollectedTanks[i] = 0;
    }

    gInGameTimer = sSramDefaultInGameTimer;
    gDisableDrawingSamusAndScrollingFlag = FALSE;
    gPreviousNavigationConversation = UCHAR_MAX;
    gPreviousSoundEvent = UCHAR_MAX;
    gNavigationTargetLocation = 0;
    gUnk_300004d = 0;
    gIsLoadingFile = FALSE;
    gUnk_3000be3 = FALSE;
    gMonochromeFading = 0;
    gDisableSoftReset = FALSE;
    gMaxInGameTimeFlag = TRUE;
    gDisableMusicFlag = FALSE;
    gSkipDoorTransition = FALSE;
    gPauseScreenFlag = 0;
    gUnk_3000b85 = 0;
    gDisablePauseFlag = FALSE;
    gSamusDoorPositionOffset = 0;
    gDebugFlag = FALSE;
}

/**
 * @brief 80664 | e0 | Loads the current save file, or starts a new file
 *
 */
void Sram_CheckLoadSaveFile(void)
{
    gButtonAssignments = sSramDefaultButtonAssignments;
    gBootDebugOptions = sSramDefaultBootDebugOptions;

    gIsLoadingFile = gFileSelectFileInfo[gMostRecentSaveFile].exists;
    if (gIsLoadingFile == FALSE)
    {
        Sram_InitSaveFile();
        gGameCompletion.completedGame = gFileSelectFileInfo[gMostRecentSaveFile].completedGame;
        gGameCompletion.introPlayed = gFileSelectFileInfo[gMostRecentSaveFile].introPlayed;
        gUnk_3000016 = 0;
    }
    else
    {
        SramLoad_CurrentSave();
    }

    gUnk_3000be3 = FALSE;
    gMonochromeFading = 0;
    gDisableSoftReset = FALSE;
    gMaxInGameTimeFlag = FALSE;
    gDisableMusicFlag = FALSE;
    gSkipDoorTransition = FALSE;
    gPauseScreenFlag = 0;
    gUnk_3000b85 = 0;
    gDisablePauseFlag = FALSE;
    gSamusDoorPositionOffset = 0;
    gDebugFlag = FALSE;
}

/**
 * @brief 80744 | a8 | Erases the current save file
 *
 * @param stage Stage
 */
void Sram_EraseFile(u8 stage)
{
    struct FileSelectFileInfo empty;

    memset(&empty, 0, sizeof(empty));

    switch (stage)
    {
        case 0:
            gDisableSoftReset = TRUE;
            gFileSelectFileInfo[gMostRecentSaveFile] = empty;
            BitFill(3, USHORT_MAX, SRAM_FILES_SAVE(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
            return;

        case 1:
            WriteMostRecentFileToSram();
            return;

        case 2:
            BitFill(3, USHORT_MAX, SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile), sizeof(struct SramFilesSaveFile), 16);
            return;

        case 3:
            WriteMostRecentFileBackupToSram();
            break;
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 807ec | c8 | Copies the current save file to another file
 *
 * @param dstFile Destination file
 * @param stage Stage
 */
void Sram_CopyFile(u8 dstFile, u8 stage)
{
    u8 currentFile;

    switch (stage)
    {
        case 0:
            gDisableSoftReset = TRUE;
            gFileSelectFileInfo[dstFile] = gFileSelectFileInfo[gMostRecentSaveFile];
            DmaTransfer(3, SRAM_FILES_SAVE(gMostRecentSaveFile), SRAM_FILES_SAVE(dstFile),
                sizeof(struct SramFilesSaveFile), 16);
            return;

        case 1:
            currentFile = gMostRecentSaveFile;
            gMostRecentSaveFile = dstFile;
            WriteMostRecentFileToSram();
            gMostRecentSaveFile = currentFile;
            return;

        case 2:
            DmaTransfer(3, SRAM_FILES_SAVE_BACKUP(gMostRecentSaveFile), SRAM_FILES_SAVE_BACKUP(dstFile),
                sizeof(struct SramFilesSaveFile), 16);
            return;

        case 3:
            currentFile = gMostRecentSaveFile;
            gMostRecentSaveFile = dstFile;
            WriteMostRecentFileBackupToSram();
            gMostRecentSaveFile = currentFile;
            break;
    }

    gDisableSoftReset = FALSE;
}

/**
 * @brief 808b4 | 9c | Updates the file select info of every save file
 *
 */
void Sram_WriteFileInfo(void)
{
    struct FileSelectFileInfo* pInfo;
    struct SramFilesSaveFile* pFile;
    s32 i;

    pInfo = gFileSelectFileInfo;
    for (i = 0; i < ARRAY_SIZE(gFileSelectFileInfo); i++, pInfo++)
    {
        if (pInfo->exists == TRUE)
        {
            pFile = SRAM_FILES_SAVE(i);
            pInfo->currentArea = pFile->currentArea;
            pInfo->eventCounter = pFile->eventCounter;
            pInfo->currentEnergy = pFile->equipment.currentEnergy;
            pInfo->maxEnergy = pFile->equipment.maxEnergy;
            pInfo->currentMissiles = pFile->equipment.currentMissiles;
            pInfo->maxMissiles = pFile->equipment.maxMissiles;
            pInfo->weaponsStatus = pFile->equipment.weaponsStatus;
            pInfo->igtHours = pFile->inGameTimer.hours;
            pInfo->igtMinutes = pFile->inGameTimer.minutes;
            pInfo->unk_f = pFile->unk_1C;
            pInfo->completedGame = pFile->completedGame;
            pInfo->introPlayed = pFile->introPlayed;
        }

        if (pInfo->exists == FALSE || pInfo->unk_f == 0)
        {
            pInfo->exists = FALSE;
            pInfo->currentArea = 0;
            pInfo->eventCounter = 0;
            pInfo->currentEnergy = 0;
            pInfo->maxEnergy = 0;
            pInfo->currentMissiles = 0;
            pInfo->maxMissiles = 0;
            pInfo->weaponsStatus = 0;
            pInfo->igtHours = 0;
            pInfo->igtMinutes = 0;
        }
    }
}

/**
 * @brief 80950 | c | V-blank code while loading a file (empty)
 *
 */
void Sram_LoadingfileVblank(void)
{
    vu8 c = 0;
}

/**
 * @brief 8095c | c | V-blank code after loading a file
 *
 */
void Sram_AfterLoadingFileVblank(void)
{
    UpdateAudio();
}

/**
 * @brief 80968 | 2c | Loads the current save file (with the audio updated during it)
 *
 * @return s8 Is loading file
 */
s8 Sram_ChecLoadSaveFileWithBlank(void)
{
    CallbackSetVBlank(Sram_AfterLoadingFileVblank);
    Sram_CheckLoadSaveFile();
    CallbackSetVBlank(Sram_LoadingfileVblank);

    return gIsLoadingFile;
}

/**
 * @brief 80994 | 5c | Sets the current file and rewrites its corrupted copies
 *
 * @param file File
 */
void Sram_SetCurrentFile(u8 file)
{
    u8 previousFile;

    previousFile = gMostRecentSaveFile;
    gMostRecentSaveFile = file;

    switch (gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag)
    {
        case 1:
            WriteMostRecentFileToSram();
            break;

        case 2:
            WriteMostRecentFileToSram();
            WriteMostRecentFileBackupToSram();
            break;
    }

    gFileSelectFileInfo[gMostRecentSaveFile].corruptionFlag = 0;
    gMostRecentSaveFile = previousFile;
}
