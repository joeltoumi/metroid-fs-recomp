#include "pause_screen.h"
#include "globals.h"
#include "macros.h"
#include "gba.h"

#include "callbacks.h"
#include "dma.h"
#include "init_helpers.h"
#include "music_wrappers.h"
#include "audio_wrappers.h"
#include "audio/track_internal.h"
#include "syscall_wrappers.h"
#include "event.h"
#include "oam_id.h"
#include "room.h"
#include "status_screen.h"
#include "menus/pause_screen_map.h"
#include "menus/pause_debug.h"

#include "data/menus/pause_screen_map_data.h"

#include "structs/connection.h"
#include "structs/display.h"
#include "structs/event.h"
#include "structs/minimap.h"
#include "structs/samus.h"

#ifndef PLATFORM_PC
asm(".set gUnk_300000a, 0x0300000a");
asm(".set gUnk_3005400, 0x03005400");
#endif // !PLATFORM_PC

#define PAUSE_SCREEN_STAGE (gUnk_3000b85)

// Sub stage of the various pause screen menus
#define PAUSE_SCREEN_SUB_STAGE (PAUSE_SCREEN_DATA.pauseDebugEditingValue)

#define DCNT_PAUSE_BG0 0x100

/**
 * @brief 765f8 | 2ac | Pause screen main loop
 *
 * @return u32 bool, leaving
 */
u32 PauseScreenHandler(void)
{
    u32 leaving;
    u16 step;
    u16 bldalpha;

    gNextOamSlot = 0;
    leaving = FALSE;

    switch (PAUSE_SCREEN_STAGE)
    {
        case 0:
            PAUSE_SCREEN_STAGE = PauseScreenInit();
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.unk_0 != 0)
            {
                if (gPauseScreenFlag == 4)
                    step = 1;
                else
                    step = 2;

                if ((gWrittenToBldalpha_Evb << 8 | gWrittenToBldalpha_Eva) == C_16_2_8(5, 8))
                {
                    PAUSE_SCREEN_STAGE++;
                    WRITE_16(REG_BLDCNT, 0x3F44);
                }
                else
                {
                    if (gWrittenToBldalpha_Eva != 8)
                    {
                        gWrittenToBldalpha_Eva += step;
                        if (gWrittenToBldalpha_Eva > 8)
                            gWrittenToBldalpha_Eva = 8;
                    }

                    if (gWrittenToBldalpha_Evb != 5)
                        gWrittenToBldalpha_Evb++;
                }

                WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            }
            else
            {
                if (gWrittenToBldy == 0)
                {
                    PAUSE_SCREEN_STAGE++;
                    WRITE_16(REG_BLDCNT, 0x3F00);
                    WRITE_16(REG_BLDALPHA, C_16_2_8(4, 12));
                }
                else if (gWrittenToBldy > 4)
                {
                    gWrittenToBldy -= 4;
                }
                else
                {
                    gWrittenToBldy = 0;
                }
            }
            break;

        case 2:
            if (PauseScreenCallCurrentHandler())
            {
                if (PAUSE_SCREEN_DATA.unk_0 != 0)
                {
                    WRITE_16(REG_BLDCNT, 0x3F7F);
                    bldalpha = READ_16(REG_BLDALPHA);
                    gWrittenToBldalpha_Evb = bldalpha >> 8;
                    gWrittenToBldalpha_Eva = bldalpha & 0xFF;
                }
                else
                {
                    gWrittenToBldy = 0;
                    WRITE_16(REG_BLDCNT, 0xFF);
                }

                PAUSE_SCREEN_STAGE++;
            }

            if (PAUSE_SCREEN_DATA.unk_264 == 0)
            {
                unk_7c440();
                unk_7cfb0();
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_0 != 0)
            {
                if (gPauseScreenFlag == 4)
                    step = 1;
                else
                    step = 2;

                if (gWrittenToBldalpha_Evb | gWrittenToBldalpha_Eva)
                {
                    if (gWrittenToBldalpha_Eva >= step)
                        gWrittenToBldalpha_Eva -= step;
                    else
                        gWrittenToBldalpha_Eva = 0;

                    if (gWrittenToBldalpha_Evb != 0)
                        gWrittenToBldalpha_Evb--;
                }
                else
                {
                    PAUSE_SCREEN_STAGE++;
                }

                WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            }
            else
            {
                if (gWrittenToBldy < 16)
                {
                    gWrittenToBldy += 4;
                    if (gWrittenToBldy > 16)
                        gWrittenToBldy = 16;
                }
                else
                {
                    PAUSE_SCREEN_STAGE++;
                }
            }
            break;

        case 4:
            if (gPauseScreenFlag == 3 && gEventCounter == 0x61 && gPreviousCutscene != 7)
            {
                gPauseScreenFlag = 5;
                gCurrentCutscene = 7;
                DmaTransfer(3, gCommonSpriteGfxBackup, VRAM_OBJ, 0x8000, 32);
            }

            leaving = TRUE;
            PAUSE_SCREEN_STAGE = 0;
            break;
    }

    MapScreenUpdateArrowsAndBlinkingSquare();
    PauseScreenProcessOam();
    ResetFreeOam();

    return leaving;
}

/**
 * @brief 768a4 | 84 | Pause screen V-blank
 *
 */
void PauseScreenVBLank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    WRITE_16(REG_DISPCNT, PAUSE_SCREEN_DATA.dispcnt);
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_MOSAIC, gWrittenToMosaic_L);

    WRITE_16(REG_BG0HOFS, gBackgroundPositions.bg[0].x);
    WRITE_16(REG_BG0HOFS + 2, gBackgroundPositions.bg[0].y);
    WRITE_16(REG_BG0HOFS + 4, gBackgroundPositions.bg[1].x);
    WRITE_16(REG_BG0HOFS + 6, gBackgroundPositions.bg[1].y);
    WRITE_16(REG_BG0HOFS + 8, gBackgroundPositions.bg[2].x);
    WRITE_16(REG_BG0HOFS + 10, gBackgroundPositions.bg[2].y);
    WRITE_16(REG_BG0HOFS + 12, gBackgroundPositions.bg[3].x);
    WRITE_16(REG_BG0HOFS + 14, gBackgroundPositions.bg[3].y);
}

/**
 * @brief 76928 | 5c | Pause screen V-blank (unused)
 *
 */
void PauseScreenVBLank_Unused(void)
{
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_DISPCNT, PAUSE_SCREEN_DATA.dispcnt);

    if (gUnk_300000a != 0)
    {
        WRITE_16(REG_BG3CNT, gUnk_300000a);
        gUnk_300000a = 0;
    }

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
}

/**
 * @brief 76984 | c | Pause screen V-blank during the initialization
 *
 */
void PauseScreenInitVBlank(void)
{
    UpdateAudio();
}

/**
 * @brief 76990 | 6f4 | Initializes the pause screen
 *
 * @return u8 Next pause screen stage (1)
 */
