#include "data/blob_pieces.h"
#ifndef NEW_FILE_INTRO_ASM_H
#define NEW_FILE_INTRO_ASM_H

// New file intro (landing on the BSL), Samus in ship, ship alert, Samus drifting out,
// intro OAM handlers. Translated from asm/disasm_0x0808F5C4.s (0x08090D60 - 0x0809397C).

#include "types.h"
#include "oam.h"
#include "structs/cutscene.h"
#include "structs/intro.h"

// ---------------------------------------------------------------------------
// Static data from src/data/new_file_intro_data.c and src/new_file_intro.c
// (static in the decomp, externed here; the equiv/agbcc build resolves them
// through the US ROM symbols).
// PORT: these blobs are still raw ROM bytes in the decomp. The OAM frame data
// (struct FrameData, which contains a pointer) and the pointer tables inside
// &sPointers_79c448[0] contain 32-bit GBA addresses, so on 64-bit they must be
// replaced by properly extracted arrays by the integrator.
// ---------------------------------------------------------------------------
extern const u8 sBlob_6101b8_612e48[];
extern const u32* sIntroSamusSittingBgGfxPointers[5];

#define NFIA_BLOB_5F6990(addr) (sBlob_5f6990_5fe370 + ((addr) - 0x5f6990))
#define NFIA_BLOB_6094D0(addr) (sBlob_6094d0_60ac08 + ((addr) - 0x6094d0))
#define NFIA_BLOB_64E470(addr) (sBlob_64e470_65bb38 + ((addr) - 0x64e470))
#define NFIA_OAM(ptr) ((const struct FrameData*)(ptr))

// Landing on BSL graphics (sBlob_5f6990_5fe370)
#define sIntroLandingOnBslBgGfx           (&sBlob_5f6990_5fe370[0x800])
#define sIntroLandingOnBslObjGfx          (&sBlob_5f6990_5fe370[0x41c4])
#define sIntroLandingOnBslBgPal           (&sBlob_5ff708_60093c[0x0])
#define sIntroLandingOnBslDoorLightPals   (&sBlob_5ff708_60093c[0x200]) // 32 bytes per entry
#define sIntroLandingOnBslLightPals       (&sBlob_5ff708_60093c[0x400]) // 32 bytes per entry
#define sIntroLandingOnBslObjPal          (&sBlob_5ff708_60093c[0x600])
#define sIntroLandingOnBslTilemap_5fff08  (&sBlob_5ff708_60093c[0x800])
#define sIntroLandingOnBslTilemap_60030c  (&sBlob_5ff708_60093c[0xc04])

#define sIntroLandingOnBslOam_5fe370 NFIA_OAM(((const u8*)&sFrameData_5fe370[0]))
#define sIntroLandingOnBslOam_5fe3c0 NFIA_OAM(((const u8*)&sFrameData_5fe3c0[0]))
#define sIntroLandingOnBslOam_5fe410 NFIA_OAM(((const u8*)&sFrameData_5fe410[0]))
#define sIntroLandingOnBslOam_5fe420 NFIA_OAM(((const u8*)&sFrameData_5fe420[0]))
#define sIntroLandingOnBslOam_5fe430 NFIA_OAM(((const u8*)&sFrameData_5fe430[0]))
#define sIntroLandingOnBslOam_5ff4d8 NFIA_OAM(((const u8*)&sFrameData_5ff4d8[0]))
#define sIntroLandingOnBslOam_5ff530 NFIA_OAM(((const u8*)&sFrameData_5ff530[0]))
#define sIntroLandingOnBslOam_5ff540 NFIA_OAM(((const u8*)&sFrameData_5ff540[0]))
#define sIntroLandingOnBslOam_5ff580 NFIA_OAM(((const u8*)&sFrameData_5ff580[0]))
#define sIntroLandingOnBslOam_5ff5a8 NFIA_OAM(((const u8*)&sFrameData_5ff5a8[0]))
#define sIntroLandingOnBslOam_5ff5b8 NFIA_OAM(((const u8*)&sFrameData_5ff5b8[0]))
#define sIntroLandingOnBslOam_5ff5e8 NFIA_OAM(((const u8*)&sFrameData_5ff5e8[0]))
#define sIntroLandingOnBslOam_5ff618 NFIA_OAM(((const u8*)&sFrameData_5ff618[0]))
#define sIntroLandingOnBslOam_5ff628 NFIA_OAM(((const u8*)&sFrameData_5ff628[0]))
#define sIntroLandingOnBslOam_5ff638 NFIA_OAM(((const u8*)&sFrameData_5ff638[0]))
#define sIntroLandingOnBslOam_5ff6c0 NFIA_OAM(((const u8*)&sFrameData_5ff6c0[0]))

