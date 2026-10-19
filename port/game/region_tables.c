// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — region-specific fix-ups of the game's pointer tables, done
// once the player's ROM is loaded. Compiled with the game code (game
// headers, -nostdinc), not with the port layer.
//
// The decomp writes some ROM pointer tables as C, each entry being
// `sBlob_X + offset` with the US offset. That is only right for blobs whose
// internal layout is the same in every region. tools/port (database.json
// check) shows a single such blob differs in the EU ROM: the text blob
// sBlob_6b2fac_72eee0 (US 0x7bf34 bytes, EU 0x7c05c, every language's text
// was re-translated). So the tables pointing into it are rebuilt from the
// ROM's own tables, which have the same shape in both regions:
//   sPointers_79c5c0  (messages, location names)   US 0x0879c5c0  EU 0x0879cdf4
//   sPointers_79ce10  (navigation, Adam, etc.)      US 0x0879ce10  EU 0x0879d644
//   sMonologueTextPointers* (intro/ending, 6 tables) US 0x0879e6a0  EU 0x0879eed4
// PortGbaAddressToPointer() maps each ROM address back into the game's copy
// of the blob (port/src/assets.c), so pointers stay inside sBlob_6b2fac_72eee0.
#include "types.h"
#include "macros.h"
#include "constants/game_state.h"

#include "port_rom.h"

const void* PortGbaAddressToPointer(u32 address);

void Port_GameRomLoaded(void);

#ifdef REGION_EU
extern const void* sPointers_79c5c0[518];
extern const void* sPointers_79ce10[1572];
extern u16** sMonologueTextPointers[LANGUAGE_COUNT];

#define MONOLOGUE_TEXT_COUNT 19

static void RelocateTable(const void** table, u32 count, u32 romAddress)
{
    const u8* src = (const u8*)Port_RomPointer(romAddress);
    u32 i;

    for (i = 0; i < count; i++)
        table[i] = PortGbaAddressToPointer(PortReadGbaU32(src + i * 4));
}
#endif // REGION_EU

void Port_GameRomLoaded(void)
{
#ifdef REGION_EU
    s32 i;

    RelocateTable(sPointers_79c5c0, ARRAY_SIZE(sPointers_79c5c0), 0x0879cdf4);
    RelocateTable(sPointers_79ce10, ARRAY_SIZE(sPointers_79ce10), 0x0879d644);

    // Japanese, English, German, French, Italian, Spanish (hiragana shares the Japanese table)
    for (i = LANGUAGE_HIRAGANA; i < LANGUAGE_COUNT; i++)
    {
        RelocateTable((const void**)sMonologueTextPointers[i], MONOLOGUE_TEXT_COUNT,
            0x0879eed4 + (i - LANGUAGE_HIRAGANA) * MONOLOGUE_TEXT_COUNT * 4);
    }
#endif // REGION_EU
}
