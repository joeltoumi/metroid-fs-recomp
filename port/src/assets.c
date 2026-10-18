// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — runtime game data, copied out of the player's own ROM.
//
// The build contains no game data: every array the decomp would fill from the
// ROM at compile time is zero-filled and registered by the generated wrappers
// (tools/port/gen_assets.py). At startup Port_LoadRom() checks the ROM is the
// exact dump this build expects (SHA-1) and copies each block into place.
// A copy of the whole ROM is also kept for the sound engine, which reads the
// music data in place (Port_RomPointer).
#include "port.h"
#include "port_assets.h"

#include "../../include/port/assets_glue.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef MF_ROM_SHA1
#error "MF_ROM_SHA1 must be defined by the build (expected SHA-1 of the ROM)"
#endif

typedef struct AssetChunk {
    PortAsset* assets;
    unsigned long count;
} AssetChunk;

static uint8_t* sRom;
static size_t sRomSize;

// Every asset sorted by host address, for Port_RomMirror().
static const PortAsset** sByHost;
static size_t sByHostCount;

static AssetChunk* sChunks;
static size_t sChunkCount;
static size_t sChunkCap;

void Port_RegisterAssets(PortAsset* assets, unsigned long count)
{
    if (sChunkCount == sChunkCap) {
        size_t cap = sChunkCap ? sChunkCap * 2 : 512;
        AssetChunk* grown = realloc(sChunks, cap * sizeof(*grown));
        if (!grown)
            abort();
        sChunks = grown;
        sChunkCap = cap;
    }
    sChunks[sChunkCount].assets = assets;
    sChunks[sChunkCount].count = count;
    sChunkCount++;
}

const void* Port_RomPointer(unsigned int gbaAddress)
{
    const uint32_t offset = gbaAddress - 0x08000000u;

    if (gbaAddress < 0x08000000u || offset >= sRomSize)
        return NULL;
    return sRom + offset;
}

const uint8_t* Port_RomData(size_t* size)
{
    *size = sRomSize;
    return sRom;
}

static int CompareHost(const void* a, const void* b)
{
    const uintptr_t x = (uintptr_t)(*(const PortAsset* const*)a)->dst;
    const uintptr_t y = (uintptr_t)(*(const PortAsset* const*)b)->dst;
    return (x > y) - (x < y);
}

static void IndexAssets(void)
{
    size_t n = 0;

    for (size_t c = 0; c < sChunkCount; c++)
        n += sChunks[c].count;
    free(sByHost);
    sByHost = malloc(n * sizeof(*sByHost));
    if (!sByHost)
        Port_Fatal("out of memory (asset index)");
    sByHostCount = 0;
    for (size_t c = 0; c < sChunkCount; c++) {
        for (unsigned long i = 0; i < sChunks[c].count; i++)
            sByHost[sByHostCount++] = &sChunks[c].assets[i];
    }
    qsort(sByHost, sByHostCount, sizeof(*sByHost), CompareHost);
}

const void* Port_RomMirror(const void* data)
{
    const uintptr_t p = (uintptr_t)data;
    size_t lo = 0;
    size_t hi = sByHostCount;

    // Last asset that starts at or before `data`.
    while (lo < hi) {
        size_t mid = (lo + hi) / 2;
        if ((uintptr_t)sByHost[mid]->dst <= p)
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo != 0 && sRom != NULL) {
        const PortAsset* a = sByHost[lo - 1];
        if (p < (uintptr_t)a->dst + a->size)
            return sRom + a->romOffset + (p - (uintptr_t)a->dst);
    }
    return data;
}