u8 PauseScreenInit(void)
{
    u32 suitPal;
    u32 zero;
    s32 i;

    CallbackSetVBlank(PauseScreenInitVBlank);

    WRITE_16(REG_BLDCNT, 0xFF);
    gWrittenToBldy = 16;
    WRITE_16(REG_BLDY, 16);
    WRITE_16(REG_DISPCNT, 0);
    PAUSE_SCREEN_DATA.dispcnt = 0;

    gNextOamSlot = 0;
    BitFill(3, 0, &gNonGameplayRam, sizeof(gNonGameplayRam), 32);
    ResetFreeOam();
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    if (gPauseScreenFlag != 4)
        DmaTransfer(3, VRAM_OBJ, gCommonSpriteGfxBackup, 0x8000, 16);

    PAUSE_SCREEN_DATA.currentArea = gCurrentArea;
    PAUSE_SCREEN_DATA.mapX = gMinimapX;
    PAUSE_SCREEN_DATA.mapY = gMinimapY;
    PAUSE_SCREEN_DATA.enableDebug = FALSE;
    PAUSE_SCREEN_DATA.unk_0 = 1;

    if (gPauseScreenFlag == 3)
    {
        if (gCurrentArea == 0 && gCurrentRoom == 0)
            PAUSE_SCREEN_DATA.unk_0 = 2;
    }
    else if (gPauseScreenFlag == 1)
    {
        PAUSE_SCREEN_DATA.unk_0 = 2;
        unk_36c4();
    }
    else if (gPauseScreenFlag != 4)
    {
        PAUSE_SCREEN_DATA.unk_0 = 0;
    }

    DMA3_COPY_16(sPauseScreenBgPal_Base, PALRAM_BASE, 0x30);
    CallLZ77UncompVram(sPauseScreenObjGfx, VRAM_OBJ);
    DmaTransfer(3, sMinimapTilesGfx, VRAM_BASE + 0x8000, sizeof(sMinimapTilesGfx), 16);
    DMA3_COPY_16(sPauseScreenObjPal, PALRAM_OBJ, 0x100);

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
    {
        CallLZ77UncompVram(sPauseScreenStatusGfx, VRAM_BASE);
        DMA3_COPY_16(sPauseScreenBgPal_Status, PALRAM_BASE + 0x60, 0xD0);
    }
    else if (PAUSE_SCREEN_DATA.unk_0 == 1)
    {
        CallLZ77UncompVram(sPauseScreenMapGfx, VRAM_BASE);

        if (gEquipment.suitMiscStatus & 0x20)
            suitPal = 2;
        else
            suitPal = (gEquipment.suitMiscStatus & 0x10) ? 1 : 0;

        if (suitPal != 0)
            DMA3_COPY_16(sPauseScreenSuitPal + suitPal * PAL_ROW_SIZE, PALRAM_OBJ, 0x10);
    }
    else
    {
        CallLZ77UncompVram(sPauseScreenOtherGfx, VRAM_BASE);
    }

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        DMA3_COPY_16(VRAM_BASE + 0x9800, VRAM_BASE + 0x9400, 0x200);
        DMA3_COPY_16(sPauseScreenBgPal_Map, PALRAM_BASE + 0x60, 0xD0);
    }

    WRITE_16(PALRAM_BASE, 0);

    GetMinimapData(10, EWRAM_BASE + 0x34800);
    DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xE800, 0x400);
    DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xF000, 0x400);
    DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xF800, 0x400);
    DMA3_COPY_16(EWRAM_BASE + 0x34000, VRAM_BASE + 0xE000, 0x400);

    CallLZ77UncompVram(sPauseScreenTilemap_eb40, EWRAM_BASE + 0xF800);
    DMA3_COPY_16(EWRAM_BASE + 0xF800, VRAM_BASE + 0xC000, 0x400);

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
    {
        if (PAUSE_SCREEN_DATA.enableDebug)
            CallLZ77UncompVram(sPauseScreenTilemap_e6f8, EWRAM_BASE + 0x34800);
        else
            CallLZ77UncompVram(sPauseScreenTilemap_f104, EWRAM_BASE + 0x34800);

        DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xC800, 0x400);
    }
    else
    {
        if (PAUSE_SCREEN_DATA.unk_0 == 1)
            CallLZ77UncompVram(sPauseScreenTilemap_f5a0, EWRAM_BASE + 0x34800);
        else
            CallLZ77UncompVram(sPauseScreenTilemap_fc40, EWRAM_BASE + 0x34800);

        DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xD800, 0x400);
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
    {
        CallLZ77UncompVram(sPauseScreenTilemap_e954, EWRAM_BASE + 0x34800);
        DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xD000, 0x400);
        CallLZ77UncompVram(sPauseScreenTilemap_ee00, EWRAM_BASE + 0x10000);
    }
    else
    {
        // Same tilemap regardless of gPauseScreenFlag
        CallLZ77UncompVram(sPauseScreenTilemap_e5fc, EWRAM_BASE + 0x34800);
        DMA3_COPY_16(EWRAM_BASE + 0x34800, VRAM_BASE + 0xD000, 0x400);
    }

    GetMinimapData(gCurrentArea, EWRAM_BASE + 0x34800);

    for (i = 3; i >= 0; i--)
    {
        gBackgroundPositions.bg[3 - i].x = 0;
        gBackgroundPositions.bg[3 - i].y = 0;
    }

    PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
    PAUSE_SCREEN_DATA.unk_9 = 0;
    PAUSE_SCREEN_DATA.timer = 0;
    PAUSE_SCREEN_DATA.unk_8 = 0;

    PAUSE_SCREEN_DATA.unk_28 = sUnk_79be88[0];
    PAUSE_SCREEN_DATA.unk_29 = sUnk_79be88[1];
    PAUSE_SCREEN_DATA.unk_2A = sUnk_79be88[2];
    PAUSE_SCREEN_DATA.unk_2B = sUnk_79be88[3];

    gBackgroundPositions.bg[1].y = 0x100;

    PAUSE_SCREEN_DATA.unk_1 = 3;
    if (PAUSE_SCREEN_DATA.unk_0 != 0)
        PAUSE_SCREEN_DATA.unk_1 = 1;
    else if (gPauseScreenFlag == 2)
        PAUSE_SCREEN_DATA.unk_1 = 0;
    else
        PAUSE_SCREEN_DATA.unk_1 = 2;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        if (EventCheckSetNavigationRoomEvent())
        {
            PAUSE_SCREEN_DATA.unk_28 = 4;
            GetMinimapData(gCurrentArea, EWRAM_BASE + 0x34000);
            MinimapSetVisitedTilesAndCollectedItems(gCurrentArea);
        }
        else
        {
            PAUSE_SCREEN_DATA.unk_28 = 10;
        }

        if (gEventCounter <= 0x5B)
        {
            zero = 0;
            DMA_SET(3, &zero, VRAM_BASE + 0x17C00, C_32_2_16(DMA_ENABLE | DMA_32BIT | DMA_SRC_FIXED, 0x10));
        }
    }

    if (PAUSE_SCREEN_DATA.enableDebug)
        PauseDebugDrawEverything();
    else
        StatusScreenDrawEverything();

    unk_75988(FALSE);
    ProcessPauseScreenText();
    ProcessEasySleepText();
    PauseScreenSetupOam();
    NavigationConversationGetCurrentConversation();
    NavigationConversationLoadPopUpGraphics();
    NavigationConversationLoadSpecialGraphics();
    unk_77840(0xFF);
    unk_7ce6c();

    WRITE_16(REG_BG0HOFS, gBackgroundPositions.bg[0].x);
    WRITE_16(REG_BG0HOFS + 2, gBackgroundPositions.bg[0].y);
    WRITE_16(REG_BG0HOFS + 4, gBackgroundPositions.bg[1].x);
    WRITE_16(REG_BG0HOFS + 6, gBackgroundPositions.bg[1].y);
    WRITE_16(REG_BG0HOFS + 8, gBackgroundPositions.bg[2].x);
    WRITE_16(REG_BG0HOFS + 10, gBackgroundPositions.bg[2].y);
    WRITE_16(REG_BG0HOFS + 12, gBackgroundPositions.bg[3].x);
    WRITE_16(REG_BG0HOFS + 14, gBackgroundPositions.bg[3].y);

    gWrittenToBldy = 0;
    gWrittenToBldalpha_Evb = 0;
    gWrittenToBldalpha_Eva = 16;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        gWrittenToBldalpha_Evb = 0;
        gWrittenToBldalpha_Eva = 0;
        WRITE_16(REG_BLDCNT, 0x3F7F);
        WRITE_16(REG_BLDALPHA, 0);
    }
    else
    {
        gWrittenToBldy = 16;
        WRITE_16(REG_BLDCNT, 0xFF);
    }

    WRITE_16(REG_WIN0H, 0xF0);

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        WRITE_8(REG_WINOUT, 0x37);
        WRITE_8(REG_WININ + 1, 0x3F);
    }
    else
    {
        WRITE_8(REG_WINOUT, 0x35);
        WRITE_8(REG_WININ + 1, 0x3D);
    }
    WRITE_8(REG_WININ, 0x3F);

    WRITE_16(REG_WIN0V, (PAUSE_SCREEN_DATA.unk_28 != 1 ? 0xA0 : 0) << 8 | 0xA0);
    WRITE_16(REG_WIN1H, 0xF0);
    WRITE_16(REG_WIN1V, 0xA0);

    gWrittenToMosaic_L = 0;
    WRITE_16(REG_MOSAIC, 0);

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        WRITE_16(REG_BG1CNT, 0x1B03);
        WRITE_16(REG_BG3CNT, 0xDC49);
        WRITE_16(REG_BG0CNT, 0x1800);
        PAUSE_SCREEN_DATA.dispcnt = 0x5F00;

        WRITE_16(REG_BG2CNT, 0x1A0A);
        if (gPauseScreenFlag == 4)
            PAUSE_SCREEN_DATA.dispcnt = 0x5F00 ^ 0x800;
    }
    else
    {
        WRITE_16(REG_BG3CNT, 0xDC4B);
        WRITE_16(REG_BG2CNT, 0x1A02);
        WRITE_16(REG_BG0CNT, 0x1801);
        WRITE_16(REG_BG1CNT, 0x1900);
        PAUSE_SCREEN_DATA.dispcnt = 0x7E00;
    }

    CallbackSetVBlank(PauseScreenVBLank);
    WRITE_16(REG_DISPCNT, PAUSE_SCREEN_DATA.dispcnt);

    return 1;
}

