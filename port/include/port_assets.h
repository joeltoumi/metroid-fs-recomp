// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — loading game data from the player's ROM.
#ifndef PORT_ASSETS_H
#define PORT_ASSETS_H

#include <stddef.h>
#include <stdint.h>

typedef enum PortRomStatus {
    PORT_ROM_OK,
    PORT_ROM_MISSING,
    PORT_ROM_BAD_SIZE,
    PORT_ROM_NOT_MF,
    PORT_ROM_WRONG_VERSION,
} PortRomStatus;

// Validate and copy all game data out of `rom`. The buffer can be freed after.
PortRomStatus Port_LoadRom(const uint8_t* rom, size_t size);
PortRomStatus Port_CheckRom(const uint8_t* rom, size_t size);
const char* Port_RomStatusText(PortRomStatus status);
const char* Port_RomRegionName(void);
// The player's ROM as kept in memory (the sound engine reads it in place).
const uint8_t* Port_RomData(size_t* size);
const char* Port_RomExpectedSha1(void);

void Port_Sha1(const void* data, size_t size, uint8_t out[20]);

#endif // PORT_ASSETS_H
