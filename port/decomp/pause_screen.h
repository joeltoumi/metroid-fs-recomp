#ifndef PAUSE_SCREEN_PORT_H
#define PAUSE_SCREEN_PORT_H

#include "types.h"
#include "oam.h"

// ---------------------------------------------------------------------------
// RAM without a linker.ld name (bound in pause_screen.c with .set for GBA builds)
// ---------------------------------------------------------------------------

// 0x0300000a : pending BG3CNT value, written by PauseScreenVBLank_Unused
extern u16 gUnk_300000a;

// 0x03005400 : maintained input (auto-repeat) state
struct PauseScreenMaintainedInput {
    u8 timer;
    u8 delayIndex;
};
extern struct PauseScreenMaintainedInput gUnk_3005400;

// ---------------------------------------------------------------------------
// Data (static blobs of the decomp, externed)
// ---------------------------------------------------------------------------

// src/data/menus (static) : pause screen graphics/palettes/tilemaps
extern const u8 sBlob_5657a8_575a60[];
// src/data/event_data.c (static)
extern const u8 sBlob_5760e8_576168[];
// static blob containing navigation panel oam ids/positions
extern const u8 sBlob_5766D4_581510[];
// src/menus/pause_screen_map.c (static)
extern u8* sUnk_79be5c[11];
extern u8 sUnk_79be88[32];
// src/data/menus/pause_debug.c
extern const u8 sMaintainedInputDelays[7];

// Pointers to the frame data of every pause screen oam id (0x0879bec0)
#ifdef PLATFORM_PC
// PORT: in the ROM this is a blob of raw 32 bit ROM pointers (sBlob_79bec0_79c128),
// the native build must provide it as a real pointer table.
extern const struct FrameData* const sPauseScreenOamFramePointers[];
#else
extern u8 sBlob_79bec0_79c128[];
#define sPauseScreenOamFramePointers ((const struct FrameData* const*)sBlob_79bec0_79c128)
#endif

#define PAUSE_SCREEN_BLOB(offset) (&sBlob_5657a8_575a60[(offset)])

#define sPauseScreenBgPal_Base PAUSE_SCREEN_BLOB(0x0)                 // 0x085657a8
#define sPauseScreenBgPal_Status PAUSE_SCREEN_BLOB(0x60)              // 0x08565808
#define sPauseScreenBgPal_Map PAUSE_SCREEN_BLOB(0x200)                // 0x085659a8
#define sPauseScreenObjPal PAUSE_SCREEN_BLOB(0x3A0)                   // 0x08565b48
#define sPauseScreenSuitPal PAUSE_SCREEN_BLOB(0x5A0)                  // 0x08565d48
#define sPauseScreenStatusGfx PAUSE_SCREEN_BLOB(0x4AAC)               // 0x0856a254
#define sPauseScreenMapGfx PAUSE_SCREEN_BLOB(0x70C0)                  // 0x0856c868
#define sPauseScreenOtherGfx PAUSE_SCREEN_BLOB(0x86D8)                // 0x0856de80
#define sPauseScreenObjGfx PAUSE_SCREEN_BLOB(0x9F74)                  // 0x0856f71c
#define sPauseScreenTilemap_e5fc PAUSE_SCREEN_BLOB(0xE5FC)            // 0x08573da4
#define sPauseScreenTilemap_e6f8 PAUSE_SCREEN_BLOB(0xE6F8)            // 0x08573ea0
#define sPauseScreenTilemap_e954 PAUSE_SCREEN_BLOB(0xE954)            // 0x085740fc
#define sPauseScreenTilemap_eb40 PAUSE_SCREEN_BLOB(0xEB40)            // 0x085742e8
#define sPauseScreenTilemap_ee00 PAUSE_SCREEN_BLOB(0xEE00)            // 0x085745a8
#define sPauseScreenTilemap_f104 PAUSE_SCREEN_BLOB(0xF104)            // 0x085748ac
#define sPauseScreenTilemap_f5a0 PAUSE_SCREEN_BLOB(0xF5A0)            // 0x08574d48
#define sPauseScreenTilemap_fc40 PAUSE_SCREEN_BLOB(0xFC40)            // 0x085753e8

// 0x08576142 : u8 pairs indexed by area, [1] = area name oam id
#define sPauseScreenAreaNameOamIds (&sBlob_5760e8_576168[0x5A])
// 0x08576150 : 4 u8 pairs {oam slot, oam id} (security levels)
#define sPauseScreenSecurityOam (&sBlob_5760e8_576168[0x68])

// 0x08576158 : map screen arrows
struct PauseScreenArrowInfo {
    u8 oamSlot;
    u8 oamId;
    u8 xPosition;
    u8 yPosition;
};
#define sPauseScreenMapArrows ((const struct PauseScreenArrowInfo*)&sBlob_5760e8_576168[0x70])

// 0x085766e0 : u8 y positions of the navigation text panel cursor
#define sPauseScreenNavPanelYPositions (&sBlob_5766D4_581510[0xC])
// 0x085767f0 : 3 byte entries {oam8 id, oam9 id, oam7 id}
#define sPauseScreenNavPanelOamIds (&sBlob_5766D4_581510[0x11C])

// sUnk_79be88 : 8 entries {oam slot, oam id, x, y} (status screen tanks)
struct PauseScreenTankOamInfo {
    u8 oamSlot;
    u8 oamId;
    u8 xPosition;
    u8 yPosition;
};

// ---------------------------------------------------------------------------
// Functions still in asm / not declared in the decomp headers
// ---------------------------------------------------------------------------
u32 EasySleepMenuHandler(void);
void ProcessPauseScreenText(void);
void ProcessEasySleepText(void);
void NavigationConversationGetCurrentConversation(void);
void NavigationConversationLoadPopUpGraphics(void);
void NavigationConversationLoadSpecialGraphics(void);
void NavigationConversationUpdatePopUp(void);
u32 NavigationConversationHandler(void);
void unk_7c440(void);
void unk_7c630(void);
void unk_7ce6c(void);
void unk_7cfb0(void);

// ---------------------------------------------------------------------------
// This file
// ---------------------------------------------------------------------------
u32 PauseScreenHandler(void);
void PauseScreenVBLank(void);
void PauseScreenVBLank_Unused(void);
void PauseScreenInitVBlank(void);
u8 PauseScreenInit(void);
void GetMinimapData(u8 area, void* dst);
u32 PauseScreenCallCurrentHandler(void);
void PauseScreenMoveDebugCursor(void);
u32 PauseScreenMoveBackgroundToXPosition(u8 bg, u16 target);
u32 PauseScreenMoveBackgroundToYPosition(u8 bg, u16 target);
void PauseScreenSetPauseDebugWindow(void);
u32 PauseDebugWindowAppearing(void);
u32 PauseDebugWindowDisappearing(void);
u32 EasySleepMenuInit(void);
u32 EasySleepMenuQuit(void);
void unk_77840(u8 request);
void MapScreenUpdateArrowsAndBlinkingSquare(void);
void MapScreenDrawSpecialOam(u8 mode);
void PauseScreenSetupOam(void);
void PauseScreenProcessOam(void);
void CheckForMaintainedInput(void);
void unk_78af0(u8 arg0);
void PauseScreenSetNavigationTextPanelOam(u8 arg0);
void unk_78c44(void);
void NavigationConversationUpdatePanel(void);

#endif /* PAUSE_SCREEN_PORT_H */
