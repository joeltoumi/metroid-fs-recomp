# Pruebas del port nativo

## Modo warp (`MF_WARP`)

Herramienta de pruebas: salta el título, empieza una partida nueva con todo el
equipo (energía, misiles y bombas al máximo, todas las habilidades, nivel de
seguridad 4, todos los mapas) y entra directamente en una sala, o en uno de
los modos de juego que normalmente quedan a horas de partida. Funciona en
cualquier frontend (headless, SDL, Android) porque se lee del entorno. El
código está en `port/src/warp.c` (lista de destinos, entrada simulada) y
`port/game/warp.c` (lado del juego).

```
MF_WARP=DESTINO[,DESTINO...]
  DESTINO = ÁREA:SALA[@EVENTO]
          | MODO:N[@EVENTO]
```

- `ÁREA`: número (0-9) o nombre: `main` (Main Deck), `s1`..`s6` o `srx`,
  `tro`, `pyr`, `aqa`, `arc`, `noc`; `test1`..`test3` son las áreas de prueba
  que quedaron en la ROM.
- `SALA`: número, o `*` para todas las salas del área (las que tienen puerta),
  una detrás de otra.
- `EVENTO`: contador de eventos (decimal o `0x..`). Por defecto, el evento en
  que se llega a ese sector por primera vez (Main Deck: 13, tras el ascensor
  con el SA-X).
- `MODO`:
  - `cutscene:1`..`12` o `cutscene:*`: monólogos, conversación secreta, el
    laboratorio que se desprende, la explosión del BSL.
  - `nav:EVENTO` o `nav:*`: la conversación con el ordenador de ese evento,
    empezando en su sala de navegación.
  - `pause:0`: pantalla de pausa (mapa, estado con R/L).
  - `gameover:0`: Samus muere, pantalla de fin de partida.
  - `ending:0`: final completo, créditos y resultados.
  - `credits:0`: sólo los créditos.
  - `sr388:0`: el final en que la nave choca con SR388.
  - `saxcloseup:0`: primer plano del SA-X.
  - `save:0`: guarda en la ranura A, reinicia y la carga desde el menú.
  - `event:N` o `event:*`: la sala donde ocurre el evento N (jefes,
    habilidades, encuentros con el SA-X, huidas...) con el evento anterior,
    es decir, justo antes de que ocurra.

Los modos se alcanzan desde una sala, como en el juego: tras 40 frames de
juego se pone `gPauseScreenFlag` / `gCurrentCutscene` y se hace el mismo
fundido que usa el juego. Con `MF_WARP_DIRECT=1` las cinemáticas empiezan
nada más arrancar, sin pasar por una sala (para comparar con un emulador
escribiendo esas mismas variables).

Otras variables:

- `MF_WARP_FRAMES=N`: frames por destino cuando hay varios o se usa `*`
  (300 por defecto). Con un solo destino se queda ahí. Al acabar la lista el
  programa termina.
- `MF_WARP_MOVE=0`: sin entrada simulada. Por defecto, en las salas Samus
  corre disparando hacia donde mira, salta, vuelve, se hace bola, pone bombas
  y apunta arriba; en menús y textos se pulsa A; en la pausa se mueve el mapa
  y se pasa a la pantalla de estado y vuelta.

Ejemplos:

```sh
# Todas las salas del Sector 3, 300 frames cada una, un PPM cada 60 frames
MF_WARP='s3:*' ./build/mf_headless --rom mf_eu.gba --frames 100000 \
    --dump-every 60 --out out/s3

# La sala de Box, justo antes de su combate (evento 40, Box derrotado)
MF_WARP='event:40' ./build/mf_headless --rom mf_eu.gba --frames 2000

# Todas las cinemáticas, 2400 frames cada una
MF_WARP='cutscene:*' MF_WARP_FRAMES=2400 ./build/mf_headless --rom mf_eu.gba \
    --frames 30000 --dump-every 120
```

## Barrido con AddressSanitizer

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

Con Clang de Ubuntu hace falta `libclang-rt-18-dev` (el runtime de ASan).

## Qué se ha encontrado así

Atajos de la GBA que en un host de 64 bits fallan o dibujan otra cosa:

- **Macros DMA**: el `DMA_SET` de la GBA hace `(vu32)src`, que convierte sólo
  el primer operando, así que `paleta_u16 + 2 * PAL_ROW_SIZE` suma *bytes*.
  La versión nativa sumaba elementos (el doble o el cuádruple): paletas de
  fila equivocada, gráficos del banner de mensajes y de Samus en los créditos
  leídos fuera de su sitio. Ahora `src/` sigue la regla de agbcc y el código
  escrito para el port (`port/decomp`, `port/game`) la de C
  (`PORT_DMA_C_ARITHMETIC`).
- **Lecturas más allá de una tabla**, que en la GBA leen la ROM que sigue:
  tilemaps de tileset (salas que usan bloques fuera de su tileset), la tabla de
  ruido del motor de sonido, los tiempos de bloques que se rehacen. Se leen de
  la copia de la ROM (`Port_RomMirror` / `Port_RomFind`, que ahora también
  busca tablas de bytes no alineadas).
- **NULL leído como BIOS**: jefes ya derrotados (Box, Nightmare...) que se
  borran al iniciarse pero siguen animando sus datos multi-sprite; el
  cursor del monólogo final antes de tener texto.
- **Estructuras más grandes en nativo**: `SamusInit` copiaba un bloque de
  40 bytes de ceros a estructuras con punteros.
- **Tablas de punteros "fin del array anterior"** (`sUnk_79bea8`, pantalla de
  estado): en la GBA los arrays están seguidos, en nativo no.
- **Código copiado a RAM**: el HBlank de Samus en los créditos se llama
  directamente.
