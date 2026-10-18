#ifndef SPECIAL_CUTSCENE_H
#define SPECIAL_CUTSCENE_H

#include "types.h"
#include "macros.h"
#include "oam.h"
#include "globals.h"
#include "structs/cutscene.h"

// ---------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------

// Data used here lives inside the (static) blob sBlob_6131c8_63a19c of
// src/data/new_file_intro_data.c (0x086131c8 .. 0x0863a19c)
// PORT: that blob is declared static in the decomp; the native build must
// make it visible (or provide these tables) for this extern to resolve.
extern const u8 sBlob_6131c8_63a19c[];

#define SPECIAL_CUTSCENE_BLOB(offset) (&sBlob_6131c8_63a19c[(offset)])

// Died on SR388 collision
#define sDiedOnSr388CollisionObjGfx ((const u8*)SPECIAL_CUTSCENE_BLOB(0x1072C))                // 0x086238f4 (LZ77)
#define sDiedOnSr388CollisionBgGfx ((const u8*)SPECIAL_CUTSCENE_BLOB(0x1842C))                 // 0x0862b5f4 (LZ77)
#define sDiedOnSr388CollisionBslOam_1 ((const struct FrameData*)SPECIAL_CUTSCENE_BLOB(0x22E58)) // 0x08636020
#define sDiedOnSr388CollisionBslOam_2 ((const struct FrameData*)SPECIAL_CUTSCENE_BLOB(0x22E70)) // 0x08636038
#define sDiedOnSr388CollisionOam_3 ((const struct FrameData*)SPECIAL_CUTSCENE_BLOB(0x22E88))    // 0x08636050
#define sDiedOnSr388CollisionBslOam_Crash ((const struct FrameData*)SPECIAL_CUTSCENE_BLOB(0x230F0)) // 0x086362b8
#define sDiedOnSr388CollisionFadingPal ((const u16*)SPECIAL_CUTSCENE_BLOB(0x23870))             // 0x08636a38, [16][16]
#define sDiedOnSr388CollisionObjPal ((const u16*)SPECIAL_CUTSCENE_BLOB(0x23A70))                // 0x08636c38
#define sDiedOnSr388CollisionBgPal ((const u16*)SPECIAL_CUTSCENE_BLOB(0x23E70))                 // 0x08637038
#define sDiedOnSr388CollisionTilemap_1 ((const u8*)SPECIAL_CUTSCENE_BLOB(0x25A4C))              // 0x08638c14 (LZ77)
#define sDiedOnSr388CollisionTilemap_2 ((const u8*)SPECIAL_CUTSCENE_BLOB(0x269FC))              // 0x08639bc4 (LZ77)

// Copies of sOamXFlipOffsets / sOamYFlipOffsets (u8 [3][4])
#define sSpecialCutsceneOamXFlipOffsets CAST_TO_ARRAY(const u8, [3][4], SPECIAL_CUTSCENE_BLOB(0x26FBC)) // 0x0863a184
#define sSpecialCutsceneOamYFlipOffsets CAST_TO_ARRAY(const u8, [3][4], SPECIAL_CUTSCENE_BLOB(0x26FC8)) // 0x0863a190

// ---------------------------------------------------------------------------
// RAM
// ---------------------------------------------------------------------------

// 0x03001238 (u8) : next affine matrix slot used by the special cutscene OAM
extern u8 gUnk_3001238;
// 0x03005404 (u16) : special cutscene random number seed (high byte = last value)
extern u16 gUnk_3005404;

// Window (WIN0H per scanline) buffers in EWRAM, used by the samus getting cured cutscene
#define gSpecialCutsceneWindowValues CAST_TO_ARRAY(u16, [0xB0], EWRAM_BASE + 0x1000)
#define gSpecialCutsceneWindowValuesCopy CAST_TO_ARRAY(u16, [0xB0], EWRAM_BASE + 0x2000)

