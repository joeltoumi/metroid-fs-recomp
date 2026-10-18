// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — the handful of game symbols the port layer touches.
// (Declared by hand: game headers can't be mixed with libc headers.)
#ifndef PORT_GAME_H
#define PORT_GAME_H

#include <stdint.h>

typedef void (*PortGameFunc)(void);

// src/agbmain.c — the game's main loop. Returns on soft reset.
void AgbMain(void);

// port/game/linker_glue.c — IRQ handler table indexed like asm/intr_main.s.
extern const PortGameFunc sIntrTable[13];

// Unwind from deep inside the game back to main() (quit request).
_Noreturn void Port_ExitToMain(void);

#endif // PORT_GAME_H
