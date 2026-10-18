// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — sound output: the GBA's audio hardware, as far as the game
// uses it.
//
//   * DirectSound: the game mixes its PCM channels into
//     gMusicInfo.soundRawData; on the GBA, DMA 1/2 feed that buffer to FIFO
//     A/B 16 samples at a time, paced by timer 0, and the DMA 2 IRQ
//     (DMA2IntrCode) tracks the read position. Here each frame plays the
//     frame's worth of samples, raising that IRQ after every 16.
//   * PSG: the four Game Boy channels (2 squares, wave, noise), emulated from
//     their I/O registers. The game writes them once per frame (from
//     UpdateAudio), so they are sampled once per frame too; a write with the
//     "restart" bit set (re)starts a note.
//
// Everything is mixed to 48 kHz stereo and handed to the host once per frame.
#include "port.h"
#include "port_game.h"

#define CYCLES_PER_FRAME 280896.0
#define FRAME_RATE (16777216.0 / CYCLES_PER_FRAME) // 59.7275 Hz
#define MAX_PCM_PER_FRAME 2048
#define MAX_OUT_PER_FRAME 1024
#define SEQUENCER_RATE 512.0 // PSG length/envelope/sweep clock

enum {
    IO_SOUND1CNT_L = 0x60,
    IO_SOUND1CNT_H = 0x62,
    IO_SOUND1CNT_X = 0x64,
    IO_SOUND2CNT_L = 0x68,
    IO_SOUND2CNT_H = 0x6C,
    IO_SOUND3CNT_L = 0x70,
    IO_SOUND3CNT_H = 0x72,
    IO_SOUND3CNT_X = 0x74,
    IO_SOUND4CNT_L = 0x78,
    IO_SOUND4CNT_H = 0x7C,
    IO_SOUNDCNT_L = 0x80,
    IO_SOUNDCNT_H = 0x82,
    IO_SOUNDCNT_X = 0x84,
    IO_WAVE_RAM = 0x90,
    IO_DMA1CNT_H = 0xC6,
    IO_DMA2CNT_H = 0xD2,
    IO_TM0CNT_L = 0x100,
    IO_TM0CNT_H = 0x102,

    IRQ_DMA2 = 1 << 10,
    DMA_IRQ_ENABLE = 1 << 14,
    DMA_ENABLE = 1 << 15,
    RESTART = 1 << 15,
    LENGTH_ENABLE = 1 << 14,

    INTR_SLOT_DMA2 = 0,
};

typedef struct Envelope {
    int volume;
    int step; // in 1/64 s, 0 = off
    int timer;
    bool increase;
} Envelope;

typedef struct PsgChannel {
    bool on;
    int length; // remaining, in 1/256 s
    bool lengthEnabled;
    double phase;
    Envelope env;
} PsgChannel;

typedef struct Apu {
    PsgChannel square[2];
    int sweepTimer;
    int sweepFrequency;
    PsgChannel wave;
    PsgChannel noise;
    uint16_t lfsr;
    double sequencerPhase;
    int sequencerStep;

    int8_t fifoA[16];
    int8_t fifoB[16];
    int fifoPos; // 16 = empty
    double pcmCarry;
    double outCarry;
    // Last DirectSound sample of the previous frame (resampling continuity).
    float lastLeft;
    float lastRight;
    // DC blocker state.
    float hpInLeft, hpInRight, hpLeft, hpRight;
} Apu;

static Apu sApu PORT_STATE;

void Port_ApuReset(void)
{
    memset(&sApu, 0, sizeof(sApu));
    sApu.fifoPos = 16;
    sApu.lfsr = 0x7FFF;
}

static uint8_t Io8(uint32_t off)
{
    return gPortIo[off];
}

// ---- PSG --------------------------------------------------------------------

// NRx2-style envelope byte (high byte of SOUND1CNT_H, SOUND2CNT_L, SOUND4CNT_L).
static void StartEnvelope(PsgChannel* ch, uint8_t nrx2)
{
    ch->env.volume = nrx2 >> 4;
    ch->env.increase = (nrx2 & 8) != 0;
    ch->env.step = nrx2 & 7;
    ch->env.timer = ch->env.step;
    // The DAC is off when the upper 5 bits are 0: no sound at all.
    ch->on = (nrx2 & 0xF8) != 0;
}

static void ClockEnvelope(PsgChannel* ch)
{
    if (ch->env.step == 0 || --ch->env.timer > 0)
        return;
    ch->env.timer = ch->env.step;
    if (ch->env.increase && ch->env.volume < 15)
        ch->env.volume++;
    else if (!ch->env.increase && ch->env.volume > 0)
        ch->env.volume--;
}

