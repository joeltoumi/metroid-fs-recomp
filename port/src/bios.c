// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — replacements for the GBA BIOS calls (asm/syscalls.s).
#include "port.h"

#include <math.h>

// ---- memory -----------------------------------------------------------------

// CpuSet: bits 0-20 = unit count, bit 24 = fill (fixed source), bit 26 = 32-bit.
void CpuSet(const void* src, void* dst, uint32_t control)
{
    const uint32_t count = control & 0x1FFFFF;
    const bool fill = (control >> 24) & 1;
    const uint32_t unit = ((control >> 26) & 1) ? 4 : 2;
    const uint8_t* s = (const uint8_t*)Port_RomMirror(src); // see Port_DmaSet
    uint8_t* d = (uint8_t*)dst;

    if (!fill) {
        memmove(d, s, (size_t)count * unit);
        return;
    }
    for (uint32_t i = 0; i < count; i++)
        memcpy(d + (size_t)i * unit, s, unit);
}

// CpuFastSet: 32-bit units, count rounded up to a multiple of 8 words.
void CpuFastSet(const void* src, void* dst, uint32_t control)
{
    const uint32_t count = ((control & 0x1FFFFF) + 7) & ~7u;
    const bool fill = (control >> 24) & 1;
    const uint8_t* s = (const uint8_t*)Port_RomMirror(src);
    uint8_t* d = (uint8_t*)dst;

    if (!fill) {
        memmove(d, s, (size_t)count * 4);
        return;
    }
    for (uint32_t i = 0; i < count; i++)
        memcpy(d + (size_t)i * 4, s, 4);
}

// ---- math -------------------------------------------------------------------

int32_t DivArmDiv(int32_t number, int32_t denom)
{
    // SWI 7 (DivArm) takes (denom, number): the game's wrapper names follow
    // the register order, see asm/syscalls.s.
    if (number == 0)
        return 0;
    return denom / number;
}

int32_t DivArmMod(int32_t number, int32_t denom)
{
    if (number == 0)
        return 0;
    return denom % number;
}

uint16_t Sqrt(uint32_t number)
{
    uint32_t r = (uint32_t)sqrt((double)number);
    // Guard against floating point rounding at the boundaries.
    while ((uint64_t)r * r > number)
        r--;
    while ((uint64_t)(r + 1) * (r + 1) <= number)
        r++;
    return (uint16_t)r;
}

// ---- decompression ----------------------------------------------------------

static void Lz77Uncomp(const void* src, void* dst)
{
    const uint8_t* s = (const uint8_t*)src;
    uint8_t* d = (uint8_t*)dst;
    uint32_t header;
    uint32_t size;
    uint32_t written = 0;

    memcpy(&header, s, 4);
    s += 4;
    if ((header & 0xF0) != 0x10) {
        Port_Log("LZ77: bad header %08X", header);
        return;
    }
    size = header >> 8;

    while (written < size) {
        uint8_t flags = *s++;
        for (int bit = 0; bit < 8 && written < size; bit++, flags <<= 1) {
            if (flags & 0x80) {
                uint32_t len = (uint32_t)(s[0] >> 4) + 3;
                uint32_t disp = (((uint32_t)(s[0] & 0xF) << 8) | s[1]) + 1;
                s += 2;
                while (len-- > 0 && written < size) {
                    d[written] = d[written - disp];
                    written++;
                }
            } else {
                d[written++] = *s++;
            }
        }
    }
}

void LZ77UncompWram(const void* src, void* dst)
{
    Lz77Uncomp(src, dst);
}

void LZ77UncompVram(const void* src, void* dst)
{
    // VRAM only accepts 16-bit writes on hardware; the byte-wise result is
    // identical, except that an odd trailing byte would not be written.
    Lz77Uncomp(src, dst);
}

// ---- sound ------------------------------------------------------------------

struct PortWaveData {
    uint16_t type;
    uint16_t stat;
    uint32_t freq;
    uint32_t loop;
    uint32_t size;
};

uint32_t MidiKey2Freq(uint32_t* wd, uint8_t mk, uint8_t fp)
{
    const struct PortWaveData* wave = (const struct PortWaveData*)wd;
    double exponent = (180.0 - (double)mk - (double)fp / 256.0) / 12.0;
    return (uint32_t)((double)wave->freq / pow(2.0, exponent));
}

void SoundBias0(void)
{
}

void SoundBias1(void)
{
}

// ---- misc -------------------------------------------------------------------

int Multiboot(void* mbp)
{
    (void)mbp;
    return 1; // failure: no link cable
}

void VBlankIntrWait(void)
{
    Port_RunFrame();
}

void Port_Syscall(unsigned int number)
{
    switch (number) {
    case 2: // Halt: the main loop halts until the VBlank IRQ fires
        Port_RunFrame();
        Port_HostFrameBoundary(); // only AgbMain's loop halts with SWI 2
        break;
    case 3: // Stop (sleep mode): treat as waiting for the next frame
        Port_RunFrame();
        break;
    default:
        Port_Log("unhandled SWI %u", number);
        break;
    }
}