/**
 * @brief 77084 | 30 | Decompresses the minimap data of an area
 *
 * @param area Area
 * @param dst Destination
 */
void GetMinimapData(u8 area, void* dst)
{
    if (area == 0 && gEventCounter > 0x5D)
        area = 9;

    CallLZ77UncompVram(sUnk_79be5c[area], dst);
}

/**
 * @brief 770b4 | 1bc | Calls the current pause screen sub-handler
 *
 * @return u32 bool, leaving
 */
u32 PauseScreenCallCurrentHandler(void)
{
    u32 leaving;

    leaving = FALSE;

    if ((u8)(PAUSE_SCREEN_DATA.unk_28 - 2) > 1)
        CheckForMaintainedInput();

    PAUSE_SCREEN_DATA.timer++;

    switch (PAUSE_SCREEN_DATA.unk_28)
    {
        case 0:
            if (gChangedInput & (gButtonAssignments.pause | KEY_B))
                leaving = TRUE;
            else
                PauseScreenMapHandler();
            break;

        case 2:
            leaving = TRUE;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.enableDebug)
            {
                PauseScreenMoveDebugCursor();
                PauseDebugHandler();
            }
            else
            {
                StatusScreenHandler();
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_264 != 0)
            {
                unk_7c630();
            }
            else
            {
                NavigationConversationUpdatePopUp();
                if (NavigationConversationHandler())
                    PAUSE_SCREEN_DATA.unk_28 = 9;
            }
            break;

        case 4:
            if (PauseScreenMapDownload())
                PAUSE_SCREEN_DATA.unk_28 = 8;
            break;

        case 5:
            if (EasySleepMenuHandler())
                PAUSE_SCREEN_DATA.unk_28 = 12;
            break;

        case 6:
            if (PauseDebugWindowAppearing())
            {
                PAUSE_SCREEN_DATA.unk_28 = 1;
                PAUSE_SCREEN_SUB_STAGE = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 7:
            if (PauseDebugWindowDisappearing())
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                PAUSE_SCREEN_SUB_STAGE = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 8:
        case 10:
            PAUSE_SCREEN_DATA.unk_28 = 3;
            PAUSE_SCREEN_DATA.unk_C = 0;
            PAUSE_SCREEN_DATA.unk_E[0] = 0;
            PAUSE_SCREEN_DATA.unk_E[1] = 0;
            PAUSE_SCREEN_DATA.unk_E[2] = 0;
            PAUSE_SCREEN_DATA.unk_E[3] = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9 = 0;
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B = 0;
            PAUSE_SCREEN_SUB_STAGE = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 9:
            if (PAUSE_SCREEN_DATA.unk_0 != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 2;
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                unk_77840(4);
            }
            break;

        case 11:
            if (EasySleepMenuInit())
            {
                PAUSE_SCREEN_DATA.unk_28 = 5;
                PAUSE_SCREEN_SUB_STAGE = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 12:
            if (EasySleepMenuQuit())
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                PAUSE_SCREEN_SUB_STAGE = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;
    }

    return leaving;
}

/**
 * @brief 77270 | a8 | Moves the pause debug cursor
 *
 */
void PauseScreenMoveDebugCursor(void)
{
    if (gButtonInput & KEY_A || PAUSE_SCREEN_SUB_STAGE != 0)
        return;

    if (gChangedInput & KEY_UP)
    {
        if (PAUSE_SCREEN_DATA.oam[0].yPosition != 0)
            PAUSE_SCREEN_DATA.oam[0].yPosition -= 8;
    }
    else if (gChangedInput & KEY_DOWN)
    {
        if (PAUSE_SCREEN_DATA.oam[0].yPosition < 0x90)
            PAUSE_SCREEN_DATA.oam[0].yPosition += 8;
    }

    if (gChangedInput & KEY_RIGHT)
    {
        if (PAUSE_SCREEN_DATA.oam[0].xPosition < 0xE8)
            PAUSE_SCREEN_DATA.oam[0].xPosition += 8;
    }
    else if (gChangedInput & KEY_LEFT)
    {
        if (PAUSE_SCREEN_DATA.oam[0].xPosition != 0)
            PAUSE_SCREEN_DATA.oam[0].xPosition -= 8;
    }
}

/**
 * @brief 77318 | 6c | Moves a background towards an X position
 *
 * @param bg Background
 * @param target Target position
 * @return u32 bool, reached
 */
u32 PauseScreenMoveBackgroundToXPosition(u8 bg, u16 target)
{
    u32 reached;
    s32 direction;
    s32 speed;

    reached = FALSE;
    direction = 1;
    if (gBackgroundPositions.bg[bg].x > target)
        direction = -1;

    speed = PAUSE_SCREEN_DATA.timer + 4;
    if (speed < 32)
        speed *= direction;
    else
        speed = direction * 32;

    gBackgroundPositions.bg[bg].x += speed;

    if (direction > 0)
    {
        if (gBackgroundPositions.bg[bg].x >= target)
        {
            gBackgroundPositions.bg[bg].x = target;
            reached = TRUE;
        }
    }
    else
    {
        if ((s16)gBackgroundPositions.bg[bg].x <= target)
        {
            gBackgroundPositions.bg[bg].x = target;
            reached = TRUE;
        }
    }

    return reached;
}

/**
 * @brief 77384 | 74 | Moves a background towards a Y position
 *
 * @param bg Background
 * @param target Target position
 * @return u32 bool, reached
 */
u32 PauseScreenMoveBackgroundToYPosition(u8 bg, u16 target)
{
    u32 reached;
    s32 direction;
    s32 speed;

    reached = FALSE;
    direction = 1;
    if (gBackgroundPositions.bg[bg].y > target)
        direction = -1;

    speed = PAUSE_SCREEN_DATA.timer + 4;
    if (speed < 32)
        speed *= direction;
    else
        speed = direction * 32;

    gBackgroundPositions.bg[bg].y += speed;

    if (direction > 0)
    {
        if (gBackgroundPositions.bg[bg].y >= target)
            reached = TRUE;
    }
    else
    {
        if ((s16)gBackgroundPositions.bg[bg].y <= target)
            reached = TRUE;
    }

    if (reached)
        gBackgroundPositions.bg[bg].y = target;

    return reached;
}

/**
 * @brief 773f8 | 28 | Sets the window used by the pause debug menu
 *
 */
void PauseScreenSetPauseDebugWindow(void)
{
    s32 top;

    top = 0x200 - gBackgroundPositions.bg[1].y;
    if (top > 0xA0)
        top = 0xA0;

    WRITE_16(REG_WIN0V, top << 8 | 0xA0);
}

/**
 * @brief 77420 | 80 | Handles the pause debug window appearing
 *
 * @return u32 bool, ended
 */
u32 PauseDebugWindowAppearing(void)
{
    u32 ended;

    ended = FALSE;

    switch (PAUSE_SCREEN_SUB_STAGE)
    {
        case 0:
            SoundPlay(0x200);
            UpdateMenuOamDataId(16, 0x29);
            PAUSE_SCREEN_SUB_STAGE = 2;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer > 16)
            {
                PAUSE_SCREEN_SUB_STAGE = 2;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 2:
            if (PauseScreenMoveBackgroundToYPosition(1, 0x200))
            {
                UpdateMenuOamDataId(16, 0x28);
                UpdateMenuOamDataId(17, 0x2A);
                unk_77840(3);

                if (PAUSE_SCREEN_DATA.enableDebug)
                    PauseDebugSetupCursor();

                ended = TRUE;
            }

            PauseScreenSetPauseDebugWindow();
            break;
    }

    return ended;
}

/**
 * @brief 774a0 | 60 | Handles the pause debug window disappearing
 *
 * @return u32 bool, ended
 */
u32 PauseDebugWindowDisappearing(void)
{
    u32 ended;

    ended = FALSE;

    switch (PAUSE_SCREEN_SUB_STAGE)
    {
        case 0:
            SoundPlay(0x201);
            unk_77840(4);
            PAUSE_SCREEN_SUB_STAGE = 2;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer > 4)
            {
                PAUSE_SCREEN_SUB_STAGE = 2;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 2:
            if (PauseScreenMoveBackgroundToYPosition(1, 0x100))
                ended = TRUE;

            PauseScreenSetPauseDebugWindow();
            break;
    }

    return ended;
}

/**
 * @brief 77500 | 220 | Initializes the easy sleep menu
 *
 * @return u32 bool, ended
 */
u32 EasySleepMenuInit(void)
{
    u32 ended;

    ended = FALSE;

    switch (PAUSE_SCREEN_SUB_STAGE)
    {
        case 0:
            SoundPlay(0x202);
            UpdateMenuOamDataId(17, 0x2B);
            unk_77840(3);
            break;

        case 1:
            DMA3_COPY_16(EWRAM_BASE + 0x10000, VRAM_BASE + 0xC000, 0x400);
            break;

        case 2:
            WRITE_16(REG_BLDCNT, 0x3FFE);
            WRITE_16(REG_BLDALPHA, 16);
            break;

        case 3:
            DMA3_COPY_16(EWRAM_BASE + 0xF000, EWRAM_BASE + 0xD380, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF400, EWRAM_BASE + 0xD780, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF080, EWRAM_BASE + 0xDB80, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF480, EWRAM_BASE + 0xDF80, 0x40);
            break;

        case 4:
            DMA3_COPY_16(EWRAM_BASE + 0xF1C0, EWRAM_BASE + 0xE380, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF5C0, EWRAM_BASE + 0xE780, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF240, EWRAM_BASE + 0xEB80, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF640, EWRAM_BASE + 0xEF80, 0x40);
            break;

        case 5:
            DmaTransfer(3, EWRAM_BASE + 0xD000, VRAM_BASE + 0x6000, 0x1000, 16);
            break;

        case 6:
            DmaTransfer(3, EWRAM_BASE + 0xE000, VRAM_BASE + 0x7000, 0x1000, 16);
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.timer > 1)
            {
                PAUSE_SCREEN_DATA.timer = 0;

                if (gWrittenToBldy < 12)
                {
                    gWrittenToBldy++;
                    if (gWrittenToBldy == 6)
                    {
                        PAUSE_SCREEN_DATA.dispcnt |= DCNT_PAUSE_BG0;
                        UpdateMenuOamDataId(1, 2);
                        PAUSE_SCREEN_DATA.oam[1].xPosition = 0x8C;
                        PAUSE_SCREEN_DATA.oam[1].yPosition = 0x44;
                        PAUSE_SCREEN_DATA.oam[1].objMode = 1;
                    }
                }
                else
                {
                    UpdateMenuOamDataId(16, 0x28);
                    UpdateMenuOamDataId(17, 0x2A);
                    break;
                }
            }
            return ended;

        case 8:
            gDisableSoftReset = TRUE;
            ended = TRUE;
            PAUSE_SCREEN_SUB_STAGE = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            return ended;

        default:
            return ended;
    }

    PAUSE_SCREEN_SUB_STAGE++;
    PAUSE_SCREEN_DATA.timer = 0;
    return ended;
}

