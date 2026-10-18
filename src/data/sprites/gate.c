#include "data/sprites/gate.h"

const u32 sGateGfx[1 * 512] = INCBIN_U32("data/sprites/gate.gfx");
const u16 sGatePal[1 * 16] = INCBIN_U16("data/sprites/gate.pal");

static const u16 sGateOam_OpenedThin_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sGateOam_OpenedWide_Frame0[OAM_DATA_SIZE(1)] = {
    1,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame0[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateSwitchOam_IdleLeft_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
};

static const u16 sGateSwitchOam_PressingLeft_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-41, -57, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_PressingLeft_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-41, -59, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_PressedLeft_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-41, -61, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_IdleRight_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_PressingRight_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -57, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_PressingRight_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -59, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_PressedRight_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -61, OAM_DIMS_16x8, OAM_NO_FLIP, 0x228, 8, 0),
};

static const u16 sGateSwitchOam_IdleLeft_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-41, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21e, 8, 0),
};

static const u16 sGateSwitchOam_IdleLeft_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-41, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x208, 8, 0),
    OAM_ENTRY(-41, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23e, 8, 0),
};

static const u16 sGateSwitchOam_IdleRight_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21e, 8, 0),
};

static const u16 sGateSwitchOam_IdleRight_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(11, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x216, 8, 0),
    OAM_ENTRY(25, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23e, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x8, OAM_NO_FLIP, 0x226, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -64, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame3[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame4[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame5[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame6[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -44, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame7[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -40, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame8[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame9[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame10[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -28, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame11[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -20, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -36, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -52, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -60, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingThin_Frame13[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame0[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -60, OAM_DIMS_32x8, OAM_NO_FLIP, 0x232, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame1[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame2[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -60, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame3[OAM_DATA_SIZE(2)] = {
    2,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -56, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame4[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -52, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -60, OAM_DIMS_32x8, OAM_NO_FLIP, 0x22f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame5[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame6[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -44, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -60, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame7[OAM_DATA_SIZE(3)] = {
    3,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -40, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -56, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame8[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -36, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -52, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -60, OAM_DIMS_32x8, OAM_NO_FLIP, 0x22f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame9[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame10[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -28, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -44, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -60, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame11[OAM_DATA_SIZE(4)] = {
    4,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -24, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -40, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -56, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame12[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -20, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -36, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -52, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -60, OAM_DIMS_32x8, OAM_NO_FLIP, 0x22f, 8, 0),
};

static const u16 sGateOam_ClosingWide_Frame13[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame1[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame2[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame3[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame4[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame5[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame7[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame8[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame9[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame10[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame11[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame13[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-6, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-6, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame14[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-6, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame15[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-6, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x236, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame16[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-6, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-6, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedWide_Frame17[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-6, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x23c, 8, 0),
    OAM_ENTRY(-6, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x21c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x220, 8, 0),
    OAM_ENTRY(-20, -16, OAM_DIMS_32x16, OAM_NO_FLIP, 0x212, 8, 0),
    OAM_ENTRY(-12, -32, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -48, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
    OAM_ENTRY(-12, -64, OAM_DIMS_32x16, OAM_NO_FLIP, 0x20f, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame1[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame2[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame3[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-8, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x20c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame4[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame5[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame6[OAM_DATA_SIZE(5)] = {
    5,
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame7[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-8, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame8[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame9[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-8, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame10[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -40, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame11[OAM_DATA_SIZE(7)] = {
    7,
    OAM_ENTRY(-8, -48, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-8, -24, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22a, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

static const u16 sGateOam_ClosedThin_Frame12[OAM_DATA_SIZE(6)] = {
    6,
    OAM_ENTRY(-8, -56, OAM_DIMS_16x8, OAM_NO_FLIP, 0x22c, 8, 0),
    OAM_ENTRY(-16, -64, OAM_DIMS_32x8, OAM_NO_FLIP, 0x200, 8, 0),
    OAM_ENTRY(-8, -16, OAM_DIMS_16x16, OAM_NO_FLIP, 0x206, 8, 0),
    OAM_ENTRY(-8, -32, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -48, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
    OAM_ENTRY(-8, -56, OAM_DIMS_16x16, OAM_NO_FLIP, 0x204, 8, 0),
};

const struct FrameData sGateOam_OpenedThin[2] = {
    [0] = {
        .pFrame = sGateOam_OpenedThin_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_ClosingThin[15] = {
    [0] = {
        .pFrame = sGateOam_ClosingThin_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sGateOam_ClosingThin_Frame1,
        .timer = 3
    },
    [2] = {
        .pFrame = sGateOam_ClosingThin_Frame2,
        .timer = 3
    },
    [3] = {
        .pFrame = sGateOam_ClosingThin_Frame3,
        .timer = 2
    },
    [4] = {
        .pFrame = sGateOam_ClosingThin_Frame4,
        .timer = 2
    },
    [5] = {
        .pFrame = sGateOam_ClosingThin_Frame5,
        .timer = 2
    },
    [6] = {
        .pFrame = sGateOam_ClosingThin_Frame6,
        .timer = 2
    },
    [7] = {
        .pFrame = sGateOam_ClosingThin_Frame7,
        .timer = 2
    },
    [8] = {
        .pFrame = sGateOam_ClosingThin_Frame8,
        .timer = 1
    },
    [9] = {
        .pFrame = sGateOam_ClosingThin_Frame9,
        .timer = 1
    },
    [10] = {
        .pFrame = sGateOam_ClosingThin_Frame10,
        .timer = 1
    },
    [11] = {
        .pFrame = sGateOam_ClosingThin_Frame11,
        .timer = 1
    },
    [12] = {
        .pFrame = sGateOam_ClosingThin_Frame12,
        .timer = 1
    },
    [13] = {
        .pFrame = sGateOam_ClosingThin_Frame13,
        .timer = 1
    },
    [14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_OpeningThin[15] = {
    [0] = {
        .pFrame = sGateOam_ClosingThin_Frame13,
        .timer = 1
    },
    [1] = {
        .pFrame = sGateOam_ClosingThin_Frame12,
        .timer = 1
    },
    [2] = {
        .pFrame = sGateOam_ClosingThin_Frame11,
        .timer = 1
    },
    [3] = {
        .pFrame = sGateOam_ClosingThin_Frame10,
        .timer = 1
    },
    [4] = {
        .pFrame = sGateOam_ClosingThin_Frame9,
        .timer = 1
    },
    [5] = {
        .pFrame = sGateOam_ClosingThin_Frame8,
        .timer = 1
    },
    [6] = {
        .pFrame = sGateOam_ClosingThin_Frame7,
        .timer = 1
    },
    [7] = {
        .pFrame = sGateOam_ClosingThin_Frame6,
        .timer = 1
    },
    [8] = {
        .pFrame = sGateOam_ClosingThin_Frame5,
        .timer = 1
    },
    [9] = {
        .pFrame = sGateOam_ClosingThin_Frame4,
        .timer = 1
    },
    [10] = {
        .pFrame = sGateOam_ClosingThin_Frame3,
        .timer = 1
    },
    [11] = {
        .pFrame = sGateOam_ClosingThin_Frame2,
        .timer = 1
    },
    [12] = {
        .pFrame = sGateOam_ClosingThin_Frame1,
        .timer = 1
    },
    [13] = {
        .pFrame = sGateOam_ClosingThin_Frame0,
        .timer = 1
    },
    [14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_ClosedThin[14] = {
    [0] = {
        .pFrame = sGateOam_ClosedThin_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sGateOam_ClosedThin_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sGateOam_ClosedThin_Frame2,
        .timer = 10
    },
    [3] = {
        .pFrame = sGateOam_ClosedThin_Frame3,
        .timer = 10
    },
    [4] = {
        .pFrame = sGateOam_ClosedThin_Frame4,
        .timer = 10
    },
    [5] = {
        .pFrame = sGateOam_ClosedThin_Frame5,
        .timer = 10
    },
    [6] = {
        .pFrame = sGateOam_ClosedThin_Frame6,
        .timer = 10
    },
    [7] = {
        .pFrame = sGateOam_ClosedThin_Frame7,
        .timer = 10
    },
    [8] = {
        .pFrame = sGateOam_ClosedThin_Frame8,
        .timer = 10
    },
    [9] = {
        .pFrame = sGateOam_ClosedThin_Frame9,
        .timer = 10
    },
    [10] = {
        .pFrame = sGateOam_ClosedThin_Frame10,
        .timer = 10
    },
    [11] = {
        .pFrame = sGateOam_ClosedThin_Frame11,
        .timer = 10
    },
    [12] = {
        .pFrame = sGateOam_ClosedThin_Frame12,
        .timer = 10
    },
    [13] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_OpenedWide[2] = {
    [0] = {
        .pFrame = sGateOam_OpenedWide_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_ClosingWide[15] = {
    [0] = {
        .pFrame = sGateOam_ClosingWide_Frame0,
        .timer = 2
    },
    [1] = {
        .pFrame = sGateOam_ClosingWide_Frame1,
        .timer = 2
    },
    [2] = {
        .pFrame = sGateOam_ClosingWide_Frame2,
        .timer = 2
    },
    [3] = {
        .pFrame = sGateOam_ClosingWide_Frame3,
        .timer = 2
    },
    [4] = {
        .pFrame = sGateOam_ClosingWide_Frame4,
        .timer = 2
    },
    [5] = {
        .pFrame = sGateOam_ClosingWide_Frame5,
        .timer = 2
    },
    [6] = {
        .pFrame = sGateOam_ClosingWide_Frame6,
        .timer = 2
    },
    [7] = {
        .pFrame = sGateOam_ClosingWide_Frame7,
        .timer = 2
    },
    [8] = {
        .pFrame = sGateOam_ClosingWide_Frame8,
        .timer = 2
    },
    [9] = {
        .pFrame = sGateOam_ClosingWide_Frame9,
        .timer = 1
    },
    [10] = {
        .pFrame = sGateOam_ClosingWide_Frame10,
        .timer = 1
    },
    [11] = {
        .pFrame = sGateOam_ClosingWide_Frame11,
        .timer = 1
    },
    [12] = {
        .pFrame = sGateOam_ClosingWide_Frame12,
        .timer = 1
    },
    [13] = {
        .pFrame = sGateOam_ClosingWide_Frame13,
        .timer = 1
    },
    [14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_OpeningWide[15] = {
    [0] = {
        .pFrame = sGateOam_ClosingWide_Frame13,
        .timer = 1
    },
    [1] = {
        .pFrame = sGateOam_ClosingWide_Frame12,
        .timer = 1
    },
    [2] = {
        .pFrame = sGateOam_ClosingWide_Frame11,
        .timer = 1
    },
    [3] = {
        .pFrame = sGateOam_ClosingWide_Frame10,
        .timer = 1
    },
    [4] = {
        .pFrame = sGateOam_ClosingWide_Frame9,
        .timer = 1
    },
    [5] = {
        .pFrame = sGateOam_ClosingWide_Frame8,
        .timer = 1
    },
    [6] = {
        .pFrame = sGateOam_ClosingWide_Frame7,
        .timer = 1
    },
    [7] = {
        .pFrame = sGateOam_ClosingWide_Frame6,
        .timer = 1
    },
    [8] = {
        .pFrame = sGateOam_ClosingWide_Frame5,
        .timer = 1
    },
    [9] = {
        .pFrame = sGateOam_ClosingWide_Frame4,
        .timer = 1
    },
    [10] = {
        .pFrame = sGateOam_ClosingWide_Frame3,
        .timer = 1
    },
    [11] = {
        .pFrame = sGateOam_ClosingWide_Frame2,
        .timer = 1
    },
    [12] = {
        .pFrame = sGateOam_ClosingWide_Frame1,
        .timer = 1
    },
    [13] = {
        .pFrame = sGateOam_ClosingWide_Frame0,
        .timer = 1
    },
    [14] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateOam_ClosedWide[19] = {
    [0] = {
        .pFrame = sGateOam_ClosedWide_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sGateOam_ClosedWide_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sGateOam_ClosedWide_Frame2,
        .timer = 10
    },
    [3] = {
        .pFrame = sGateOam_ClosedWide_Frame3,
        .timer = 10
    },
    [4] = {
        .pFrame = sGateOam_ClosedWide_Frame4,
        .timer = 10
    },
    [5] = {
        .pFrame = sGateOam_ClosedWide_Frame5,
        .timer = 10
    },
    [6] = {
        .pFrame = sGateOam_ClosedWide_Frame0,
        .timer = 10
    },
    [7] = {
        .pFrame = sGateOam_ClosedWide_Frame7,
        .timer = 10
    },
    [8] = {
        .pFrame = sGateOam_ClosedWide_Frame8,
        .timer = 10
    },
    [9] = {
        .pFrame = sGateOam_ClosedWide_Frame9,
        .timer = 10
    },
    [10] = {
        .pFrame = sGateOam_ClosedWide_Frame10,
        .timer = 10
    },
    [11] = {
        .pFrame = sGateOam_ClosedWide_Frame11,
        .timer = 10
    },
    [12] = {
        .pFrame = sGateOam_ClosedWide_Frame0,
        .timer = 10
    },
    [13] = {
        .pFrame = sGateOam_ClosedWide_Frame13,
        .timer = 10
    },
    [14] = {
        .pFrame = sGateOam_ClosedWide_Frame14,
        .timer = 10
    },
    [15] = {
        .pFrame = sGateOam_ClosedWide_Frame15,
        .timer = 10
    },
    [16] = {
        .pFrame = sGateOam_ClosedWide_Frame16,
        .timer = 10
    },
    [17] = {
        .pFrame = sGateOam_ClosedWide_Frame17,
        .timer = 10
    },
    [18] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_IdleLeft[4] = {
    [0] = {
        .pFrame = sGateSwitchOam_IdleLeft_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sGateSwitchOam_IdleLeft_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sGateSwitchOam_IdleLeft_Frame2,
        .timer = 10
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_PressingLeft[3] = {
    [0] = {
        .pFrame = sGateSwitchOam_PressingLeft_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sGateSwitchOam_PressingLeft_Frame1,
        .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_IdleRight[4] = {
    [0] = {
        .pFrame = sGateSwitchOam_IdleRight_Frame0,
        .timer = 10
    },
    [1] = {
        .pFrame = sGateSwitchOam_IdleRight_Frame1,
        .timer = 10
    },
    [2] = {
        .pFrame = sGateSwitchOam_IdleRight_Frame2,
        .timer = 10
    },
    [3] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_PressingRight[3] = {
    [0] = {
        .pFrame = sGateSwitchOam_PressingRight_Frame0,
        .timer = 3
    },
    [1] = {
        .pFrame = sGateSwitchOam_PressingRight_Frame1,
        .timer = 3
    },
    [2] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_PressedLeft[2] = {
    [0] = {
        .pFrame = sGateSwitchOam_PressedLeft_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};

const struct FrameData sGateSwitchOam_PressedRight[2] = {
    [0] = {
        .pFrame = sGateSwitchOam_PressedRight_Frame0,
        .timer = 255
    },
    [1] = FRAME_DATA_TERMINATOR
};
