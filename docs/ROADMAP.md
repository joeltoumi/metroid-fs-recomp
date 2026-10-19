# Hoja de ruta

Port nativo de Metroid Fusion (GBA) a PC y Android, desde la decompilación
[metroidret/mf](https://github.com/metroidret/mf) y con la misma capa de
plataforma que mzm-android. El juego lee sus datos de la ROM del jugador
(US o EU, verificada por SHA-1); el repositorio no contiene datos del juego.

## M0 — Completar la decompilación

- [x] Build GBA idéntico a la ROM US (`make`, agbcc)
- [x] Direcciones de ROM fijas en `src/` sustituidas por símbolos
- [ ] Funciones que siguen en ensamblador (`asm/disasm_*.s`): traducción a C
      en `port/decomp/`, cada una comparada con la original (emulador ARM con
      estados de RAM reales de la partida)
- [ ] Bloques de datos con punteros (`sBlob_*`): animaciones y tablas de
      punteros pasadas a C con `tools/port/split_blobs.py`; quedan las
      estructuras del menú de navegación y del final
- [ ] Motor de sonido (`asm/audio_internal.s`, `asm/sound_code.s`)

## M1 — Build nativo

- [x] Mapa de memoria de la GBA en buffers del host; variables de
      `linker.ld` en su sitio (`tools/port/gen_ram_symbols.py`)
- [x] Datos cargados de la ROM del jugador (`tools/port/gen_assets.py`)
- [ ] Compila y enlaza entero (clang, x86-64 y ARM64)
- [ ] Arranca en headless: intro, título, selección de partida, primera sala

## M2 — Versión europea

- [x] Direcciones de la ROM EU en `database.json`
- [ ] Diferencias de código EU (pantalla de título con idioma,
      `SetLanguage`, final, SRAM) bajo `#ifdef REGION_EU`
- [ ] Probada con la ROM EU

## M3 — Jugable en PC y Android

- [ ] Frontend SDL3 (heredado de mzm-android): vídeo, controles, táctil
- [ ] Sonido comparado con mGBA
- [ ] APK en GitHub Actions (una por región)
- [ ] Menú de opciones, guardados rápidos, avance rápido
- [ ] Partida completa jugada a mano

## No soportado

- Conexión con Metroid Zero Mission por cable link.
