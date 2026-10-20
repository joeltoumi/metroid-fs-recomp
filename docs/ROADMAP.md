# Roadmap

Native port of Metroid Fusion (GBA) to PC and Android, from the
[metroidret/mf](https://github.com/metroidret/mf) decompilation and with the
same platform layer as mzm-android. The game reads its data from the player's
ROM (US or EU, verified by SHA-1); the repository contains no game data.

## M0 — Complete the decompilation

- [x] GBA build identical to the US ROM (`make`, agbcc)
- [x] Hardcoded ROM addresses in `src/` replaced with symbols
- [x] Functions still in assembly (`asm/disasm_*.s`): translated to C in
      `port/decomp/`, each one compared against the original (ARM emulator
      with real RAM states from gameplay)
- [x] Data blocks with pointers (`sBlob_*`): animations and pointer tables
      converted to C with `tools/port/split_blobs.py`; the navigation menu and
      ending tables are rebuilt when the ROM is loaded
- [x] Sound engine (`asm/audio_internal.s`, `asm/sound_code.s`)

## M1 — Native build

- [x] GBA memory map in host buffers; `linker.ld` variables in place
      (`tools/port/gen_ram_symbols.py`)
- [x] Data loaded from the player's ROM (`tools/port/gen_assets.py`)
- [x] Fully compiles and links (clang, x86-64 and ARM64)
- [x] Boots in headless: intro, title, file select, first room

## M2 — European version

- [x] EU ROM addresses in `database.json`
- [x] EU code differences (title screen with language, `SetLanguage`, ending,
      SRAM) under `#ifdef REGION_EU`
- [x] Tested with the EU ROM (up to the first room, text in all 5 languages)

## M3 — Playable on PC and Android

- [ ] SDL3 frontend (inherited from mzm-android): video, controls, touch
- [ ] Sound compared against mGBA
- [x] APK in GitHub Actions (one per region)
- [ ] Options menu, quick saves, fast-forward
- [x] Warp test mode (`MF_WARP`, see [PORT.md](PORT.md)): every room in every
      area, cutscenes, navigation conversations, boss and event rooms, pause
      (map and status), saving and loading, game over, ending and credits
- [x] AddressSanitizer sweep with no errors (EU) and visual review of every
      room and mode
- [ ] Full playthrough by hand

## Not supported

- Link cable connection with Metroid Zero Mission.
