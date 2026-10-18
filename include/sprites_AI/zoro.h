#ifndef ZORO_AI_H
#define ZORO_AI_H

#include "types.h"

u8 ZoroCheckCollidingWithAir(void);
void ZoroSetHitboxAndDrawDistance(void);
void ZoroSetCrawlingOam(void);
void ZoroSetTurningOam(void);
void ZoroSetTurningAroundSecondPartOam(void);
void ZoroSetDeathPosition(void);
void ZoroInit(void);
void ZoroCrawlingInit(void);
u16 ZoroRedGetSpeed(void);
u16 ZoroBlueGetSpeed(void);
void ZoroCrawl(void);
void ZoroTurningInit(void);
void ZoroTurningAround(void);
void ZoroTurningAroundSecondPart(void);
void ZoroFallingInit(void);
void ZoroFalling(void);
void Zoro(void);

#endif /* ZORO_AI_H */
