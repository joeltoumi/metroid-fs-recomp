#ifndef CHOZO_STATUE_AI_H
#define CHOZO_STATUE_AI_H

#include "types.h"

void ChozoStatueSetCollision(u8 caa);
void ChozoStatueInit(void);
void ChozoStatueIdle(void);
void ChozoStatueTransformingInit(void);
void ChozoStatueTransforming(void);
void FakeChozoBallInit(void);
void FakeChozoBallIdle(void);
void FakeChozoBallExposedInit(void);
void FakeChozoBallExposed(void);
void FakeChozoBallTransformation(void);
void ChozoStatue(void);
void FakeChozoBall(void);

#endif /* CHOZO_STATUE_AI_H */
