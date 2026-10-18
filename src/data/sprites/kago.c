#include "data/sprites/kago.h"

const s16 sKagoInsectHighJumpVelocity[10] = {
    -8, -16, -8, -4, 0,
    4, 8, 16, 16, 16
};

const s16 sKagoInsectMediumJumpVelocity[10] = {
    -5, -10, -5, -3, 0,
    4, 8, 12, 16, 16
};

const s16 sKagoInsectLowJumpVelocity[10] = {
    -4, -8, -4, -2, 0,
    4, 8, 12, 16, 16
};

const u32 sKagoGfx[2 * 512] = INCBIN_U32("data/sprites/kago.gfx");
const u16 sKagoPal[2 * 16] = INCBIN_U16("data/sprites/kago.pal");

static const u16 sKagoOam_IdleTall_Frame0[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x210, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame1[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-17, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x230, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-18, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-17, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-17, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x214, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame3[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-18, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-18, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-17, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-19, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-17, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x234, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame4[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-17, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-18, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-18, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-18, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-17, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x234, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame5[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-17, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-17, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-17, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x214, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame6[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-17, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-17, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x230, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame8[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x230, 9, 0),
    OAM_ENTRY(-15, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame9[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-14, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-15, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-15, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x214, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame10[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-14, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-14, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-15, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-13, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-15, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x234, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame11[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-15, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20c, 9, 0),
    OAM_ENTRY(-14, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-14, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-14, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-15, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x234, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame12[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-15, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x208, 9, 0),
    OAM_ENTRY(-15, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-15, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x214, 9, 0),
};

static const u16 sKagoOam_IdleTall_Frame13[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-16, -40, OAM_DIMS_32x8, OAM_NO_FLIP, 0x230, 9, 0),
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-15, -16, OAM_DIMS_32x16, OAM_X_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, 32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
    OAM_ENTRY(-15, 16, OAM_DIMS_32x16, OAM_X_FLIP, 0x200, 9, 0),
    OAM_ENTRY(-16, 0, OAM_DIMS_32x16, OAM_NO_FLIP, 0x204, 9, 0),
};

static const u16 sKagoInsectOam_JumpWarning_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x250, 9, 0),
};

static const u16 sKagoInsectOam_JumpWarning_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x252, 9, 0),
};

static const u16 sKagoInsectOam_JumpWarning_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x254, 9, 0),
};

static const u16 sKagoInsectOam_Midair_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x256, 9, 0),
};

static const u16 sKagoInsectOam_TurningAround_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x258, 9, 0),
};

static const u16 sKagoInsectOam_Exploding_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25a, 9, 0),
};

static const u16 sKagoInsectOam_Exploding_Frame1[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25c, 9, 0),
};

static const u16 sKagoInsectOam_Exploding_Frame2[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x25e, 9, 0),
};

static const u16 sKagoOam_IdleShort_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x218, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x244, 8, 0),
};

static const u16 sKagoOam_IdleShort_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x248, 8, 0),
};

static const u16 sKagoOam_IdleShort_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x240, 8, 0),
    OAM_ENTRY(-16, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x24c, 8, 0),
};

