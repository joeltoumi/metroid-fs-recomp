# mf-android

Native port of **Metroid Fusion** (GBA) to Android and PC, built from the
[metroidret/mf](https://github.com/metroidret/mf) decompilation. It is not an
emulator: the game code is compiled as C for the device, with an SDL3 platform
layer (the same one as
[mzm-android](https://github.com/joeltoumi/mzm-android)).

The repository **contains no game data**. On launch, the app asks for your own
copy of the ROM and reads the graphics, sound and text from it.

## Status

- European (EU) and American (US) versions. Each one needs its own ROM:

  | Region | File | SHA-1 |
  |---|---|---|
  | EU | Metroid Fusion (Europe) | `cc46d54b70c1ee38c856ee6e58ec712136763389` |
  | US | Metroid Fusion (USA) | `ca33f4348c2c05dd330d37b97e2c5a69531dfe87` |

- All the code the decompilation still had in assembly has been translated to
  C (`port/decomp/`), and every function has been compared against the
  original. The sound engine is in `port/game/audio_engine.c`.
- Tested on PC with both ROMs:
  - every room in the station and the 6 sectors (381);
  - the cutscenes and the conversations with the computer;
  - the menus, saving and loading, game over, the ending and the credits.
- It still needs thorough testing on Android and a full playthrough by hand.
  Details in [docs/ROADMAP.md](docs/ROADMAP.md).

## Downloading the APK

GitHub Actions builds one APK per region on every change to `main`. Download
it from the **Actions** tab: open the latest `build` run and grab the
`mf-android-apk` artifact. Install the one for your region and pick your ROM
when you open it.

## Building

### Android

You need JDK 17 and the Android SDK with NDK 27.2.12479018:

```
cd android
./gradlew assembleEuRelease   # or assembleUsRelease
```

### PC (Linux, Windows, macOS)

You need CMake, Ninja, a C compiler (clang or gcc) and Python 3. SDL3 is
downloaded automatically if it is not installed.

```
cmake -B build -G Ninja -DMF_REGION=eu    # or us
ninja -C build
./build/mf [path/to/rom.gba]
```

Without a path, the program looks for `mf_eu.gba` / `mf_us.gba` next to the
executable or opens a file picker. `-DMF_HOST=headless` builds `mf_headless`,
a windowless version for testing that dumps screenshots.

### Testing

[docs/PORT.md](docs/PORT.md) explains the `MF_WARP` mode. It jumps to any
room, cutscene or menu with all equipment, and that is how the whole game has
been tested without playing it.

## GBA ROM (decompilation)

The decompilation tree still builds the original US ROM, byte-for-byte
identical, with [agbcc](https://github.com/pret/agbcc) and
`binutils-arm-none-eabi`:

```
cp your_us_rom.gba mf_us_baserom.gba
python3 tools/extractor.py
make -j
sha1sum mf_us.gba   # ca33f4348c2c05dd330d37b97e2c5a69531dfe87
```

The port's changes are under `#ifdef PLATFORM_PC`, so they do not affect that
build. Full agbcc installation instructions are in the
[metroidret/mf README](https://github.com/metroidret/mf#readme).

## Credits

- Decompilation: [metroidret](https://github.com/metroidret/mf)
  ([Discord](https://discord.gg/2MGB9Xbr9y)).
- Metroid Fusion is a trademark of Nintendo. This project is not affiliated
  with Nintendo and does not distribute any game data.
