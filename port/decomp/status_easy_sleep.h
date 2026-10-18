#ifndef STATUS_EASY_SLEEP_H
#define STATUS_EASY_SLEEP_H

/*
 * Status screen and easy sleep menu of the pause screen
 * (asm/disasm_0x0807e678.s, 0x0807e678 - 0x0807eea0).
 */

#include "types.h"

/* ---------------------------------------------------------------------------------------------- */
/* Data blobs (static in src/data and src/ C files, externed here)                                       */
/* ---------------------------------------------------------------------------------------------- */

/* PORT: static in src/data/menus/pause_debug.c (0x0858217b), must be made visible for the native build */
extern const u8 sBlob_58217b_58225c[];
/* PORT: static in src/menus/pause_screen_map.c (0x0879bea8), holds 5 pointers to the status flag tables */
extern u8* sUnk_79bea8[5];

/*
 * 0x0858217c: status screen sections, 11 entries of 5 bytes, indexed by enum StatusScreenSection.
 * [0] top row, [1] bottom row, [2] left column, [3] right column, [4] unused here
 */
#define sStatusScreenSectionInfo ((const u8 (*)[5])(sBlob_58217b_58225c + 0x1))
/*
 * 0x085821b3: where the "owned" graphics of each item section are in the tilemap, 7 entries of 5 bytes.
 * [0] first row - 1, [1] closing row, [2] left column, ...
 */
#define sStatusScreenSourceInfo ((const u8 (*)[5])(sBlob_58217b_58225c + 0x38))
/*
 * 0x085821d6: ammo headers, 3 entries of 4 bytes ([0] = blank source, [1] missiles, [2] power bombs).
 * [0] top row, [1] bottom row, [2] left column, [3] right column
 */
#define sStatusScreenAmmoHeaderInfo ((const u8 (*)[4])(sBlob_58217b_58225c + 0x5b))

#define STATUS_SCREEN_SECTION_TOP(section) (sStatusScreenSectionInfo[(section)][0])
#define STATUS_SCREEN_SECTION_LEFT(section) (sStatusScreenSectionInfo[(section)][2])
#define STATUS_SCREEN_SECTION_RIGHT(section) (sStatusScreenSectionInfo[(section)][3])
#define STATUS_SCREEN_SECTION_WIDTH(section) (STATUS_SCREEN_SECTION_RIGHT((section)) - STATUS_SCREEN_SECTION_LEFT((section)))

/* BG tilemap used by the status screen */
#define STATUS_SCREEN_TILEMAP ((u16*)(VRAM_BASE + 0xC800))

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

void StatusScreenHandler(void);
void StatusScreenDrawEverything(void);
void StatusScreenDrawNumber(u8 section, u16 value, u8 palette, boolu8 isMax);
void StatusScreenDrawBeamOrSuit(u8 section, u8 value);
void StatusScreenDrawMissileOrBomb(u8 section, u8 value);
void StatusScreenDrawMisc(u8 section, u8 value);
void StatusScreenRemoveAmmoHeader(u8 position);
u8 EasySleepMenuHandler(void);

#endif /* STATUS_EASY_SLEEP_H */