const struct FrameData sKagoOam_IdleShort[5] = {
    [0] = {
        .pFrame = sKagoOam_IdleShort_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sKagoOam_IdleShort_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sKagoOam_IdleShort_Frame2,
        .timer = 10
    },
    [3] = {
        .pFrame = sKagoOam_IdleShort_Frame1,
        .timer = 10
    },
    [4] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoOam_IdleTallVerySlow[14] = {
    [0] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 12
    },
    [1] = {
        .pFrame = sKagoOam_IdleTall_Frame1,
        .timer = 12
    },
    [2] = {
        .pFrame = sKagoOam_IdleTall_Frame2,
        .timer = 12
    },
    [3] = {
        .pFrame = sKagoOam_IdleTall_Frame3,
        .timer = 12
    },
    [4] = {
        .pFrame = sKagoOam_IdleTall_Frame4,
        .timer = 12
    },
    [5] = {
        .pFrame = sKagoOam_IdleTall_Frame5,
        .timer = 12
    },
    [6] = {
        .pFrame = sKagoOam_IdleTall_Frame6,
        .timer = 12
    },
    [7] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 12
    },
    [8] = {
        .pFrame = sKagoOam_IdleTall_Frame8,
        .timer = 12
    },
    [9] = {
        .pFrame = sKagoOam_IdleTall_Frame9,
        .timer = 12
    },
    [10] = {
        .pFrame = sKagoOam_IdleTall_Frame10,
        .timer = 12
    },
    [11] = {
        .pFrame = sKagoOam_IdleTall_Frame11,
        .timer = 12
    },
    [12] = {
        .pFrame = sKagoOam_IdleTall_Frame12,
        .timer = 12
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoOam_IdleTallSlow[15] = {
    [0] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 8
    },
    [1] = {
        .pFrame = sKagoOam_IdleTall_Frame1,
        .timer = 8
    },
    [2] = {
        .pFrame = sKagoOam_IdleTall_Frame2,
        .timer = 8
    },
    [3] = {
        .pFrame = sKagoOam_IdleTall_Frame3,
        .timer = 8
    },
    [4] = {
        .pFrame = sKagoOam_IdleTall_Frame4,
        .timer = 8
    },
    [5] = {
        .pFrame = sKagoOam_IdleTall_Frame5,
        .timer = 8
    },
    [6] = {
        .pFrame = sKagoOam_IdleTall_Frame6,
        .timer = 8
    },
    [7] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 8
    },
    [8] = {
        .pFrame = sKagoOam_IdleTall_Frame8,
        .timer = 8
    },
    [9] = {
        .pFrame = sKagoOam_IdleTall_Frame9,
        .timer = 8
    },
    [10] = {
        .pFrame = sKagoOam_IdleTall_Frame10,
        .timer = 8
    },
    [11] = {
        .pFrame = sKagoOam_IdleTall_Frame11,
        .timer = 8
    },
    [12] = {
        .pFrame = sKagoOam_IdleTall_Frame12,
        .timer = 8
    },
    [13] = {
        .pFrame = sKagoOam_IdleTall_Frame13,
        .timer = 8
    },
    [14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoOam_IdleTallMedium[14] = {
    [0] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 5
    },
    [1] = {
        .pFrame = sKagoOam_IdleTall_Frame1,
        .timer = 5
    },
    [2] = {
        .pFrame = sKagoOam_IdleTall_Frame2,
        .timer = 5
    },
    [3] = {
        .pFrame = sKagoOam_IdleTall_Frame3,
        .timer = 5
    },
    [4] = {
        .pFrame = sKagoOam_IdleTall_Frame4,
        .timer = 5
    },
    [5] = {
        .pFrame = sKagoOam_IdleTall_Frame5,
        .timer = 5
    },
    [6] = {
        .pFrame = sKagoOam_IdleTall_Frame6,
        .timer = 5
    },
    [7] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 5
    },
    [8] = {
        .pFrame = sKagoOam_IdleTall_Frame8,
        .timer = 5
    },
    [9] = {
        .pFrame = sKagoOam_IdleTall_Frame9,
        .timer = 5
    },
    [10] = {
        .pFrame = sKagoOam_IdleTall_Frame10,
        .timer = 5
    },
    [11] = {
        .pFrame = sKagoOam_IdleTall_Frame11,
        .timer = 5
    },
    [12] = {
        .pFrame = sKagoOam_IdleTall_Frame12,
        .timer = 5
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoOam_IdleTallFast[14] = {
    [0] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sKagoOam_IdleTall_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sKagoOam_IdleTall_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sKagoOam_IdleTall_Frame3,
        .timer = 3
    },
    [4] = {
        .pFrame = sKagoOam_IdleTall_Frame4,
        .timer = 3
    },
    [5] = {
        .pFrame = sKagoOam_IdleTall_Frame5,
        .timer = 3
    },
    [6] = {
        .pFrame = sKagoOam_IdleTall_Frame6,
        .timer = 3
    },
    [7] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 3
    },
    [8] = {
        .pFrame = sKagoOam_IdleTall_Frame8,
        .timer = 3
    },
    [9] = {
        .pFrame = sKagoOam_IdleTall_Frame9,
        .timer = 3
    },
    [10] = {
        .pFrame = sKagoOam_IdleTall_Frame10,
        .timer = 3
    },
    [11] = {
        .pFrame = sKagoOam_IdleTall_Frame11,
        .timer = 3
    },
    [12] = {
        .pFrame = sKagoOam_IdleTall_Frame12,
        .timer = 3
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoOam_IdleTallVeryFast[14] = {
    [0] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sKagoOam_IdleTall_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sKagoOam_IdleTall_Frame2,
        .timer = 2
    },
    [3] = {
        .pFrame = sKagoOam_IdleTall_Frame3,
        .timer = 2
    },
    [4] = {
        .pFrame = sKagoOam_IdleTall_Frame4,
        .timer = 2
    },
    [5] = {
        .pFrame = sKagoOam_IdleTall_Frame5,
        .timer = 2
    },
    [6] = {
        .pFrame = sKagoOam_IdleTall_Frame6,
        .timer = 2
    },
    [7] = {
        .pFrame = sKagoOam_IdleTall_Frame0,
        .timer = 2
    },
    [8] = {
        .pFrame = sKagoOam_IdleTall_Frame8,
        .timer = 2
    },
    [9] = {
        .pFrame = sKagoOam_IdleTall_Frame9,
        .timer = 2
    },
    [10] = {
        .pFrame = sKagoOam_IdleTall_Frame10,
        .timer = 2
    },
    [11] = {
        .pFrame = sKagoOam_IdleTall_Frame11,
        .timer = 2
    },
    [12] = {
        .pFrame = sKagoOam_IdleTall_Frame12,
        .timer = 2
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoInsectOam_JumpWarning[4] = {
    [0] = {
        .pFrame = sKagoInsectOam_JumpWarning_Frame0,
        .timer = 5
    },
    [1] = {
        .pFrame = sKagoInsectOam_JumpWarning_Frame1,
        .timer = 5
    },
    [2] = {
        .pFrame = sKagoInsectOam_JumpWarning_Frame2,
        .timer = 16
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoInsectOam_Midair[2] = {
    [0] = {
        .pFrame = sKagoInsectOam_Midair_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoInsectOam_TurningAround[2] = {
    [0] = {
        .pFrame = sKagoInsectOam_TurningAround_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sKagoInsectOam_Exploding[4] = {
    [0] = {
        .pFrame = sKagoInsectOam_Exploding_Frame0,
        .timer = 4
    },
    [1] = {
        .pFrame = sKagoInsectOam_Exploding_Frame1,
        .timer = 4
    },
    [2] = {
        .pFrame = sKagoInsectOam_Exploding_Frame2,
        .timer = 4
    },
    [3] = FRAME_DATA_TERMINATOR
};
