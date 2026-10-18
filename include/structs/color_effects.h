#ifndef COLOR_EFFECTS_STRUCT_H
#define COLOR_EFFECTS_STRUCT_H

#include "types.h"

#include "constants/color_fading.h"

// Structs

struct ColorFading {
    ColorFadingEffect type;
    u8 stage;
    u8 fadeTimer;
    u8 unk_3;
    ColorFadingStatus status;
    u8 usePalette3:4;
    u8 unk_5_4:4;
    u16 workTimer;
};

struct ColorFadingColorInfo {
    const u8* const colorArray;
    u8 size;
};

struct ColorMultiplier {
    s32 red;
    s32 green;
    s32 blue;
};

// Globals

extern struct ColorFading gColorFading;

#endif /* COLOR_EFFECTS_STRUCT_H */
