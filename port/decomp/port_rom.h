#ifndef PORT_DECOMP_PORT_ROM_H
#define PORT_DECOMP_PORT_ROM_H

#include "types.h"

#ifdef PLATFORM_PC
/*
 * Native build: for data still kept as raw ROM bytes that embed 32-bit GBA
 * pointers. The game's copy of the ROM (port/src/assets.c) resolves them.
 */
const void* Port_RomPointer(unsigned int gbaAddress);

static inline u32 PortReadGbaU32(const void* src)
{
    const u8* p = (const u8*)src;
    return p[0] | (p[1] << 8) | (p[2] << 16) | ((u32)p[3] << 24);
}

static inline u16 PortReadGbaU16(const void* src)
{
    const u8* p = (const u8*)src;
    return p[0] | (p[1] << 8);
}

// A GBA ROM pointer stored at src, as a host pointer into the ROM copy.
#define PORT_GBA_PTR(src) Port_RomPointer(PortReadGbaU32(src))
#endif /* PLATFORM_PC */

#endif /* PORT_DECOMP_PORT_ROM_H */
