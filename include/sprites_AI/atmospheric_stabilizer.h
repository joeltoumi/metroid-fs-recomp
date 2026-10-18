#ifndef ATMOSPHERIC_STABILIZER_AI_H
#define ATMOSPHERIC_STABILIZER_AI_H

#include "types.h"

u8 AtmosphericStabilizerCheckIsInfected(void);
void AtmosphericStabilizerInit(void);
void AtmosphericStabilizerBackOnlineInit(void);
void AtmosphericStabilizerBackOnline(void);
void AtmosphericStabilizerCoverInit(void);
void AtmosphericStabilizerCoverIdle(void);
void AtmosphericStabilizerCoverExploding(void);
void AtmosphericStabilizerParasiteInit(void);
void AtmosphericStabilizerParasiteIdleInit(void);
void AtmosphericStabilizerParasiteIdle(void);
void AtmosphericStabilizerParasiteSpawnX(void);
void AtmosphericStabilizerParasiteDeath(void);
void AtmosphericStabilizer(void);
void AtmosphericStabilizerCover(void);
void AtmosphericStabilizerParasite(void);

#endif /* ATMOSPHERIC_STABILIZER_AI_H */
