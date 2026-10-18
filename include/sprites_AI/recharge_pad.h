#ifndef RECHARGE_PAD_AI_H
#define RECHARGE_PAD_AI_H

#include "types.h"

void RechargePadInit(void);
void RechargePadIdleInit(void);
void RechargePadIdle(void);
void RechargePadOpening(void);
void RechargePadOpened(void);
void RechargePadClosing(void);
void RechargePadExtending(void);
void RechargePadRefilling(void);
void RechargePadRetracting(void);
void RechargePadMonitorInit(void);
void RechargePadMonitorIdle(void);
void RechargePadMonitorExtended(void);
void RechargePadMonitorRetractingInit(void);
void RechargePadMonitorRetracting(void);
void RechargePadScreenInit(void);
void RechargePad(void);
void RechargePadMonitor(void);
void RechargePadScreen(void);

#endif /* RECHARGE_PAD_AI_H */