/**
 * @brief 77720 | 120 | Quits the easy sleep menu
 *
 * @return u32 bool, ended
 */
u32 EasySleepMenuQuit(void)
{
    u32 ended;

    ended = FALSE;

    // Note: in the original, the paths that don't advance check a register (r6)
    // that is never initialized; its value comes from the caller
    // (PauseScreenCallCurrentHandler), where it is always 0, so they never advance.

    switch (PAUSE_SCREEN_SUB_STAGE)
    {
        case 0:
            gDisableSoftReset = FALSE;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer <= 1)
                return ended;

            PAUSE_SCREEN_DATA.timer = 0;
            if (gWrittenToBldy == 0)
                break;

            gWrittenToBldy--;
            if (gWrittenToBldy == 6)
            {
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                UpdateMenuOamDataId(1, 0);
                PAUSE_SCREEN_DATA.oam[1].objMode = 0;
            }
            return ended;

        case 2:
            break;

        case 3:
            BitFill(3, 0, VRAM_BASE + 0x6000, 0x1000, 32);
            break;

        case 4:
            DMA3_COPY_16(EWRAM_BASE + 0xF800, VRAM_BASE + 0xC000, 0x400);
            break;

        case 5:
            WRITE_16(REG_BLDCNT, 0x3F00);
            WRITE_16(REG_BLDALPHA, C_16_2_8(4, 12));
            unk_77840(4);
            break;

        case 6:
            ended = TRUE;
            PAUSE_SCREEN_SUB_STAGE = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            return ended;

        default:
            return ended;
    }

    PAUSE_SCREEN_SUB_STAGE++;
    PAUSE_SCREEN_DATA.timer = 0;
    return ended;
}

