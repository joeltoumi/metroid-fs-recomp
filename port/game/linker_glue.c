// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — game-side definitions for symbols that the GBA build gets
// from hand-written assembly or blobs. Compiled with the game code (game
// headers, -nostdinc), not with the port layer. The variables linker.ld
// places by address are in ram_symbols.c.
#include "types.h"
#include "callbacks.h"


// The IRQ handlers, in the order asm/intr_main.s checks the IF bits (DMA2,
// V-blank, H-blank, V-count, then the unused ones). On the GBA this table is
// the blob at 0x080A5224 in src/data/generic_data.c.
void (*const sIntrTable[13])(void) = {
    Dma2IntrCode,
    CallbackCallVblank,
    CallbackCallHBlank,
    CallbackCallVCount,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
    Callback_Empty,
};

// asm/intr_main.s: LoadInterruptCode() copies 512 bytes of it to IWRAM. The
// port dispatches interrupts itself (sIntrTable), so the copy is never run:
// natively it is 512 zero bytes the copy can read.
__asm__(
    "\t.section .rodata.mf_interrupt_code,\"a\"\n"
    "\t.balign 4\n"
    "\t.globl InterruptCode\n"
    "InterruptCode:\n"
    "\t.zero 512\n"
    "\t.previous\n");