const void* Port_RomFind(const void* data, unsigned int size)
{
    enum { CACHE_SIZE = 16 };
    static struct {
        const void* data;
        const void* found;
    } sCache[CACHE_SIZE];
    static int sCached;
    const uint8_t* hit = NULL;

    if (sRom == NULL || size == 0)
        return data;
    hit = Port_RomMirror(data);
    if (hit != data)
        return hit;
    hit = NULL;
    for (int i = 0; i < sCached; i++) {
        if (sCache[i].data == data)
            return sCache[i].found;
    }

    // The array must appear exactly once in the ROM (4-byte aligned).
    size_t off;
    for (off = 0; off + size <= sRomSize; off += 4) {
        if (memcmp(sRom + off, data, size) != 0)
            continue;
        if (hit != NULL) {
            Port_Log("Port_RomFind: %u bytes found more than once in the ROM", size);
            hit = NULL;
            break;
        }
        hit = sRom + off;
    }
    if (hit == NULL) {
        // Fall back to the compiled-in array: reads past its end then see
        // other data instead of the ROM's. Never happens with the EU ROM; a
        // region not yet tested with its real ROM (JP) would show it here.
        if (off + size > sRomSize)
            Port_Log("Port_RomFind: %u bytes not found in the ROM", size);
        hit = data;
    }
    if (sCached < CACHE_SIZE) {
        sCache[sCached].data = data;
        sCache[sCached].found = hit;
        sCached++;
    }
    return hit;
}

const char* Port_RomRegionName(void)
{
    return MF_ROM_REGION_NAME;
}

const char* Port_RomExpectedSha1(void)
{
    return MF_ROM_SHA1;
}

PortRomStatus Port_CheckRom(const uint8_t* rom, size_t size)
{
    char hex[41];
    uint8_t digest[20];

    if (size < 0x200 || size > 32 * 1024 * 1024)
        return PORT_ROM_BAD_SIZE;
    // Development/CI only: boot with any image (e.g. a zero-filled dummy) to
    // smoke-test the engine without game data.
    if (getenv("MF_DEV_SKIP_ROM_CHECK") != NULL) {
        Port_Log("MF_DEV_SKIP_ROM_CHECK set: not verifying the ROM");
        return PORT_ROM_OK;
    }
    // Header: game title at 0xA0, game code at 0xAC ("BMXE" for the US version).
    if (memcmp(rom + 0xA0, "METROID4", 8) != 0)
        return PORT_ROM_NOT_MF;

    Port_Sha1(rom, size, digest);
    for (int i = 0; i < 20; i++)
        snprintf(hex + i * 2, 3, "%02x", digest[i]);
    if (strcmp(hex, MF_ROM_SHA1) != 0) {
        Port_Log("ROM SHA-1 %s, expected %s (%s)", hex, MF_ROM_SHA1, MF_ROM_REGION_NAME);
        return PORT_ROM_WRONG_VERSION;
    }
    return PORT_ROM_OK;
}

PortRomStatus Port_LoadRom(const uint8_t* rom, size_t size)
{
    size_t total = 0;
    unsigned long assets = 0;
    PortRomStatus status = Port_CheckRom(rom, size);

    if (status != PORT_ROM_OK)
        return status;

    for (size_t c = 0; c < sChunkCount; c++) {
        for (unsigned long i = 0; i < sChunks[c].count; i++) {
            const PortAsset* a = &sChunks[c].assets[i];
            if ((size_t)a->romOffset + a->size > size)
                Port_Fatal("asset at 0x%X (+0x%X) is outside the ROM", a->romOffset, a->size);
            memcpy(a->dst, rom + a->romOffset, a->size);
            total += a->size;
            assets++;
        }
    }
    Port_Log("ROM %s OK: %lu assets, %zu KiB copied", MF_ROM_REGION_NAME, assets, total / 1024);

    // The sound engine plays the ROM's track scripts and samples in place.
    free(sRom);
    sRom = malloc(size);
    if (!sRom)
        Port_Fatal("out of memory (ROM copy)");
    memcpy(sRom, rom, size);
    sRomSize = size;
    IndexAssets();
    Port_SoundInit(sRom, (unsigned int)size);
    return PORT_ROM_OK;
}

const char* Port_RomStatusText(PortRomStatus status)
{
    switch (status) {
    case PORT_ROM_OK:
        return "OK";
    case PORT_ROM_MISSING:
        return "No ROM selected";
    case PORT_ROM_BAD_SIZE:
        return "The file is not a GBA ROM";
    case PORT_ROM_NOT_MF:
        return "The file is not Metroid Fusion";
    case PORT_ROM_WRONG_VERSION:
        return "Wrong version of Metroid Fusion (this build needs the " MF_ROM_REGION_NAME " ROM)";
    }
    return "?";
}
