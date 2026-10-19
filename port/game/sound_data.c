// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — sound engine data that the GBA build gets from assembler
// files or from fixed IWRAM addresses.
//
//   * sSoundDataEntries (sound/sound_entries.s): pointers to the track
//     headers in the ROM. Port_SoundInit (port/game/audio_engine.c) fills it
//     with host pointers into the player's ROM once it is loaded.
//   * gPortAudioRam: the engine's IWRAM variables (gMusicInfo, gPsgSounds,
//     gTrack*Variables, gTrackData*...), which hold pointers and so are
//     bigger natively than their GBA slots (see include/structs/audio.h).
#include "types.h"
#include "constants/audio.h"
#include "structs/audio.h"

// In the save states, like the other game globals (port/src/savestate.c).
#define PORT_STATE __attribute__((section("mf_state")))

PORT_STATE struct PortAudioRam gPortAudioRam;

// The game sees `const struct SoundEntry sSoundDataEntries[]` (data/audio.h).
// This file doesn't include that header and defines the table writable, so
// no compiler can assume it keeps its zero initializer.
struct SoundEntry sSoundDataEntries[SOUND_COUNT];

struct SoundEntry* Port_SoundEntriesForWriting(void)
{
    return sSoundDataEntries;
}
