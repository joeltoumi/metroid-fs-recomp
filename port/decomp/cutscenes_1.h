#include "data/blob_pieces.h"
#ifndef PORT_DECOMP_CUTSCENES_1_H
#define PORT_DECOMP_CUTSCENES_1_H

// Cutscenes (asm/disasm_0x0808F5C4.s, from CutsceneElevatorMonologue up to unk_9c04c):
// elevator/internal/federation monologues, secret conversation, restricted lab detaching.
// The shared cutscene RAM structs (struct CutsceneData, CutsceneOam, CutsceneMonologueData,
// CutsceneMonologueOam) and the helper prototypes live in cutscenes_2.h.

#include "types.h"
#include "cutscenes_2.h"

// Static data of src/data/new_file_intro_data.c (must be made non-static for the native build)
extern const u8 sBlob_662cfc_663820[];
// (sBlob_6638a0_663dd0 is declared in cutscenes_2.h)

// Static data of src/new_file_intro.c (must be made non-static for the native build)
extern u16** sMonologueTextPointers[];

// Elevator monologue
u32 CutsceneElevatorMonologue(u8 secondVariant);
void CutsceneElevatorMonologueInit(u8 secondVariant);
u32 CutsceneElevatorMonologueProcess(void);
u8 CutsceneElevatorMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneProcessElevatorScrolling(struct CutsceneMonologueOam* pOam);
void unk_9a1a8(struct CutsceneMonologueOam* pOam);
void CutsceneElevatorMonologueVblank(void);
void unk_9a31c(void);

// Internal monologue
u32 CutsceneInternalMonologue(u8 unused);
void CutsceneInternalMonologueInit(void);
u32 CutsceneInternalMonologueProcess(void);
u8 CutsceneInternalMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneInternalMonologueVblank(void);
void unk_9a63c(void);

// Federation monologue
u32 CutsceneFederationMonologue(u8 unused);
void CutsceneFederationMonologueInit(void);
u32 CutsceneFederationMonologueProcess(void);
u8 CutsceneFederationMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneFederationMonologueVblank(void);
void unk_9a99c(void);

// Secret conversation
u32 CutsceneSecretConversation(void);
void CutsceneSecretConversationInit(void);
u32 CutsceneSecretConversationProcess(void);
u8 CutsceneSecretConversationSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneSecretConversationProcessNavigationPanel(struct CutsceneOam* pOam);
void CutsceneSecretConversationProcessIncomingDispatch(struct CutsceneOam* pOam);
void CutsceneSecretConversationVblank(void);
void unk_9ae0c(void);

// Restricted lab detaching
u32 CutsceneRestrictedLabDetaching(void);
void CutsceneRestrictedLabDetachingInit(void);
u32 CutsceneRestrictedLabDetachingProcess(void);
void CutsceneRestrictedLabDetachingProcessFallingLab(struct CutsceneOam* pOam);
// u8 CutsceneRestrictedLabDetachingSetupOam(u8 type, u16 xPosition, u16 yPosition); (in cutscenes_2.h)
void CutsceneRestrictedLabDetachingProcessBslPart(struct CutsceneOam* pOam);
void CutsceneRestrictedLabDetachingProcessScrolling(struct CutsceneOam* pOam);
void unk_9ba50(struct CutsceneOam* pOam);
void unk_9bac0(struct CutsceneOam* pOam);
void unk_9bb30(struct CutsceneOam* pOam);
void unk_9bc04(struct CutsceneOam* pOam);
void unk_9bcdc(struct CutsceneOam* pOam);
void unk_9bd24(struct CutsceneOam* pOam);
void unk_9bdf8(struct CutsceneOam* pOam);
void unk_9be8c(struct CutsceneOam* pOam);
void unk_9bf54(struct CutsceneOam* pOam);
void unk_9bfb8(struct CutsceneOam* pOam);

#endif /* PORT_DECOMP_CUTSCENES_1_H */
