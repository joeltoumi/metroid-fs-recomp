#include "data/sprites/toxic_gas.h"

const u32 sToxicGasGfx[2 * 512] = INCBIN_U32("data/sprites/toxic_gas.gfx");
const u16 sToxicGasPal[2 * 16] = INCBIN_U16("data/sprites/toxic_gas.pal");

static const u16 sToxicGasOam_3364a8[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x10, 2, 0),
};

static const u16 sToxicGasOam_3364b0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x14, 2, 0),
};

static const u16 sToxicGasOam_3364b8[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x274, 8, 0),
};

static const u16 sToxicGasOam_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 9, 0),
};

static const u16 sToxicGasOam_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x204, 9, 0),
};

static const u16 sToxicGasOam_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x208, 9, 0),
};

static const u16 sToxicGasOam_Frame3[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -16, OAM_DIMS_32x32, OAM_NO_FLIP, 0x20c, 9, 0),
};

static const u16 sToxicGasExplosionOam_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-11, -11, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame1[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-13, -20, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(3, -20, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-21, -10, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-5, -10, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-3, -9, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame2[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(-33, -22, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-17, -22, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-19, -32, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-3, -32, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-3, -31, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(13, -31, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(8, -21, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(24, -21, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(7, -4, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(23, -4, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-32, -3, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-16, -3, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-18, 8, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-2, 8, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-1, 8, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(15, 8, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame3[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(-33, 1, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-17, 1, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-14, 11, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(2, 11, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(3, 6, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(19, 6, OAM_DIMS_8x32, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-37, -18, OAM_DIMS_16x32, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-21, -18, OAM_DIMS_8x32, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-29, -36, OAM_DIMS_16x32, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-13, -36, OAM_DIMS_8x32, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-11, -42, OAM_DIMS_16x32, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(5, -42, OAM_DIMS_8x32, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(6, -31, OAM_DIMS_16x32, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(22, -31, OAM_DIMS_8x32, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(11, -11, OAM_DIMS_16x32, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(27, -11, OAM_DIMS_8x32, OAM_NO_FLIP, 0x215, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame4[OAM_DATA_SIZE(20)] = {
    20,
    OAM_ENTRY(-23, 13, OAM_DIMS_16x32, OAM_X_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-31, 13, OAM_DIMS_8x32, OAM_X_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-30, -2, OAM_DIMS_16x32, OAM_X_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-38, -2, OAM_DIMS_8x32, OAM_X_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-38, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-22, -24, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-28, -39, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-12, -39, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(9, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(19, -23, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(35, -23, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(15, -1, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(31, -1, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(7, 15, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(23, 15, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-10, -45, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(6, -45, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-11, 19, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(5, 19, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame5[OAM_DATA_SIZE(24)] = {
    24,
    OAM_ENTRY(-42, -23, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-26, -23, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-35, -41, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-19, -41, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(20, -42, OAM_DIMS_16x32, OAM_X_FLIP, 0x219, 8, 0),
    OAM_ENTRY(12, -42, OAM_DIMS_8x32, OAM_X_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(23, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(39, -24, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(23, -1, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(39, -1, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(21, 14, OAM_DIMS_16x32, OAM_X_FLIP, 0x219, 8, 0),
    OAM_ENTRY(13, 14, OAM_DIMS_8x32, OAM_X_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-36, 13, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-20, 13, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-44, -3, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-28, -3, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-21, -46, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-5, -46, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-1, -45, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(15, -45, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-21, 22, OAM_DIMS_16x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-5, 22, OAM_DIMS_8x32, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-3, 21, OAM_DIMS_16x32, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(13, 21, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21b, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame6[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(-45, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-37, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-8, -50, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(9, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(31, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(32, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(27, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(6, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-13, 32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-47, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, 22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(21, -41, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-27, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(17, 22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-40, 11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(31, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25e, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame7[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(-25, 30, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25e, 8, 0),
    OAM_ENTRY(35, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-43, -38, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-47, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(-21, -54, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-42, 13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(8, -55, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(24, -39, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(32, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x23a, 8, 0),
    OAM_ENTRY(6, 29, OAM_DIMS_16x16, OAM_NO_FLIP, 0x23a, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame8[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-28, 31, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-38, -43, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(29, -40, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25d, 8, 0),
    OAM_ENTRY(31, 21, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27d, 8, 0),
    OAM_ENTRY(45, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25d, 8, 0),
    OAM_ENTRY(42, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27d, 8, 0),
};

static const u16 sToxicGasExplosionOam_Frame9[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-17, 28, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27c, 8, 0),
    OAM_ENTRY(-25, 42, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27d, 8, 0),
    OAM_ENTRY(-32, 29, OAM_DIMS_8x8, OAM_XY_FLIP, 0x27d, 8, 0),
    OAM_ENTRY(46, -31, OAM_DIMS_8x8, OAM_Y_FLIP, 0x25b, 8, 0),
    OAM_ENTRY(53, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25b, 8, 0),
    OAM_ENTRY(43, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27d, 8, 0),
};

const struct FrameData sToxicGasExplosionOam[11] = {
    [0] = {
        .pFrame = sToxicGasExplosionOam_Frame0,
        .timer = 5
    },
    [1] = {
        .pFrame = sToxicGasExplosionOam_Frame1,
        .timer = 5
    },
    [2] = {
        .pFrame = sToxicGasExplosionOam_Frame2,
        .timer = 5
    },
    [3] = {
        .pFrame = sToxicGasExplosionOam_Frame3,
        .timer = 5
    },
    [4] = {
        .pFrame = sToxicGasExplosionOam_Frame4,
        .timer = 5
    },
    [5] = {
        .pFrame = sToxicGasExplosionOam_Frame5,
        .timer = 5
    },
    [6] = {
        .pFrame = sToxicGasExplosionOam_Frame6,
        .timer = 5
    },
    [7] = {
        .pFrame = sToxicGasExplosionOam_Frame7,
        .timer = 5
    },
    [8] = {
        .pFrame = sToxicGasExplosionOam_Frame8,
        .timer = 5
    },
    [9] = {
        .pFrame = sToxicGasExplosionOam_Frame9,
        .timer = 5
    },
    [10] = FRAME_DATA_TERMINATOR
};

const struct FrameData sToxicGasOam[5] = {
    [0] = {
        .pFrame = sToxicGasOam_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sToxicGasOam_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sToxicGasOam_Frame2,
        .timer = 10
    },
    [3] = {
        .pFrame = sToxicGasOam_Frame3,
        .timer = 10
    },
    [4] = FRAME_DATA_TERMINATOR
};
