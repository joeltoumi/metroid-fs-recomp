#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "types.h"

#ifdef PLATFORM_PC
#include "port/platform.h"
#define SYSCALL(num) Port_Syscall(num)
#else
#define SYSCALL(num) asm("svc " #num)
#endif

#ifdef PLATFORM_PC
// The control word's fill flag is bit 24: a u16 parameter would drop it
// (agbcc passes the full register to the BIOS).
void CpuFastSet(void *src, void *dst, u32 size);
#else // !PLATFORM_PC
void CpuFastSet(void *src, void *dst, u16 size);
#endif // PLATFORM_PC
void CpuSet(void *src, void *dst, u32 size);
s32 DivArmDiv(s32 denom, s32 numerator);
s32 DivArmMod(s32 denom, s32 numerator);
void LZ77UncompVram(const void *src, void *dst);
void LZ77UncompWram(const void *src, void *dst);
u32 MidiKey2Freq(u32* wd, u8 mk, u8 fp);
void SoundBias0(void);
void SoundBias1(void);

#endif /* SYSCALLS_H */
