// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — host buffers standing in for the GBA memory map.
#include "port.h"

// gPortEwram and gPortIwram are defined in port/game/ram_symbols.c, together
// with the game variables that live at fixed offsets inside them.

_Alignas(16) unsigned char gPortIo[0x400];
_Alignas(16) unsigned char gPortPalram[0x400];
_Alignas(16) unsigned char gPortVram[96 * 0x400];
_Alignas(16) unsigned char gPortOam[0x400];
_Alignas(16) unsigned char gPortSram[64 * 0x400];
_Alignas(16) unsigned char gPortRomStub[0x100];

void Port_MemReset(void)
{
    memset(gPortEwram, 0, sizeof(gPortEwram));
    memset(gPortIwram, 0, sizeof(gPortIwram));
    memset(gPortIo, 0, sizeof(gPortIo));
    memset(gPortPalram, 0, sizeof(gPortPalram));
    memset(gPortVram, 0, sizeof(gPortVram));
    memset(gPortOam, 0, sizeof(gPortOam));
    // Unpressed keys read as 1 (active-low KEYINPUT).
    Port_IoWrite16(0x130, 0x03FF);
}
