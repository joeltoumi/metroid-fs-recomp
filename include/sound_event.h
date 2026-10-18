#ifndef SOUND_EVENT_AND_MUSIC_H
#define SOUND_EVENT_AND_MUSIC_H

#include "types.h"

void SoundEventUpdateForSaXEncounter(void);
void SoundEventUpdateForAbility(void);
void SoundEventUpdateForNavConversation(void);
void SoundEventUpdate(u8 soundEvent, u8 triggerType);
void SoundEventUpdateMusic(u8 triggerType);

#endif /* SOUND_EVENT_AND_MUSIC_H */