static void ClockLength(PsgChannel* ch)
{
    if (ch->lengthEnabled && ch->length > 0 && --ch->length == 0)
        ch->on = false;
}

static int SweepNext(void)
{
    const uint8_t nr10 = Io8(IO_SOUND1CNT_L);
    const int delta = sApu.sweepFrequency >> (nr10 & 7);
    return (nr10 & 8) ? sApu.sweepFrequency - delta : sApu.sweepFrequency + delta;
}

static void ClockSweep(void)
{
    const uint8_t nr10 = Io8(IO_SOUND1CNT_L);
    const int time = (nr10 >> 4) & 7;
    int next;

    if (time == 0 || --sApu.sweepTimer > 0)
        return;
    sApu.sweepTimer = time;
    next = SweepNext();
    if (next > 2047) {
        sApu.square[0].on = false;
    } else if (nr10 & 7) {
        sApu.sweepFrequency = next;
        Port_IoWrite16(IO_SOUND1CNT_X, (uint16_t)((Port_IoRead16(IO_SOUND1CNT_X) & ~0x7FF) | next));
    }
}

static void ClockSequencer(void)
{
    const int step = sApu.sequencerStep;

    sApu.sequencerStep = (step + 1) & 7;
    if ((step & 1) == 0) {
        ClockLength(&sApu.square[0]);
        ClockLength(&sApu.square[1]);
        ClockLength(&sApu.wave);
        ClockLength(&sApu.noise);
    }
    if (step == 2 || step == 6)
        ClockSweep();
    if (step == 7) {
        ClockEnvelope(&sApu.square[0]);
        ClockEnvelope(&sApu.square[1]);
        ClockEnvelope(&sApu.noise);
    }
}

// Reads one channel's control/frequency registers; handles a restart.
static void UpdateSquare(int i, uint32_t ctlOff, uint32_t freqOff)
{
    PsgChannel* ch = &sApu.square[i];
    const uint16_t ctl = Port_IoRead16(ctlOff);
    uint16_t freq = Port_IoRead16(freqOff);

    ch->lengthEnabled = (freq & LENGTH_ENABLE) != 0;
    if (!(freq & RESTART))
        return;

    // The restart bit isn't stored by the hardware.
    freq &= ~RESTART;
    Port_IoWrite16(freqOff, freq);

    StartEnvelope(ch, (uint8_t)(ctl >> 8));
    ch->length = 64 - (ctl & 0x3F);
    if (i == 0) {
        const uint8_t nr10 = Io8(IO_SOUND1CNT_L);
        const int time = (nr10 >> 4) & 7;
        sApu.sweepFrequency = freq & 0x7FF;
        sApu.sweepTimer = time;
        if ((nr10 & 7) && SweepNext() > 2047)
            ch->on = false;
    }
}

static void UpdateWave(void)
{
    PsgChannel* ch = &sApu.wave;
    uint16_t freq = Port_IoRead16(IO_SOUND3CNT_X);

    ch->lengthEnabled = (freq & LENGTH_ENABLE) != 0;
    if (!(Io8(IO_SOUND3CNT_L) & 0x80))
        ch->on = false; // DAC off
    if (!(freq & RESTART))
        return;

    freq &= ~RESTART;
    Port_IoWrite16(IO_SOUND3CNT_X, freq);
    ch->on = (Io8(IO_SOUND3CNT_L) & 0x80) != 0;
    ch->length = 256 - Io8(IO_SOUND3CNT_H);
    ch->phase = 0;
}

static void UpdateNoise(void)
{
    PsgChannel* ch = &sApu.noise;
    const uint16_t ctl = Port_IoRead16(IO_SOUND4CNT_L);
    uint16_t freq = Port_IoRead16(IO_SOUND4CNT_H);

    ch->lengthEnabled = (freq & LENGTH_ENABLE) != 0;
    if (!(freq & RESTART))
        return;

    freq &= ~RESTART;
    Port_IoWrite16(IO_SOUND4CNT_H, freq);
    StartEnvelope(ch, (uint8_t)(ctl >> 8));
    ch->length = 64 - (ctl & 0x3F);
    sApu.lfsr = 0x7FFF;
}

static float SquareSample(int i, uint32_t ctlOff, uint32_t freqOff)
{
    static const double sDuty[4] = { 0.125, 0.25, 0.5, 0.75 };
    PsgChannel* ch = &sApu.square[i];
    const int n = Port_IoRead16(freqOff) & 0x7FF;
    const double hz = 131072.0 / (2048 - n);
    const double duty = sDuty[(Io8(ctlOff) >> 6) & 3];

    ch->phase += hz / PORT_AUDIO_RATE;
    ch->phase -= (int)ch->phase;
    if (!ch->on)
        return 0;
    return (float)(ch->phase < duty ? ch->env.volume : -ch->env.volume);
}

