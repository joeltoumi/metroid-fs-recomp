#include "data/blob_pieces.h"
#ifndef GUNSHIP_END_H
#define GUNSHIP_END_H

#include "types.h"
#include "oam.h"

// Data used by the gunship (end of game version), all located inside the
// (static) blob sBlob_39aa34_39eb38 of src/data/sprites/omega_metroid.c
// PORT: that blob is declared static in the decomp; the native build must
// make it visible (or provide these tables) for these externs to resolve.

#define GUNSHIP_END_BLOB(offset) (&sBlob_39aa34_39eb38[(offset)])

// 0x0839aae0 : s16 y movement table, terminated by 0x7FFF
#define sGunshipEndIdleYMovement ((const s16*)(&sBlob_39aa34_39eb38[0xac]))
// 0x0839abc4 : s16 y movement table, terminated by 0x7FFF
#define sGunshipEndEngineYMovement ((const s16*)(&sBlob_39aa34_39eb38[0x190]))
// 0x0839ac84 : u8 rotation table
#define sGunshipEndTakingOffRotation ((const u8*)(&sBlob_39aa34_39eb38[0x250]))
// 0x0839ac90 : u16 scaling table (entering)
#define sGunshipEndEnteringScaling ((const u16*)(&sBlob_39aa34_39eb38[0x25c]))
// 0x0839acd0 : u16 scaling table (taking off)
#define sGunshipEndTakingOffScaling ((const u16*)(&sBlob_39aa34_39eb38[0x29c]))

// Oam
#define sGunshipEndOam_Landed ((const struct FrameData*)((const u8*)&sFrameData_39eb48[0]))   // 0x0839eb48
#define sGunshipEndBeamOam ((const struct FrameData*)((const u8*)&sFrameData_39ebb8[0]))      // 0x0839ebb8
#define sGunshipEndOam_Engine2 ((const struct FrameData*)((const u8*)&sFrameData_39ec08[0]))  // 0x0839ec08
#define sGunshipEndBottomOam ((const struct FrameData*)((const u8*)&sFrameData_39ec30[0]))    // 0x0839ec30
#define sGunshipEndOam_Flying ((const struct FrameData*)((const u8*)&sFrameData_39ec68[0]))   // 0x0839ec68
#define sGunshipEndOam_Engine3 ((const struct FrameData*)((const u8*)&sFrameData_39ec78[0]))  // 0x0839ec78

void GunshipEndSpawnBeams(void);
void GunshipEndInit(void);
void GunshipEndWaiting(void);
void GunshipEndMovingUp(void);
void GunshipEndWaitingToEnter(void);
void GunshipEndEntering(void);
void GunshipEndWaitingForSamus(void);
void GunshipEndLockingSamus(void);
void GunshipEndMovingSamusUp(void);
void GunshipEndStartingEngine1(void);
void GunshipEndStartingEngine2(void);
void GunshipEndTakingOff(void);
void GunshipEndDone(void);
void GunshipEndBottomIdle(void);
void GunshiEndpBeamInit(void);
void GunshipEndBeamMovingDown(void);
void GunshipEndBeamMovingUp(void);
void GunshipEnd(void);
void GunshipEndBottom(void);
void GunshipEndBeam(void);

#endif /* GUNSHIP_END_H */
