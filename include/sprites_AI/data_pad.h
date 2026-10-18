#ifndef DATA_PAD_AI_H
#define DATA_PAD_AI_H

#include "types.h"

void DataPadInit(void);
void DataPadIdleInit(void);
void DataPadIdle(void);
void DataPadPressingSwitch(void);
void DataPadSwitchPressed(void);
void DataPadReleasingSwitch(void);
void DataPadLockingSamus(void);
void DataPadDownloadingData(void);
void DataPadCenterInit(void);
void DataPadCenterIdle(void);
void DataPadCenterEngaging(void);
void DataPadCenterDownloadingData(void);
void DataPadSidesInit(void);
void DataPadSidesIdle(void);
void DataPadSidesEngaging(void);
void DataPadSidesDownloadingData(void);
void DataPadSidesDoneDownloadingData(void);
void DataPadSidesDisengaging(void);
void DataPad(void);
void DataPadCenter(void);
void DataPadSides(void);

#endif /* DATA_PAD_AI_H */
