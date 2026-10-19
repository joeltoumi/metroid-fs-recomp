#include "data/blob_pieces.h"
#ifndef PORT_DECOMP_ENDING_H
#define PORT_DECOMP_ENDING_H

/*
 * Ending cutscene (gCurrentCutscene == 3): BSL crashing, ship front view,
 * Samus monologue, Adam conversation, animals.
 * Translated from asm/disasm_0x0808F5C4.s (0x08094E84 .. 0x0809741B).
 *
 * The ending uses the same gNonGameplayRam layout as the intro
 * (struct IntroData / INTRO_DATA, with its SpecialCutsceneOam array).
 */

#include "types.h"
#include "oam.h"
#include "structs/cutscene.h"
#include "structs/intro.h"
#include "constants/game_state.h"

/* ---- Data (static symbols in src/new_file_intro.c / src/data/new_file_intro_data.c) ---- */

// static const u8 sBlob_6131c8_6331ec[] in src/data/new_file_intro_data.c
// sPointers_79c394 (include/data/blob_pieces.h): pointer table from src/new_file_intro.c
// static u16** sMonologueTextPointers[LANGUAGE_COUNT] in src/new_file_intro.c
extern u16** sMonologueTextPointers[LANGUAGE_COUNT];

#define ENDING_BLOB(offset) (&sBlob_6131c8_6331ec[offset])

// Graphics / tilemaps (LZ77 compressed), palettes
#define sEndingAdamBgGfx_6131c8              ((const u32*)(&sBlob_6131c8_6331ec[0x0]))
#define sEndingMonologueObjGfx_6150e8        ((const u32*)(&sBlob_6131c8_6331ec[0x1f20]))
#define sEndingMonologueBgGfx_6186a4         ((const u32*)(&sBlob_6131c8_6331ec[0x54dc]))
#define sEndingAnimalsBgGfx_61b89c           ((const u32*)(&sBlob_6131c8_6331ec[0x86d4]))
#define sEndingAnimalsBgGfx_6217a8           ((const u32*)(&sBlob_6131c8_6331ec[0xe5e0]))
#define sEndingBslCrashingObjGfx_6238f4      ((const u32*)(&sBlob_6131c8_6331ec[0x1072c]))
#define sEndingShipFrontViewBgGfx_626738     ((const u32*)(&sBlob_6131c8_6331ec[0x13570]))
#define sEndingBslCrashingBgGfx_62b5f4       ((const u32*)(&sBlob_6131c8_6331ec[0x1842c]))
#define sEndingMonologueBgPal_636438         ((const u16*)(&sBlob_636438_63a19c[0x0]))
#define sEndingMonologueObjPal_636638        ((const u16*)(&sBlob_636438_63a19c[0x200]))
#define sEndingAnimalsBgPal_636838           ((const u16*)(&sBlob_636438_63a19c[0x400]))
#define sEndingBslFlashPal_636a38            ((const u16*)(&sBlob_636438_63a19c[0x600]))
#define sEndingBslCrashingObjPal_636c38      ((const u16*)(&sBlob_636438_63a19c[0x800]))
#define sEndingShipFrontViewBgPal_636e38     ((const u16*)(&sBlob_636438_63a19c[0xa00]))
#define sEndingBslCrashingBgPal_637038       ((const u16*)(&sBlob_636438_63a19c[0xc00]))
#define sEndingAdamBgTilemap_637238          ((const u32*)(&sBlob_636438_63a19c[0xe00]))
#define sEndingMonologueBgTilemap_6377f8     ((const u32*)(&sBlob_636438_63a19c[0x13c0]))
#define sEndingAnimalsBg3Tilemap_637db8      ((const u32*)(&sBlob_636438_63a19c[0x1980]))
#define sEndingAnimalsBg2Tilemap_638654      ((const u32*)(&sBlob_636438_63a19c[0x221c]))
#define sEndingBslCrashingTilemap_638c14     ((const u32*)(&sBlob_636438_63a19c[0x27dc]))
#define sEndingShipFrontViewTilemap_63929c   ((const u32*)(&sBlob_636438_63a19c[0x2e64]))
#define sEndingShipFrontViewTilemap_6395b8   ((const u32*)(&sBlob_636438_63a19c[0x3180]))
#define sEndingBslCrashingTilemap_639bc4     ((const u32*)(&sBlob_636438_63a19c[0x378c]))

