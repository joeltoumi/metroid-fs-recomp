#include "data/sprites/data_pad.h"

const u32 sDataPadGfx[512 * 3] = INCBIN_U32("data/sprites/data_pad.gfx");
const u16 sDataPadPal[16 * 3] = INCBIN_U16("data/sprites/data_pad.pal");

static const u16 sDataPadSidesOam_Idle_Frame0[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sDataPadSidesOam_Engaging_Frame0[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(20, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-36, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x257, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x257, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
};

static const u16 sDataPadSidesOam_Engaging_Frame1[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(21, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-37, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x258, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x258, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
};

static const u16 sDataPadSidesOam_Engaging_Frame2[OAM_DATA_SIZE(16)] = {
    16,
    OAM_ENTRY(15, -53, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(21, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -53, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-37, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x259, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x259, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
};

static const u16 sDataPadSidesOam_DownloadingData_Frame0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(15, -53, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(21, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -53, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-37, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
};

static const u16 sDataPadCenterOam_Offline_Frame0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x203, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x203, 8, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x283, 8, 0),
    OAM_ENTRY(-39, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(31, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x21f, 8, 0),
};

static const u16 sDataPadCenterOam_Online_Frame0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x217, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x217, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20e, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28e, 9, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x20e, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x28e, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
};

static const u16 sDataPadCenterOam_Online_Frame1[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x290, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x210, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x290, 9, 0),
};

static const u16 sDataPadCenterOam_Online_Frame2[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x292, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x212, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x292, 9, 0),
};

static const u16 sDataPadCenterOam_DownloadingData_Frame0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x205, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x285, 9, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x205, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x285, 9, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x219, 8, 0),
};

static const u16 sDataPadCenterOam_DownloadingData_Frame1[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x207, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x287, 9, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x207, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x287, 9, 0),
};

static const u16 sDataPadCenterOam_DownloadingData_Frame2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x217, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x217, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x209, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x289, 9, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x209, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x289, 9, 0),
};

