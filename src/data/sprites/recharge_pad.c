#include "data/sprites/recharge_pad.h"

const u32 sRechargePadGfx[3 * 512] = INCBIN_U32("data/sprites/recharge_pad.gfx");
const u16 sRechargePadPal[3 * 16] = INCBIN_U16("data/sprites/recharge_pad.pal");

static const u16 sRechargePadOam_325700_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27a, 8, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sRechargePadOam_325710_Frame1[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(12, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 8, 0),
    OAM_ENTRY(12, -17, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24d, 8, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 8, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sRechargePadOam_325710_Frame2[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(16, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(16, -17, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 8, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sRechargePadOam_325710_Frame3[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(16, -33, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 8, 0),
    OAM_ENTRY(16, -17, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24d, 8, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 8, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sRechargePadOam_325758_Frame0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(16, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27a, 8, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 8, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24a, 8, 0),
};

static const u16 sRechargePadOam_325640_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x24e, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x250, 8, 0),
};

static const u16 sRechargePadOam_325640_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x251, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x253, 8, 0),
};

static const u16 sRechargePadOam_325640_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x254, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x256, 8, 0),
};

static const u16 sRechargePadOam_325668_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x210, 8, 0),
};

static const u16 sRechargePadOam_325668_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x213, 8, 0),
};

static const u16 sRechargePadOam_325668_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x216, 8, 0),
};

static const u16 sRechargePadOam_325690_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x219, 8, 0),
};

static const u16 sRechargePadOam_325690_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21c, 8, 0),
};

static const u16 sRechargePadOam_325690_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -43, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(8, -43, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(0, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-1, -46, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-2, -44, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame3[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-3, -42, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame4[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-4, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame5[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-5, -38, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame6[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-6, -36, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_3256b8_Frame7[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-7, -34, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sRechargePadOam_325738_Frame0[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(16, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27a, 9, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 9, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x257, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 9, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_8x32, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 9, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x24a, 9, 0),
    OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 0x205, 9, 0),
};

static const u16 sRechargePadOam_325738_Frame1[OAM_DATA_SIZE(10)] = {
    10,
    OAM_ENTRY(16, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27a, 9, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 9, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x277, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x27b, 9, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_8x32, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 9, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x24a, 9, 0),
    OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 0x205, 9, 0),
};

static const u16 sRechargePadOam_325738_Frame2[OAM_DATA_SIZE(9)] = {
    9,
    OAM_ENTRY(16, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27a, 9, 0),
    OAM_ENTRY(8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x279, 9, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x259, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20a, 9, 0),
    OAM_ENTRY(-24, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_8x32, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x246, 9, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x24a, 9, 0),
    OAM_ENTRY(16, -48, OAM_DIMS_8x8, OAM_NO_FLIP, 0x205, 9, 0),
};

static const u16 sRechargePadOam_3257d0_Frame0[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x285, 9, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x287, 9, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x285, 9, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x287, 9, 0),
    OAM_ENTRY(-23, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-18, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x281, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 9, 0),
    OAM_ENTRY(2, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x281, 9, 0),
    OAM_ENTRY(15, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25d, 9, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x25d, 9, 0),
};

static const u16 sRechargePadOam_325780_Frame0[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(-8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 9, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x285, 9, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x287, 9, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x285, 9, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x287, 9, 0),
    OAM_ENTRY(-23, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-18, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x281, 9, 0),
    OAM_ENTRY(2, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x281, 9, 0),
    OAM_ENTRY(15, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-16, -7, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(0, -7, OAM_DIMS_16x8, OAM_X_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25d, 9, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x25d, 9, 0),
};

static const u16 sRechargePadOam_325780_Frame1[OAM_DATA_SIZE(15)] = {
    15,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a5, 9, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x2a7, 9, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a5, 9, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x2a7, 9, 0),
    OAM_ENTRY(-23, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-18, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x281, 9, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 9, 0),
    OAM_ENTRY(2, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x281, 9, 0),
    OAM_ENTRY(15, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_X_FLIP, 0x25e, 9, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25d, 9, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x25d, 9, 0),
};

static const u16 sRechargePadOam_325780_Frame2[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x288, 9, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28a, 9, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28a, 9, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x288, 9, 0),
    OAM_ENTRY(-24, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x281, 9, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 9, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x281, 9, 0),
    OAM_ENTRY(16, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25d, 9, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x25d, 9, 0),
};

static const u16 sRechargePadOam_325780_Frame3[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x288, 9, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28a, 9, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28a, 9, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 9, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x288, 9, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x281, 9, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x281, 9, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x280, 9, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25d, 9, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x25b, 9, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x25d, 9, 0),
};

const struct FrameData sRechargePadOam_325640[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325640_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325640_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325640_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sRechargePadOam_325640_Frame1,
        .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325668[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325668_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325668_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325668_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sRechargePadOam_325668_Frame1,
        .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325690[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325690_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325690_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325690_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sRechargePadOam_325690_Frame1,
        .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_3256b8[9] = {
    [0] = {
        .pFrame = sRechargePadOam_3256b8_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_3256b8_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_3256b8_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sRechargePadOam_3256b8_Frame3,
        .timer = 8
    },
    [4] = {
        .pFrame = sRechargePadOam_3256b8_Frame4,
        .timer = 8
    },
    [5] = {
        .pFrame = sRechargePadOam_3256b8_Frame5,
        .timer = 8
    },
    [6] = {
        .pFrame = sRechargePadOam_3256b8_Frame6,
        .timer = 8
    },
    [7] = {
        .pFrame = sRechargePadOam_3256b8_Frame7,
        .timer = 8
    },
    [8] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325700[2] = {
    [0] = {
        .pFrame = sRechargePadOam_325700_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325710[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325700_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325710_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325710_Frame2,
        .timer = 20
    },
    [3] = {
        .pFrame = sRechargePadOam_325710_Frame3,
        .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325738[4] = {
    [0] = {
        .pFrame = sRechargePadOam_325738_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325738_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325738_Frame2,
        .timer = 8
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325758[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325758_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sRechargePadOam_325710_Frame3,
        .timer = 8
    },
    [2] = {
        .pFrame = sRechargePadOam_325710_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sRechargePadOam_325710_Frame1,
        .timer = 8
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_325780[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325780_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sRechargePadOam_325780_Frame1,
        .timer = 4
    },
    [2] = {
        .pFrame = sRechargePadOam_325780_Frame2,
        .timer = 4
    },
    [3] = {
        .pFrame = sRechargePadOam_325780_Frame3,
        .timer = 4
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_3257a8[5] = {
    [0] = {
        .pFrame = sRechargePadOam_325780_Frame3,
        .timer = 6
    },
    [1] = {
        .pFrame = sRechargePadOam_325780_Frame2,
        .timer = 6
    },
    [2] = {
        .pFrame = sRechargePadOam_325780_Frame1,
        .timer = 6
    },
    [3] = {
        .pFrame = sRechargePadOam_325780_Frame0,
        .timer = 6
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_3257d0[2] = {
    [0] = {
        .pFrame = sRechargePadOam_3257d0_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sRechargePadOam_3257e0[2] = {
    [0] = {
        .pFrame = sRechargePadOam_325780_Frame3,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};
