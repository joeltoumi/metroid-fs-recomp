// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — entry point (replaces asm/crt0.s).
#include "port.h"
#include "port_game.h"
#include "port_assets.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __ANDROID__
#include <android/log.h>
#endif

static jmp_buf sExitJump;
static bool sQuit;
static bool sSramDirty;

void Port_RequestQuit(void)
{
    sQuit = true;
}

bool Port_QuitRequested(void)
{
    return sQuit;
}

_Noreturn void Port_ExitToMain(void)
{
    longjmp(sExitJump, 1);
}

void Port_SramWritten(void)
{
    sSramDirty = true;
}

void Port_FlushSave(void)
{
    if (!sSramDirty)
        return;
    Port_HostWriteSave(gPortSram, sizeof(gPortSram));
    sSramDirty = false;
}

void Port_Log(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
#ifdef __ANDROID__
    __android_log_vprint(ANDROID_LOG_INFO, "mf", fmt, ap);
#else
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
#endif
    va_end(ap);
}

_Noreturn void Port_Fatal(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
#ifdef __ANDROID__
    __android_log_vprint(ANDROID_LOG_FATAL, "mf", fmt, ap);
#else
    fputs("FATAL: ", stderr);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
#endif
    va_end(ap);
    abort();
}

int Port_Main(int argc, char** argv)
{
    PortHostConfig cfg = { argc, argv };

    if (!Port_HostInit(&cfg))
        return 1;

    // Game data comes from the player's ROM (nothing is embedded in the build).
    {
        const char* error = NULL;
        for (;;) {
            size_t size = 0;
            uint8_t* rom = Port_HostLoadRom(&size, error);
            if (!rom) {
                Port_HostShutdown();
                return 1;
            }
            PortRomStatus status = Port_LoadRom(rom, size);
            if (status == PORT_ROM_OK)
                Port_HostRomAccepted(rom, size);
            free(rom);
            if (status == PORT_ROM_OK)
                break;
            error = Port_RomStatusText(status);
            Port_Log("ROM rejected: %s", error);
        }
    }

    Port_MemReset();
    Port_DmaReset();
    Port_ApuReset();
    Port_PpuInit();

    // Erased flash reads as 0xFF; the host overwrites it with the save file.
    memset(gPortSram, 0xFF, sizeof(gPortSram));
    Port_HostLoadSave(gPortSram, sizeof(gPortSram));

    if (setjmp(sExitJump) == 0) {
        // asm/crt0.s: `bl AgbMain; b _start` — AgbMain returns on soft reset.
        while (!sQuit) {
            AgbMain();
            Port_FlushSave();
        }
    }

    Port_FlushSave();
    Port_HostShutdown();
    return 0;
}