// Raw byte area of the intro data, from 0x14 to 0x20C : two [9][28] u8 arrays
// (at 0x14 : text tile states, at 0x110 : text tile timers) that overlap the
// unk_110/unk_111/unk_112/unk_12C/... fields of struct IntroData.
// PORT: these are views over a range of consecutive u8 fields of struct
// IntroData, the offsets are relative to unk_14 so they stay valid with a
// 64-bit layout (only u8 fields between unk_14 and unk_20C).
#ifdef PLATFORM_PC
#include <stddef.h>
#define SPECIAL_CUTSCENE_UNK_14_OFFSET offsetof(struct IntroData, unk_14)
#else
#define SPECIAL_CUTSCENE_UNK_14_OFFSET OFFSET_OF(struct IntroData, unk_14)
#endif
#define SPECIAL_CUTSCENE_INTRO_BYTES ((u8*)&INTRO_DATA + SPECIAL_CUTSCENE_UNK_14_OFFSET)
#define SPECIAL_CUTSCENE_INTRO_U8(offset) (SPECIAL_CUTSCENE_INTRO_BYTES[(offset) - 0x14])
#define SPECIAL_CUTSCENE_TEXT_STATE(index) (SPECIAL_CUTSCENE_INTRO_BYTES[(index)])
#define SPECIAL_CUTSCENE_TEXT_TIMER(index) (SPECIAL_CUTSCENE_INTRO_BYTES[0x110 - 0x14 + (index)])

// Byte 0x18 of struct SpecialCutsceneOam (holds unk_18_0, affineMode, unk_18_3,
// unk_18_5, bit 6 = x flip, bit 7 = y flip)
#define SPECIAL_CUTSCENE_OAM_FLAGS(pOam) (((u8*)&(pOam)->unk_17)[1])
#define SPECIAL_CUTSCENE_OAM_FLAG_X_FLIP (1 << 6)
#define SPECIAL_CUTSCENE_OAM_FLAG_Y_FLIP (1 << 7)

typedef void (*SpecialCutsceneOamFunc_T)(struct SpecialCutsceneOam* pOam);

// ---------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------

boolu32 DiedFromSr388CollisionHandler(void);
void DiedOnSr388CollisionInit(void);
boolu32 DiedOnSr388CollisionProcess(void);
boolu32 DiedOnSr388Collision(void);
void DiedOnSr388CollisionProcessFallingBsl(struct SpecialCutsceneOam* pOam);
void unk_979d0(struct SpecialCutsceneOam* pOam);
u8 DiedOnSr388CollisionSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void DiedOnSr388CollisionVblank(void);
void DiedOnSr388CollisionVblank_Unused(void);
u8 DiedOnSr388CollisionGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void unk_97dcc(void);
boolu32 NewFileIntroCheckMonologueEnded(void);
boolu32 EndingCheckMonologueEnded(void);
void SpecialCutsceneProcessMonologue(void);
void unk_98158(void);
boolu32 EndingProcessAdamText(void);
boolu32 IntroProcessText(void);
boolu32 NewFileIntroProcessAdamText(void);
void Dma3Transfer_Unused1(const void* src, void* dst, u32 size, u16 count);
void Dma3Transfer_Unused2(const void* src, void* dst, u32 size, u16 count);
void Dma3Clear_Unused(void* dst, u32 size, u16 count);
void unk_98a04(void);
void NewFileIntroSamusGettingCuredSetupWindow(void);
void SpecialCutsceneFadeIn(void);
void SpecialCutsceneFadOut(void);
void NewFileIntroProcessTextCursor(struct SpecialCutsceneOam* pOam);
void SpecialCutsceneClearOam(void);
void SpecialCutsceneEnableOam(void);
void SpecialCutsceneDestroyOamOfType(u8 type);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneDrawOam(struct SpecialCutsceneOam* pOam);
void NewFileIntroInit(void);
u8 SpecialCutsceneGetRandomNumber(void);
void NewFileIntroVblank(void);
void unk_99940(void);
boolu32 CutsceneHandler(void);
void CutsceneInit(void);
void CutsceneVblank(void);
void unk_99af8(void);
boolu32 CutsceneProcess(void);

// Callees implemented elsewhere (other asm functions of the same file)
boolu32 CutsceneInternalMonologue(u8 param_1);
boolu32 CutsceneElevatorMonologue(u8 param_1);
boolu32 CutsceneFederationMonologue(u8 param_1);
boolu32 CutsceneSecretConversation(void);
boolu32 CutsceneRestrictedLabDetaching(void);
boolu8 CutsceneBslExploding(void);

#endif /* SPECIAL_CUTSCENE_H */
