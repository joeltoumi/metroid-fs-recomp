# Native port testing

## Warp mode (`MF_WARP`)

A testing tool: it skips the title screen, starts a new game with all
equipment (energy, missiles and bombs maxed out, every ability, security level
4, every map) and goes straight into a room, or into one of the game modes
that are normally hours of play away. It works in any frontend (headless, SDL,
Android) because it is read from the environment. The code is in
`port/src/warp.c` (destination list, simulated input) and `port/game/warp.c`
(game side).

```
MF_WARP=DESTINATION[,DESTINATION...]
  DESTINATION = AREA:ROOM[@EVENT]
              | MODE:N[@EVENT]
```

- `AREA`: number (0-9) or name: `main` (Main Deck), `s1`..`s6` or `srx`,
  `tro`, `pyr`, `aqa`, `arc`, `noc`; `test1`..`test3` are the test areas left
  in the ROM.
- `ROOM`: number, or `*` for every room in the area (those with a door), one
  after another.
- `EVENT`: event counter (decimal or `0x..`). By default, the event at which
  that sector is first reached (Main Deck: 13, after the elevator with the
  SA-X).
- `MODE`:
  - `cutscene:1`..`12` or `cutscene:*`: monologues, the secret conversation,
    the lab detaching, the BSL explosion.
  - `nav:EVENT` or `nav:*`: the conversation with the computer for that
    event, starting in its navigation room.
  - `pause:0`: pause screen (map, status with R/L).
  - `gameover:0`: Samus dies, game over screen.
  - `ending:0`: full ending, credits and results.
  - `credits:0`: just the credits.
  - `sr388:0`: the ending where the ship crashes into SR388.
  - `saxcloseup:0`: SA-X close-up.
  - `save:0`: saves to slot A, resets and loads it from the menu.
  - `event:N` or `event:*`: the room where event N happens (bosses,
    abilities, SA-X encounters, escapes...) with the previous event, that is,
    just before it happens.

Modes are reached from a room, as in the game: after 40 frames of gameplay
`gPauseScreenFlag` / `gCurrentCutscene` is set and the same fade the game uses
is performed. With `MF_WARP_DIRECT=1` cutscenes start right at boot, without
going through a room (to compare against an emulator by writing those same
variables).

Other variables:

- `MF_WARP_FRAMES=N`: frames per destination when there are several or `*` is
  used (300 by default). With a single destination it stays there. When the
  list ends the program exits.
- `MF_WARP_ABILITIES=N`: number of abilities (0-18, in game order; 8 = up to
  the Varia Suit, 14 = up to the Gravity Suit). All by default.
- `MF_WARP_MOVE=0`: no simulated input. By default, in rooms Samus runs
  shooting in the direction she faces, jumps, turns back, morphs into a ball,
  lays bombs and aims up; in menus and text A is pressed; in the pause screen
  the map is moved and it switches to the status screen and back.

Examples:

```sh
# Every room in Sector 3, 300 frames each, one PPM every 60 frames
MF_WARP='s3:*' ./build/mf_headless --rom mf_eu.gba --frames 100000 \
    --dump-every 60 --out out/s3

# Box's room, just before its fight (event 40, Box defeated)
MF_WARP='event:40' ./build/mf_headless --rom mf_eu.gba --frames 2000

# Every cutscene, 2400 frames each
MF_WARP='cutscene:*' MF_WARP_FRAMES=2400 ./build/mf_headless --rom mf_eu.gba \
    --frames 30000 --dump-every 120
```

## AddressSanitizer sweep

```sh
cmake -B build-asan -G Ninja -DMF_HOST=headless -DMF_REGION=eu \
    -DCMAKE_C_COMPILER=clang \
    "-DCMAKE_C_FLAGS=-fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer" \
    -DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address
ninja -C build-asan
export ASAN_OPTIONS=detect_leaks=0:halt_on_error=0:suppress_equal_pcs=0
for a in main s1 s2 s3 s4 s5 s6; do
    MF_WARP="$a:*" ./build-asan/mf_headless --rom mf_eu.gba --frames 100000 \
        --dump-every 60 --out out/$a > out/$a.log 2>&1 &
done
```

With Ubuntu's Clang you need `libclang-rt-18-dev` (the ASan runtime).

## What was found this way

GBA shortcuts that crash or draw something else on a 64-bit host:

- **DMA macros**: the GBA's `DMA_SET` does `(vu32)src`, which only casts the
  first operand, so `palette_u16 + 2 * PAL_ROW_SIZE` adds *bytes*. The native
  version added elements (twice or four times as much): palettes from the
  wrong row, and message banner and credits Samus graphics read from the wrong
  place. Now `src/` follows the agbcc rule and the code written for the port
  (`port/decomp`, `port/game`) follows the C rule (`PORT_DMA_C_ARITHMETIC`).
- **Reads past the end of a table**, which on the GBA read the ROM that
  follows: tileset tilemaps (rooms that use blocks outside their tileset), the
  sound engine's noise table, the timers of blocks that regenerate. They are
  read from the ROM copy (`Port_RomMirror` / `Port_RomFind`, which now also
  finds unaligned byte tables).
- **NULL read as BIOS**: already-defeated bosses (Box, Nightmare...) that are
  deleted on init but keep animating their multi-sprite data; the final
  monologue cursor before it has any text.
- **Larger structs natively**: `SamusInit` copied a 40-byte block of zeros
  into structs containing pointers.
- **"End of previous array" pointer tables** (`sUnk_79bea8`, status screen):
  on the GBA the arrays are contiguous, natively they are not.
- **Code copied to RAM**: Samus's HBlank in the credits is called directly.
