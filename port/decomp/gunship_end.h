#ifndef GUNSHIP_END_H
#define GUNSHIP_END_H

#include "types.h"
#include "oam.h"

// Data used by the gunship (end of game version), all located inside the
// (static) blob sBlob_39aa34_39f4b0 of src/data/sprites/omega_metroid.c
// PORT: that blob is declared static in the decomp; the native build must
// make it visible (or provide these tables) for these externs to resolve.
extern const u8 sBlob_39aa34_39f4b0[];

#define GUNSHIP_END_BLOB(offset) (&sBlob_39aa34_39f4b0[(offset)])

// 0x0839aae0 : s16 y movement table, terminated by 0x7FFF
#define sGunshipEndIdleYMovement ((const s16*)GUNSHIP_END_BLOB(0xAC))
// 0x0839abc4 : s16 y movement table, terminated by 0x7FFF
#define sGunshipEndEngineYMovement ((const s16*)GUNSHIP_END_BLOB(0x190))
// 0x0839ac84 : u8 rotation table
#define sGunshipEndTakingOffRotation ((const u8*)GUNSHIP_END_BLOB(0x250))
// 0x0839ac90 : u16 scaling table (entering)
#define sGunshipEndEnteringScaling ((const u16*)GUNSHIP_END_BLOB(0x25C))
// 0x0839acd0 : u16 scaling table (taking off)
#define sGunshipEndTakingOffScaling ((const u16*)GUNSHIP_END_BLOB(0x29C))

// Oam
#define sGunshipEndOam_Landed ((const struct FrameData*)GUNSHIP_END_BLOB(0x4114))   // 0x0839eb48
#define sGunshipEndBeamOam ((const struct FrameData*)GUNSHIP_END_BLOB(0x4184))      // 0x0839ebb8
#define sGunshipEndOam_Engine2 ((const struct FrameData*)GUNSHIP_END_BLOB(0x41D4))  // 0x0839ec08
#define sGunshipEndBottomOam ((const struct FrameData*)GUNSHIP_END_BLOB(0x41FC))    // 0x0839ec30
#define sGunshipEndOam_Flying ((const struct FrameData*)GUNSHIP_END_BLOB(0x4234))   // 0x0839ec68
#define sGunshipEndOam_Engine3 ((const struct FrameData*)GUNSHIP_END_BLOB(0x4244))  // 0x0839ec78

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