// PORT: the OAM animations below are struct FrameData arrays inside a raw
// ROM blob, i.e. they embed 32-bit GBA ROM pointers. Natively they must be
// replaced by real FrameData arrays (the blob cannot be reinterpreted).
#define ENDING_FRAMES(offset) ((const struct FrameData*)ENDING_BLOB(offset))
#define sEndingOam_6331ec ((const struct FrameData*)((const u8*)&sFrameData_6331ec[0]))
#define sEndingOam_633244 ((const struct FrameData*)((const u8*)&sFrameData_633244[0]))
#define sEndingOam_633294 ((const struct FrameData*)((const u8*)&sFrameData_633294[0]))
#define sEndingOam_6332fc ((const struct FrameData*)((const u8*)&sFrameData_6332fc[0]))
#define sEndingOam_633364 ((const struct FrameData*)((const u8*)&sFrameData_633364[0]))
#define sEndingOam_6333cc ((const struct FrameData*)((const u8*)&sFrameData_6333cc[0]))
#define sEndingOam_633434 ((const struct FrameData*)((const u8*)&sFrameData_633434[0]))
#define sEndingOam_63345c ((const struct FrameData*)((const u8*)&sFrameData_63345c[0]))
#define sEndingOam_6338a4 ((const struct FrameData*)((const u8*)&sFrameData_6338a4[0]))
#define sEndingOam_6338d4 ((const struct FrameData*)((const u8*)&sFrameData_6338d4[0]))
#define sEndingOam_6339d4 ((const struct FrameData*)((const u8*)&sFrameData_6339d4[0]))
#define sEndingOam_633c4c ((const struct FrameData*)((const u8*)&sFrameData_633c4c[0]))
#define sEndingOam_633e64 ((const struct FrameData*)((const u8*)&sFrameData_633e64[0]))
#define sEndingOam_633e8c ((const struct FrameData*)((const u8*)&sFrameData_633e8c[0]))
#define sEndingOam_633ec4 ((const struct FrameData*)((const u8*)&sFrameData_633ec4[0]))
#define sEndingOam_633f0c ((const struct FrameData*)((const u8*)&sFrameData_633f0c[0]))
#define sEndingOam_633f24 ((const struct FrameData*)((const u8*)&sFrameData_633f24[0]))
#define sEndingOam_636020 ((const struct FrameData*)((const u8*)&sFrameData_636020[0]))
#define sEndingOam_636038 ((const struct FrameData*)((const u8*)&sFrameData_636038[0]))
#define sEndingOam_636050 ((const struct FrameData*)((const u8*)&sFrameData_636050[0]))
#define sEndingOam_636288 ((const struct FrameData*)((const u8*)&sFrameData_636288[0]))
#define sEndingOam_6362a0 ((const struct FrameData*)((const u8*)&sFrameData_6362a0[0]))
#define sEndingOam_6362b8 ((const struct FrameData*)((const u8*)&sFrameData_6362b8[0]))
#define sEndingOam_6363a0 ((const struct FrameData*)((const u8*)&sFrameData_6363a0[0]))
#define sEndingOam_6363b8 ((const struct FrameData*)((const u8*)&sFrameData_6363b8[0]))

// PORT: per-language table of text pointer tables (u16** [LANGUAGE_COUNT])
// stored inside a raw ROM blob (0x0879c3ac), contains GBA ROM pointers.
#define sEndingAdamTextPointers ((u16** const*)&sPointers_79c394[6])

/* ---- Functions implemented elsewhere (still asm / other files) ---- */
void unk_99940(void);
void unk_98158(void);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneFadeIn(void);
void SpecialCutsceneDestroyOamOfType(u8 type);
void SpecialCutsceneProcessMonologue(void);
boolu32 EndingCheckMonologueEnded(void);
boolu32 EndingProcessAdamText(void);
void Sram_ProcessEndingSave(u8 stage);

/* ---- Functions of this file ---- */
boolu32 EndingHandler(void);
void EndingBslCrashingInit(void);
void EndingShipFrontViewInit(void);
boolu32 EndingBslCrashingProcess(void);
boolu32 EndingBslCrashing(void);
void EndingProcessFallingBsl(struct SpecialCutsceneOam* pOam);
void unk_9579c(struct SpecialCutsceneOam* pOam);
void EndingProcessLeavingSmallShip(struct SpecialCutsceneOam* pOam);
void EndingProcessLeavingBigShip(struct SpecialCutsceneOam* pOam);
void EndingProcessFrontFacingShipThrusters(struct SpecialCutsceneOam* pOam);
void EndingProcessFrontFacingShip(struct SpecialCutsceneOam* pOam);
u8 EndingBslCrashingSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void EndingBslCrashingVblank(void);
void EndingShipFrontViewVblank(void);
u8 EndingGetPositionAndSlotOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void unk_95e20(struct SpecialCutsceneOam* pOam);
void EndingMonologueInit(void);
void EndingAdamConversationInit(void);
void EndingAnimalsInit(void);
boolu32 EndingInShipProcess(void);
boolu32 EndingInShip(void);
void EndingProcessMonologueCursor(struct SpecialCutsceneOam* pOam);
void unk_969e0(struct SpecialCutsceneOam* pOam);
void EndingProcessSr388RadarView(struct SpecialCutsceneOam* pOam);
void EndingProcessSamusViewRadarView(struct SpecialCutsceneOam* pOam);
void unk_96a70(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamTextCursor(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamPanel(struct SpecialCutsceneOam* pOam);
void EndingProcessAdamIcon(struct SpecialCutsceneOam* pOam);
void EndingProcessAnimalsScrolling(struct SpecialCutsceneOam* pOam);
void unk_96f00(struct SpecialCutsceneOam* pOam);
u8 EndingDialogueSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void EndingMonologueVblank(void);
void EndingConversationAndAnimalsVblank(void);
u8 EndingGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition);
void unk_97418(struct SpecialCutsceneOam* pOam);

#endif /* PORT_DECOMP_ENDING_H */