// Drifting out OAM (sBlob_6094d0_60ac08)
#define sIntroDriftingOutOam_60ac08 NFIA_OAM(((const u8*)&sFrameData_60ac08[0]))
#define sIntroDriftingOutOam_60ac18 NFIA_OAM(((const u8*)&sFrameData_60ac18[0]))
#define sIntroDriftingOutOam_60ac28 NFIA_OAM(((const u8*)&sFrameData_60ac28[0]))
#define sIntroDriftingOutOam_60ac38 NFIA_OAM(((const u8*)&sFrameData_60ac38[0]))
#define sIntroDriftingOutOam_60acd0 NFIA_OAM(((const u8*)&sFrameData_60acd0[0]))
#define sIntroDriftingOutOam_60acf8 NFIA_OAM(((const u8*)&sFrameData_60acf8[0]))
#define sIntroDriftingOutOam_60ad08 NFIA_OAM(((const u8*)&sFrameData_60ad08[0]))
#define sIntroDriftingOutOam_60ad18 NFIA_OAM(((const u8*)&sFrameData_60ad18[0]))
#define sIntroDriftingOutOam_60ad28 NFIA_OAM(((const u8*)&sFrameData_60ad28[0]))
#define sIntroDriftingOutOam_60ad48 NFIA_OAM(((const u8*)&sFrameData_60ad48[0]))

// Samus in ship / ship alert (sBlob_64e470_65bb38)
#define sIntroSamusInShipTilemap   (&sBlob_64e470_65bb38[0xa770])
#define sIntroSamusInShipPal       (&sBlob_64e470_65bb38[0xad74])
#define sIntroShipAlertTilemap     (&sBlob_64e470_65bb38[0xaf74])
#define sIntroShipAlertPal         (&sBlob_64e470_65bb38[0xb534])
#define sIntroShipAlertObjPal      (&sBlob_65c268_662804[0x0])

#define sIntroShipAlertOam_65bb38 NFIA_OAM(((const u8*)&sFrameData_65bb38[0]))
#define sIntroShipAlertOam_65bd00 NFIA_OAM(((const u8*)&sFrameData_65bd00[0]))
#define sIntroShipAlertOam_65bd48 NFIA_OAM(((const u8*)&sFrameData_65bd48[0]))
#define sIntroShipAlertOam_65bd60 NFIA_OAM(((const u8*)&sFrameData_65bd60[0]))
#define sIntroShipAlertOam_65be00 NFIA_OAM(((const u8*)&sFrameData_65be00[0]))
#define sIntroShipAlertOam_65bf10 NFIA_OAM(((const u8*)&sFrameData_65bf10[0]))
#define sIntroShipAlertOam_65c0d0 NFIA_OAM(((const u8*)&sFrameData_65c0d0[0]))
#define sIntroShipAlertOam_65c128 NFIA_OAM(((const u8*)&sFrameData_65c128[0]))
#define sIntroShipAlertOam_65c180 NFIA_OAM(((const u8*)&sFrameData_65c180[0]))
#define sIntroShipAlertOam_65c1d8 NFIA_OAM(((const u8*)&sFrameData_65c1d8[0]))
#define sIntroShipAlertOam_65c230 NFIA_OAM(((const u8*)&sFrameData_65c230[0]))

