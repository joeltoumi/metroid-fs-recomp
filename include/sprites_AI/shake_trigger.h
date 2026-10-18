#ifndef SHAKE_TRIGGER_AI_H
#define SHAKE_TRIGGER_AI_H

#include "types.h"

void ShakeTriggerStartScreenShake(void);
#ifndef BUGFIX
u32 PreBoxCeilingDebrisCheckSamusInRange(u16 yBlockOffset, u16 xBlockOffset);
#endif // !BUGFIX
void ShakeTrigger(void);
void PreBoxCeilingDebris(void);

#endif /* SHAKE_TRIGGER_AI_H */
