#ifndef GATE_AI_H
#define GATE_AI_H

#include "types.h"

void GateSetCollision(u8 caa);
void GateInit(void);
void GateClosed(void);
void GateOpeningInit(void);
void GateOpening(void);
void GateSwitchInit(void);
void GateSwitchIdle(void);
void GateSwitchPressing(void);
void GateSwitchPressed(void);
void Gate(void);
void GateSwitch(void);

#endif /* GATE_AI_H */
