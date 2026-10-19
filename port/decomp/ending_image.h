#ifndef PORT_DECOMP_ENDING_IMAGE_H
#define PORT_DECOMP_ENDING_IMAGE_H

#include "types.h"

/*
 * Ending image (final picture) helpers from asm/disasm_0x0809deb4.s (0x080a1480 - 0x080a1c84),
 * called by EndingImage in src/ending.c. They fill ENDING_DATA the same way src/ending.c reads it
 * (the arrays at 0x124/0x142/0x160 and the OAM position/frame arrays hold 30 entries).
 * The text tables exist for every language of the european ROM; the US ROM uses the default ones.
 */

// 0xC bytes on GBA
struct EndingImageTextOamData {
    u8 unk_0;           // -> ENDING_DATA.unk_124[slot]
    u8 spawnDelay;      // -> ENDING_DATA.unk_124[slot + 30]
    u8 unk_2;           // -> ENDING_DATA.unk_160[slot]
    u16 xPosition;      // -> ENDING_DATA.oamXPositions[slot]
    u16 yPosition;      // -> ENDING_DATA.oamYPositions[slot]
    const u16* pOam;    // -> ENDING_DATA.oamFramePointers[slot]
};

// Static data blobs of src/data/ending_data.c
extern const u8 sBlob_74dc48_74e620[]; // ROM 0x0874dc48
extern const u8 sBlob_74e650_74eb50[]; // ROM 0x0874e650

// PORT: these tables live inside a raw binary blob and hold GBA ROM pointers (pOam),
// they must be decoded into real struct EndingImageTextOamData arrays for a native build.
#ifdef PLATFORM_PC
// Native: decoded on first use from the blob (12 bytes per entry on the GBA).
const struct EndingImageTextOamData* EndingImageTextNative(u32 offset);
#define ENDING_IMAGE_TEXT(off) EndingImageTextNative(off)
#else
#define ENDING_IMAGE_TEXT(off) ((const struct EndingImageTextOamData*)&sBlob_74dc48_74e620[(off)])
#endif
#define sEndingImageLines_Default    ENDING_IMAGE_TEXT(0x0)   // 0x0874dc48 [6]
#define sEndingImageText0_Default    ENDING_IMAGE_TEXT(0x48)  // 0x0874dc90 [9]
#define sEndingImageText1_Default    ENDING_IMAGE_TEXT(0xb4)  // 0x0874dcfc [11]
#define sEndingImageText2_Default    ENDING_IMAGE_TEXT(0x138) // 0x0874dd80 [17]
#define sEndingImageLines_German     ENDING_IMAGE_TEXT(0x204) // 0x0874de4c [6]
#define sEndingImageText0_German     ENDING_IMAGE_TEXT(0x24c) // 0x0874de94 [13]
#define sEndingImageText1_German     ENDING_IMAGE_TEXT(0x2e8) // 0x0874df30 [14]
#define sEndingImageLines_French     ENDING_IMAGE_TEXT(0x390) // 0x0874dfd8 [6]
#define sEndingImageText0_French     ENDING_IMAGE_TEXT(0x3d8) // 0x0874e020 [16]
#define sEndingImageText1_French     ENDING_IMAGE_TEXT(0x498) // 0x0874e0e0 [20]
#define sEndingImageLines_Italian    ENDING_IMAGE_TEXT(0x588) // 0x0874e1d0 [6]
#define sEndingImageText0_Italian    ENDING_IMAGE_TEXT(0x5d0) // 0x0874e218 [18]
#define sEndingImageText1_Italian    ENDING_IMAGE_TEXT(0x6a8) // 0x0874e2f0 [11]
#define sEndingImageText2_Italian    ENDING_IMAGE_TEXT(0x72c) // 0x0874e374 [17]
#define sEndingImageLines_Spanish    ENDING_IMAGE_TEXT(0x7f8) // 0x0874e440 [6]
#define sEndingImageText0_Spanish    ENDING_IMAGE_TEXT(0x840) // 0x0874e488 [15]
#define sEndingImageText1_Spanish    ENDING_IMAGE_TEXT(0x8f4) // 0x0874e53c [19]

#define sEndingImageNumbersTopGfx    (&sBlob_74e650_74eb50[0x0])   // 0x0874e650, 10 digits * 0x40 bytes
#define sEndingImageNumbersBottomGfx (&sBlob_74e650_74eb50[0x280]) // 0x0874e8d0, 10 digits * 0x40 bytes

void EndingDrawIgtAndCompletionPercentage(void);
void EndingImageUpdateLettersSpawnDelay(u32 slot);
void EndingImageLoadTextOam(u32 text);
void EndingImageDisplayLinePermanently(u32 line);

#endif /* PORT_DECOMP_ENDING_IMAGE_H */