// Pointer tables at 0x79c448 (5 BG gfx) and 0x79c45c (6 OBJ gfx) inside &sPointers_79c448[0].
// PORT: 32-bit ROM pointers stored in a byte blob, see above.
#define sIntroShipAlertBgGfxPointers  ((const u32* const*)(&sPointers_79c448[0]))
#define sIntroShipAlertObjGfxPointers ((const u32* const*)(&sPointers_79c448[5]))

// Raw bytes of struct IntroData that have no proper field yet (offsets from the struct start)
#define INTRO_DATA_U8_12E(offset) (INTRO_DATA.unk_12E[(offset) - 0x12E])

#define NFIA_OAM_ANIM_ENDED(p) ((p)->pOam[(p)->currentAnimationFrame].timer == (p)->animationDurationCounter && \
    (p)->pOam[(p)->currentAnimationFrame + 1].timer == 0)

// ---------------------------------------------------------------------------
// Callees still in assembly / other files (no prototype in the decomp headers)
// ---------------------------------------------------------------------------
void unk_99940(void);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneFadeIn(void);
u8 SpecialCutsceneGetRandomNumber(void);
boolu32 IntroProcessText(void);

// ---------------------------------------------------------------------------
// Functions of this file
// ---------------------------------------------------------------------------
void NewFileIntroLandingOnBslInit(void);
boolu32 NewFileIntroLandingOnBslProcess(void);
boolu32 NewFileIntroLandingOnBsl(void);
void NewFileIntroProcessLandingOnBslScroll(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessBslDoor(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessBslDoorLight(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessBslDoorTop(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessBslDoorBottom(struct SpecialCutsceneOam* pOam);
void unk_91444(struct SpecialCutsceneOam* pOam);
void unk_914a8(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessShipLandingSmoke(struct SpecialCutsceneOam* pOam);
void unk_918a8(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessExtendingShipArms(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessLandingLights(struct SpecialCutsceneOam* pOam);
void NewFileIntroProcessShipLanding(struct SpecialCutsceneOam* pOam);
u8 NewFileIntroLandingOnBslSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void NewFileIntroLandingOnBslVblank(void);
u8 NewFileIntroGetPositionAndSlotOfOamByType_2(u8 type, s16* pXPosition, s16* pYPosition);
void unk_92098(void);
void unk_9209c(void);
boolu32 IntroSamusInShipProcess(void);
void IntroShipAlertInit(void);
boolu32 IntroShipAlertProcess(void);
void IntroSamusDriftingOutInit(void);
boolu32 IntroSamusDriftingOutProcess(void);
boolu32 IntroSamusShipCrashing(void);
void unk_92d0c(struct SpecialCutsceneOam* pOam);
void IntroProcessDriftingShip(struct SpecialCutsceneOam* pOam);
void IntroProcessBslShipSpawning(struct SpecialCutsceneOam* pOam);
void IntroProcessBslShipBack(struct SpecialCutsceneOam* pOam);
void IntroProcessDepthParticle(struct SpecialCutsceneOam* pOam);
void IntroProcessTimeAndDistanceOam(struct SpecialCutsceneOam* pOam);
void IntroProcessAsteroidsPopUp(struct SpecialCutsceneOam* pOam);
void unk_93300(struct SpecialCutsceneOam* pOam);
void unk_93334(struct SpecialCutsceneOam* pOam);
void IntroOamProcessBigChangingNumber(struct SpecialCutsceneOam* pOam);
u8 IntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
void IntroSetupBigNumberOam(u8 type, s16 xPosition, s16 yPosition, u16 delay);
void unk_93884(void);
void IntroShipAlertAndDraftingVblank(void);
void unk_9397c(struct SpecialCutsceneOam* pOam);

#endif /* NEW_FILE_INTRO_ASM_H */