/**
 * @brief 77840 | 43c | Updates the pause screen top bar/arrows depending on a request
 *
 * @param request Request
 */
void unk_77840(u8 request)
{
    u32 action;

    action = 0;

    switch (PAUSE_SCREEN_DATA.unk_1)
    {
        case 0:
            action = 5;
            DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_1 = 8;
            break;

        case 3:
            action = 1;
            PAUSE_SCREEN_DATA.oam[13].currentAnimationFrame = 9;
            PAUSE_SCREEN_DATA.oam[14].currentAnimationFrame = 9;
            DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
            PAUSE_SCREEN_DATA.unk_1 = 4;
            break;

        case 4:
            if (request == 1)
            {
                action = 2;
                PAUSE_SCREEN_DATA.dispcnt ^= DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 5;
            }
            else if (request == 3)
            {
                action = 2;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 6;
            }
            else if (request == 5)
            {
                action = 3;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 6;
            }
            break;

        case 5:
            if (request == 2)
            {
                action = 1;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 4;
                SoundPlay(0x203);
            }
            else if (request == 3)
            {
                PAUSE_SCREEN_DATA.unk_1 = 7;
            }
            break;

        case 6:
            if (request == 4)
            {
                action = 1;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_PAUSE_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = request;
            }
            break;

        case 7:
            if (request == 4)
            {
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 5;
            }
            break;

        case 8:
            if (request == 2)
            {
                action = 4;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 9;
                SoundPlay(0x203);
            }
            else if (request == 3 || request == 5)
            {
                action = 6;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 11;
            }
            break;

        case 9:
            if (request == 1)
            {
                action = 5;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 8;
            }
            else if (request == 3 || request == 5)
            {
                action = 6;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                PAUSE_SCREEN_DATA.unk_1 = 10;
            }
            break;

        case 10:
            if (request == 4)
            {
                action = 4;
                PAUSE_SCREEN_DATA.dispcnt |= DCNT_PAUSE_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 9;
            }
            break;

        case 11:
            if (request == 4)
            {
                action = 5;
                PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_PAUSE_BG0;
                DmaTransfer(3, EWRAM_BASE + 0xC000, VRAM_BASE + 0x7000, 0x1000, 16);
                PAUSE_SCREEN_DATA.unk_1 = 8;
            }
            break;
    }

    switch (action)
    {
        case 1:
        case 4:
            PAUSE_SCREEN_DATA.oam[13].oamId = 0x59;
            PAUSE_SCREEN_DATA.oam[13].priority = 2;
            PAUSE_SCREEN_DATA.oam[13].objMode = 0;
            PAUSE_SCREEN_DATA.oam[14].oamId = 0x5C;
            PAUSE_SCREEN_DATA.oam[14].priority = 2;
            PAUSE_SCREEN_DATA.oam[14].objMode = 1;
            PAUSE_SCREEN_DATA.oam[13].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[13].yPosition = 0x84;
            PAUSE_SCREEN_DATA.oam[14].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[14].yPosition = 0x84;

            if (action == 1)
            {
                PAUSE_SCREEN_DATA.oam[12].xPosition = 0x1C;
            }
            else
            {
                PAUSE_SCREEN_DATA.oam[13].currentAnimationFrame = 9;
                PAUSE_SCREEN_DATA.oam[14].currentAnimationFrame = 9;
                PAUSE_SCREEN_DATA.oam[13].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[14].animationDurationCounter = 0;
            }
            break;

        case 2:
            PAUSE_SCREEN_DATA.oam[13].oamId = 0;
            PAUSE_SCREEN_DATA.oam[14].oamId = 0;
            PAUSE_SCREEN_DATA.oam[12].xPosition = -100;
            break;

        case 3:
            PAUSE_SCREEN_DATA.oam[13].oamId = 0;
            PAUSE_SCREEN_DATA.oam[14].oamId = 0;
            break;

        case 5:
            PAUSE_SCREEN_DATA.oam[14].oamId = 0;
            PAUSE_SCREEN_DATA.oam[13].oamId = 0x34;
            PAUSE_SCREEN_DATA.oam[13].xPosition = 0xCA;
            PAUSE_SCREEN_DATA.oam[13].yPosition = 0x8E;
            PAUSE_SCREEN_DATA.oam[13].currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.oam[13].animationDurationCounter = 0;
            PAUSE_SCREEN_DATA.oam[13].priority = 2;
            PAUSE_SCREEN_DATA.oam[13].objMode = 0;
            break;

        case 6:
            PAUSE_SCREEN_DATA.oam[14].oamId = 0;
            PAUSE_SCREEN_DATA.oam[13].oamId = 0;
            break;
    }
}

/**
 * @brief 77c7c | 1c4 | Updates the map screen arrows and the blinking square (samus position)
 *
 */
void MapScreenUpdateArrowsAndBlinkingSquare(void)
{
    u8 oamId;
    const struct PauseScreenArrowInfo* pArrows;

    PAUSE_SCREEN_DATA.oam[32].xPosition = PAUSE_SCREEN_DATA.mapX * 8 - gBackgroundPositions.bg[3].x;
    PAUSE_SCREEN_DATA.oam[32].yPosition = PAUSE_SCREEN_DATA.mapY * 8 - gBackgroundPositions.bg[3].y;

    oamId = PAUSE_SCREEN_DATA.oam[31].oamId;
    if (oamId == 0x12 || oamId == 0x13 || oamId == 0x14 || oamId == 0x15 || oamId == 0xE || oamId == 0xF)
    {
        PAUSE_SCREEN_DATA.oam[31].xPosition = PAUSE_SCREEN_DATA.navTargetX * 8 - gBackgroundPositions.bg[3].x;
        PAUSE_SCREEN_DATA.oam[31].yPosition = PAUSE_SCREEN_DATA.navTargetY * 8 - gBackgroundPositions.bg[3].y;
    }

    if (gPauseScreenFlag != 2)
        return;

    pArrows = sPauseScreenMapArrows;

    if (PAUSE_SCREEN_DATA.unk_28 != 0)
    {
        PAUSE_SCREEN_DATA.oam[pArrows[0].oamSlot].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[pArrows[1].oamSlot].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[pArrows[2].oamSlot].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[pArrows[3].oamSlot].xPosition = 0x100;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_25A - PAUSE_SCREEN_DATA.mapViewX > 13)
        PAUSE_SCREEN_DATA.oam[pArrows[0].oamSlot].xPosition = pArrows[0].xPosition;
    else
        PAUSE_SCREEN_DATA.oam[pArrows[0].oamSlot].xPosition = 0x100;

    if (PAUSE_SCREEN_DATA.mapViewX - PAUSE_SCREEN_DATA.unk_25B > 14)
        PAUSE_SCREEN_DATA.oam[pArrows[1].oamSlot].xPosition = pArrows[1].xPosition;
    else
        PAUSE_SCREEN_DATA.oam[pArrows[1].oamSlot].xPosition = 0x100;

    if (PAUSE_SCREEN_DATA.mapViewY - PAUSE_SCREEN_DATA.unk_25C > 8)
        PAUSE_SCREEN_DATA.oam[pArrows[2].oamSlot].xPosition = pArrows[2].xPosition;
    else
        PAUSE_SCREEN_DATA.oam[pArrows[2].oamSlot].xPosition = 0x100;

    if (PAUSE_SCREEN_DATA.unk_25D - PAUSE_SCREEN_DATA.mapViewY > 8)
        PAUSE_SCREEN_DATA.oam[pArrows[3].oamSlot].xPosition = pArrows[3].xPosition;
    else
        PAUSE_SCREEN_DATA.oam[pArrows[3].oamSlot].xPosition = 0x100;
}

