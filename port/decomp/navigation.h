#include "data/blob_pieces.h"
#ifndef NAVIGATION_H
#define NAVIGATION_H

/*
 * Navigation conversations, pause screen text, easy sleep text and navigation pop-ups
 * (asm/disasm_0x08079afc.s, 0x08079afc - 0x0807d2xx).
 */

#include "types.h"
#include "structs/menus/pause_screen.h"

/* ---------------------------------------------------------------------------------------------- */
/* Data blobs (static in src/data, src/menus/pause_screen_map.c and src/text.c; externed here)  */
/* ---------------------------------------------------------------------------------------------- */

/* static in src/data/menus/pause_debug.c (0x085766d4) */
extern const u8 sBlob_5766D4_581510[];
/* static in src/menus/pause_screen_map.c (0x0879bec0) */
/* static in src/text.c (0x0879c170) */
/* static in src/data/menus/pause_debug.c (0x08576217) */
extern const u8 sBlob_576217_576234[];
/* static in src/data/event_data.c (0x085760e8) */
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

/**
 * @brief Navigation pop-up info (0x0857bc50, 5 entries of 24 bytes)
 */
struct NavigationPopUpInfo {
    const u8* pFrames; /* (frame, duration) pairs */
    u8 frameCount;
    u8 padding_5[3];
    const u16* pPalette; /* 16 colors, faded in at obj palette row 15 */
    const u16* pFlashingColors; /* 0 terminated, written to the last obj color */
    u8 flashingColorDelay;
    u8 tiles; /* low nibble: number of tile rows, high nibble: first tile row slot */
    u8 type; /* low nibble: 8 (32x? object) or 4 */
    u8 padding_13;
    const u32* pGraphics; /* LZ77 */
};

/**
 * @brief Navigation conversation pop-ups (0x0857bcc8, 3 entries)
 */
struct NavigationPopUpConversation {
    s8 conversation;
    u8 popUps[3];
};

/*
 * PORT: 0x0857bc50, contains raw 32-bit GBA pointers; the native port has to provide a real table.
 */
#ifdef PLATFORM_PC
const struct NavigationPopUpInfo* NavigationPopUpsNative(void);
#define sNavigationPopUps (NavigationPopUpsNative())
#else
#define sNavigationPopUps ((const struct NavigationPopUpInfo*)(sBlob_5766D4_581510 + 0x557C))
#endif
#define sNavigationPopUpConversations ((const struct NavigationPopUpConversation*)(sBlob_5766D4_581510 + 0x55F4))
/* 0x0857bcd4, 0x0857bcf4, 0x0857bd34, 0x0857bdb4: u16 tables (palette animations) */
#define sNavigation_57bcd4 ((const u16*)(sBlob_5766D4_581510 + 0x5600))
#define sNavigation_57bcf4 ((const u16*)(sBlob_5766D4_581510 + 0x5620))
#define sNavigation_57bd34 ((const u16*)(sBlob_5766D4_581510 + 0x5660))
#define sNavigation_57bdb4 ((const u16*)(sBlob_5766D4_581510 + 0x56E0))
/* 0x0857beb4, 0x0857beb8, 0x0857bebc: u8 durations */
#define sNavigation_57beb4 (sBlob_5766D4_581510 + 0x57E0)
#define sNavigation_57beb8 (sBlob_5766D4_581510 + 0x57E4)
#define sNavigation_57bebc (sBlob_5766D4_581510 + 0x57E8)
/* LZ77 graphics of the special conversations (0x0857c0c4, 0x0857fca0, 0x08580238, 0x085807d0, 0x08580d68) */
#define sNavigation_57c0c4 (sBlob_5766D4_581510 + 0x59F0)
#define sNavigation_57fca0 (sBlob_5766D4_581510 + 0x95CC)
#define sNavigation_580238 (sBlob_5766D4_581510 + 0x9B64)
#define sNavigation_5807d0 (sBlob_5766D4_581510 + 0xA0FC)
#define sNavigation_580d68 (sBlob_5766D4_581510 + 0xA694)

/* 0x0857bec4: palette of the special conversation 0x35 */
#define sNavigation_57bec4 ((const u16*)(sBlob_5766D4_581510 + 0x57F0))
/* 0x08581300: u16 [6][16], animated minimap palette colors */
#define sNavigation_581300 ((const u16*)(sBlob_5766D4_581510 + 0xAC2C))
/* 0x0879c17c: u8 [4], durations of the special conversation 0x35 */
#define sNavigation_79c17c (sBlob_79c17c_79c228)
/* 0x0879c180: u8 [36], oam ids of the navigation map compass */
#define sNavigation_79c180 (((const u8*)sBlob_79c17c_79c228 + 0x4))
/* 0x0879c1a4, 0x0879c210: s8 (x offset, y offset, oam id) triples */
#define sNavigation_79c1a4 ((const s8*)(((const u8*)sBlob_79c17c_79c228 + 0x28)))
#define sNavigation_79c210 ((const s8*)(((const u8*)sBlob_79c17c_79c228 + 0x94)))

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
#define sNavigationConversationTextPointers ((const u16* const* const*)(&sPointers_79bec0[140]))
/* PORT: 0x0879c10c, per language table of pointers to the pause screen texts (indexed by event), raw GBA pointers */
#define sPauseScreenTextPointers ((const u16* const* const*)(&sPointers_79bec0[147]))

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
void PauseScreenVBLank(void);
void PauseScreenVBLank_Unused(void);

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
void NavigationConversationLoadPopUpGraphics(void);
void NavigationConversationUpdatePopUp(void);
void unk_7bde0(void);
void NavigationConversationFadeInPopUpPalette(void);
void NavigationConversationUpdateXParasitePopUp(void);
void NavigationConversationClearPopUpGraphics(void);
void unk_7c3b4(void);
void unk_7c440(void);
void NavigationConversationLoadSpecialGraphics(void);
void unk_7c630(void);
void unk_7ce6c(void);
void unk_7cfb0(void);
void unk_7d27c(void);

#endif /* NAVIGATION_H */
