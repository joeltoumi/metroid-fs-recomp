#include "data/sprites/zebesian_wall.h"

const s16 sZebesianWallJumpYVelocity[34] = {
    -16, -15, -14, -13,
    -12, -11, -10, -9,
    -8, -7, -6, -5,
    -4, -3, -2, -1,
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15,
    16, SHORT_MAX
};

const s16 sZebesianWallJumpXVelocity[34] = {
    24, 20, 20, 20,
    20, 19, 19, 19,
    19, 18, 18, 18,
    18, 17, 17, 17,
    17, 16, 16, 16,
    16, 16, 16, 16,
    16, 16, 16, 16,
    16, 16, 16, 16,
    16, SHORT_MAX
};

const u32 sZebesianWallGfx[2 * 512] = INCBIN_U32("data/sprites/zebesian_wall.gfx");
const u16 sZebesianWallPal[2 * 16] = INCBIN_U16("data/sprites/zebesian_wall.pal");

static const u16 sZebesianWallOam_Crawling_Frame0[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-1, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(4, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(9, -20, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(8, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(22, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(4, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-1, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
};

static const u16 sZebesianWallOam_Crawling_Frame1[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-1, -32, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(11, -17, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(24, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(5, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(8, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(5, 5, OAM_DIMS_8x16, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-4, 20, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(-2, 9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, -7, OAM_DIMS_16x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(4, -6, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(-1, -39, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sZebesianWallOam_Crawling_Frame2[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(-1, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(3, -13, OAM_DIMS_16x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(8, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(5, 1, OAM_DIMS_8x16, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-4, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(10, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x235, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(24, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(6, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-1, -37, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-4, 13, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(7, -7, OAM_DIMS_16x8, OAM_X_FLIP, 0x231, 8, 0),
};

static const u16 sZebesianWallOam_Crawling_Frame3[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-1, -45, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(3, -14, OAM_DIMS_16x8, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(-4, 10, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, -5, OAM_DIMS_16x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(5, -4, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(24, -14, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(5, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-1, -35, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(4, -10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(8, -1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x16, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-4, 18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sZebesianWallOam_Crawling_Frame4[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(-1, -46, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(4, -21, OAM_DIMS_16x16, OAM_XY_FLIP, 0x203, 8, 0),
    OAM_ENTRY(-4, 7, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(7, -10, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(10, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 8, 0),
    OAM_ENTRY(9, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(4, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-4, 22, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(6, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(8, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(0, -32, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sZebesianWallOam_Idle_Frame0[OAM_DATA_SIZE(11)] = {
    11,
    OAM_ENTRY(-1, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(3, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(4, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(-1, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sZebesianWallOam_Idle_Frame1[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-1, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(3, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(10, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x235, 8, 0),
    OAM_ENTRY(25, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(11, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(4, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(-1, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sZebesianWallOam_Idle_Frame2[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(-1, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-5, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(3, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(10, -19, OAM_DIMS_16x8, OAM_NO_FLIP, 0x235, 8, 0),
    OAM_ENTRY(8, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(24, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(4, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(13, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(0, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-5, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
};

static const u16 sZebesianWallOam_Idle_Frame8[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(0, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-6, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(3, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(24, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(4, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(15, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(0, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-5, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
};

static const u16 sZebesianWallOam_Idle_Frame9[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(0, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-5, -17, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(3, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(9, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(24, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(4, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(15, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(5, -9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(1, -44, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-6, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
};

static const u16 sZebesianWallOam_TurningAround_Frame13[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(8, -5, OAM_DIMS_32x16, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(21, -14, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
    OAM_ENTRY(9, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(11, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
};

static const u16 sZebesianWallOam_TurningAround_Frame14[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(14, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(2, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(14, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(6, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(24, -1, OAM_DIMS_8x32, OAM_Y_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame0[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(4, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(-1, -42, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(11, -21, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(24, -19, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(3, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(10, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(24, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(-1, -33, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(12, 8, OAM_DIMS_16x8, OAM_XY_FLIP, 0x231, 8, 0),
    OAM_ENTRY(7, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(8, 9, OAM_DIMS_16x8, OAM_XY_FLIP, 0x231, 8, 0),
    OAM_ENTRY(17, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(-2, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame1[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(27, -20, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(24, -20, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(4, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-1, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(11, -21, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(24, -19, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(3, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(8, -1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(16, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(5, 1, OAM_DIMS_16x16, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(21, 7, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(7, 7, OAM_DIMS_16x8, OAM_XY_FLIP, 0x231, 8, 0),
    OAM_ENTRY(9, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-1, -31, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-2, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame2[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(24, -19, OAM_DIMS_8x16, OAM_X_FLIP, 0x25b, 8, 0),
    OAM_ENTRY(27, -21, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(31, -18, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(4, -15, OAM_DIMS_16x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-1, -39, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(11, -21, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(24, -19, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(3, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(8, -1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(16, 10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(5, 1, OAM_DIMS_16x16, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(21, 7, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(7, 7, OAM_DIMS_16x8, OAM_XY_FLIP, 0x231, 8, 0),
    OAM_ENTRY(9, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-1, -30, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-1, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame3[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(26, -19, OAM_DIMS_8x16, OAM_X_FLIP, 0x25b, 8, 0),
    OAM_ENTRY(32, -17, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(34, -10, OAM_DIMS_8x8, OAM_X_FLIP, 0x219, 8, 0),
    OAM_ENTRY(1, -33, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(4, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(11, -21, OAM_DIMS_16x8, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(24, -19, OAM_DIMS_8x16, OAM_NO_FLIP, 0x247, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(3, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(8, -2, OAM_DIMS_16x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(14, 7, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(5, -1, OAM_DIMS_16x16, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(19, 5, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(7, 6, OAM_DIMS_16x8, OAM_XY_FLIP, 0x231, 8, 0),
    OAM_ENTRY(9, -4, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-1, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-2, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame4[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(24, -20, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(4, -30, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(6, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(7, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(7, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(16, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(6, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(25, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(0, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(18, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(17, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(34, -16, OAM_DIMS_8x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(39, -9, OAM_DIMS_8x8, OAM_X_FLIP, 0x219, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame5[OAM_DATA_SIZE(14)] = {
    14,
    OAM_ENTRY(22, -20, OAM_DIMS_8x8, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(4, -30, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(6, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(7, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(7, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(16, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(6, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(25, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(0, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(18, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(17, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
    OAM_ENTRY(44, -6, OAM_DIMS_8x8, OAM_X_FLIP, 0x219, 8, 0),
};

static const u16 sZebesianWallOam_Jumping_Frame6[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(4, -30, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(6, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(7, 8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(7, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(16, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(6, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(25, -15, OAM_DIMS_8x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x242, 8, 0),
    OAM_ENTRY(0, -28, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(18, -17, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(17, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 0x249, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame3[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(15, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(16, -3, OAM_DIMS_32x16, OAM_X_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(15, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(6, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(6, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(17, -14, OAM_DIMS_16x16, OAM_X_FLIP, 0x205, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame4[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(15, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(18, -6, OAM_DIMS_32x16, OAM_NO_FLIP, 0x24f, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(15, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(6, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(6, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(17, -14, OAM_DIMS_16x16, OAM_X_FLIP, 0x205, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame5[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(14, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(25, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(41, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(28, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(14, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(8, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(10, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(22, -12, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame6[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(13, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(39, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(26, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(20, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame7[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(13, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(39, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(26, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(20, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame8[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(13, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(39, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(26, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(20, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
    OAM_ENTRY(33, -7, OAM_DIMS_8x16, OAM_NO_FLIP, 0x257, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame13[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(13, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(39, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(26, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(20, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
    OAM_ENTRY(36, -7, OAM_DIMS_8x16, OAM_NO_FLIP, 0x258, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame20[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(36, -16, OAM_DIMS_8x16, OAM_Y_FLIP, 0x259, 8, 0),
    OAM_ENTRY(36, -1, OAM_DIMS_8x16, OAM_NO_FLIP, 0x259, 8, 0),
    OAM_ENTRY(13, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(5, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(39, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(26, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(23, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(20, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallOam_Shooting_Frame21[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(12, -22, OAM_DIMS_16x16, OAM_X_FLIP, 0x240, 8, 0),
    OAM_ENTRY(1, -34, OAM_DIMS_8x32, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(13, -9, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26a, 8, 0),
    OAM_ENTRY(4, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-4, 25, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(7, 11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(9, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-4, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24a, 8, 0),
    OAM_ENTRY(5, -10, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_16x16, OAM_XY_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-4, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(38, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(25, 4, OAM_DIMS_16x8, OAM_X_FLIP, 0x239, 8, 0),
    OAM_ENTRY(22, -12, OAM_DIMS_16x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -13, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extended_Frame3[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x255, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x255, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x273, 8, 0),
    OAM_ENTRY(40, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extended_Frame0[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x275, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x275, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x274, 8, 0),
    OAM_ENTRY(40, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extended_Frame4[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x275, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x275, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x274, 8, 0),
    OAM_ENTRY(40, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extended_Frame1[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x255, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x255, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x273, 8, 0),
    OAM_ENTRY(40, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extended_Frame2[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x253, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x253, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x273, 8, 0),
    OAM_ENTRY(40, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Spawning_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x273, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Spawning_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x274, 8, 0),
    OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Spawning_Frame3[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(8, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x274, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extending_Frame0[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x255, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x273, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extending_Frame3[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x275, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x274, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extending_Frame4[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x275, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x274, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_X_FLIP, 0x274, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extending_Frame1[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_Y_FLIP, 0x255, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x273, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x273, 8, 0),
};

static const u16 sZebesianWallBeamOam_Extending_Frame2[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x253, 8, 0),
    OAM_ENTRY(0, -4, OAM_DIMS_8x8, OAM_Y_FLIP, 0x273, 8, 0),
    OAM_ENTRY(24, -4, OAM_DIMS_8x8, OAM_XY_FLIP, 0x273, 8, 0),
};

const struct FrameData sZebesianWallOam_Crawling[9] = {
    [0] = {
        .pFrame = sZebesianWallOam_Crawling_Frame0,
        .timer = 9
    },
    [1] = {
        .pFrame = sZebesianWallOam_Crawling_Frame1,
        .timer = 9
    },
    [2] = {
        .pFrame = sZebesianWallOam_Crawling_Frame2,
        .timer = 9
    },
    [3] = {
        .pFrame = sZebesianWallOam_Crawling_Frame3,
        .timer = 9
    },
    [4] = {
        .pFrame = sZebesianWallOam_Crawling_Frame4,
        .timer = 9
    },
    [5] = {
        .pFrame = sZebesianWallOam_Crawling_Frame3,
        .timer = 9
    },
    [6] = {
        .pFrame = sZebesianWallOam_Crawling_Frame2,
        .timer = 9
    },
    [7] = {
        .pFrame = sZebesianWallOam_Crawling_Frame1,
        .timer = 9
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallOam_Idle[13] = {
    [0] = {
        .pFrame = sZebesianWallOam_Idle_Frame0,
        .timer = 12
    },
    [1] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 6
    },
    [4] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 8
    },
    [5] = {
        .pFrame = sZebesianWallOam_Idle_Frame0,
        .timer = 15
    },
    [6] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 12
    },
    [7] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 10
    },
    [8] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 9
    },
    [9] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 9
    },
    [10] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 8
    },
    [11] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 12
    },
    [12] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallOam_323790[8] = {
    [0] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 12
    },
    [1] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 5
    },
    [2] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 2
    },
    [3] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 5
    },
    [4] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 2
    },
    [5] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 5
    },
    [6] = {
        .pFrame = sZebesianWallOam_Idle_Frame1,
        .timer = 2
    },
    [7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallOam_TurningAround[16] = {
    [0] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 2
    },
    [1] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 4
    },
    [2] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 1
    },
    [3] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 2
    },
    [4] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 4
    },
    [5] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 1
    },
    [6] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 2
    },
    [7] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 4
    },
    [8] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 1
    },
    [9] = {
        .pFrame = sZebesianWallOam_Idle_Frame2,
        .timer = 2
    },
    [10] = {
        .pFrame = sZebesianWallOam_Idle_Frame8,
        .timer = 4
    },
    [11] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 1
    },
    [12] = {
        .pFrame = sZebesianWallOam_Idle_Frame0,
        .timer = 4
    },
    [13] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame13,
        .timer = 4
    },
    [14] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame14,
        .timer = 40
    },
    [15] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallOam_Jumping[8] = {
    [0] = {
        .pFrame = sZebesianWallOam_Jumping_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sZebesianWallOam_Jumping_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sZebesianWallOam_Jumping_Frame2,
        .timer = 2
    },
    [3] = {
        .pFrame = sZebesianWallOam_Jumping_Frame3,
        .timer = 1
    },
    [4] = {
        .pFrame = sZebesianWallOam_Jumping_Frame4,
        .timer = 1
    },
    [5] = {
        .pFrame = sZebesianWallOam_Jumping_Frame5,
        .timer = 1
    },
    [6] = {
        .pFrame = sZebesianWallOam_Jumping_Frame6,
        .timer = 255
    },
    [7] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallOam_Shooting[27] = {
    [0] = {
        .pFrame = sZebesianWallOam_Idle_Frame9,
        .timer = 4
    },
    [1] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame13,
        .timer = 8
    },
    [2] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame14,
        .timer = 3
    },
    [3] = {
        .pFrame = sZebesianWallOam_Shooting_Frame3,
        .timer = 3
    },
    [4] = {
        .pFrame = sZebesianWallOam_Shooting_Frame4,
        .timer = 2
    },
    [5] = {
        .pFrame = sZebesianWallOam_Shooting_Frame5,
        .timer = 2
    },
    [6] = {
        .pFrame = sZebesianWallOam_Shooting_Frame6,
        .timer = 2
    },
    [7] = {
        .pFrame = sZebesianWallOam_Shooting_Frame7,
        .timer = 3
    },
    [8] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 3
    },
    [9] = {
        .pFrame = sZebesianWallOam_Shooting_Frame7,
        .timer = 3
    },
    [10] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 3
    },
    [11] = {
        .pFrame = sZebesianWallOam_Shooting_Frame7,
        .timer = 3
    },
    [12] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 3
    },
    [13] = {
        .pFrame = sZebesianWallOam_Shooting_Frame13,
        .timer = 2
    },
    [14] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 2
    },
    [15] = {
        .pFrame = sZebesianWallOam_Shooting_Frame13,
        .timer = 2
    },
    [16] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 2
    },
    [17] = {
        .pFrame = sZebesianWallOam_Shooting_Frame13,
        .timer = 2
    },
    [18] = {
        .pFrame = sZebesianWallOam_Shooting_Frame8,
        .timer = 2
    },
    [19] = {
        .pFrame = sZebesianWallOam_Shooting_Frame13,
        .timer = 1
    },
    [20] = {
        .pFrame = sZebesianWallOam_Shooting_Frame20,
        .timer = 1
    },
    [21] = {
        .pFrame = sZebesianWallOam_Shooting_Frame21,
        .timer = 4
    },
    [22] = {
        .pFrame = sZebesianWallOam_Shooting_Frame7,
        .timer = 20
    },
    [23] = {
        .pFrame = sZebesianWallOam_Shooting_Frame3,
        .timer = 4
    },
    [24] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame14,
        .timer = 4
    },
    [25] = {
        .pFrame = sZebesianWallOam_TurningAround_Frame13,
        .timer = 8
    },
    [26] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallBeamOam_Extended[6] = {
    [0] = {
        .pFrame = sZebesianWallBeamOam_Extended_Frame0,
        .timer = 1
    },
    [1] = {
        .pFrame = sZebesianWallBeamOam_Extended_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sZebesianWallBeamOam_Extended_Frame2,
        .timer = 2
    },
    [3] = {
        .pFrame = sZebesianWallBeamOam_Extended_Frame3,
        .timer = 2
    },
    [4] = {
        .pFrame = sZebesianWallBeamOam_Extended_Frame4,
        .timer = 1
    },
    [5] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallBeamOam_Spawning[5] = {
    [0] = {
        .pFrame = sZebesianWallBeamOam_Spawning_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sZebesianWallBeamOam_Spawning_Frame1,
        .timer = 4
    },
    [2] = {
        .pFrame = sZebesianWallBeamOam_Spawning_Frame0,
        .timer = 4
    },
    [3] = {
        .pFrame = sZebesianWallBeamOam_Spawning_Frame3,
        .timer = 3
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZebesianWallBeamOam_Extending[6] = {
    [0] = {
        .pFrame = sZebesianWallBeamOam_Extending_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sZebesianWallBeamOam_Extending_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sZebesianWallBeamOam_Extending_Frame2,
        .timer = 2
    },
    [3] = {
        .pFrame = sZebesianWallBeamOam_Extending_Frame3,
        .timer = 2
    },
    [4] = {
        .pFrame = sZebesianWallBeamOam_Extending_Frame4,
        .timer = 2
    },
    [5] = FRAME_DATA_TERMINATOR
};