static float WaveSample(void)
{
    static const float sVolume[4] = { 0, 1, 0.5f, 0.25f };
    PsgChannel* ch = &sApu.wave;
    const int n = Port_IoRead16(IO_SOUND3CNT_X) & 0x7FF;
    const uint16_t ctl = Port_IoRead16(IO_SOUND3CNT_H);
    const float volume = (ctl & 0x8000) ? 0.75f : sVolume[(ctl >> 13) & 3];
    int index;
    int nibble;

    // 32 4-bit samples per period.
    ch->phase += (2097152.0 / (2048 - n)) / PORT_AUDIO_RATE / 32;
    ch->phase -= (int)ch->phase;
    if (!ch->on)
        return 0;
    index = (int)(ch->phase * 32) & 31;
    nibble = Io8(IO_WAVE_RAM + index / 2);
    nibble = (index & 1) ? nibble & 0xF : nibble >> 4;
    return (nibble * 2 - 15) * volume;
}

static float NoiseSample(void)
{
    PsgChannel* ch = &sApu.noise;
    const uint8_t nr43 = Io8(IO_SOUND4CNT_H);
    const double divider = (nr43 & 7) ? (nr43 & 7) : 0.5;
    const double hz = 524288.0 / divider / (double)(2 << (nr43 >> 4));

    ch->phase += hz / PORT_AUDIO_RATE;
    while (ch->phase >= 1) {
        const int bit = (sApu.lfsr ^ (sApu.lfsr >> 1)) & 1;
        sApu.lfsr = (uint16_t)((sApu.lfsr >> 1) | (bit << 14));
        if (nr43 & 8)
            sApu.lfsr = (uint16_t)((sApu.lfsr & ~0x40) | (bit << 6));
        ch->phase -= 1;
    }
    if (!ch->on)
        return 0;
    return (float)((sApu.lfsr & 1) ? -ch->env.volume : ch->env.volume);
}

// ---- DirectSound ------------------------------------------------------------

static bool RefillFifo(void)
{
    const signed char* a;
    const signed char* b;

    if (!(Port_IoRead16(IO_DMA1CNT_H) & DMA_ENABLE) || !(Port_IoRead16(IO_DMA2CNT_H) & DMA_ENABLE))
        return false;
    if (!Port_SoundFifoBlock(&a, &b))
        return false;
    memcpy(sApu.fifoA, a, sizeof(sApu.fifoA));
    memcpy(sApu.fifoB, b, sizeof(sApu.fifoB));
    sApu.fifoPos = 0;

    // DMA 2 IRQ after each 16-sample transfer: the engine's read position.
    if ((Port_IoRead16(IO_DMA2CNT_H) & DMA_IRQ_ENABLE) && (Port_IoRead16(IO_IME) & 1) &&
        (Port_IoRead16(IO_IE) & IRQ_DMA2) && sIntrTable[INTR_SLOT_DMA2] != NULL)
        sIntrTable[INTR_SLOT_DMA2]();
    return true;
}

// Samples played this frame at the timer 0 rate (224 per frame by default).
static int PlayFifo(float* left, float* right)
{
    const uint16_t soundcnt = Port_IoRead16(IO_SOUNDCNT_H);
    const float volA = (soundcnt & (1 << 2)) ? 2.0f : 1.0f;
    const float volB = (soundcnt & (1 << 3)) ? 2.0f : 1.0f;
    const uint16_t period = (uint16_t)(0x10000 - Port_IoRead16(IO_TM0CNT_L));
    int count;

    if (!(Port_IoRead16(IO_TM0CNT_H) & 0x80) || period == 0)
        return 0;

    sApu.pcmCarry += CYCLES_PER_FRAME / period;
    count = (int)sApu.pcmCarry;
    sApu.pcmCarry -= count;
    if (count > MAX_PCM_PER_FRAME)
        count = MAX_PCM_PER_FRAME;

    for (int i = 0; i < count; i++) {
        float a = 0;
        float b = 0;

        if (sApu.fifoPos == 16 && !RefillFifo()) {
            memset(sApu.fifoA, 0, sizeof(sApu.fifoA));
            memset(sApu.fifoB, 0, sizeof(sApu.fifoB));
            sApu.fifoPos = 0;
        }
        a = sApu.fifoA[sApu.fifoPos] * volA;
        b = sApu.fifoB[sApu.fifoPos] * volB;
        sApu.fifoPos++;

        left[i] = ((soundcnt & (1 << 9)) ? a : 0) + ((soundcnt & (1 << 13)) ? b : 0);
        right[i] = ((soundcnt & (1 << 8)) ? a : 0) + ((soundcnt & (1 << 12)) ? b : 0);
    }
    return count;
}

