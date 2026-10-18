#include "data/sprites/electric_water.h"

const u32 sElectricWaterGfx[2 * 512] = INCBIN_U32("data/sprites/electric_water.gfx");
const u16 sElectricWaterPal[2 * 16] = INCBIN_U16("data/sprites/electric_water.pal");

static const u16 sElectricWaterDamageOam_Idle_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -34, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(1, -18, OAM_DIMS_8x16, OAM_NO_FLIP, 0x202, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x203, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-10, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame3[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(0, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-8, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 0x229, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame4[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-1, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22e, 8, 0),
    OAM_ENTRY(-5, -15, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(-8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22d, 8, 0),
    OAM_ENTRY(1, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20d, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame5[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(1, -19, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(-9, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(2, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-3, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x233, 8, 0),
};

static const u16 sElectricWaterDamageOam_Stopping_Frame6[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(1, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x235, 8, 0),
    OAM_ENTRY(1, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-9, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x230, 8, 0),
    OAM_ENTRY(-13, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-9, -19, OAM_DIMS_8x8, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(2, -36, OAM_DIMS_8x8, OAM_NO_FLIP, 0x233, 8, 0),
    OAM_ENTRY(4, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(-9, -31, OAM_DIMS_8x8, OAM_NO_FLIP, 0x211, 8, 0),
    OAM_ENTRY(1, -19, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(-9, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(2, -30, OAM_DIMS_8x8, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-3, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x233, 8, 0),
};

static const u16 sElectricWaterDamageOam_Stopping_Frame7[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(2, -15, OAM_DIMS_8x8, OAM_NO_FLIP, 0x235, 8, 0),
    OAM_ENTRY(3, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-12, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(5, -23, OAM_DIMS_8x8, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(1, -32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x214, 8, 0),
};

static const u16 sElectricWaterDamageOam_Stopping_Frame8[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27f, 8, 0),
};

static const u16 sElectricWireOam_Frame0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(1, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(11, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame1[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(12, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(12, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame3[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(12, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(1, -9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame4[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(8, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(12, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(1, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame5[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(8, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-14, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame6[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-14, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame7[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-14, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(2, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame8[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-14, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-2, 8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(2, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame9[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(3, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame10[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(3, -5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame11[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame12[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(0, -24, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-15, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(15, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
};

static const u16 sElectricWireOam_Frame13[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -24, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-15, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
};

static const u16 sElectricWireOam_Frame14[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -24, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-15, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
};

static const u16 sElectricWireOam_Frame15[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(0, -24, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-15, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame16[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(8, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-15, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-1, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame17[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(8, -18, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame18[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame19[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame20[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-1, 16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame21[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-1, 18, OAM_DIMS_8x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame22[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame23[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame24[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(7, -10, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame25[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(7, -10, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame26[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(7, -10, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame27[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(7, -10, OAM_DIMS_8x16, OAM_Y_FLIP, 0x21b, 8, 0),
};

static const u16 sElectricWireOam_Frame28[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame29[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(7, -11, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame30[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(0, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame31[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-5, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame32[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-5, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame33[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21b, 8, 0),
    OAM_ENTRY(-5, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame34[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-5, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21e, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame35[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(1, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(6, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame36[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(10, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(1, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(6, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame37[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(10, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(1, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(6, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame38[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(10, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(-8, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(1, -11, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-4, 1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(6, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x8, OAM_Y_FLIP, 0x219, 8, 0),
};

static const u16 sElectricWireOam_Frame39[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(10, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-10, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(9, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame40[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x237, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-10, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(9, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame41[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(7, -10, OAM_DIMS_8x8, OAM_Y_FLIP, 0x237, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-10, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(9, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-7, 7, OAM_DIMS_16x8, OAM_Y_FLIP, 0x239, 8, 0),
};

static const u16 sElectricWireOam_Frame42[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-10, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(9, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame43[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(1, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(11, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame44[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(1, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(11, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWireOam_Frame45[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(1, -13, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-11, -7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(11, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-2, 7, OAM_DIMS_8x8, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(-7, 1, OAM_DIMS_16x8, OAM_NO_FLIP, 0x239, 8, 0),
    OAM_ENTRY(-7, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x217, 8, 0),
};

static const u16 sElectricWaterOam_Frame0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sElectricWaterOam_Frame1[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
};

static const u16 sElectricWaterOam_Frame2[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
};

static const u16 sElectricWaterOam_Frame3[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
};

static const u16 sElectricWaterOam_Frame4[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
};

static const u16 sElectricWaterOam_Frame5[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
};

static const u16 sElectricWaterOam_Frame6[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
};

static const u16 sElectricWaterOam_Frame7[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-128, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x244, 8, 0),
    OAM_ENTRY(-32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x248, 8, 0),
    OAM_ENTRY(0, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x26c, 8, 0),
    OAM_ENTRY(32, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x260, 8, 0),
    OAM_ENTRY(64, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x264, 8, 0),
    OAM_ENTRY(96, -14, OAM_DIMS_32x8, OAM_NO_FLIP, 0x268, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame6[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-7, -34, OAM_DIMS_16x16, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -18, OAM_DIMS_8x16, OAM_X_FLIP, 0x202, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame7[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-9, -24, OAM_DIMS_16x16, OAM_X_FLIP, 0x203, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame8[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x205, 8, 0),
    OAM_ENTRY(-10, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame9[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -18, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 8, 0),
    OAM_ENTRY(0, -34, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-8, -26, OAM_DIMS_8x8, OAM_NO_FLIP, 0x229, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame10[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-1, -6, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22e, 8, 0),
    OAM_ENTRY(-5, -15, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(-8, -25, OAM_DIMS_8x8, OAM_NO_FLIP, 0x22d, 8, 0),
    OAM_ENTRY(1, -29, OAM_DIMS_8x8, OAM_NO_FLIP, 0x20d, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame11[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-10, -18, OAM_DIMS_8x8, OAM_X_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-10, -9, OAM_DIMS_8x8, OAM_X_FLIP, 0x235, 8, 0),
    OAM_ENTRY(-10, -13, OAM_DIMS_8x8, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_8x8, OAM_X_FLIP, 0x230, 8, 0),
    OAM_ENTRY(4, -21, OAM_DIMS_8x8, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(0, -19, OAM_DIMS_8x8, OAM_X_FLIP, 0x211, 8, 0),
    OAM_ENTRY(-11, -36, OAM_DIMS_8x8, OAM_X_FLIP, 0x233, 8, 0),
    OAM_ENTRY(-13, -30, OAM_DIMS_8x8, OAM_X_FLIP, 0x231, 8, 0),
    OAM_ENTRY(0, -31, OAM_DIMS_8x8, OAM_X_FLIP, 0x211, 8, 0),
    OAM_ENTRY(-10, -19, OAM_DIMS_8x8, OAM_X_FLIP, 0x22f, 8, 0),
    OAM_ENTRY(0, -26, OAM_DIMS_8x8, OAM_X_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-11, -30, OAM_DIMS_8x8, OAM_X_FLIP, 0x210, 8, 0),
    OAM_ENTRY(-6, -11, OAM_DIMS_8x8, OAM_X_FLIP, 0x233, 8, 0),
};

static const u16 sElectricWaterDamageOam_Idle_Frame12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-9, -15, OAM_DIMS_8x8, OAM_X_FLIP, 0x235, 8, 0),
    OAM_ENTRY(-10, -21, OAM_DIMS_8x8, OAM_X_FLIP, 0x236, 8, 0),
    OAM_ENTRY(5, -16, OAM_DIMS_8x8, OAM_X_FLIP, 0x213, 8, 0),
    OAM_ENTRY(-12, -23, OAM_DIMS_8x8, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_8x8, OAM_X_FLIP, 0x214, 8, 0),
};

const struct FrameData sElectricWaterDamageOam_Idle[14] = {
    [0] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame4,
        .timer = 6
    },
    [5] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame5,
        .timer = 6
    },
    [6] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame6,
        .timer = 6
    },
    [7] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame7,
        .timer = 6
    },
    [8] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame8,
        .timer = 6
    },
    [9] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame9,
        .timer = 6
    },
    [10] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame10,
        .timer = 6
    },
    [11] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame11,
        .timer = 6
    },
    [12] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame12,
        .timer = 6
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sElectricWaterDamageOam_Stopping[10] = {
    [0] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame4,
        .timer = 6
    },
    [5] = {
        .pFrame = sElectricWaterDamageOam_Idle_Frame5,
        .timer = 6
    },
    [6] = {
        .pFrame = sElectricWaterDamageOam_Stopping_Frame6,
        .timer = 6
    },
    [7] = {
        .pFrame = sElectricWaterDamageOam_Stopping_Frame7,
        .timer = 6
    },
    [8] = {
        .pFrame = sElectricWaterDamageOam_Stopping_Frame8,
        .timer = 10
    },
    [9] = FRAME_DATA_TERMINATOR
};

const struct FrameData sElectricWireOam[47] = {
    [0] = {
        .pFrame = sElectricWireOam_Frame0,
        .timer = 1
    },
    [1] = {
        .pFrame = sElectricWireOam_Frame1,
        .timer = 1
    },
    [2] = {
        .pFrame = sElectricWireOam_Frame2,
        .timer = 1
    },
    [3] = {
        .pFrame = sElectricWireOam_Frame3,
        .timer = 1
    },
    [4] = {
        .pFrame = sElectricWireOam_Frame4,
        .timer = 1
    },
    [5] = {
        .pFrame = sElectricWireOam_Frame5,
        .timer = 1
    },
    [6] = {
        .pFrame = sElectricWireOam_Frame6,
        .timer = 1
    },
    [7] = {
        .pFrame = sElectricWireOam_Frame7,
        .timer = 1
    },
    [8] = {
        .pFrame = sElectricWireOam_Frame8,
        .timer = 1
    },
    [9] = {
        .pFrame = sElectricWireOam_Frame9,
        .timer = 1
    },
    [10] = {
        .pFrame = sElectricWireOam_Frame10,
        .timer = 1
    },
    [11] = {
        .pFrame = sElectricWireOam_Frame11,
        .timer = 1
    },
    [12] = {
        .pFrame = sElectricWireOam_Frame12,
        .timer = 1
    },
    [13] = {
        .pFrame = sElectricWireOam_Frame13,
        .timer = 1
    },
    [14] = {
        .pFrame = sElectricWireOam_Frame14,
        .timer = 1
    },
    [15] = {
        .pFrame = sElectricWireOam_Frame15,
        .timer = 1
    },
    [16] = {
        .pFrame = sElectricWireOam_Frame16,
        .timer = 1
    },
    [17] = {
        .pFrame = sElectricWireOam_Frame17,
        .timer = 1
    },
    [18] = {
        .pFrame = sElectricWireOam_Frame18,
        .timer = 1
    },
    [19] = {
        .pFrame = sElectricWireOam_Frame19,
        .timer = 1
    },
    [20] = {
        .pFrame = sElectricWireOam_Frame20,
        .timer = 1
    },
    [21] = {
        .pFrame = sElectricWireOam_Frame21,
        .timer = 1
    },
    [22] = {
        .pFrame = sElectricWireOam_Frame22,
        .timer = 1
    },
    [23] = {
        .pFrame = sElectricWireOam_Frame23,
        .timer = 1
    },
    [24] = {
        .pFrame = sElectricWireOam_Frame24,
        .timer = 1
    },
    [25] = {
        .pFrame = sElectricWireOam_Frame25,
        .timer = 1
    },
    [26] = {
        .pFrame = sElectricWireOam_Frame26,
        .timer = 1
    },
    [27] = {
        .pFrame = sElectricWireOam_Frame27,
        .timer = 1
    },
    [28] = {
        .pFrame = sElectricWireOam_Frame28,
        .timer = 1
    },
    [29] = {
        .pFrame = sElectricWireOam_Frame29,
        .timer = 1
    },
    [30] = {
        .pFrame = sElectricWireOam_Frame30,
        .timer = 1
    },
    [31] = {
        .pFrame = sElectricWireOam_Frame31,
        .timer = 1
    },
    [32] = {
        .pFrame = sElectricWireOam_Frame32,
        .timer = 1
    },
    [33] = {
        .pFrame = sElectricWireOam_Frame33,
        .timer = 1
    },
    [34] = {
        .pFrame = sElectricWireOam_Frame34,
        .timer = 1
    },
    [35] = {
        .pFrame = sElectricWireOam_Frame35,
        .timer = 1
    },
    [36] = {
        .pFrame = sElectricWireOam_Frame36,
        .timer = 1
    },
    [37] = {
        .pFrame = sElectricWireOam_Frame37,
        .timer = 1
    },
    [38] = {
        .pFrame = sElectricWireOam_Frame38,
        .timer = 1
    },
    [39] = {
        .pFrame = sElectricWireOam_Frame39,
        .timer = 1
    },
    [40] = {
        .pFrame = sElectricWireOam_Frame40,
        .timer = 1
    },
    [41] = {
        .pFrame = sElectricWireOam_Frame41,
        .timer = 1
    },
    [42] = {
        .pFrame = sElectricWireOam_Frame42,
        .timer = 1
    },
    [43] = {
        .pFrame = sElectricWireOam_Frame43,
        .timer = 1
    },
    [44] = {
        .pFrame = sElectricWireOam_Frame44,
        .timer = 1
    },
    [45] = {
        .pFrame = sElectricWireOam_Frame45,
        .timer = 1
    },
    [46] = FRAME_DATA_TERMINATOR
};

const struct FrameData sElectricWaterOam[9] = {
    [0] = {
        .pFrame = sElectricWaterOam_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sElectricWaterOam_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sElectricWaterOam_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sElectricWaterOam_Frame3,
        .timer = 3
    },
    [4] = {
        .pFrame = sElectricWaterOam_Frame4,
        .timer = 3
    },
    [5] = {
        .pFrame = sElectricWaterOam_Frame5,
        .timer = 3
    },
    [6] = {
        .pFrame = sElectricWaterOam_Frame6,
        .timer = 3
    },
    [7] = {
        .pFrame = sElectricWaterOam_Frame7,
        .timer = 3
    },
    [8] = FRAME_DATA_TERMINATOR
};
