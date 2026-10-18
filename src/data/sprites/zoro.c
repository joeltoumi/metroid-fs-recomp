#include "data/sprites/zoro.h"

const u32 sZoroGfx[1 * 512] = INCBIN_U32("data/sprites/zoro.gfx");
const u32 sBlueZoroGfx[1 * 512] = INCBIN_U32("data/sprites/blue_zoro.gfx");
const u16 sZoroPal[1 * 16] = INCBIN_U16("data/sprites/zoro.pal");
const u16 sBlueZoroPal[1 * 16] = INCBIN_U16("data/sprites/blue_zoro.pal");

static const u16 sZoroOam_CrawlingVertical_Frame0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(16, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(0, 1, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(8, 9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x230, 8, 0),
    OAM_ENTRY(0, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(0, -19, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(0, -17, OAM_DIMS_8x8, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sZoroOam_CrawlingVertical_Frame1[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -3, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(16, -3, OAM_DIMS_8x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(0, 1, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(8, 9, OAM_DIMS_8x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x230, 8, 0),
    OAM_ENTRY(0, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(0, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(0, -19, OAM_DIMS_8x8, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sZoroOam_CrawlingVertical_Frame2[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -2, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(16, -2, OAM_DIMS_8x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(0, 2, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(8, 10, OAM_DIMS_8x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x230, 8, 0),
    OAM_ENTRY(0, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(0, -21, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(0, -21, OAM_DIMS_8x8, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sZoroOam_CrawlingVertical_Frame3[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -1, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
    OAM_ENTRY(16, -1, OAM_DIMS_8x8, OAM_NO_FLIP, 0x231, 8, 0),
    OAM_ENTRY(0, 4, OAM_DIMS_8x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(8, 12, OAM_DIMS_8x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x230, 8, 0),
    OAM_ENTRY(0, -9, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(0, -22, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(0, -22, OAM_DIMS_8x8, OAM_NO_FLIP, 0x207, 8, 0),
};

static const u16 sZoroOam_TurningAroundVertical1_Frame0[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, 4, OAM_DIMS_16x8, OAM_NO_FLIP, 0x210, 8, 0),
    OAM_ENTRY(0, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21a, 8, 0),
    OAM_ENTRY(16, -9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21c, 8, 0),
};

static const u16 sZoroOam_TurningAroundVertical1_Frame1[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(0, -12, OAM_DIMS_16x16, OAM_NO_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(0, 3, OAM_DIMS_16x8, OAM_Y_FLIP, 0x21d, 8, 0),
    OAM_ENTRY(16, -9, OAM_DIMS_8x16, OAM_NO_FLIP, 0x21f, 8, 0),
};

static const u16 sZoroOam_CrawlingHorizontal_Frame0[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-2, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
    OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x202, 8, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x226, 8, 0),
    OAM_ENTRY(-18, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-16, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sZoroOam_CrawlingHorizontal_Frame1[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-2, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-2, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(2, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
    OAM_ENTRY(10, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x202, 8, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x226, 8, 0),
    OAM_ENTRY(-19, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-18, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sZoroOam_CrawlingHorizontal_Frame2[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(-1, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-1, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(5, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
    OAM_ENTRY(13, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x202, 8, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x226, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-20, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sZoroOam_CrawlingHorizontal_Frame3[OAM_DATA_SIZE(8)] = {
    8,
    OAM_ENTRY(0, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(0, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x227, 8, 0),
    OAM_ENTRY(7, -8, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
    OAM_ENTRY(15, -16, OAM_DIMS_8x8, OAM_NO_FLIP, 0x209, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x202, 8, 0),
    OAM_ENTRY(-7, -24, OAM_DIMS_8x8, OAM_NO_FLIP, 0x226, 8, 0),
    OAM_ENTRY(-21, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-21, -8, OAM_DIMS_8x8, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sZoroOam_TurningAroundHorizontal1_Frame0[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x213, 8, 0),
    OAM_ENTRY(4, -16, OAM_DIMS_8x16, OAM_NO_FLIP, 0x215, 8, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x218, 8, 0),
};

static const u16 sZoroOam_TurningAroundHorizontal1_Frame1[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-12, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(3, -16, OAM_DIMS_8x16, OAM_X_FLIP, 0x216, 8, 0),
    OAM_ENTRY(-9, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x238, 8, 0),
};

const struct FrameData sZoroOam_CrawlingHorizontal[7] = {
    [0] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame2,
        .timer = 6
    },
    [5] = {
        .pFrame = sZoroOam_CrawlingHorizontal_Frame1,
        .timer = 6
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZoroOam_TurningAroundHorizontal1[3] = {
    [0] = {
        .pFrame = sZoroOam_TurningAroundHorizontal1_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sZoroOam_TurningAroundHorizontal1_Frame1,
        .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZoroOam_TurningAroundHorizontal2[3] = {
    [0] = {
        .pFrame = sZoroOam_TurningAroundHorizontal1_Frame1,
        .timer = 4
    },
    [1] = {
        .pFrame = sZoroOam_TurningAroundHorizontal1_Frame0,
        .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZoroOam_CrawlingVertical[7] = {
    [0] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame0,
        .timer = 6
    },
    [1] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame1,
        .timer = 6
    },
    [2] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame2,
        .timer = 6
    },
    [3] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame3,
        .timer = 6
    },
    [4] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame2,
        .timer = 6
    },
    [5] = {
        .pFrame = sZoroOam_CrawlingVertical_Frame1,
        .timer = 6
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZoroOam_TurningAroundVertical1[3] = {
    [0] = {
        .pFrame = sZoroOam_TurningAroundVertical1_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sZoroOam_TurningAroundVertical1_Frame1,
        .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sZoroOam_TurningAroundVertical2[3] = {
    [0] = {
        .pFrame = sZoroOam_TurningAroundVertical1_Frame1,
        .timer = 4
    },
    [1] = {
        .pFrame = sZoroOam_TurningAroundVertical1_Frame0,
        .timer = 4
    },
    [2] = FRAME_DATA_TERMINATOR
};
