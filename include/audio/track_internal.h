#ifndef TRACK_INTERNAL_H
#define TRACK_INTERNAL_H

#include "structs/audio.h"

u8 InitTrack(struct TrackData* pTrack, const u32* pHeader);
void StopMusicOrSound(struct TrackData* pTrack);
void ResetTrack(struct TrackData* pTrack);
u32 unk_475c(struct TrackData* pTrack);
void unk_477c(struct TrackData* pTrack, struct TrackVariables* pVariables);
void UpdateAudio(void);
void unk_481c(struct TrackVariables* pVariables);
void unk_48c0(struct TrackVariables* pVariables);
void unk_491c(struct TrackVariables* pVariables);
void unk_4998(struct SoundChannel* pChannel, struct TrackVariables* pVariables, s32 param_3);
void AudioCommand_Goto(struct TrackVariables* pVariables);
void AudioCommand_PatternPlay(struct TrackVariables* pVariables);
// The names of AudioCommand_Goto/AudioCommand_PatternPlay in asm/audio_internal.s
void unk_4a3c(struct TrackVariables* pVariables);
void unk_4a7c(struct TrackVariables* pVariables);
void UploadSampleToWaveRam(const u32* pSample);
void unk_4b10(struct PsgSoundData* pSound);

// asm/sound_code.s
u32 CallGetNoteFrequency(u32 frequency, u32 pitch);

#endif /* TRACK_INTERNAL_H */