// ---- frame ------------------------------------------------------------------

void Port_ApuRunFrame(void)
{
    static float sPcmLeft[MAX_PCM_PER_FRAME + 1];
    static float sPcmRight[MAX_PCM_PER_FRAME + 1];
    static int16_t sOut[MAX_OUT_PER_FRAME * 2];
    const bool enabled = (Io8(IO_SOUNDCNT_X) & 0x80) != 0;
    const uint16_t psgCnt = Port_IoRead16(IO_SOUNDCNT_L);
    const float psgRatio[4] = { 0.25f, 0.5f, 1.0f, 0.25f };
    const float psgScale = psgRatio[Port_IoRead16(IO_SOUNDCNT_H) & 3] * 0.5f;
    const float psgVolRight = (float)((psgCnt & 7) + 1) * psgScale;
    const float psgVolLeft = (float)(((psgCnt >> 4) & 7) + 1) * psgScale;
    int pcmCount;
    int outCount;

    UpdateSquare(0, IO_SOUND1CNT_H, IO_SOUND1CNT_X);
    UpdateSquare(1, IO_SOUND2CNT_L, IO_SOUND2CNT_H);
    UpdateWave();
    UpdateNoise();

    // pcm[0] is the last sample of the previous frame.
    sPcmLeft[0] = sApu.lastLeft;
    sPcmRight[0] = sApu.lastRight;
    pcmCount = PlayFifo(&sPcmLeft[1], &sPcmRight[1]);
    if (pcmCount > 0) {
        sApu.lastLeft = sPcmLeft[pcmCount];
        sApu.lastRight = sPcmRight[pcmCount];
    }

    sApu.outCarry += PORT_AUDIO_RATE / FRAME_RATE;
    outCount = (int)sApu.outCarry;
    sApu.outCarry -= outCount;
    if (outCount > MAX_OUT_PER_FRAME)
        outCount = MAX_OUT_PER_FRAME;

    for (int i = 0; i < outCount; i++) {
        float left = 0;
        float right = 0;
        float ch[4];

        sApu.sequencerPhase += SEQUENCER_RATE / PORT_AUDIO_RATE;
        if (sApu.sequencerPhase >= 1) {
            sApu.sequencerPhase -= 1;
            ClockSequencer();
        }

        ch[0] = SquareSample(0, IO_SOUND1CNT_H, IO_SOUND1CNT_X);
        ch[1] = SquareSample(1, IO_SOUND2CNT_L, IO_SOUND2CNT_H);
        ch[2] = WaveSample();
        ch[3] = NoiseSample();
        for (int c = 0; c < 4; c++) {
            if (psgCnt & (1 << (8 + c)))
                right += ch[c];
            if (psgCnt & (1 << (12 + c)))
                left += ch[c];
        }
        left *= psgVolLeft;
        right *= psgVolRight;

        // DirectSound, linearly resampled from the timer 0 rate.
        if (pcmCount > 0) {
            const float pos = (float)i * pcmCount / outCount;
            const int k = (int)pos;
            const float t = pos - k;
            left += sPcmLeft[k] + (sPcmLeft[k + 1] - sPcmLeft[k]) * t;
            right += sPcmRight[k] + (sPcmRight[k + 1] - sPcmRight[k]) * t;
        }

        if (!enabled)
            left = right = 0;

        // The GBA adds the bias and clamps to its 10-bit DAC range (0-0x3FF),
        // here +-256 since DirectSound at 100% is s8 * 2. Loud passages of the
        // music do hit that limit.
        left = left < -256 ? -256 : left > 255.5f ? 255.5f : left;
        right = right < -256 ? -256 : right > 255.5f ? 255.5f : right;

        // The output is AC-coupled: remove the DC offset (~4 Hz high-pass).
        sApu.hpLeft = left - sApu.hpInLeft + 0.9995f * sApu.hpLeft;
        sApu.hpRight = right - sApu.hpInRight + 0.9995f * sApu.hpRight;
        sApu.hpInLeft = left;
        sApu.hpInRight = right;
        left = sApu.hpLeft;
        right = sApu.hpRight;

        // Gain chosen to match the loudness of mGBA's output for this game.
        left *= 94;
        right *= 94;
        sOut[i * 2] = (int16_t)(left > 32767 ? 32767 : left < -32768 ? -32768 : left);
        sOut[i * 2 + 1] = (int16_t)(right > 32767 ? 32767 : right < -32768 ? -32768 : right);
    }

    Port_HostQueueAudio(sOut, outCount);
}
