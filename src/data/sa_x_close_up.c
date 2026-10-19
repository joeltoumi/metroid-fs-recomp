#include "data/blob_pieces.h"
#include "data/sa_x_close_up.h"
#include "macros.h"

const u16 sSaXCloseUpPal[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette.pal");
const u16 sSaXCloseUpPalGrayscale[16 * 16] = INCBIN_U16("data/sa_x_close_up/palette_grayscale.pal");
const u32 sSaXCloseUpGfx[4472] = INCBIN_U32("data/sa_x_close_up/graphics.gfx.lz");
const u32 sSaXCloseUpTileTable1[294] = INCBIN_U32("data/sa_x_close_up/first.tt.lz");
const u32 sSaXCloseUpTileTable2[305] = INCBIN_U32("data/sa_x_close_up/second.tt.lz");

const u8 sSaXCloseUpDurations[2] = { 25, 60 };

const u8 sBlob_73421e_73c274[32854] = INCBIN_U8("data/Blob_73421e_73c274.bin");

const struct FrameData sFrameData_73c274[5] = {
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x7ffa), 14 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8044), 14 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x804c), 14 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8044), 14 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_73c29c[9] = {
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x7ffa), 8 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8002), 4 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x800a), 4 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8012), 8 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x801a), 5 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8028), 5 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8036), 5 },
    { (const u16*)((const u8*)sBlob_73421e_73c274 + 0x8012), 255 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_73c2e4_7406f8[17428] = INCBIN_U8("data/Blob_73c2e4_7406f8.bin");

const struct FrameData sFrameData_7406f8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x2f50), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740708[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x2f8e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740718[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x2fcc), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740728[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x300a), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740738[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3048), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740748[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3086), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33ec), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740760[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3094), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33ec), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740778[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x30a2), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33ec), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740790[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x30b0), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33ec), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7407a8[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x30be), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33ec), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7407c0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x30e6), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7407d0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x310c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7407e0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3126), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7407f0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x314c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740800[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36fc), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x37a0), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3844), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740820[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x38e8), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x398c), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3a30), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740840[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3ad4), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3b78), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3c1c), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740860[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3190), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740870[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31a4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740880[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31b8), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31c0), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31c8), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31c0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7408a8[3] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31d0), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31d8), 20 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7408c0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x31e0), 16 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7408d0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x327e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7408e0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32aa), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7408f0[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x30cc), 10 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36a0), 10 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36ba), 10 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36a0), 10 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740918[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32d6), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32e4), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32f2), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x330c), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740940[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3332), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740950[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x330c), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32f2), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32e4), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x32d6), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740978[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x334c), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3366), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3374), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x338e), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7409a0[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33b4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7409b0[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x338e), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3374), 2 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3366), 1 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x334c), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7409d8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x33f4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7409e8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3402), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_7409f8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3410), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a08[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x341e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a18[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x342c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a28[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x343a), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a38[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3448), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a48[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3456), 14 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4402), 14 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x440a), 14 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4402), 14 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740a70[9] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3456), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x345e), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3466), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x346e), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3476), 5 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3484), 5 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3492), 5 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x346e), 30 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ab8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x34ae), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ac8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x354c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ad8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x35ea), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ae8[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3cc0), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3d64), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3e08), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740b08[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3eac), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3f50), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x3ff4), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740b28[4] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4098), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x413c), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x41e0), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740b48[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36d4), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36dc), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36e4), 8 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36dc), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740b70[5] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36ec), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36f4), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36ec), 4 },
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x36f4), 20 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740b98[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4284), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ba8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x428c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740bb8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x429a), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740bc8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42a8), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740bd8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42b6), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740be8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42c4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740bf8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42d2), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c08[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42e0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c18[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x42ee), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c28[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4302), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c38[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4316), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c48[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x432a), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c58[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x433e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c68[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4352), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c78[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4366), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c88[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x436e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740c98[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4382), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ca8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x4396), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740cb8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x43aa), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740cc8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x43be), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740cd8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x43d2), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740ce8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x43e6), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_740cf8[2] = {
    { (const u16*)((const u8*)sBlob_73c2e4_7406f8 + 0x43f4), 4 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_740d08_7478a0[27544] = INCBIN_U8("data/Blob_740d08_7478a0.bin");