/**
 * @brief 77e40 | 2cc | Draws the special oam of the map screen (security levels, tanks)
 *
 * @param mode Mode (0 = setup, 1 = update ids, 2 = clear)
 */
void MapScreenDrawSpecialOam(u8 mode)
{
    u32 i;
    u32 levelUnlocked;
    u8 priority;
    u8 slot;
    const struct PauseScreenTankOamInfo* pTanks;

    if (gPauseScreenFlag == 4)
        return;

    switch (mode)
    {
        case 0:
            priority = PAUSE_SCREEN_DATA.unk_0 != 0 ? 1 : 3;

            for (i = 0; i < 4; i++)
            {
                levelUnlocked = FALSE;
                if (gEquipment.securityHatchLevel != 0xFF && gEquipment.securityHatchLevel >= i + 1)
                    levelUnlocked = TRUE;

                slot = sPauseScreenSecurityOam[i * 2];
                PAUSE_SCREEN_DATA.oam[slot].oamId = sPauseScreenSecurityOam[i * 2 + 1] + levelUnlocked;
                PAUSE_SCREEN_DATA.oam[slot].yPosition = 0x24;
                PAUSE_SCREEN_DATA.oam[slot].xPosition = 0xD4;
                PAUSE_SCREEN_DATA.oam[slot].priority = priority;
            }
            break;

        case 1:
            for (i = 0; i < 4; i++)
            {
                levelUnlocked = FALSE;
                if (gEquipment.securityHatchLevel != 0xFF && gEquipment.securityHatchLevel >= i + 1)
                    levelUnlocked = TRUE;

                slot = sPauseScreenSecurityOam[i * 2];
                PAUSE_SCREEN_DATA.oam[slot].oamId = sPauseScreenSecurityOam[i * 2 + 1] + levelUnlocked;
            }
            break;

        case 2:
            for (i = 0; i < 4; i++)
                PAUSE_SCREEN_DATA.oam[sPauseScreenSecurityOam[i * 2]].oamId = 0;
            break;
    }

    if (gGameCompletion.completedGame == 0 || PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        PAUSE_SCREEN_DATA.unk_274 = 0;
        return;
    }

    if (mode != 0)
        return;

    PauseScreenMapCountTanks();
    PauseScreenMapDrawIgtAndTanks(FALSE);

    pTanks = (const struct PauseScreenTankOamInfo*)sUnk_79be88;

    for (i = 1; i < 5; i++)
    {
        slot = pTanks[i].oamSlot;
        PAUSE_SCREEN_DATA.oam[slot].oamId = pTanks[i].oamId;
        PAUSE_SCREEN_DATA.oam[slot].priority = 3;
        PAUSE_SCREEN_DATA.oam[slot].xPosition = pTanks[i].xPosition;
        PAUSE_SCREEN_DATA.oam[slot].yPosition = pTanks[i].yPosition;
    }

    for (i = 5; i < 8; i++)
    {
        slot = pTanks[i].oamSlot;
        PAUSE_SCREEN_DATA.oam[slot].priority = 3;
        PAUSE_SCREEN_DATA.oam[slot].xPosition = pTanks[i].xPosition;
        PAUSE_SCREEN_DATA.oam[slot].yPosition = pTanks[i].yPosition;
    }

    if (PAUSE_SCREEN_DATA.maxEnergyTanks == PAUSE_SCREEN_DATA.currentEnergyTanks)
        PAUSE_SCREEN_DATA.oam[pTanks[5].oamSlot].oamId = pTanks[5].oamId;

    if (PAUSE_SCREEN_DATA.maxMissileTanks == PAUSE_SCREEN_DATA.currentMissileTanks)
        PAUSE_SCREEN_DATA.oam[pTanks[6].oamSlot].oamId = pTanks[6].oamId;

    if (PAUSE_SCREEN_DATA.maxPowerBombTanks == PAUSE_SCREEN_DATA.currentPowerBombTanks)
        PAUSE_SCREEN_DATA.oam[pTanks[7].oamSlot].oamId = pTanks[7].oamId;
}

/**
 * @brief 7810c | 2e4 | Sets up the oam of the pause screen
 *
 */
void PauseScreenSetupOam(void)
{
    s32 i;
    u32 hatches;
    u8 slot;
    const struct PauseScreenArrowInfo* pArrow;

    PAUSE_SCREEN_DATA.unk_C = 0;
    PAUSE_SCREEN_DATA.unk_E[0] = 0;
    PAUSE_SCREEN_DATA.unk_E[1] = 0;
    PAUSE_SCREEN_DATA.unk_E[2] = 0;
    PAUSE_SCREEN_DATA.unk_E[3] = 0;
    PAUSE_SCREEN_DATA.unk_17 = 0;
    PAUSE_SCREEN_DATA.unk_18 = 0;

    for (i = 0; i < ARRAY_SIZE(PAUSE_SCREEN_DATA.oam); i++)
    {
        PAUSE_SCREEN_DATA.oam[i].oamId = 0;
        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
        PAUSE_SCREEN_DATA.oam[i].xPosition = 0;
        PAUSE_SCREEN_DATA.oam[i].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[i].priority = 0;
        PAUSE_SCREEN_DATA.oam[i].objMode = 0;
    }

    if (PAUSE_SCREEN_DATA.unk_28 != 4 && gPauseScreenFlag != 4)
        PAUSE_SCREEN_DATA.oam[32].oamId = 1;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        PAUSE_SCREEN_DATA.oam[32].priority = 1;
        PAUSE_SCREEN_DATA.oam[31].priority = 1;
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[32].priority = 3;
        PAUSE_SCREEN_DATA.oam[31].priority = 3;
    }

    MapScreenUpdateArrowsAndBlinkingSquare();

    if (PAUSE_SCREEN_DATA.unk_28 == 1)
    {
        if (PAUSE_SCREEN_DATA.enableDebug)
            PauseDebugSetupCursor();
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[0].oamId = 0;
        PAUSE_SCREEN_DATA.oam[0].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[0].xPosition = 0;
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
    {
        PAUSE_SCREEN_DATA.oam[16].oamId = 0x28;
        PAUSE_SCREEN_DATA.oam[16].yPosition = 2;
        PAUSE_SCREEN_DATA.oam[16].xPosition = 0xD6;
        PAUSE_SCREEN_DATA.oam[16].priority = 2;

        PAUSE_SCREEN_DATA.oam[17].oamId = 0x2A;
        PAUSE_SCREEN_DATA.oam[17].yPosition = 2;
        PAUSE_SCREEN_DATA.oam[17].xPosition = 0x12;
        PAUSE_SCREEN_DATA.oam[17].priority = 2;

        if (gCurrentArea <= 6)
            UpdateMenuOamDataId(18, sPauseScreenAreaNameOamIds[gCurrentArea * 2 + 1]);
        else
            UpdateMenuOamDataId(18, 0);

        PAUSE_SCREEN_DATA.oam[18].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[18].xPosition = 0x74;
        PAUSE_SCREEN_DATA.oam[18].priority = 2;
    }

    MapScreenDrawSpecialOam(0);

    PAUSE_SCREEN_DATA.oam[15].yPosition = 0x20;
    PAUSE_SCREEN_DATA.oam[15].xPosition = 0xC0;
    PAUSE_SCREEN_DATA.oam[15].oamId = 0;

    for (i = 3; i >= 0; i--)
    {
        pArrow = &sPauseScreenMapArrows[i];
        slot = pArrow->oamSlot;

        if (PAUSE_SCREEN_DATA.unk_0 == 0)
            PAUSE_SCREEN_DATA.oam[slot].oamId = pArrow->oamId;

        PAUSE_SCREEN_DATA.oam[slot].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[slot].yPosition = pArrow->yPosition;
        PAUSE_SCREEN_DATA.oam[slot].priority = 2;
    }

    if (PAUSE_SCREEN_DATA.unk_0 != 1)
        return;

    PAUSE_SCREEN_DATA.oam[37].yPosition = 0x7C;
    PAUSE_SCREEN_DATA.oam[37].xPosition = 0x74;
    PAUSE_SCREEN_DATA.oam[37].oamId = 0x3E;
    PAUSE_SCREEN_DATA.oam[37].priority = 3;

    hatches = RoomGetClosedNavigationHatches();
    if (gPauseScreenFlag == 4)
    {
        hatches = 3;
        PAUSE_SCREEN_DATA.oam[37].oamId = 0x3D;
    }

    if (hatches & 2)
    {
        PAUSE_SCREEN_DATA.oam[38].yPosition = 0x4C;
        PAUSE_SCREEN_DATA.oam[38].xPosition = 0x18;
        PAUSE_SCREEN_DATA.oam[38].oamId = 0x3F;
        PAUSE_SCREEN_DATA.oam[38].priority = 3;
    }

    if (hatches & 1)
    {
        PAUSE_SCREEN_DATA.oam[39].yPosition = 0x4C;
        PAUSE_SCREEN_DATA.oam[39].xPosition = 0xD0;
        PAUSE_SCREEN_DATA.oam[39].oamId = 0x40;
        PAUSE_SCREEN_DATA.oam[39].priority = 3;
    }
}

