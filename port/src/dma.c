// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — DMA emulation.
//
// The game programs DMA either through DmaTransfer/BitFill (src/dma.c on the
// GBA) or the DMA_SET macro, both routed here in the native build. Immediate
// transfers are plain memcpy/memset; HBlank- and VBlank-timed channels are
// latched and replayed by the frame loop (haze/heat-wave effects use HBlank
// DMA on channel 0). Sound FIFO DMA (channels 1/2, start mode "special") is
// ignored: audio is produced by the port's own mixer.
#include "port.h"

// DMA control (high half of DMAxCNT) bits.
enum {
    DMA_CTL_DEST_MASK = 3 << 5,
    DMA_CTL_DEST_INC = 0 << 5,
    DMA_CTL_DEST_DEC = 1 << 5,
    DMA_CTL_DEST_FIXED = 2 << 5,
    DMA_CTL_DEST_RELOAD = 3 << 5,
    DMA_CTL_SRC_MASK = 3 << 7,
    DMA_CTL_SRC_INC = 0 << 7,
    DMA_CTL_SRC_DEC = 1 << 7,
    DMA_CTL_SRC_FIXED = 2 << 7,
    DMA_CTL_REPEAT = 1 << 9,
    DMA_CTL_32BIT = 1 << 10,
    DMA_CTL_START_MASK = 3 << 12,
    DMA_CTL_START_NOW = 0 << 12,
    DMA_CTL_START_VBLANK = 1 << 12,
    DMA_CTL_START_HBLANK = 2 << 12,
    DMA_CTL_START_SPECIAL = 3 << 12,
    DMA_CTL_IRQ = 1 << 14,
    DMA_CTL_ENABLE = 1 << 15,
};

typedef struct PortDmaChannel {
    bool armed;
    const uint8_t* src;
    uint8_t* dst;
    uint8_t* dstReload;
    uint32_t units;
    uint16_t control;
} PortDmaChannel;

static PortDmaChannel sChannels[4] PORT_STATE;

void Port_DmaReset(void)
{
    memset(sChannels, 0, sizeof(sChannels));
}

static ptrdiff_t StepFor(uint16_t mode, uint32_t unit, bool isDest)
{
    switch (mode) {
    case 0: // increment
        return (ptrdiff_t)unit;
    case 1: // decrement
        return -(ptrdiff_t)unit;
    case 2: // fixed
        return 0;
    default: // 3: dest = increment/reload, src = prohibited (treated as inc)
        (void)isDest;
        return (ptrdiff_t)unit;
    }
}

static void Transfer(PortDmaChannel* ch)
{
    const uint32_t unit = (ch->control & DMA_CTL_32BIT) ? 4 : 2;
    const ptrdiff_t srcStep = StepFor((ch->control & DMA_CTL_SRC_MASK) >> 7, unit, false);
    const ptrdiff_t dstStep = StepFor((ch->control & DMA_CTL_DEST_MASK) >> 5, unit, true);
    const uint8_t* src = ch->src;
    uint8_t* dst = ch->dst;

    if (src == NULL || dst == NULL)
        return;

    if (srcStep == (ptrdiff_t)unit && dstStep == (ptrdiff_t)unit) {
        memmove(dst, src, (size_t)ch->units * unit);
        src += (size_t)ch->units * unit;
        dst += (size_t)ch->units * unit;
    } else {
        for (uint32_t i = 0; i < ch->units; i++) {
            memcpy(dst, src, unit);
            src += srcStep;
            dst += dstStep;
        }
    }

    ch->src = src;
    ch->dst = ((ch->control & DMA_CTL_DEST_MASK) == DMA_CTL_DEST_RELOAD) ? ch->dstReload : dst;
}

void Port_DmaSet(unsigned int channel, const void* src, void* dst, unsigned int control)
{
    PortDmaChannel* ch;
    uint16_t ctl = (uint16_t)(control >> 16);
    uint32_t units = control & 0xFFFF;

    if (channel > 3)
        return;
    ch = &sChannels[channel];

    if (!(ctl & DMA_CTL_ENABLE)) {
        ch->armed = false;
        return;
    }

    if (units == 0)
        units = (channel == 3) ? 0x10000 : 0x4000;

    // Copies from ROM data come from the ROM image, so a copy that runs past
    // the end of the array reads the next data, as on the GBA.
    ch->src = (const uint8_t*)Port_RomMirror(src);
    ch->dst = (uint8_t*)dst;
    ch->dstReload = (uint8_t*)dst;
    ch->units = units;
    ch->control = ctl;

    switch (ctl & DMA_CTL_START_MASK) {
    case DMA_CTL_START_NOW:
        Transfer(ch);
        ch->armed = false;
        break;
    case DMA_CTL_START_VBLANK:
    case DMA_CTL_START_HBLANK:
        ch->armed = true;
        break;
    default: // sound FIFO / video capture: not emulated
        ch->armed = false;
        break;
    }
}

static void RunTimed(uint16_t start)
{
    for (int i = 0; i < 4; i++) {
        PortDmaChannel* ch = &sChannels[i];
        if (!ch->armed || (ch->control & DMA_CTL_START_MASK) != start)
            continue;
        Transfer(ch);
        if (!(ch->control & DMA_CTL_REPEAT))
            ch->armed = false;
    }
}

void Port_DmaOnHBlank(void)
{
    RunTimed(DMA_CTL_START_HBLANK);
}

void Port_DmaOnVBlank(void)
{
    RunTimed(DMA_CTL_START_VBLANK);
}

// ---- game-facing helpers (replace src/dma.c) --------------------------------

void DmaTransfer(uint8_t channel, const void* src, void* dst, uint32_t len, uint8_t bitSize)
{
    (void)channel;
    (void)bitSize;
    if (len != 0)
        memmove(dst, Port_RomMirror(src), len); // see Port_DmaSet
}

void BitFill(uint8_t channel, uint32_t value, void* dst, uint32_t len, uint8_t bitSize)
{
    (void)channel;
    uint8_t* d = (uint8_t*)dst;
    if (bitSize == 32) {
        uint32_t v = value;
        for (uint32_t i = 0; i + 4 <= len; i += 4)
            memcpy(d + i, &v, 4);
    } else {
        uint16_t v = (uint16_t)value;
        for (uint32_t i = 0; i + 2 <= len; i += 2)
            memcpy(d + i, &v, 2);
    }
}
