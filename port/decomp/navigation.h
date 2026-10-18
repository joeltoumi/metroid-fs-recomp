#ifndef NAVIGATION_H
#define NAVIGATION_H

/*
 * Navigation conversations, pause screen text, easy sleep text and navigation pop-ups
 * (asm/disasm_0x08079afc.s, 0x08079afc - 0x0807d2xx).
 */

#include "types.h"
#include "structs/menus/pause_screen.h"

/* ---------------------------------------------------------------------------------------------- */
/* Data blobs (static in src/data / src/*.c, externed here)                                       */
/* ---------------------------------------------------------------------------------------------- */

/* static in src/data/menus/pause_debug.c (0x085766d4) */
extern const u8 sBlob_5766D4_581510[];
/* static in src/menus/pause_screen_map.c (0x0879bec0) */
extern u8 sBlob_79bec0_79c128[];
/* static in src/text.c (0x0879c170) */
extern u8 sBlob_79c170_79c27c[];
/* src/data (0x08576217) */
extern const u8 sBlob_576217_576234[];
/* src/data (0x085760e8) */
extern const u8 sBlob_5760e8_576168[];

/**
 * @brief Navigation target info (0x085766e4, 33 entries of 8 bytes)
 */
struct NavigationTargetInfo {
    s8 conversation;
    u8 location;
    u8 xPosition;
    u8 yPosition;
    u8 textDirection;
    u8 padding_5[3];
};

/* 0x085766e0: u8 pairs, Y position of the text cursor object per text line (indexed by line * 2) */
#define sNavigationTextCursorYPositions (sBlob_5766D4_581510 + 0xC)
/* 0x085766e4 */
#define sNavigationTargetInfo ((const struct NavigationTargetInfo*)(sBlob_5766D4_581510 + 0x10))
/* 0x085767ec: navigation target arrow oam ids, indexed by text direction */
#define sNavigationTargetArrowOamIds (sBlob_5766D4_581510 + 0x118)
/* 0x08576802: final mosaic value */
#define sNavigationMosaicTarget (sBlob_5766D4_581510 + 0x12E)
/* 0x08576218: (x, y) map position of the navigation room of each area (when the target is in another area) */
#define sNavigationAreaNavRoomPositions (sBlob_576217_576234 + 0x1)
/* 0x08576226: (x, y) map position of the main deck elevator of each area */
#define sNavigationAreaElevatorPositions (sBlob_576217_576234 + 0xF)

/*
 * PORT: 0x0879c0f0, per language table of pointers to the navigation conversation texts.
 * This blob holds raw 32-bit GBA pointers; the native port has to provide a real pointer table here.
 */
#define sNavigationConversationTextPointers ((const u16* const* const*)(sBlob_79bec0_79c128 + 0x230))
/* PORT: 0x0879c10c, per language table of pointers to the pause screen texts (indexed by event), raw GBA pointers */
#define sPauseScreenTextPointers ((const u16* const* const*)(sBlob_79bec0_79c128 + 0x24C))

/* ---------------------------------------------------------------------------------------------- */
/* RAM without a linker.ld name                                                                    */
/* ---------------------------------------------------------------------------------------------- */

/* 0x0300004c, navigation target location (enum NavigationTargetLocation) */
extern u8 gNavigationTargetLocation;
/* 0x0300004d */
extern u8 gUnk_300004d;
/* 0x0300000a */
extern u16 gUnk_300000a;

/* ---------------------------------------------------------------------------------------------- */
/* Functions still in asm elsewhere (disasm_0x080765f8.s)                                          */
/* ---------------------------------------------------------------------------------------------- */

void GetMinimapData(u8 area, void* dst);
void PauseScreenSetNavigationTextPanelOam(u8 arg0);
void unk_78c44(void);
void NavigationConversationUpdatePanel(void);

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

void NavigationConversationProcessText(void);
u32 unk_7a0fc(u8 line);
void NavigationConversationGetCurrentConversation(void);
u32 NavigationConversationHandler(void);
void NavigationConversationSetupOam(void);
void NavigationConversationUpdateTarget(u8 updateArrow);
u32 NavigationConverstionFindTarget(void);
void NavigationConversionScrollToTarget(void);
u32 NavigationConversationScrollMapToDestination(u8 xPosition, u8 yPosition);
void unk_7b56c(void);
void unk_7b674(void);
void ProcessPauseScreenText(void);
void ProcessEasySleepText(void);
u8 GetFlashingSectorNumber(void);

#endif /* NAVIGATION_H */
