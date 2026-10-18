#include "data/sprites/atmospheric_stabilizer.h"

const u32 sAtmosphericStabilizerGfx[3 * 512] = INCBIN_U32("data/sprites/atmospheric_stabilizer.gfx");
const u16 sAtmosphericStabilizerPal[3 * 16] = INCBIN_U16("data/sprites/atmospheric_stabilizer.pal");

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-10, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame1[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-9, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame2[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-6, -5, OAM_DIMS_16x16, OAM_NO_FLIP, 0x270, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame3[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-7, -7, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame4[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-13, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(3, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-13, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame5[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-9, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sOam_327110[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-10, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sOam_327130[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-9, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame6[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-7, -7, OAM_DIMS_16x16, OAM_NO_FLIP, 0x270, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame7[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-9, -7, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame8[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-13, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(3, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-13, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-10, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame9[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-11, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame10[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-8, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame11[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-9, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-7, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x270, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame13[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-7, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame14[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-13, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(3, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-13, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(3, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-7, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28c, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_Idle_Frame15[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
    OAM_ENTRY(-6, -5, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28e, 9, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x286, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28a, 8, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x221, 7, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_XY_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x286, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28a, 8, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x221, 7, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_XY_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x286, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x28a, 8, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineVertical_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x284, 8, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineVertical_Frame1[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x221, 7, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_XY_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x284, 8, 0),
};

static const u16 sAtmosphericStabilizerFanOam_OnlineVertical_Frame2[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x221, 7, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_XY_FLIP, 0x24c, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x32, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x284, 8, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_SpawningX_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-6, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27d, 9, 0),
    OAM_ENTRY(-11, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(5, -11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-11, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(5, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_SpawningX_Frame1[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-9, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x215, 9, 0),
    OAM_ENTRY(-12, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(4, -12, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-12, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(4, 4, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
};

static const u16 sAtmosphericStabilizerParasiteOam_SpawningX_Frame2[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-9, -6, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 9, 0),
    OAM_ENTRY(-13, -11, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(3, -11, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-13, 5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x250, 9, 0),
    OAM_ENTRY(3, 5, OAM_DIMS_8x8, OAM_NO_FLIP, 0x252, 9, 0),
};

static const u16 sAtmosphericStabilizerCoverOam_Down_Frame0[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
    OAM_ENTRY(-3, -24, OAM_DIMS_16x16, OAM_X_FLIP, 0x297, 10, 0),
    OAM_ENTRY(8, -27, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 10, 0),
    OAM_ENTRY(-10, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 10, 0),
    OAM_ENTRY(6, -25, OAM_DIMS_8x16, OAM_NO_FLIP, 0x294, 10, 0),
    OAM_ENTRY(-25, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(-25, 3, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
    OAM_ENTRY(-28, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(-12, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 10, 0),
    OAM_ENTRY(-28, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(-12, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(-33, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
    OAM_ENTRY(8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
    OAM_ENTRY(-30, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 0x295, 10, 0),
    OAM_ENTRY(13, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 10, 0),
};

static const u16 sAtmosphericStabilizerCoverOam_Right_Frame0[OAM_DATA_SIZE(13)] = {
    13,
    OAM_ENTRY(-31, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x297, 10, 0),
    OAM_ENTRY(8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
    OAM_ENTRY(-11, 13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x259, 10, 0),
    OAM_ENTRY(-22, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 10, 0),
    OAM_ENTRY(-22, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(-22, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
    OAM_ENTRY(-10, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 10, 0),
    OAM_ENTRY(6, -25, OAM_DIMS_8x16, OAM_NO_FLIP, 0x294, 10, 0),
    OAM_ENTRY(-25, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(-25, 3, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
    OAM_ENTRY(-27, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
    OAM_ENTRY(-3, 14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 10, 0),
};

static const u16 sAtmosphericStabilizerCoverOam_Left_Frame0[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(5, -30, OAM_DIMS_16x16, OAM_X_FLIP, 0x297, 10, 0),
    OAM_ENTRY(0, 10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x259, 10, 0),
    OAM_ENTRY(-24, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
    OAM_ENTRY(-24, 7, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
    OAM_ENTRY(-11, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 10, 0),
    OAM_ENTRY(-2, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x295, 10, 0),
    OAM_ENTRY(7, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(7, 16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
    OAM_ENTRY(11, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(11, 3, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
    OAM_ENTRY(2, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 10, 0),
    OAM_ENTRY(18, -23, OAM_DIMS_8x16, OAM_NO_FLIP, 0x294, 10, 0),
    OAM_ENTRY(-15, 6, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(1, 6, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 10, 0),
    OAM_ENTRY(-15, 22, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(1, 22, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(-20, -31, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
};

static const u16 sAtmosphericStabilizerCoverOam_UpLeft_Frame0[OAM_DATA_SIZE(18)] = {
    18,
    OAM_ENTRY(-10, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
    OAM_ENTRY(16, 0, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
    OAM_ENTRY(-16, 6, OAM_DIMS_16x16, OAM_X_FLIP, 0x297, 10, 0),
    OAM_ENTRY(19, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 10, 0),
    OAM_ENTRY(-26, 4, OAM_DIMS_16x16, OAM_NO_FLIP, 0x295, 10, 0),
    OAM_ENTRY(-17, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 10, 0),
    OAM_ENTRY(-22, 12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(-24, -14, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(-24, 2, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(11, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
    OAM_ENTRY(-14, -26, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 10, 0),
    OAM_ENTRY(2, -26, OAM_DIMS_8x16, OAM_NO_FLIP, 0x294, 10, 0),
    OAM_ENTRY(-25, -23, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
    OAM_ENTRY(6, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(22, -28, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 10, 0),
    OAM_ENTRY(6, -12, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(22, -12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
};

static const u16 sAtmosphericStabilizerCoverOam_UpRight_Frame0[OAM_DATA_SIZE(17)] = {
    17,
    OAM_ENTRY(-25, -10, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
    OAM_ENTRY(4, -24, OAM_DIMS_16x16, OAM_X_FLIP, 0x297, 10, 0),
    OAM_ENTRY(-6, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
    OAM_ENTRY(-25, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(-25, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
    OAM_ENTRY(11, 3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x217, 10, 0),
    OAM_ENTRY(-9, -26, OAM_DIMS_16x16, OAM_X_FLIP, 0x292, 10, 0),
    OAM_ENTRY(-17, -26, OAM_DIMS_8x16, OAM_X_FLIP, 0x294, 10, 0),
    OAM_ENTRY(7, -13, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(23, -13, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 10, 0),
    OAM_ENTRY(7, 3, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(23, 3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(12, -25, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
    OAM_ENTRY(3, -29, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 10, 0),
    OAM_ENTRY(2, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x295, 10, 0),
    OAM_ENTRY(11, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(11, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327a70_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x292, 10, 0),
    OAM_ENTRY(8, -8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x294, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327a80_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x299, 10, 0),
    OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25b, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327a90_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x253, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327aa0_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x257, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327ae0_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x295, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327af0_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327b00_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x219, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327ab0_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x255, 10, 0),
};

static const u16 sOam_327628[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-8, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x27b, 10, 0),
    OAM_ENTRY(-8, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2bb, 10, 0),
};

static const u16 sAtmosphericStabilizerOam_327ad0_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x297, 10, 0),
};

const struct FrameData sAtmosphericStabilizerFanOam_OnlineHorizontal[4] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerFanOam_CloggedHorizontal[16] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 3
    },
    [4] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 3
    },
    [5] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 3
    },
    [6] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 2
    },
    [7] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 2
    },
    [8] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 2
    },
    [9] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 5
    },
    [10] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 6
    },
    [11] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 7
    },
    [12] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 3
    },
    [13] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 4
    },
    [14] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 5
    },
    [15] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerFanOam_RestartingHorizontal[31] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 8
    },
    [4] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 8
    },
    [5] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 8
    },
    [6] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 6
    },
    [7] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 6
    },
    [8] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 6
    },
    [9] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 6
    },
    [10] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 6
    },
    [11] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 6
    },
    [12] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 5
    },
    [13] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 5
    },
    [14] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 5
    },
    [15] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 5
    },
    [16] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 5
    },
    [17] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 5
    },
    [18] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 3
    },
    [19] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 3
    },
    [20] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 3
    },
    [21] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 3
    },
    [22] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 3
    },
    [23] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 3
    },
    [24] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 2
    },
    [25] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 2
    },
    [26] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 2
    },
    [27] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame0,
        .timer = 2
    },
    [28] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame1,
        .timer = 2
    },
    [29] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineHorizontal_Frame2,
        .timer = 2
    },
    [30] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerFanOam_OnlineVertical[4] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 2
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerFanOam_CloggedVertical[16] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 3
    },
    [4] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 3
    },
    [5] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 3
    },
    [6] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 2
    },
    [7] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 2
    },
    [8] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 2
    },
    [9] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 5
    },
    [10] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 6
    },
    [11] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 7
    },
    [12] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 3
    },
    [13] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 4
    },
    [14] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 5
    },
    [15] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerFanOam_RestartingVertical[31] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 8
    },
    [4] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 8
    },
    [5] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 8
    },
    [6] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 6
    },
    [7] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 6
    },
    [8] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 6
    },
    [9] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 6
    },
    [10] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 6
    },
    [11] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 6
    },
    [12] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 5
    },
    [13] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 5
    },
    [14] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 5
    },
    [15] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 5
    },
    [16] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 5
    },
    [17] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 5
    },
    [18] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 3
    },
    [19] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 3
    },
    [20] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 3
    },
    [21] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 3
    },
    [22] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 3
    },
    [23] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 3
    },
    [24] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 2
    },
    [25] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 2
    },
    [26] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 2
    },
    [27] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame0,
        .timer = 2
    },
    [28] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame1,
        .timer = 2
    },
    [29] = {
        .pFrame = sAtmosphericStabilizerFanOam_OnlineVertical_Frame2,
        .timer = 2
    },
    [30] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerParasiteOam_Idle[17] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame0,
        .timer = 7
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame1,
        .timer = 7
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame2,
        .timer = 7
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame3,
        .timer = 7
    },
    [4] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame4,
        .timer = 7
    },
    [5] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame5,
        .timer = 7
    },
    [6] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame6,
        .timer = 7
    },
    [7] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame7,
        .timer = 7
    },
    [8] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame8,
        .timer = 7
    },
    [9] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame9,
        .timer = 7
    },
    [10] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame10,
        .timer = 7
    },
    [11] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame11,
        .timer = 7
    },
    [12] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame12,
        .timer = 7
    },
    [13] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame13,
        .timer = 7
    },
    [14] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame14,
        .timer = 7
    },
    [15] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_Idle_Frame15,
        .timer = 7
    },
    [16] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerParasiteOam_SpawningX[5] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_SpawningX_Frame0,
        .timer = 5
    },
    [1] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_SpawningX_Frame1,
        .timer = 5
    },
    [2] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_SpawningX_Frame2,
        .timer = 5
    },
    [3] = {
        .pFrame = sAtmosphericStabilizerParasiteOam_SpawningX_Frame1,
        .timer = 5
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerCoverOam_Down[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerCoverOam_Down_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerCoverOam_Right[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerCoverOam_Right_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerCoverOam_Left[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerCoverOam_Left_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerCoverOam_UpLeft[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerCoverOam_UpLeft_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerCoverOam_UpRight[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerCoverOam_UpRight_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327a70[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327a70_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327a80[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327a80_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327a90[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327a90_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327aa0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327aa0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327ab0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327ab0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327ac0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327ab0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327ad0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327ad0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327ae0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327ae0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327af0[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327af0_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sAtmosphericStabilizerOam_327b00[2] = {
    [0] = {
        .pFrame = sAtmosphericStabilizerOam_327b00_Frame0,
        .timer = 4
    },
    [1] = FRAME_DATA_TERMINATOR
};
