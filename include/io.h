#ifndef IO_H
#define IO_H

#include "types.h"

#define WRITE_32(addr, val) (*(vu32 *)(addr)) = (val)
#define WRITE_16(addr, val) (*(vu16 *)(addr)) = (val)
#define WRITE_8(addr, val) (*(vu8 *)(addr)) = (val)

#ifdef PLATFORM_PC
#include "port/platform.h"
// Native build: nothing advances the scanline counter while the CPU spins, so
// polling REG_VCOUNT (0x04000006) ticks a virtual one (see port/src/frame.c).
#define PORT_IS_VCOUNT(addr) ((const volatile void *)(addr) == (const volatile void *)(gPortIo + 6))
#define READ_32(addr) (*(vu32 *)(addr))
#define READ_16(addr) (PORT_IS_VCOUNT(addr) ? Port_PollVCount() : *(vu16 *)(addr))
#define READ_8(addr) (PORT_IS_VCOUNT(addr) ? (u8)Port_PollVCount() : *(vu8 *)(addr))
#else // !PLATFORM_PC
#define READ_32(addr) (*(vu32 *)(addr))
#define READ_16(addr) (*(vu16 *)(addr))
#define READ_8(addr) (*(vu8 *)(addr))
#endif // PLATFORM_PC

#endif /* IO_H */