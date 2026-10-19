#include "data/blob_pieces.h"
#include "data/menus/pause_screen_map_data.h"

#include "macros.h"

const u8 sMinimapTilesGfx[32 * 14 * TILE_SIZE] = INCBIN_U8("data/menus/pause_screen/minimap_tiles.gfx");


const u8 sBlob_5657a8_566848[4256] = INCBIN_U8("data/Blob_5657a8_566848.bin");

const struct FrameData sFrameData_566848[3] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x600), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x71a), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566860[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x760), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x768), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x770), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x768), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566888[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x748), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x750), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x758), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x750), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5668b0[7] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x63c), 3 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x65c), 3 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x676), 3 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x696), 3 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x676), 3 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x65c), 3 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5668e8[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6b0), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa44), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa4c), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa44), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566910[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6b8), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa54), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa5c), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa54), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566938[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6c0), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa64), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa6c), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa64), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566960[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6c8), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa74), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa7c), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa74), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566988[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6d0), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6de), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6ec), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6de), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5669b0[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x6fa), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x702), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x70a), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x702), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5669d8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x712), 30 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5669e8[3] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x712), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x71a), 16 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566a00[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x722), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566a10[8] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7fc), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x804), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x812), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x826), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x834), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x83c), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x71a), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566a50[8] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x844), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x84c), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x85a), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x86e), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x87c), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x884), 4 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x71a), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566a90[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x88c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x8be), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x8f0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x922), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566ab8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x88c), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566ac8[33] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x778), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x778), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x778), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x778), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x794), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x794), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x794), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x794), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7b0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7b0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7b0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7b0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566bd0[33] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x954), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x954), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x954), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x954), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x968), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x968), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x968), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x968), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x97c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x97c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x97c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x97c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x990), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x990), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x990), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x990), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566cd8[33] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9a4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9a4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9a4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9a4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9b8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9b8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9b8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9b8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9cc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566de0[33] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9f4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9f4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9f4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x9f4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x78c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa08), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa08), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa08), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa08), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7a8), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa1c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa1c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa1c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa1c), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7c4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa30), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa30), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa30), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa30), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x7e0), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566ee8[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xa84), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xaa4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xaac), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xacc), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566f10[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xad4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xaf4), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xafc), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb1c), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566f38[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb24), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb44), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb52), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb72), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566f60[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xb80), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xba0), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xbae), 1 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xbce), 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566f88[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe32), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566f98[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xbf0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566fa8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc04), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566fb8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc18), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566fc8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc2c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566fd8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc40), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566fe8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc54), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_566ff8[10] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc68), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc82), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc9c), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcb6), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcd0), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcb6), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc9c), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc82), 2 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xc68), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567048[7] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcea), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcf8), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd06), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd14), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd06), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xcf8), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567080[7] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd22), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd30), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd3e), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd4c), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd3e), 8 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd30), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5670b8[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xdfa), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe08), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xdfa), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe08), 6 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5670e0[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe16), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe24), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe16), 6 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe24), 6 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567108[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd5a), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567118[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd6e), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567128[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd82), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567138[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xd96), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567148[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xdaa), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567158[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xdbe), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567168[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xdd2), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567178[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xde6), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567188[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xbdc), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567198[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe40), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671a8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe4e), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671b8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe5c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671c8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe6a), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671d8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe78), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671e8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe86), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5671f8[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xe94), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567208[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xea2), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xef8), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xf4e), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xef8), 16 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567230[5] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xfa4), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xfee), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x1038), 16 },
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0xfee), 16 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567258[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x1082), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_567268[2] = {
    { (const u16*)((const u8*)sBlob_5657a8_566848 + 0x1090), 4 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_567278_5688cc[5716] = INCBIN_U8("data/Blob_567278_5688cc.bin");

const struct FrameData sFrameData_5688cc[10] = {
    { (const u16*)sBlob_567278_5688cc, 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1a), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x34), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x60), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x86), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xac), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x108), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x15e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1b4), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56891c[10] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1b4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x15e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x108), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xac), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x86), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x60), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x34), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1a), 1 },
    { (const u16*)sBlob_567278_5688cc, 1 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56896c[13] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x20a), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x242), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x28c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x2d6), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x32c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x37c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x3e4), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x44c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x4c0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x52e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x5a8), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x622), 50 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_5689d4[13] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x622), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x5a8), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x52e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x4c0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x44c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x3e4), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x37c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x32c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x2d6), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x28c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x242), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x20a), 50 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568a3c[13] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x6a8), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x6ce), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x70c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x750), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x788), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x7ea), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x84c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x8b4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x922), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x99c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xa1c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xaa2), 50 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568aa4[13] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xaa2), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xa1c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x99c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x922), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x8b4), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x84c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x7ea), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x788), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x750), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x70c), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x6ce), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x6a8), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568b0c[5] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xad4), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xae8), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xafc), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb10), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568b34[5] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb10), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xafc), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xae8), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xad4), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568b5c[2] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb24), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568b6c[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb3a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb42), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb4a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb52), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb66), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb86), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xbb2), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xc20), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xc8e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd08), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568bc4[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd08), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xc8e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xc20), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xbb2), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb86), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb66), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb52), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb4a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb42), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb3a), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568c1c[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xfe2), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x100e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x103a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1090), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568c74[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1090), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x103a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x100e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xfe2), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568ccc[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x10bc), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x10e8), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1114), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x116a), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568d24[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x116a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1114), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x10e8), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x10bc), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568d7c[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd82), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd8a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd92), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xda0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xdb4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xdda), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xe12), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xe80), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xeee), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xf68), 255 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568dd4[11] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xf68), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xeee), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xe80), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xe12), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xdda), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xdb4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xda0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd92), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd8a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xd82), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568e2c[2] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1196), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568e3c[3] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1196), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x11e0), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568e54[2] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1236), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568e64[3] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1236), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1298), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568e7c[8] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1300), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1308), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1310), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1324), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x136e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x13d0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x142c), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568ebc[8] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x142c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x13d0), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x136e), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1324), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1310), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1308), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1300), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568efc[8] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x147c), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1484), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1492), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x14a6), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x14e4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x153a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1596), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568f3c[8] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1596), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x153a), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x14e4), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x14a6), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1492), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1484), 2 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x147c), 2 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568f7c[6] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb10), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x15fe), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1612), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x1626), 8 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x15fe), 8 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_568fac[3] = {
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0x163a), 1 },
    { (const u16*)((const u8*)sBlob_567278_5688cc + 0xb32), 2 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_568fc4_56a014[4176] = INCBIN_U8("data/Blob_568fc4_56a014.bin");

const struct FrameData sFrameData_56a014[2] = {
    { (const u16*)sBlob_568fc4_56a014, 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a024[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x74), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a034[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xe8), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a044[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x15c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a054[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x1d0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a064[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x244), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a074[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x2b8), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a084[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x32c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a094[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x3a0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0a4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x414), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0b4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x488), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0c4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x4fc), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0d4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x570), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0e4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x5e4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a0f4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x658), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a104[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x6cc), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a114[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x740), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a124[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x7b4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a134[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x828), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a144[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x89c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a154[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x910), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a164[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x984), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a174[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0x9f8), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a184[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xa6c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a194[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xae0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1a4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xb54), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1b4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xbc8), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1c4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xc3c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1d4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xcb0), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1e4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xd24), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a1f4[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xd98), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a204[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xe0c), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a214[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xe80), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a224[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xef4), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a234[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xf68), 4 },
    FRAME_DATA_TERMINATOR
};

const struct FrameData sFrameData_56a244[2] = {
    { (const u16*)((const u8*)sBlob_568fc4_56a014 + 0xfdc), 4 },
    FRAME_DATA_TERMINATOR
};

const u8 sBlob_56a254_575a60[47116] = INCBIN_U8("data/Blob_56a254_575a60.bin");