static const u16 sOam_321360[OAM_DATA_SIZE(12)] = {
    12,
    OAM_ENTRY(15, -53, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(21, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -53, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-37, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
};

static const u16 sDataPadOam_Unpressed_Frame0[OAM_DATA_SIZE(23)] = {
    23,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x24b, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x24d, 10, 0),
    OAM_ENTRY(-23, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-18, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(2, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(15, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(-8, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(8, 24, OAM_DIMS_16x8, OAM_X_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_8x8, OAM_X_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(8, 32, OAM_DIMS_16x8, OAM_X_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_X_FLIP, 0x25f, 10, 0),
};

static const u16 sDataPadOam_Pressing_Frame0[OAM_DATA_SIZE(23)] = {
    23,
    OAM_ENTRY(-8, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x24b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x24d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x24b, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x24d, 10, 0),
    OAM_ENTRY(-23, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-18, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(2, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(15, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-16, -7, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(0, -7, OAM_DIMS_16x8, OAM_X_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x27d, 10, 0),
    OAM_ENTRY(-8, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27f, 10, 0),
    OAM_ENTRY(8, 24, OAM_DIMS_16x8, OAM_X_FLIP, 0x27d, 10, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_8x8, OAM_X_FLIP, 0x27f, 10, 0),
    OAM_ENTRY(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(8, 32, OAM_DIMS_16x8, OAM_X_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_X_FLIP, 0x25f, 10, 0),
};

static const u16 sDataPadOam_Pressing_Frame1[OAM_DATA_SIZE(23)] = {
    23,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x26b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x26d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x26b, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x26d, 10, 0),
    OAM_ENTRY(-23, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-18, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(2, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(15, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-16, -5, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(0, -5, OAM_DIMS_16x8, OAM_X_FLIP, 0x2ab, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(-8, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(8, 24, OAM_DIMS_16x8, OAM_X_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_8x8, OAM_X_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x25f, 10, 0),
    OAM_ENTRY(8, 32, OAM_DIMS_16x8, OAM_X_FLIP, 0x25d, 10, 0),
    OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_X_FLIP, 0x25f, 10, 0),
};

static const u16 sDataPadOam_Pressing_Frame2[OAM_DATA_SIZE(21)] = {
    21,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-24, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(16, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(-8, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(8, 24, OAM_DIMS_16x8, OAM_X_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_8x8, OAM_X_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x27d, 10, 0),
    OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x27f, 10, 0),
    OAM_ENTRY(8, 32, OAM_DIMS_16x8, OAM_X_FLIP, 0x27d, 10, 0),
    OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_X_FLIP, 0x27f, 10, 0),
};

static const u16 sDataPadOam_Pressed_Frame0[OAM_DATA_SIZE(21)] = {
    21,
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(-24, 24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(-8, 24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(-24, 32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(-8, 32, OAM_DIMS_8x8, OAM_NO_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(8, 24, OAM_DIMS_16x8, OAM_X_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(0, 24, OAM_DIMS_8x8, OAM_X_FLIP, 0x29f, 10, 0),
    OAM_ENTRY(8, 32, OAM_DIMS_16x8, OAM_X_FLIP, 0x29d, 10, 0),
    OAM_ENTRY(0, 32, OAM_DIMS_8x8, OAM_X_FLIP, 0x29f, 10, 0),
};

static const u16 sDataPadOam_321aec_Frame0[OAM_DATA_SIZE(35)] = {
    35,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x203, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x283, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x203, 8, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_X_FLIP, 0x283, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
    OAM_ENTRY(-39, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(31, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x21f, 8, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
};

static const u16 sDataPadOam_321afc_Frame0[OAM_DATA_SIZE(37)] = {
    37,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x217, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x217, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x20e, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28e, 9, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x20e, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x28e, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
};

static const u16 sDataPadOam_321afc_Frame1[OAM_DATA_SIZE(37)] = {
    37,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x210, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x290, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x210, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x290, 9, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
};

static const u16 sDataPadOam_321afc_Frame2[OAM_DATA_SIZE(37)] = {
    37,
    OAM_ENTRY(15, -52, OAM_DIMS_8x16, OAM_X_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(19, -49, OAM_DIMS_16x16, OAM_X_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-23, -52, OAM_DIMS_8x16, OAM_NO_FLIP, 0x25c, 8, 0),
    OAM_ENTRY(-35, -49, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_8x16, OAM_NO_FLIP, 0x219, 8, 0),
    OAM_ENTRY(32, -40, OAM_DIMS_8x16, OAM_X_FLIP, 0x219, 8, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(-16, -48, OAM_DIMS_16x32, OAM_NO_FLIP, 0x212, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_16x8, OAM_NO_FLIP, 0x292, 9, 0),
    OAM_ENTRY(0, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x2a3, 8, 0),
    OAM_ENTRY(0, -48, OAM_DIMS_16x32, OAM_X_FLIP, 0x212, 9, 0),
    OAM_ENTRY(0, -16, OAM_DIMS_16x8, OAM_X_FLIP, 0x292, 9, 0),
    OAM_ENTRY(24, -40, OAM_DIMS_16x32, OAM_X_FLIP, 0x214, 8, 0),
    OAM_ENTRY(24, -8, OAM_DIMS_16x8, OAM_X_FLIP, 0x294, 8, 0),
    OAM_ENTRY(16, -40, OAM_DIMS_8x32, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_X_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -40, OAM_DIMS_16x32, OAM_NO_FLIP, 0x214, 8, 0),
    OAM_ENTRY(-40, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x294, 8, 0),
    OAM_ENTRY(-24, -40, OAM_DIMS_8x32, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-24, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x296, 8, 0),
    OAM_ENTRY(-40, -48, OAM_DIMS_32x32, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-40, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x280, 8, 0),
    OAM_ENTRY(8, -48, OAM_DIMS_32x32, OAM_X_FLIP, 0x200, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x280, 8, 0),
    OAM_ENTRY(-24, 0, OAM_DIMS_16x8, OAM_NO_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-8, 0, OAM_DIMS_8x8, OAM_NO_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(0, 0, OAM_DIMS_8x8, OAM_X_FLIP, 0x28d, 10, 0),
    OAM_ENTRY(-8, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 10, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_16x8, OAM_X_FLIP, 0x28b, 10, 0),
    OAM_ENTRY(-25, 9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-19, 9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(3, 9, OAM_DIMS_16x16, OAM_X_FLIP, 0x21b, 10, 0),
    OAM_ENTRY(17, 9, OAM_DIMS_8x16, OAM_X_FLIP, 0x21a, 10, 0),
    OAM_ENTRY(-24, 8, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(-8, 8, OAM_DIMS_8x16, OAM_NO_FLIP, 0x20d, 10, 0),
    OAM_ENTRY(8, 8, OAM_DIMS_16x16, OAM_X_FLIP, 0x20b, 10, 0),
    OAM_ENTRY(0, 8, OAM_DIMS_8x16, OAM_X_FLIP, 0x20d, 10, 0),
};

const struct FrameData sDataPadOam_Unpressed[2] = {
    [0] = {
        .pFrame = sDataPadOam_Unpressed_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_Pressed[2] = {
    [0] = {
        .pFrame = sDataPadOam_Pressed_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_Pressing[5] = {
    [0] = {
        .pFrame = sDataPadOam_Pressing_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sDataPadOam_Pressing_Frame1,
        .timer = 4
    },
    [2] = {
        .pFrame = sDataPadOam_Pressing_Frame2,
        .timer = 4
    },
    [3] = {
        .pFrame = sDataPadOam_Pressed_Frame0,
        .timer = 4
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_Depressing[5] = {
    [0] = {
        .pFrame = sDataPadOam_Pressed_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sDataPadOam_Pressing_Frame2,
        .timer = 6
    },
    [2] = {
        .pFrame = sDataPadOam_Pressing_Frame1,
        .timer = 6
    },
    [3] = {
        .pFrame = sDataPadOam_Pressing_Frame0,
        .timer = 6
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadCenterOam_Offline[2] = {
    [0] = {
        .pFrame = sDataPadCenterOam_Offline_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadCenterOam_Online[4] = {
    [0] = {
        .pFrame = sDataPadCenterOam_Online_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sDataPadCenterOam_Online_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sDataPadCenterOam_Online_Frame2,
        .timer = 10
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadCenterOam_DownloadingData[5] = {
    [0] = {
        .pFrame = sDataPadCenterOam_DownloadingData_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sDataPadCenterOam_DownloadingData_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sDataPadCenterOam_DownloadingData_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sDataPadCenterOam_DownloadingData_Frame1,
        .timer = 6
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadSidesOam_Idle[2] = {
    [0] = {
        .pFrame = sDataPadSidesOam_Idle_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadSidesOam_Engaging[4] = {
    [0] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame2,
        .timer = 8
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadSidesOam_Disengaging[4] = {
    [0] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame2,
        .timer = 8
    },
    [1] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame0,
        .timer = 8
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadSidesOam_DownloadingData[2] = {
    [0] = {
        .pFrame = sDataPadSidesOam_DownloadingData_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_321aec[2] = {
    [0] = {
        .pFrame = sDataPadOam_321aec_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_321afc[4] = {
    [0] = {
        .pFrame = sDataPadOam_321afc_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sDataPadOam_321afc_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sDataPadOam_321afc_Frame2,
        .timer = 6
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sDataPadOam_321b1c[9] = {
    [0] = {
        .pFrame = sDataPadSidesOam_Idle_Frame0,
        .timer = 50
    },
    [1] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame0,
        .timer = 8
    },
    [2] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame1,
        .timer = 8
    },
    [3] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame2,
        .timer = 8
    },
    [4] = {
        .pFrame = sDataPadSidesOam_DownloadingData_Frame0,
        .timer = 50
    },
    [5] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame2,
        .timer = 8
    },
    [6] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame1,
        .timer = 8
    },
    [7] = {
        .pFrame = sDataPadSidesOam_Engaging_Frame0,
        .timer = 8
    },
    [8] = FRAME_DATA_TERMINATOR
};