/**
 * @brief 783f0 | 684 | Processes (animates and draws) the pause screen oam
 *
 */
void PauseScreenProcessOam(void)
{
    u16* dst;
    s32 nextSlot;
    s32 currSlot;
    s32 i;
    struct MenuOam* pOam;
    const struct FrameData* pFrames;
    const u16* src;
    u16 yPosition;
    u16 xPosition;
    u8 priority;
    u8 objMode;
    u16 part;

    dst = (u16*)&gOamData[gNextOamSlot];
    nextSlot = gNextOamSlot;
    currSlot = gNextOamSlot;

    for (i = 0; i < ARRAY_SIZE(PAUSE_SCREEN_DATA.oam); i++)
    {
        pOam = &PAUSE_SCREEN_DATA.oam[i];
        if (pOam->oamId == 0)
            continue;

        pOam->ended = FALSE;
        pFrames = sPauseScreenOamFramePointers[pOam->oamId];

        switch (pOam->oamId)
        {
            // Looping animation
            case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7: case 0x8: case 0x9:
            case 0xB: case 0xC: case 0xE: case 0xF: case 0x16: case 0x17: case 0x18: case 0x19:
            case 0x28: case 0x29: case 0x2A: case 0x2B: case 0x3D: case 0x3E: case 0x4B: case 0x4C:
            case 0x60: case 0x67:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                        pOam->currentAnimationFrame = 0;
                }
                break;

            // Looping animation with a sound
            case 0x12: case 0x13: case 0x14: case 0x15:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                    {
                        pOam->currentAnimationFrame = 0;
                        if (PAUSE_SCREEN_DATA.unk_28 != 1)
                        {
                            if (PAUSE_SCREEN_DATA.unk_0 != 0)
                                SoundPlay(0x11A);
                            else
                                SoundPlay(0x12B);
                        }
                    }
                }
                break;

            // Play once, stays on the last frame
            case 0x41: case 0x43: case 0x45: case 0x46: case 0x48: case 0x49: case 0x4A: case 0x4D:
            case 0x50: case 0x53: case 0x56: case 0x59: case 0x5C:
                if (pFrames[pOam->currentAnimationFrame + 1].timer == 0)
                    pOam->ended = TRUE;

                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                        pOam->currentAnimationFrame--;
                }
                break;

            // Play once, then removed
            case 0x10: case 0x42: case 0x4F: case 0x52: case 0x55: case 0x58: case 0x5B: case 0x5E:
            case 0x62: case 0x66:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                    {
                        pOam->oamId = 0;
                        pOam->currentAnimationFrame = 0;
                        continue;
                    }
                }
                break;

            // Play once, then go to the next oam id
            case 0x5F:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                    {
                        pOam->oamId++;
                        pFrames = sPauseScreenOamFramePointers[pOam->oamId];
                        pOam->animationDurationCounter = 0;
                        pOam->currentAnimationFrame = 0;
                    }
                }
                break;

            // Play once, then go to the next oam id and set oam 6
            case 0x63:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                    {
                        pOam->oamId++;
                        pFrames = sPauseScreenOamFramePointers[pOam->oamId];
                        pOam->animationDurationCounter = 0;
                        pOam->currentAnimationFrame = 0;

                        PAUSE_SCREEN_DATA.oam[6].oamId = 0x67;
                        PAUSE_SCREEN_DATA.oam[6].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[6].currentAnimationFrame = 0;
                    }
                }
                break;

            // Play once, then go to the previous oam id
            case 0x1B: case 0x1D: case 0x1F: case 0x21: case 0x23: case 0x25: case 0x27: case 0x35:
            case 0x65:
                if (pOam->animationDurationCounter >= pFrames[pOam->currentAnimationFrame].timer)
                {
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame++;
                    if (pFrames[pOam->currentAnimationFrame].timer == 0)
                    {
                        pOam->oamId--;
                        pFrames = sPauseScreenOamFramePointers[pOam->oamId];
                        pOam->animationDurationCounter = 0;
                        pOam->currentAnimationFrame = 0;
                    }
                }
                break;

            // Static
            default:
                pOam->animationDurationCounter = 0;
                break;
        }

        pOam->animationDurationCounter++;

        yPosition = pOam->yPosition + 4;
        xPosition = pOam->xPosition + 4;
        src = pFrames[pOam->currentAnimationFrame].pFrame;
        priority = pOam->priority;
        objMode = pOam->objMode;

        part = *src;
        if (nextSlot + part > 0x7F)
            break;

        nextSlot += part;
        src++;

        for (; currSlot < nextSlot; currSlot++)
        {
            part = *src++;
            *dst++ = part;
            gOamData[currSlot].split.y = part + yPosition;

            part = *src++;
            *dst++ = part;
            gOamData[currSlot].split.x = (part + xPosition) & 0x1FF;

            *dst = *src++;
            gOamData[currSlot].split.priority = priority;
            gOamData[currSlot].split.objMode = objMode;

            dst += 2;
        }
    }

    gNextOamSlot = nextSlot;
}

/**
 * @brief 78a74 | 7c | Checks for a maintained d-pad input (auto repeat)
 *
 */
void CheckForMaintainedInput(void)
{
    if (gButtonInput & (KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN))
    {
        gUnk_3005400.timer++;
    }
    else
    {
        gUnk_3005400.timer = 0;
        gUnk_3005400.delayIndex = 0;
    }

    // PORT: the original copies sMaintainedInputDelays (7 bytes) to the stack and
    // indexes it, delayIndex never exceeds 6 in practice
    if (gUnk_3005400.timer >= sMaintainedInputDelays[gUnk_3005400.delayIndex])
    {
        gChangedInput |= gButtonInput & (KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN);
        gUnk_3005400.timer = 0;

        if (gUnk_3005400.delayIndex <= 5)
            gUnk_3005400.delayIndex++;
    }
}

/**
 * @brief 78af0 | b4 | Sets the oam of the navigation panel
 *
 * @param arg0 Mode (0 = only update position)
 */
