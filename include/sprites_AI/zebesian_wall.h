#ifndef ZEBESIAN_WALL_AI_H
#define ZEBESIAN_WALL_AI_H

#include "types.h"

void ZebesianWallSetSideHitboxes(void);
void ZebesianWallDecideRandomAction(void);
void ZebesianWallInit(void);
void ZebesianWallFormingFromX(void);
void ZebesianWallDeath(void);
void ZebesianWallMovingVerticallyInit(void);
void ZebesianWallMoveVertically(void);
void ZebesianWallTurningAroundInit(void);
void ZebesianWallTurningAround(void);
void ZebesianWallJumping(void);
void ZebesianWallIdleInit(void);
void ZebesianWallIdle(void);
void ZebesianWallShootingInit(void);
void ZebesianWallShooting(void);
void ZebesianBeamInit(void);
void ZebesianBeamSpawning(void);
void ZebesianBeamExtending(void);
void ZebesianWall(void);
void ZebesianBeam(void);

#endif /* ZEBESIAN_WALL_AI_H */
