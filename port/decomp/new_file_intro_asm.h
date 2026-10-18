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
// sBlob_79c448_79c5a4 contain 32-bit GBA addresses, so on 64-bit they must be
// replaced by properly extracted arrays by the integrator.
// ---------------------------------------------------------------------------
extern const u8 sBlob_5f6990_60093c[];
extern const u8 sBlob_6094d0_60b148[];
extern const u8 sBlob_6101b8_612e48[];
extern const u8 sBlob_64e470_662804[];
extern u8 sBlob_79c448_79c5a4[];
extern const u32* sIntroSamusSittingBgGfxPointers[5];

#define NFIA_BLOB_5F6990(addr) (sBlob_5f6990_60093c + ((addr) - 0x5f6990))
#define NFIA_BLOB_6094D0(addr) (sBlob_6094d0_60b148 + ((addr) - 0x6094d0))
#define NFIA_BLOB_64E470(addr) (sBlob_64e470_662804 + ((addr) - 0x64e470))
#define NFIA_OAM(ptr) ((const struct FrameData*)(ptr))

// Landing on BSL graphics (sBlob_5f6990_60093c)
#define sIntroLandingOnBslBgGfx           NFIA_BLOB_5F6990(0x5f7190)
#define sIntroLandingOnBslObjGfx          NFIA_BLOB_5F6990(0x5fab54)
#define sIntroLandingOnBslBgPal           NFIA_BLOB_5F6990(0x5ff708)
#define sIntroLandingOnBslDoorLightPals   NFIA_BLOB_5F6990(0x5ff908) // 32 bytes per entry
#define sIntroLandingOnBslLightPals       NFIA_BLOB_5F6990(0x5ffb08) // 32 bytes per entry
#define sIntroLandingOnBslObjPal          NFIA_BLOB_5F6990(0x5ffd08)
#define sIntroLandingOnBslTilemap_5fff08  NFIA_BLOB_5F6990(0x5fff08)
#define sIntroLandingOnBslTilemap_60030c  NFIA_BLOB_5F6990(0x60030c)

#define sIntroLandingOnBslOam_5fe370 NFIA_OAM(NFIA_BLOB_5F6990(0x5fe370))
#define sIntroLandingOnBslOam_5fe3c0 NFIA_OAM(NFIA_BLOB_5F6990(0x5fe3c0))
#define sIntroLandingOnBslOam_5fe410 NFIA_OAM(NFIA_BLOB_5F6990(0x5fe410))
#define sIntroLandingOnBslOam_5fe420 NFIA_OAM(NFIA_BLOB_5F6990(0x5fe420))
#define sIntroLandingOnBslOam_5fe430 NFIA_OAM(NFIA_BLOB_5F6990(0x5fe430))
#define sIntroLandingOnBslOam_5ff4d8 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff4d8))
#define sIntroLandingOnBslOam_5ff530 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff530))
#define sIntroLandingOnBslOam_5ff540 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff540))
#define sIntroLandingOnBslOam_5ff580 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff580))
#define sIntroLandingOnBslOam_5ff5a8 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff5a8))
#define sIntroLandingOnBslOam_5ff5b8 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff5b8))
#define sIntroLandingOnBslOam_5ff5e8 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff5e8))
#define sIntroLandingOnBslOam_5ff618 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff618))
#define sIntroLandingOnBslOam_5ff628 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff628))
#define sIntroLandingOnBslOam_5ff638 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff638))
#define sIntroLandingOnBslOam_5ff6c0 NFIA_OAM(NFIA_BLOB_5F6990(0x5ff6c0))

// Drifting out OAM (sBlob_6094d0_60b148)
#define sIntroDriftingOutOam_60ac08 NFIA_OAM(NFIA_BLOB_6094D0(0x60ac08))
#define sIntroDriftingOutOam_60ac18 NFIA_OAM(NFIA_BLOB_6094D0(0x60ac18))
#define sIntroDriftingOutOam_60ac28 NFIA_OAM(NFIA_BLOB_6094D0(0x60ac28))
#define sIntroDriftingOutOam_60ac38 NFIA_OAM(NFIA_BLOB_6094D0(0x60ac38))
#define sIntroDriftingOutOam_60acd0 NFIA_OAM(NFIA_BLOB_6094D0(0x60acd0))
#define sIntroDriftingOutOam_60acf8 NFIA_OAM(NFIA_BLOB_6094D0(0x60acf8))
#define sIntroDriftingOutOam_60ad08 NFIA_OAM(NFIA_BLOB_6094D0(0x60ad08))
#define sIntroDriftingOutOam_60ad18 NFIA_OAM(NFIA_BLOB_6094D0(0x60ad18))
#define sIntroDriftingOutOam_60ad28 NFIA_OAM(NFIA_BLOB_6094D0(0x60ad28))
#define sIntroDriftingOutOam_60ad48 NFIA_OAM(NFIA_BLOB_6094D0(0x60ad48))

// Samus in ship / ship alert (sBlob_64e470_662804)
#define sIntroSamusInShipTilemap   NFIA_BLOB_64E470(0x658be0)
#define sIntroSamusInShipPal       NFIA_BLOB_64E470(0x6591e4)
#define sIntroShipAlertTilemap     NFIA_BLOB_64E470(0x6593e4)
#define sIntroShipAlertPal         NFIA_BLOB_64E470(0x6599a4)
#define sIntroShipAlertObjPal      NFIA_BLOB_64E470(0x65c268)

#define sIntroShipAlertOam_65bb38 NFIA_OAM(NFIA_BLOB_64E470(0x65bb38))
#define sIntroShipAlertOam_65bd00 NFIA_OAM(NFIA_BLOB_64E470(0x65bd00))
#define sIntroShipAlertOam_65bd48 NFIA_OAM(NFIA_BLOB_64E470(0x65bd48))
#define sIntroShipAlertOam_65bd60 NFIA_OAM(NFIA_BLOB_64E470(0x65bd60))
#define sIntroShipAlertOam_65be00 NFIA_OAM(NFIA_BLOB_64E470(0x65be00))
#define sIntroShipAlertOam_65bf10 NFIA_OAM(NFIA_BLOB_64E470(0x65bf10))
#define sIntroShipAlertOam_65c0d0 NFIA_OAM(NFIA_BLOB_64E470(0x65c0d0))
#define sIntroShipAlertOam_65c128 NFIA_OAM(NFIA_BLOB_64E470(0x65c128))
#define sIntroShipAlertOam_65c180 NFIA_OAM(NFIA_BLOB_64E470(0x65c180))
#define sIntroShipAlertOam_65c1d8 NFIA_OAM(NFIA_BLOB_64E470(0x65c1d8))
#define sIntroShipAlertOam_65c230 NFIA_OAM(NFIA_BLOB_64E470(0x65c230))

// Pointer tables at 0x79c448 (5 BG gfx) and 0x79c45c (6 OBJ gfx) inside sBlob_79c448_79c5a4.
// PORT: 32-bit ROM pointers stored in a byte blob, see above.
#define sIntroShipAlertBgGfxPointers  ((const u32* const*)(sBlob_79c448_79c5a4 + 0x00))
#define sIntroShipAlertObjGfxPointers ((const u32* const*)(sBlob_79c448_79c5a4 + 0x14))

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