void unk_78af0(u8 arg0)
{
    u32 offset;
    u32 type;
    const u8* pIds;

    if (arg0 != 0)
    {
        offset = 0;
        if (PAUSE_SCREEN_DATA.typeFlags & 4)
            offset = 3;

        // Note: in the original, the type is an uninitialized register for an
        // unhandled mode (callers only use 2 and 3)
        type = 0;
        if (arg0 == 1)
        {
            type = 0;
        }
        else if (arg0 == 2)
        {
            SoundPlay(0x20A);
            type = 1;
        }
        else if (arg0 == 3)
        {
            SoundPlay(0x20B);
            type = 2;
        }

        offset += type;
        pIds = &sPauseScreenNavPanelOamIds[offset * 3];

        PAUSE_SCREEN_DATA.oam[8].oamId = pIds[0];
        PAUSE_SCREEN_DATA.oam[9].oamId = pIds[1];
        PAUSE_SCREEN_DATA.oam[7].oamId = pIds[2];
        PAUSE_SCREEN_DATA.oam[8].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[8].currentAnimationFrame = 0;
        PAUSE_SCREEN_DATA.oam[9].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[9].currentAnimationFrame = 0;
    }

    PAUSE_SCREEN_DATA.oam[9].xPosition = PAUSE_SCREEN_DATA.oam[8].xPosition;
    PAUSE_SCREEN_DATA.oam[9].yPosition = PAUSE_SCREEN_DATA.oam[8].yPosition;
}

/**
 * @brief 78ba4 | a0 | Sets the oam of the navigation text panel
 *
 * @param arg0 Mode (0 = only update position)
 */
void PauseScreenSetNavigationTextPanelOam(u8 arg0)
{
    u16 xPosition;
    u16 yPosition;

    if (arg0 == 1)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x44;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x47;
    }
    else if (arg0 == 2)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x43;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x46;
        SoundPlay(0x20A);
    }
    else if (arg0 == 3)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x45;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x48;
        SoundPlay(0x20B);
    }

    if (arg0 != 0)
    {
        PAUSE_SCREEN_DATA.oam[4].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[4].currentAnimationFrame = 0;
        PAUSE_SCREEN_DATA.oam[5].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[5].currentAnimationFrame = 0;
    }

    xPosition = PAUSE_SCREEN_DATA.oam[4].xPosition;
    yPosition = PAUSE_SCREEN_DATA.oam[4].yPosition;

    PAUSE_SCREEN_DATA.oam[5].xPosition = xPosition;
    PAUSE_SCREEN_DATA.oam[5].yPosition = yPosition;
    PAUSE_SCREEN_DATA.oam[3].xPosition = xPosition;
    PAUSE_SCREEN_DATA.oam[3].yPosition = yPosition;
}

/**
 * @brief 78c44 | 260 | Updates the navigation panel (map download/target)
 *
 */
void unk_78c44(void)
{
    if (!(PAUSE_SCREEN_DATA.typeFlags & 6))
    {
        PAUSE_SCREEN_DATA.unk_23C = 0;
        PAUSE_SCREEN_DATA.unk_23D = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_23D++;

    switch (PAUSE_SCREEN_DATA.unk_23C)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.unk_23D > 16)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 1:
            PAUSE_SCREEN_DATA.oam[8].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[8].yPosition = 0x1C;
            unk_78af0(2);
            MapScreenDrawSpecialOam(2);
            PAUSE_SCREEN_DATA.unk_23C++;
            PAUSE_SCREEN_DATA.unk_23D = 0;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.oam[8].ended && PAUSE_SCREEN_DATA.oam[9].ended)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_23D > 16)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 0x10;
                PAUSE_SCREEN_DATA.oam[2].xPosition = 8;
                PAUSE_SCREEN_DATA.oam[2].yPosition = sPauseScreenNavPanelYPositions[2];
                PAUSE_SCREEN_DATA.oam[2].oamId = 0xB;
                PAUSE_SCREEN_DATA.oam[2].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[2].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 4:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x10))
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 5:
            unk_78af0(3);
            PAUSE_SCREEN_DATA.oam[2].oamId = 0;
            PAUSE_SCREEN_DATA.oam[6].oamId = 0;
            PAUSE_SCREEN_DATA.unk_23C++;
            PAUSE_SCREEN_DATA.unk_23D = 0;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.oam[8].oamId == 0 && PAUSE_SCREEN_DATA.oam[9].oamId == 0)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
                MapScreenDrawSpecialOam(1);
            }
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.unk_23D > 16)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;

                if (PAUSE_SCREEN_DATA.typeFlags & 2)
                    PAUSE_SCREEN_DATA.typeFlags ^= 2;
                else if (PAUSE_SCREEN_DATA.typeFlags & 4)
                    PAUSE_SCREEN_DATA.typeFlags ^= 4;
            }
            break;
    }

    if (PAUSE_SCREEN_DATA.unk_1B > 1 && PAUSE_SCREEN_DATA.oam[7].oamId == 0x64)
    {
        PAUSE_SCREEN_DATA.oam[7].oamId = 0x65;
        PAUSE_SCREEN_DATA.oam[7].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[7].currentAnimationFrame = 0;
    }
}

/**
 * @brief 78ea4 | 274 | Updates the navigation conversation panel
 *
 */
void NavigationConversationUpdatePanel(void)
{
    if (!(PAUSE_SCREEN_DATA.typeFlags & 1))
    {
        PAUSE_SCREEN_DATA.unk_238 = 0;
        PAUSE_SCREEN_DATA.unk_239 = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_239++;

    switch (PAUSE_SCREEN_DATA.unk_238)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.oam[4].yPosition == 0x7C)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            else
            {
                PAUSE_SCREEN_DATA.oam[4].yPosition -= 8;
                PauseScreenSetNavigationTextPanelOam(0);
            }
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.unk_239 > 8)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 2:
            PauseScreenSetNavigationTextPanelOam(2);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 3:
        case 10:
            if (PAUSE_SCREEN_DATA.oam[4].ended)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 4:
            UpdateMenuOamDataId(3, 0x49);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 5:
            if (PAUSE_SCREEN_DATA.oam[3].ended)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 8;
                PAUSE_SCREEN_DATA.oam[1].xPosition = 8;
                PAUSE_SCREEN_DATA.oam[1].yPosition = sPauseScreenNavPanelYPositions[0];
                PAUSE_SCREEN_DATA.oam[1].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[1].currentAnimationFrame = 0;

                if (PAUSE_SCREEN_DATA.unk_1C != 5)
                    PAUSE_SCREEN_DATA.oam[1].oamId = 0xB;

                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 6:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 8))
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            else if (PAUSE_SCREEN_DATA.unk_239 == 16)
            {
                UpdateMenuOamDataId(3, 0x4C);
            }

            if (PAUSE_SCREEN_DATA.unk_239 > 60)
                PAUSE_SCREEN_DATA.unk_239 = 60;
            break;

        case 7:
            UpdateMenuOamDataId(3, 0x4A);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 8:
            if (PAUSE_SCREEN_DATA.oam[3].ended)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 9:
            PAUSE_SCREEN_DATA.oam[1].oamId = 0;
            PauseScreenSetNavigationTextPanelOam(3);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 11:
            if (PAUSE_SCREEN_DATA.oam[4].yPosition == 0xCC)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            else
            {
                PAUSE_SCREEN_DATA.oam[4].yPosition += 8;
                PauseScreenSetNavigationTextPanelOam(0);
            }
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.unk_239 > 8)
            {
                PAUSE_SCREEN_DATA.typeFlags ^= 1;
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;
    }
}
