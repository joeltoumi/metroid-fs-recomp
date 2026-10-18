#include "data/animated_palette_data.h"

#include "macros.h"
#include "gba/memory.h"

#include "data/tilesets/tilesets_set0.h"
#include "data/tilesets/tilesets_set1.h"
#include "data/tilesets/tilesets_set2.h"
#include "data/tilesets/tilesets_set4.h"
#include "data/tilesets/tilesets_set6.h"
#include "data/tilesets/tilesets_set7.h"

const struct AnimatedPaletteTiming sAnimatedPaletteTiming_Empty = {
    .timer1 = 0,
    .row1 = 0,
    .timer2 = 0,
    .row2 = 0
};

// TODO: enum for palette IDs
const struct AnimatedPaletteData sAnimatedPaletteEntries[33] = {
    [0] = {
        .type = ANIMATED_PALETTE_TYPE_NONE,
        .framesPerState = 0,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_1) / PAL_ROW,
        .pPalette = sAnimatedPal_1
    },
    [1] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_1) / PAL_ROW,
        .pPalette = sAnimatedPal_1
    },
    [2] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_2) / PAL_ROW,
        .pPalette = sAnimatedPal_2
    },
    [3] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_3) / PAL_ROW,
        .pPalette = sAnimatedPal_3
    },
    [4] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_4) / PAL_ROW,
        .pPalette = sAnimatedPal_4
    },
    [5] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 5,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_5) / PAL_ROW,
        .pPalette = sAnimatedPal_5
    },
    [6] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 2,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_6) / PAL_ROW,
        .pPalette = sAnimatedPal_6
    },
    [7] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_7) / PAL_ROW,
        .pPalette = sAnimatedPal_7
    },
    [8] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_8) / PAL_ROW,
        .pPalette = sAnimatedPal_8
    },
    [9] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_6) / PAL_ROW,
        .pPalette = sAnimatedPal_6
    },
    [10] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_10) / PAL_ROW,
        .pPalette = sAnimatedPal_10
    },
    [11] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_11) / PAL_ROW,
        .pPalette = sAnimatedPal_11
    },
    [12] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_12) / PAL_ROW,
        .pPalette = sAnimatedPal_12
    },
    [13] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_13) / PAL_ROW,
        .pPalette = sAnimatedPal_13
    },
    [14] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_14) / PAL_ROW,
        .pPalette = sAnimatedPal_14
    },
    [15] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 12,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_15) / PAL_ROW,
        .pPalette = sAnimatedPal_15
    },
    [16] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 4,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_16) / PAL_ROW,
        .pPalette = sAnimatedPal_16
    },
    [17] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_17) / PAL_ROW,
        .pPalette = sAnimatedPal_17
    },
    [18] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 14,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_18) / PAL_ROW,
        .pPalette = sAnimatedPal_18
    },
    [19] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_19) / PAL_ROW,
        .pPalette = sAnimatedPal_19
    },
    [20] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 3,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_20) / PAL_ROW,
        .pPalette = sAnimatedPal_20
    },
    [21] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 3,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_21) / PAL_ROW,
        .pPalette = sAnimatedPal_21
    },
    [22] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_22) / PAL_ROW,
        .pPalette = sAnimatedPal_22
    },
    [23] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_23) / PAL_ROW,
        .pPalette = sAnimatedPal_23
    },
    [24] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_24) / PAL_ROW,
        .pPalette = sAnimatedPal_24
    },
    [25] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_25) / PAL_ROW,
        .pPalette = sAnimatedPal_25
    },
    [26] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 7,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_26) / PAL_ROW,
        .pPalette = sAnimatedPal_26
    },
    [27] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 8,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_27) / PAL_ROW,
        .pPalette = sAnimatedPal_27
    },
    [28] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 3,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_28) / PAL_ROW,
        .pPalette = sAnimatedPal_28
    },
    [29] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 6,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_29) / PAL_ROW,
        .pPalette = sAnimatedPal_29
    },
    [30] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 12,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_30) / PAL_ROW,
        .pPalette = sAnimatedPal_30
    },
    [31] = {
        .type = ANIMATED_PALETTE_TYPE_NORMAL,
        .framesPerState = 12,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_31) / PAL_ROW,
        .pPalette = sAnimatedPal_31
    },
    [32] = {
        .type = ANIMATED_PALETTE_TYPE_ALTERNATE,
        .framesPerState = 10,
        .numberOfStates = ARRAY_SIZE(sAnimatedPal_32) / PAL_ROW,
        .pPalette = sAnimatedPal_32
    }
};
