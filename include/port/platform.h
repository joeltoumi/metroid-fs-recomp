#ifndef PORT_PLATFORM_H
#define PORT_PLATFORM_H

/*
 * mzm-android: native (PC / Android) build glue for the game code.
 *
 * On the GBA the game talks to hardware through fixed addresses
 * (0x02000000 EWRAM, 0x04000000 I/O, 0x06000000 VRAM, ...). In the native
 * build those regions are plain host buffers owned by the port layer
 * (port/src/gba_mem.c) and the *_BASE macros in include/gba/memory.h point
 * at them instead. The port's software PPU reads the same buffers.
 *
 * This header must stay free of libc includes: game translation units are
 * compiled with -nostdinc and define their own NULL/u8/u32 types.
 */

#ifdef PLATFORM_PC

typedef __UINTPTR_TYPE__ port_uptr;

extern unsigned char gPortEwram[256 * 0x400];
extern unsigned char gPortIwram[32 * 0x400];
extern unsigned char gPortIo[0x400];
extern unsigned char gPortPalram[0x400];
extern unsigned char gPortVram[96 * 0x400];
extern unsigned char gPortOam[0x400];
extern unsigned char gPortSram[64 * 0x400];
/* Nothing reads the cartridge directly in C; ROM_BASE only needs to be a
 * distinct, non-NULL address (soft-reset entry point bookkeeping). */
extern unsigned char gPortRomStub[0x100];

/* DMA: 64-bit pointers don't fit the 32-bit DMA registers, so every DMA
 * request goes through the port, which performs it (or schedules it for
 * HBlank/VBlank) with full-width pointers. */
void Port_DmaSet(unsigned int channel, const void* src, void* dst, unsigned int control);

/* BIOS SWI replacement (Halt, Stop, ...). */
void Port_Syscall(unsigned int number);

/* REG_VCOUNT read from a busy-wait loop: advances a virtual scanline and
 * returns it. */
unsigned short Port_PollVCount(void);

/* Called after the game writes save memory, so the host can persist it. */
void Port_SramWritten(void);

/* The player's ROM stays in memory: the sound engine reads its track scripts,
 * voicegroups and samples in place. Translates a GBA ROM address
 * (0x08xxxxxx) to the host copy, or returns NULL if it is outside the ROM. */
const void* Port_RomPointer(unsigned int gbaAddress);

/* The same bytes as `data` (a ROM data array), but inside the ROM copy. For
 * the few places where the game reads past the end of an array: on the GBA
 * that reads the next data in the ROM, and through this pointer it does too.
 * Returns `data` itself if it isn't ROM data. */
const void* Port_RomMirror(const void* data);
/* Same for any array of `size` bytes: data compiled into the game (not
 * copied from the ROM) is found in the ROM by its contents (it must appear
 * there only once). */
const void* Port_RomFind(const void* data, unsigned int size);

/* Game side of the sound port (port/game/audio_engine.c). */
struct Voice;
/* Builds the sound tables that hold ROM pointers (called once the ROM is
 * loaded). */
void Port_SoundInit(const unsigned char* rom, unsigned int size);
/* Host copy of the voicegroup at a GBA address (never NULL). */
struct Voice* Port_SoundVoicegroup(unsigned int gbaAddress);
/* Converts the cached voicegroups again from their addresses (after a save
 * state restored the cache's address list). */
void Port_SoundRebuildVoicegroups(void);
/* The next 16 samples sound DMA 1/2 would feed to FIFO A/B. Returns 0 when
 * the sound engine hasn't set up its buffers yet. */
int Port_SoundFifoBlock(const signed char** fifoA, const signed char** fifoB);

/* Test warp (MF_WARP, port/src/warp.c): target `index` of the list. room -1
 * means every room of the area (or every value of a mode), event -1 the
 * default event. Returns 0 past the end. The interval is how many frames
 * each target lasts (0 = stay in the only one). */
int Port_WarpTarget(int index, int* area, int* room, int* event);
unsigned int Port_WarpInterval(void);
/* MF_WARP_DIRECT=1: game modes are entered right at boot. */
int Port_WarpDirect(void);
/* Scripted input for the current target (PORT_WARP_SCRIPT_* in port.h). */
void Port_WarpScript(int script);
/* Which way Samus faces (the room script starts that way). */
void Port_WarpFacing(int left);
/* Game side (port/game/warp.c), called from AgbMain: once after
 * InitializeGame, then every frame; and from RoomReset when a new game
 * places Samus. */
void Port_WarpBoot(void);
void Port_WarpFrame(void);
void Port_WarpRoomReset(void);

void Port_Log(const char* fmt, ...);
void Port_RequestQuit(void);

#endif /* PLATFORM_PC */

#endif /* PORT_PLATFORM_H */
