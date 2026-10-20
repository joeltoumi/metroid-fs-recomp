# mf-android

Port nativo de **Metroid Fusion** (GBA) a Android y PC, hecho a partir de la
decompilación [metroidret/mf](https://github.com/metroidret/mf). No es un
emulador: el código del juego se compila en C para el dispositivo, con una
capa de plataforma SDL3 (la misma que
[mzm-android](https://github.com/joeltoumi/mzm-android)).

El repositorio **no contiene datos del juego**. Al arrancar, la app pide tu
propia copia de la ROM y lee de ella los gráficos, el sonido y los textos.

## Estado

- Versiones europea (EU) y estadounidense (US). Cada una necesita su ROM:

  | Región | Archivo | SHA-1 |
  |---|---|---|
  | EU | Metroid Fusion (Europa) | `cc46d54b70c1ee38c856ee6e58ec712136763389` |
  | US | Metroid Fusion (EE. UU.) | `ca33f4348c2c05dd330d37b97e2c5a69531dfe87` |

- Todo el código que la decompilación tenía en ensamblador está traducido a C
  (`port/decomp/`), y cada función se ha comparado con la original. El motor
  de sonido está en `port/game/audio_engine.c`.
- Probado en PC con las dos ROMs:
  - todas las salas de la estación y de los 6 sectores (381);
  - las cinemáticas y las conversaciones con el ordenador;
  - los menús, guardar y cargar, el fin de partida, el final y los créditos.
- Falta probarlo a fondo en Android y jugar una partida completa a mano.
  Detalle en [docs/ROADMAP.md](docs/ROADMAP.md).

## Descargar la APK

GitHub Actions compila una APK por región en cada cambio de `main`. Se
descarga desde la pestaña **Actions**: abre la última ejecución de `build` y
baja el artefacto `mf-android-apk`. Instala la de tu región y, al abrirla,
elige tu ROM.

## Compilar

### Android

Hace falta el JDK 17 y el SDK de Android con el NDK 27.2.12479018:

```
cd android
./gradlew assembleEuRelease   # o assembleUsRelease
```

### PC (Linux, Windows, macOS)

Hacen falta CMake, Ninja, un compilador C (clang o gcc) y Python 3. SDL3 se
descarga solo si no está instalado.

```
cmake -B build -G Ninja -DMF_REGION=eu    # o us
ninja -C build
./build/mf [ruta/a/la/rom.gba]
```

Sin ruta, el programa busca `mf_eu.gba` / `mf_us.gba` junto al ejecutable o
abre un selector de archivos. `-DMF_HOST=headless` compila `mf_headless`, una
versión sin ventana para pruebas que vuelca capturas.

### Pruebas

[docs/PORT.md](docs/PORT.md) explica el modo `MF_WARP`. Este modo salta a
cualquier sala, cinemática o menú con todo el equipo, y así se ha probado el
juego entero sin jugarlo.

## ROM de GBA (decompilación)

El árbol de la decompilación sigue generando la ROM US original, idéntica
byte a byte, con [agbcc](https://github.com/pret/agbcc) y
`binutils-arm-none-eabi`:

```
cp tu_rom_us.gba mf_us_baserom.gba
python3 tools/extractor.py
make -j
sha1sum mf_us.gba   # ca33f4348c2c05dd330d37b97e2c5a69531dfe87
```

Los cambios del port van bajo `#ifdef PLATFORM_PC`, así que no tocan esa
compilación. Las instrucciones completas de instalación de agbcc están en el
[README de metroidret/mf](https://github.com/metroidret/mf#readme).

## Créditos

- Decompilación: [metroidret](https://github.com/metroidret/mf)
  ([Discord](https://discord.gg/2MGB9Xbr9y)).
- Metroid Fusion es una marca de Nintendo. Este proyecto no está afiliado a
  Nintendo y no distribuye ningún dato del juego.
