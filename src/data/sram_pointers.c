#include "data/blob_pieces.h"
#include "data/sram_pointers.h"
#include "gba/memory.h"
#include "structs/save_file.h"
#include "macros.h"

const void* const sSaveDataEwramPointers[3] = {
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 0,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 2,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 4
};

const void* const sSaveDataEwramBackupPointers[3] = {
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 1,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 3,
    EWRAM_SRAM + 0x200 + sizeof(struct SaveFile) * 5
};

const void* const sUnk_582274[3] = {
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 0,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 2,
    EWRAM_SRAM + 0x500 + sizeof(struct SaveFile) * 4
};

const void* const sUnk_582280[2] = {
    EWRAM_SRAM + 0x7040,
    EWRAM_SRAM + 0x7080
};

const u8 sBlob_582288_582a3c[1972] = INCBIN_U8("data/Blob_582288_582a3c.bin");

const struct FrameData sFrameData_582a3c[29] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x674), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x688), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x69c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x6b0), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x6c4), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x6d8), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x6ec), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x700), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x714), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x728), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x73c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x750), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x624), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x638), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x64c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x660), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x624), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x638), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x64c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x660), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x624), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x638), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x64c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x660), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x764), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x778), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x78c), 4 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x7a0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_582b24[11] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x52e), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x542), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x556), 1 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x56a), 1 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x57e), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x592), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x5a6), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x5ba), 2 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x5ce), 1 },
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x5e2), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_582b7c[2] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x5f0), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_582b8c[2] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x60a), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_582b9c[2] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x3ce), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_582bac[2] = {
    { (const u16*)((const u8*)sBlob_582288_582a3c + 0x47e), 255 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_582bbc_58b3cc[34832] = INCBIN_U8("data/Blob_582bbc_58b3cc.bin");
