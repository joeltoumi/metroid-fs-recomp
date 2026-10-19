#include "data/blob_pieces.h"
#ifndef INTRO_SPACE_VIEW_H
#define INTRO_SPACE_VIEW_H

#include "types.h"
#include "oam.h"
#include "structs/cutscene.h"

/*
 * Intro (first boot) space view / flying view cutscene, translated from
 * asm/disasm_0x0808F5C4.s (0x08093980 - 0x08094E80).
 */

/* Static data blobs from src/data/new_file_intro_data.c and src/new_file_intro.c
 * (externed, see BRIEF addendum). */
extern const u8 sBlob_6101b8_612e48[];
extern const u32* sIntroSamusSittingBgGfxPointers[]; /* static in src/new_file_intro.c, [5] */

/*
 * Pieces of sBlob_6094d0_60ac08 used here (FrameData arrays).
 * PORT: these live inside a raw binary blob that still holds 32-bit GBA
 * pointers; on PC the blob must be split into real FrameData arrays with these
 * names (address in comment).
 */
#define sIntroSpaceViewOam_60ac08 ((const struct FrameData*)((const u8*)&sFrameData_60ac08[0])) /* 0x0860ac08 depth particle */
#define sIntroSpaceViewOam_60ac18 ((const struct FrameData*)((const u8*)&sFrameData_60ac18[0])) /* 0x0860ac18 particle */
#define sIntroSpaceViewOam_60ac28 ((const struct FrameData*)((const u8*)&sFrameData_60ac28[0])) /* 0x0860ac28 particle */
#define sIntroSpaceViewOam_60ac38 ((const struct FrameData*)((const u8*)&sFrameData_60ac38[0])) /* 0x0860ac38 particle */
#define sIntroSpaceViewOam_60ac98 ((const struct FrameData*)((const u8*)&sFrameData_60ac98[0])) /* 0x0860ac98 Samus ship entering */
#define sIntroSpaceViewOam_60acd0 ((const struct FrameData*)((const u8*)&sFrameData_60acd0[0])) /* 0x0860acd0 ship backview */
#define sIntroSpaceViewOam_60acf8 ((const struct FrameData*)((const u8*)&sFrameData_60acf8[0])) /* 0x0860acf8 BSL backview part (type 15) */
#define sIntroSpaceViewOam_60ad08 ((const struct FrameData*)((const u8*)&sFrameData_60ad08[0])) /* 0x0860ad08 BSL backview part (type 14) */
#define sIntroSpaceViewOam_60ad18 ((const struct FrameData*)((const u8*)&sFrameData_60ad18[0])) /* 0x0860ad18 BSL backview part (type 13) */
#define sIntroSpaceViewOam_60ad28 ((const struct FrameData*)((const u8*)&sFrameData_60ad28[0])) /* 0x0860ad28 BSL backview part (type 12) */
#define sIntroSpaceViewOam_60af10 ((const struct FrameData*)((const u8*)&sFrameData_60af10[0])) /* 0x0860af10 splash text */

/* Pieces of sBlob_64e470_65bb38 (same PORT note) */
#define sIntroSpaceView_658be0 (&sBlob_64e470_65bb38[0xa770]) /* 0x08658be0 LZ77 tilemap */
#define sIntroSpaceViewPal_6591e4 ((const u16*)&sBlob_64e470_65bb38[0xad74]) /* 0x086591e4 palette, 0x100 bytes */

/* Callees still in asm / elsewhere */
void unk_99940(void);
u8 SpecialCutsceneGetRandomNumber(void);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneFadeIn(void);
boolu32 IntroProcessText(void);
void Dma3Transfer_Unused2(const void* src, void* dst, u16 size, u16 rows);

/* Functions of this file */
void IntroSpaceViewInit(void);
boolu32 IntroSpaceViewPartProcess(void);
void IntroFlyingViewInit(void);
boolu32 IntroFlyingViewProcess(void);
boolu32 IntroSpaceView(void);
void IntroProcessSpaceViewScrolling(struct SpecialCutsceneOam* pOam);
void IntroProcessBslShipSideways(struct SpecialCutsceneOam* pOam);
void IntroProcessSamusSHipEntering(struct SpecialCutsceneOam* pOam);
void IntroProcessSplashText(struct SpecialCutsceneOam* pOam);
void IntroProcessSpaceViewParticle(struct SpecialCutsceneOam* pOam);
void IntroProcessIdleShipBackview(struct SpecialCutsceneOam* pOam);
void IntroProcessBslShipSpawning_2(struct SpecialCutsceneOam* pOam);
void IntroProcessBslShipBackview(struct SpecialCutsceneOam* pOam);
void IntroProcessIdleDepthParticle(struct SpecialCutsceneOam* pOam);
u8 IntroSpaceViewSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void IntroSpaceViewVblank(void);
void unk_94e80(void);

#endif /* INTRO_SPACE_VIEW_H */
