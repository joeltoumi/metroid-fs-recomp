#include "data/sprites/chozo_statue.h"

const u32 sChozoStatueGfx[1 * 512] = INCBIN_U32("data/sprites/chozo_statue.gfx");
const u16 sChozoStatuePal[1 * 16] = INCBIN_U16("data/sprites/chozo_statue.pal");

static const u16 sChozoStatueOam_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-8, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-24, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-24, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20a, 8, 0),
    OAM_ENTRY(8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x20e, 8, 0),
};

static const u16 sFakeChozoBallOam_Exposed_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x216, 8, 0),
};

static const u16 sFakeChozoBallOam_Exposed_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x214, 8, 0),
};

static const u16 sFakeChozoBallOam_Exposed_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sFakeChozoBallOam_Exposed_Frame3[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 8, 0),
};

static const u16 sFakeChozoBallOam_Idle_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -45, OAM_DIMS_16x16, OAM_NO_FLIP, 0x218, 8, 0),
};

static const u16 sFakeChozoBallOam_328378[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-24, -46, OAM_DIMS_16x16, OAM_NO_FLIP, 0x210, 8, 0),
};

const struct FrameData sChozoStatueOam[2] = {
    [0] = {
        .pFrame = sChozoStatueOam_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sFakeChozoBallOam_Idle[2] = {
    [0] = {
        .pFrame = sFakeChozoBallOam_Idle_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sFakeChozoBallOam_Exposed[7] = {
    [0] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame0,
        .timer = 25
    },
    [1] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [2] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [3] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame3,
        .timer = 18
    },
    [4] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [5] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sChozoStatueOam_3283d8[7] = {
    [0] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame0,
        .timer = 25
    },
    [1] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [2] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [3] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame3,
        .timer = 18
    },
    [4] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [5] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sChozoStatueOam_328410[7] = {
    [0] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame0,
        .timer = 25
    },
    [1] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [2] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [3] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame3,
        .timer = 18
    },
    [4] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [5] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [6] = FRAME_DATA_TERMINATOR
};

const struct FrameData sChozoStatueOam_328448[7] = {
    [0] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame0,
        .timer = 25
    },
    [1] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [2] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [3] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame3,
        .timer = 18
    },
    [4] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame2,
        .timer = 15
    },
    [5] = {
        .pFrame = sFakeChozoBallOam_Exposed_Frame1,
        .timer = 15
    },
    [6] = FRAME_DATA_TERMINATOR
};
