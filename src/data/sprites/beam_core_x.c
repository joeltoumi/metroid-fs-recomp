#include "data/sprites/beam_core_x.h"

const s16 sIceBeamAbilityFloatingYMovement[65] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3,
    3, 3, 3, 3,
    2, 2, 2, 2,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    -1, -1, -1, -1,
    -2, -2, -2, -2,
    -3, -3, -3, -3,
    -3, -3, -3, -3,
    -2, -2, -2, -2,
    -1, -1, -1, -1,
    0, 0, 0, 0,
    SHORT_MAX
};

const u32 sChargeBeamCoreXGfx[5 * 512] = INCBIN_U32("data/sprites/charge_beam_core_x.gfx");
const u16 sChargeBeamCoreXPal[5 * 16] = INCBIN_U16("data/sprites/charge_beam_core_x.pal");

static const u16 sBeamCoreXAbilityOam_Idle_Frame0[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-11, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(5, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-11, 2, OAM_DIMS_16x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(5, 2, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame1[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-11, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(-11, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24b, 8, 0),
    OAM_ENTRY(-3, -15, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20c, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-9, -16, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(7, -16, OAM_DIMS_8x32, OAM_NO_FLIP, 0x210, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame3[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-10, -16, OAM_DIMS_16x32, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(6, -16, OAM_DIMS_8x32, OAM_NO_FLIP, 0x213, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame4[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-13, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-13, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x254, 8, 0),
    OAM_ENTRY(-5, -16, OAM_DIMS_16x32, OAM_NO_FLIP, 0x215, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame5[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-7, -15, OAM_DIMS_16x8, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-15, -7, OAM_DIMS_32x16, OAM_NO_FLIP, 0x237, 8, 0),
    OAM_ENTRY(-7, 9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x278, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame6[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-7, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-15, -8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x23b, 8, 0),
    OAM_ENTRY(-7, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27c, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_Idle_Frame7[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x2c8, 8, 0),
    OAM_ENTRY(-8, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2a9, 8, 0),
    OAM_ENTRY(8, -13, OAM_DIMS_8x16, OAM_NO_FLIP, 0x2ab, 8, 0),
    OAM_ENTRY(-8, 3, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2e9, 8, 0),
    OAM_ENTRY(8, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x2eb, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_GettingAbsorbed_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x28c, 8, 0),
};

static const u16 sBeamCoreXAbilityOam_GettingAbsorbed_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -18, OAM_DIMS_32x32, OAM_NO_FLIP, 0x28c, 8, 0),
};

static const u16 sBeamCoreXShellOam_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-32, -32, OAM_DIMS_64x64, OAM_NO_FLIP, 0x200, 9, 0),
};

static const u16 sBeamCoreXEyeOam_Closed_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2d4, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opening_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x29e, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opening_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x29c, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opening_Frame3[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x29a, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opening_Frame4[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x298, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opening_Frame5[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x296, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Opened_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x290, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2d0, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame3[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2d2, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame4[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2d6, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame5[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2d8, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame6[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2da, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame7[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2dc, 11, 0),
};

static const u16 sBeamCoreXEyeOam_Charging_Frame8[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x2de, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x200, 9, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame0[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x314, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x314, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x314, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x314, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame4[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x316, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x316, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x316, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x316, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame8[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x318, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x318, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x318, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x318, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame12[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x31a, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x31a, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x31a, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x31a, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame16[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x31c, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x31c, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x31c, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x31c, 11, 0),
};

static const u16 sBeamCoreXGlowingOam_Frame20[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x31e, 11, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x31e, 11, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_16x16, OAM_Y_FLIP, 0x31e, 11, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_16x16, OAM_XY_FLIP, 0x31e, 11, 0),
};

const struct FrameData sBeamCoreXAbilityOam_Idle[9] = {
    [0] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame4,
        .timer = 6
    },
    [5] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame5,
        .timer = 6
    },
    [6] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame6,
        .timer = 6
    },
    [7] = {
        .pFrame = sBeamCoreXAbilityOam_Idle_Frame7,
        .timer = 6
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXAbilityOam_GettingAbsorbed[3] = {
    [0] = {
        .pFrame = sBeamCoreXAbilityOam_GettingAbsorbed_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sBeamCoreXAbilityOam_GettingAbsorbed_Frame1,
        .timer = 2
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXGlowingOam[25] = {
    [0] = {
        .pFrame = sBeamCoreXGlowingOam_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [2] = {
        .pFrame = sBeamCoreXGlowingOam_Frame0,
        .timer = 2
    },
    [3] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [4] = {
        .pFrame = sBeamCoreXGlowingOam_Frame4,
        .timer = 2
    },
    [5] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [6] = {
        .pFrame = sBeamCoreXGlowingOam_Frame4,
        .timer = 2
    },
    [7] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [8] = {
        .pFrame = sBeamCoreXGlowingOam_Frame8,
        .timer = 2
    },
    [9] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [10] = {
        .pFrame = sBeamCoreXGlowingOam_Frame8,
        .timer = 2
    },
    [11] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [12] = {
        .pFrame = sBeamCoreXGlowingOam_Frame12,
        .timer = 2
    },
    [13] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [14] = {
        .pFrame = sBeamCoreXGlowingOam_Frame12,
        .timer = 2
    },
    [15] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [16] = {
        .pFrame = sBeamCoreXGlowingOam_Frame16,
        .timer = 2
    },
    [17] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [18] = {
        .pFrame = sBeamCoreXGlowingOam_Frame16,
        .timer = 2
    },
    [19] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [20] = {
        .pFrame = sBeamCoreXGlowingOam_Frame20,
        .timer = 2
    },
    [21] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [22] = {
        .pFrame = sBeamCoreXGlowingOam_Frame20,
        .timer = 2
    },
    [23] = {
        .pFrame = sBeamCoreXGlowingOam_Frame1,
        .timer = 1
    },
    [24] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXShellOam[2] = {
    [0] = {
        .pFrame = sBeamCoreXShellOam_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Closed[2] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Closed_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Opening[7] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Closed_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame3,
        .timer = 4
    },
    [4] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame4,
        .timer = 4
    },
    [5] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame5,
        .timer = 4
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Opened[2] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Opened_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Charging1[10] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Opened_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame4,
        .timer = 6
    },
    [5] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame5,
        .timer = 6
    },
    [6] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame6,
        .timer = 6
    },
    [7] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame7,
        .timer = 6
    },
    [8] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame8,
        .timer = 6
    },
    [9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Charging2[10] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Opened_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame3,
        .timer = 3
    },
    [4] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame4,
        .timer = 3
    },
    [5] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame5,
        .timer = 3
    },
    [6] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame6,
        .timer = 3
    },
    [7] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame7,
        .timer = 3
    },
    [8] = {
        .pFrame = sBeamCoreXEyeOam_Charging_Frame8,
        .timer = 3
    },
    [9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sBeamCoreXEyeOam_Closing[7] = {
    [0] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame5,
        .timer = 4
    },
    [1] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame4,
        .timer = 4
    },
    [2] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame3,
        .timer = 4
    },
    [3] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame2,
        .timer = 6
    },
    [4] = {
        .pFrame = sBeamCoreXEyeOam_Opening_Frame1,
        .timer = 6
    },
    [5] = {
        .pFrame = sBeamCoreXEyeOam_Closed_Frame0,
        .timer = 6
    },
    [6] = FRAME_DATA_TERMINATOR
};

const u32 sWideBeamCoreXGfx[5 * 512] = INCBIN_U32("data/sprites/wide_beam_core_x.gfx");
const u16 sWideBeamCoreXPal[5 * 16] = INCBIN_U16("data/sprites/wide_beam_core_x.pal");
const u32 sPlasmaBeamCoreXGfx[5 * 512] = INCBIN_U32("data/sprites/plasma_beam_core_x.gfx");
const u16 sPlasmaBeamCoreXPal[5 * 16] = INCBIN_U16("data/sprites/plasma_beam_core_x.pal");
const u32 sWaveBeamCoreXGfx[5 * 512] = INCBIN_U32("data/sprites/wave_beam_core_x.gfx");
const u16 sWaveBeamCoreXPal[5 * 16] = INCBIN_U16("data/sprites/wave_beam_core_x.pal");
const u32 sIceBeamCoreXGfx[5 * 512] = INCBIN_U32("data/sprites/ice_beam_core_x.gfx");
const u16 sIceBeamCoreXPal[5 * 16] = INCBIN_U16("data/sprites/ice_beam_core_x.pal");
