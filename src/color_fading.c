#include "color_fading.h"

#include "globals.h"

#include "data/color_fading_data.h"
#include "data/common_pals.h"
#include "data/rooms/test_rooms_data.h"

#include "constants/event.h"
#include "constants/room.h"
#include "constants/samus.h"

#include "structs/animated_graphics.h"
#include "structs/audio.h"
#include "structs/color_effects.h"
#include "structs/connection.h"
#include "structs/display.h"
#include "structs/event.h"
#include "structs/haze.h"
#include "structs/room.h"
#include "structs/samus.h"

/**
 * @brief 6dacc | 264 | Updates the current color fading effect
 * 
 * @param fadeOut Fade from original to black/white
 * @param speed Which speed table to use
 * @return s32 bool, done
 */
bools32 ColorFadingUpdate(boolu8 fadeOut, u8 speed)
{
    bools32 done;
    u16 bldcnt;

    done = FALSE;

    switch (gColorFading.type)
    {
        case COLOR_FADING_DOOR_WHITE:
        case COLOR_FADING_DOOR_BLACK:
        case COLOR_FADING_WHITE_KEEP_HUD:
        case COLOR_FADING_BLACK_KEEP_HUD:
        case COLOR_FADING_SA_X_ELEVATOR:
            if (gColorFading.fadeTimer == 0)
            {
                if (!fadeOut)
                    gWrittenToBldy = 0;

                gColorFading.usePalette3 = 0;
            }
            else
            {
                if (gColorFading.fadeTimer == sColorFadingSpeeds[speed].size)
                {
                    if (!fadeOut)
                    {
                        if (gColorFading.usePalette3 & COLOR_FADING_STATUS_ON_BG)
                            ColorEffectCopyBgPal3AndObjPal2ToPal1();
                        else
                            ColorEffectCopyEwramPal2ToEwramPal1();

                        gColorFading.status = COLOR_FADING_STATUS_ON_BG | COLOR_FADING_STATUS_ON_OBJ;
                    }

                    gColorFading.fadeTimer++;
                }
                else if (gColorFading.fadeTimer > sColorFadingSpeeds[speed].size)
                {
                    done = TRUE;
                }
            }

            if (gColorFading.fadeTimer < sColorFadingSpeeds[speed].size)
            {
                ColorEffectFadePalette_SkipHud(fadeOut, sColorFadingSpeeds[speed].colorArray[gColorFading.fadeTimer]);
                gColorFading.fadeTimer++;
            }
            break;
        
        case COLOR_FADING_WHITE:
        case COLOR_FADING_BLACK:
        case COLOR_FADING_ESCAPE_FAILED:
        case COLOR_FADING_LAB_ESCAPE:
        case COLOR_FADING_DEMO_END_INPUT:
        case COLOR_FADING_DEMO_END_AUTO:
        case COLOR_FADING_FINAL_ESCAPE:
            if (gColorFading.fadeTimer == 0)
            {
                if (!fadeOut)
                    gWrittenToBldy = 0;

                gColorFading.usePalette3 = 0;
            }
            else
            {
                if (gColorFading.fadeTimer == sColorFadingSpeeds[speed].size)
                {
                    if (fadeOut)
                    {
                        if (gColorFading.type & COLOR_FADING_WHITE_FLAG)
                            bldcnt = BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT;
                        else
                            bldcnt = BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT;

                        WRITE_16(REG_BLDCNT, bldcnt);
                        gWrittenToBldy = BLDY_MAX_VALUE;
                        WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
                    }
                    else
                    {
                        if (gColorFading.usePalette3 & COLOR_FADING_STATUS_ON_BG)
                            ColorEffectCopyBgPal3AndObjPal2ToPal1();
                        else
                            ColorEffectCopyEwramPal2ToEwramPal1();

                        gColorFading.status = COLOR_FADING_STATUS_ON_BG | COLOR_FADING_STATUS_ON_OBJ;
                    }
                    gColorFading.fadeTimer++;
                }
                else if (gColorFading.fadeTimer > sColorFadingSpeeds[speed].size)
                {
                    done = TRUE;
                }
            }

            if (gColorFading.fadeTimer < sColorFadingSpeeds[speed].size)
            {
                ColorEffectFadePalette_All(fadeOut, sColorFadingSpeeds[speed].colorArray[gColorFading.fadeTimer]);
                gColorFading.fadeTimer++;
            }
            break;
        
        case COLOR_FADING_MONO_WHITE:
        case COLOR_FADING_MONO_BLACK:
            if (gColorFading.fadeTimer == 0)
            {
                gColorFading.usePalette3 = 0;
            }
            else
            {
                if (gColorFading.fadeTimer == sColorFadingSpeeds[speed].size)
                    gColorFading.fadeTimer++;
                else if (gColorFading.fadeTimer > sColorFadingSpeeds[speed].size)
                    done = TRUE;
            }

            if (gColorFading.fadeTimer < sColorFadingSpeeds[speed].size)
            {
                ColorEffectFadePalette_SkipSamus(fadeOut, sColorFadingSpeeds[speed].colorArray[gColorFading.fadeTimer]);
                gColorFading.fadeTimer++;
            }
            break;
    }

    if (done)
        gColorFading.fadeTimer = 0;

    return done;
}

/**
 * @brief 6dd30 | 88 | Transfers the faded palette during a transition
 * 
 */
void ColorFadingTransferPaletteOnTransition(void)
{
    u16 color;
    boolu8 skipBgHatches;
    boolu8 skipObjHud;

    color = COLOR_BLACK;
    skipBgHatches = FALSE;
    skipObjHud = FALSE;

    switch (gColorFading.type)
    {
        case COLOR_FADING_WHITE:
            color = COLOR_WHITE;
            break;

        case COLOR_FADING_BLACK:
            break;

        case COLOR_FADING_DOOR_WHITE:
            color = COLOR_WHITE;
            skipBgHatches = TRUE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_DOOR_BLACK:
            skipBgHatches = TRUE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_WHITE_KEEP_HUD:
            color = COLOR_WHITE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_BLACK_KEEP_HUD:
        case COLOR_FADING_SA_X_ELEVATOR:
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_WINDOW:
            ColorEffectCopyPalramToEwramPal2();
            return;

        default:
            return;
    }

    ColorFadingFillAndTransferPalette(color, skipBgHatches, skipObjHud);
}

/**
 * @brief 6ddb8 | 88 | Transfers the faded palette during a transition (excluding SA-X elevator)
 * 
 */
void ColorFadingTransferPaletteOnTransition_NoSaXElevator(void)
{
    u16 color;
    boolu8 skipBgHatches;
    boolu8 skipObjHud;

    color = COLOR_BLACK;
    skipBgHatches = FALSE;
    skipObjHud = FALSE;

    switch (gColorFading.type)
    {
        case COLOR_FADING_WHITE:
            color = COLOR_WHITE;
            break;

        case COLOR_FADING_BLACK:
            break;

        case COLOR_FADING_DOOR_WHITE:
            color = COLOR_WHITE;
            skipBgHatches = TRUE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_DOOR_BLACK:
            skipBgHatches = TRUE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_WHITE_KEEP_HUD:
            color = COLOR_WHITE;
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_BLACK_KEEP_HUD:
            skipObjHud = TRUE;
            break;

        case COLOR_FADING_WINDOW:
            ColorEffectCopyPalramToEwramPal2();
            return;

        default:
            return;
    }

    ColorFadingFillAndTransferPalette(color, skipBgHatches, skipObjHud);
}

/**
 * @brief 6de40 | 80 | Fills palette RAM with a color and transfers it to EWRAM palette 1
 * 
 * @param color Color to fill palette with
 * @param skipBgHatches Skip background palette hatch row
 * @param skipObjHud Skip object palette HUD rows
 */
void ColorFadingFillAndTransferPalette(u16 color, boolu8 skipBgHatches, boolu8 skipObjHud)
{
    s32 i;
    u16* pBgPal;
    u16* pObjPal;
    s32 row;

    gColorFading.fadeTimer = 0;
    ColorEffectCopyPalramToEwramPal2();

    i = 0;
    pObjPal = (u16*)PALRAM_OBJ;
    pBgPal = (u16*)PALRAM_BASE;

    while (i < COLORS_IN_PAL)
    {
        row = DIV_SHIFT(i, PAL_ROW);

        if (row != BG_PAL_ROW_HATCHES || !skipBgHatches)
            *pBgPal = color;

        if ((row != OBJ_PAL_ROW_HUD_AMMO && row != OBJ_PAL_ROW_MINIMAP) || !skipObjHud)
            *pObjPal = color;
    
        pObjPal++;
        pBgPal++;
        i++;
    }

    DMA3_COPY_16(PALRAM_BASE, gBackgroundPalette1, COLORS_IN_PAL);
    DMA3_COPY_16(PALRAM_OBJ, gObjectPalette1, COLORS_IN_PAL);
}

/**
 * @brief 6dec0 | c | Starts color fading for an instant transition
 * 
 */
void ColorFadingStartNoTransition(void)
{
    ColorFadingStart(COLOR_FADING_BLACK_KEEP_HUD);
}

/**
 * @brief 6decc | 1c | Starts color fading for failing an escape (unused)
 * 
 */
void ColorFadingStartEscapeFailed_Unused(void)
{
    ColorEffectCopyPalramToEwramPal2And1();
    ColorFadingStart(COLOR_FADING_ESCAPE_FAILED);
    
    gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
}

/**
 * @brief 6dee8 | 1c | Starts color fading for failing an escape
 * 
 */
void ColorFadingStartEscapeFailed(void)
{
    ColorEffectCopyPalramToEwramPal2And1();
    ColorFadingStart(COLOR_FADING_ESCAPE_FAILED);

    gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
}

/**
 * @brief 6df04 | 1c | Starts color fading for the final escape
 * 
 */
void ColorFadingStartFinalEscape(void)
{
    ColorEffectCopyPalramToEwramPal2And1();
    ColorFadingStart(COLOR_FADING_FINAL_ESCAPE);

    gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
}

/**
 * @brief 6df20 | 90 | Expands window 1 to the size of the screen
 * 
 * @return s32 bool, done expanding
 */
bools32 ColorFadingExpandWindow(void)
{
    s32 timer;
    s32 edgesReached;

    if (gWindow1Border.timer == 0)
        gWrittenToBldy = 0;

    gWindow1Border.timer++;
    if (gWindow1Border.timer == 0)
        gWindow1Border.timer = UCHAR_MAX;

    timer = (gWindow1Border.timer / 2) + 2;
    edgesReached = 0;

    if (gWindow1Border.left > timer)
    {
        gWindow1Border.left -= timer;
    }
    else
    {
        gWindow1Border.left = 0;
        edgesReached++;
    }

    if (gWindow1Border.top > timer)
    {
        gWindow1Border.top -= timer;
    }
    else
    {
        gWindow1Border.top = 0;
        edgesReached++;
    }

    if (gWindow1Border.right < SCREEN_SIZE_X - timer)
    {
        gWindow1Border.right += timer;
    }
    else
    {
        gWindow1Border.right = SCREEN_SIZE_X;
        edgesReached++;
    }

    if (gWindow1Border.bottom < SCREEN_SIZE_Y - timer)
    {
        gWindow1Border.bottom += timer;
    }
    else
    {
        gWindow1Border.bottom = SCREEN_SIZE_Y;
        edgesReached++;
    }

    edgesReached = DIV_SHIFT(edgesReached, 4);
    if (edgesReached != 0)
        gWindow1Border.timer = 0;

    return edgesReached;
}

/**
 * @brief 6dfb0 | 158 | Shrinks window 1 toward Samus
 * 
 * @return s32 bool, done shrinking
 */
bools32 ColorFadingCloseWindowOnSamus(void)
{
    s32 i;
    s32 distances[4];
    s32 samusScreenX;
    s32 samusScreenY;
    s32 j;
    s32 tmp;

    if (gWindow1Border.timer == 0)
        gWindow1Border.timer++;

    for (i = 0; i < 4; i++)
        distances[i] = 0;

    samusScreenX = gSamusData.xPosition - gBg1XPosition;
    if (samusScreenX < 0)
    {
        samusScreenX = 0;
    }
    else
    {
        samusScreenX = SUB_PIXEL_TO_PIXEL(samusScreenX);
        if (samusScreenX > SCREEN_SIZE_X)
            samusScreenX = SCREEN_SIZE_X;
    }

    samusScreenY = gSamusData.yPosition - (BLOCK_TO_SUB_PIXEL(1) - 1) - gBg1YPosition;
    if (samusScreenY < 0)
    {
        samusScreenY = 0;
    }
    else
    {
        samusScreenY = SUB_PIXEL_TO_PIXEL(samusScreenY);
        if (samusScreenY > SCREEN_SIZE_Y)
            samusScreenY = SCREEN_SIZE_Y;
    }

    // Get Samus's distance to window edges
    distances[0] = samusScreenX - gWindow1Border.left;
    distances[1] = gWindow1Border.right - samusScreenX;
    distances[2] = samusScreenY - gWindow1Border.top;
    distances[3] = gWindow1Border.bottom - samusScreenY;

    // Get index of largest distance
    j = 0;
    for (i = 0; i < ARRAY_SIZE(distances); i++)
    {
        if (distances[j] <= distances[i])
            j = i;
    }

    tmp = distances[j] - 2;
    i = tmp - (distances[j] >> 3);
    for (j = 0; j < ARRAY_SIZE(distances); j++)
    {
        if (i < distances[j])
            distances[j] = distances[j] - i;
        else
            distances[j] = 0;
    }

    j = distances[0];
    if (j != 0)
    {
        if (gWindow1Border.left < samusScreenX - j)
            gWindow1Border.left += j;
        else
            gWindow1Border.left = samusScreenX;
    }

    j = distances[1];
    if (j != 0)
    {
        if (gWindow1Border.right > samusScreenX + j)
            gWindow1Border.right -= j;
        else
            gWindow1Border.right = samusScreenX;
    }

    j = distances[2];
    if (j != 0)
    {
        if (gWindow1Border.top < samusScreenY - j)
            gWindow1Border.top += j;
        else
            gWindow1Border.top = samusScreenY;
    }

    j = distances[3];
    if (j != 0)
    {
        if (gWindow1Border.bottom > samusScreenY + j)
            gWindow1Border.bottom -= j;
        else
            gWindow1Border.bottom = samusScreenY;
    }

    i = FALSE;
    if (gWindow1Border.left == samusScreenX && gWindow1Border.right == samusScreenX &&
        gWindow1Border.top == samusScreenY && gWindow1Border.bottom == samusScreenY)
    {
        gWrittenToBldcnt = BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT;
        gWrittenToBldy = BLDY_MAX_VALUE;
        i = TRUE;
        gWindow1Border.timer = 0;
    }

    return i;
}

/**
 * @brief 6e108 | 14 | Starts a color fade
 * 
 * @param type Color fading type
 */
void ColorFadingStart(u8 type)
{
    gColorFading.type = type;
    gColorFading.stage = 0;
    gColorFading.fadeTimer = 0;
    gColorFading.unk_3 = 0;
    gColorFading.status = 0;
}

/**
 * @brief 6e11c | 90 | Starts a default color fade
 * 
 */
void ColorFadingStartDefault(void)
{
    gColorFading.stage++;

    gBackgroundPositions.doorTransition.y = gBackgroundPositions.bg[3].y;
    gBackgroundPositions.doorTransition.x = gBackgroundPositions.bg[3].x;

    DmaTransfer(3, gDecompBg3Map, VRAM_BASE + 0x3000, 0x1000, 16);

    WRITE_16(REG_BG0CNT, gIoRegisters.unk_10);
    WRITE_16(REG_BG3CNT, gIoRegisters.bg3Cnt);

    if (gHazeInfo.enabled)
        gHazeInfo.active = TRUE;

    WRITE_16(REG_BLDCNT, gIoRegisters.bldcnt);
    WRITE_16(REG_DISPCNT, gIoRegisters.dispcnt);

    if (gUnk_3000047 == 1)
        RoomEffectCheckLockHatchesWithTimer();
}

/**
 * @brief 6e1ac | b8 | Starts a door transition fade
 * 
 */
void ColorFadingStartDoorTransition(void)
{
    gBackgroundPositions.doorTransition.y = gBackgroundPositions.bg[3].y;
    gBackgroundPositions.doorTransition.x = gBackgroundPositions.bg[3].x;

    ColorEffectCopyPalramToEwramPal2And1();

    if (gPauseScreenFlag == 6)
    {
        gIoRegisters.bg0Cnt = READ_16(REG_BG0CNT);
        gIoRegisters.unk_10 = READ_16(REG_BG0CNT);
        gIoRegisters.bg1Cnt = READ_16(REG_BG1CNT);
        gIoRegisters.bg2Cnt = READ_16(REG_BG2CNT);
        gIoRegisters.bg3Cnt = READ_16(REG_BG3CNT);
        gIoRegisters.dispcnt = READ_16(REG_DISPCNT);
        gIoRegisters.winout_L = READ_8(REG_WINOUT);
        gIoRegisters.winin_H = READ_8(REG_WININ + 1);
        gIoRegisters.bldalpha_eva = LOW_BYTE(READ_16(REG_BLDALPHA));
        gIoRegisters.bldalpha_evb = HIGH_BYTE(READ_16(REG_BLDALPHA));
        gIoRegisters.bldcnt = READ_16(REG_BLDCNT);

        if (gEventCounter == EVENT_ENTERED_ELEVATOR_ROOM)
            gColorFading.type = COLOR_FADING_SA_X_ELEVATOR;
    }

    gWrittenToBldalpha_Eva = gIoRegisters.bldalpha_eva;
    gWrittenToBldalpha_Evb = gIoRegisters.bldalpha_evb;
}

/**
 * @brief 6e264 | b8 | Handles fading for BG2 and BG3 gradient except on delay frames
 * 
 * @param delay Delay frame mask
 */
void ColorFadingGradients(s32 delay)
{
    s32 changed;

    if (gFrameCounter8Bit & delay)
        return;

    changed = FALSE;

    if (gCurrentRoomEntry.visualEffect >= EFFECT_BG3_GRADIENT && gCurrentRoomEntry.visualEffect <= EFFECT_BG2_GRADIENT)
    {
        if (gWrittenToBldalpha_Evb != 0 || gWrittenToBldalpha_Eva != 0)
        {
            if (gWrittenToBldalpha_Evb != 0)
                gWrittenToBldalpha_Evb--;
    
            if (gWrittenToBldalpha_Eva != 0)
                gWrittenToBldalpha_Eva--;
            
            changed = TRUE;
        }
    }
    else if (gCurrentRoomEntry.visualEffect >= EFFECT_WATER && gCurrentRoomEntry.visualEffect <= EFFECT_SNOWFLAKES_COLD)
    {
        if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE || gWrittenToBldalpha_Eva != 0)
        {
            if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                gWrittenToBldalpha_Evb++;
    
            if (gWrittenToBldalpha_Eva != 0)
                gWrittenToBldalpha_Eva--;
            
            changed = TRUE;
        }
    }

    if (changed)
        gWrittenToBldalpha = (gWrittenToBldalpha_Evb << 8) | gWrittenToBldalpha_Eva;
}

/**
 * @brief 6e31c | a4 | Finishes a door fade and sets up door transition drawing
 * 
 */
void ColorFadingFinishDoorFade(void)
{
    unk_6ee8c();
    
    WRITE_16(PALRAM_BASE, COLOR_BLACK);
    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3));
    
    RoomRleDecompress(0, sDoorTransitionTilemap, gDecompBg3Map);
    DmaTransfer(3, gDecompBg3Map, VRAM_BASE + 0x3000, 0x1000, 16);

    WRITE_16(REG_BG3CNT, CREATE_BGCNT(1, 6, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_512x256));
    
    gBackgroundPositions.bg[3].y = 0x40;
    gBackgroundPositions.doorTransition.y = 0x40;

    WRITE_16(REG_BG3VOFS, 0x40);
    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);

    DMA3_COPY_16(sCommonTilesPal + 1 * PAL_ROW_SIZE, PALRAM_BASE + 1 * PAL_ROW_SIZE, PAL_ROW);
}

/**
 * @brief 6e3c0 | fc | Handles fading in for a transition
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingReveal(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.type)
    {
        case COLOR_FADING_SA_X_ELEVATOR:
            SaXUpdateGraphicsAndDraw();

        case COLOR_FADING_WHITE:
        case COLOR_FADING_BLACK:
        case COLOR_FADING_WHITE_KEEP_HUD:
        case COLOR_FADING_BLACK_KEEP_HUD:
            if (gColorFading.stage == 0)
                ColorFadingStartDefault();

            done = ColorFadingUpdate(FALSE, COLOR_FADING_SPEED_FASTER);
            break;
        
        case COLOR_FADING_DOOR_WHITE:
        case COLOR_FADING_DOOR_BLACK:
            done = ColorFadingUpdate_DoorTransition();
            break;
        
        case COLOR_FADING_BRIGHTNESS_WHITE:
        case COLOR_FADING_BRIGHTNESS_BLACK:
            if (gColorFading.stage == 0)
                ColorFadingStartDefault();

            if (gWrittenToBldy != 0)
                gWrittenToBldy--;
            else
                done = TRUE;
            break;
        
        case COLOR_FADING_WINDOW:
            if (gColorFading.stage == 0)
                ColorFadingStartDefault();

            done = ColorFadingExpandWindow();
            break;
    }

    if (done)
    {
        switch (gColorFading.type)
        {         
            case COLOR_FADING_DOOR_WHITE:
            case COLOR_FADING_DOOR_BLACK:
            case COLOR_FADING_WHITE_KEEP_HUD:
            case COLOR_FADING_BLACK_KEEP_HUD:
                CheckPlayNewMusicTrack();
                SoundEventUpdateMusic(SEVENT_TTYPE_ENTERING_ROOM);
                break;

            case COLOR_FADING_WHITE:
            case COLOR_FADING_BLACK:
                if (gCurrentMusicTrack.lowered)
                    IncreaseMusicVolume();
                break;
        }

        ColorFadingStart(COLOR_FADING_BLACK);
        gColorFading.stage = 0;
    }
    
    return done;
}

/**
 * @brief 6e4bc | 1b4 | Processes the current color fading effect
 * 
 * @return s32 result (non-zero when done)
 */
s32 ColorFadingProcess(void)
{
    s32 result;

    result = 0;

    if (gColorFading.unk_3 != UCHAR_MAX)
        gColorFading.unk_3++;

    switch (gColorFading.type)
    {
        case COLOR_FADING_WHITE:
        case COLOR_FADING_BLACK:
        case COLOR_FADING_WHITE_KEEP_HUD:
        case COLOR_FADING_BLACK_KEEP_HUD:
            if (ColorFadingProcess_Default())
                result = 2;
            break;

        case COLOR_FADING_DOOR_WHITE:
        case COLOR_FADING_DOOR_BLACK:
            if (ColorFadingProcess_DoorTransition())
                result = 1;
            break;

        case COLOR_FADING_LAB_ESCAPE:
            if (ColorFadingProcess_LabEscape())
                result = 1;
            break;

        case COLOR_FADING_ESCAPE_FAILED:
            if (ColorFadingProcess_EscapeFailed())
                result = 1;
            break;

        case COLOR_FADING_FINAL_ESCAPE:
            if (ColorFadingProcess_FinalEscape())
            {
                gDisableSoftReset = 1;
                result = 1;
            }
            break;

        case COLOR_FADING_DEMO_END_INPUT:
        case COLOR_FADING_DEMO_END_AUTO:
            if (ColorFadingProcess_DemoEnd())
                result = 1;
            break;

        case COLOR_FADING_SA_X_ELEVATOR:
            ColorFadingStartDoorTransition();
            WRITE_16(PALRAM_BASE, COLOR_BLACK);
            DMA3_COPY_16(sCommonTilesPal + 2 * PAL_ROW_SIZE, PALRAM_BASE + 1 * PAL_ROW_SIZE, PAL_ROW);
            gWrittenToDispcnt = READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
            ColorEffectCopyPalramToEwramPal2And1();
            result = 1;
            break;

        case COLOR_FADING_BRIGHTNESS_WHITE:
        case COLOR_FADING_BRIGHTNESS_BLACK:
            if (gColorFading.stage == 0)
            {
                ColorFadingStartDoorTransition();
                gColorFading.stage++;
            }

            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                ColorFadingFinishDoorFade();
                result = 2;
            }
            break;

        case COLOR_FADING_WINDOW:
            if (gColorFading.stage == 0)
            {
                ColorFadingStartDoorTransition();
                gColorFading.stage++;
            }

            if (ColorFadingCloseWindowOnSamus())
            {
                ColorFadingFinishDoorFade();
                result = 2;
            }
            break;
    }

    if (result != 0)
    {
        if (gSamusData.pose != SPOSE_USING_ELEVATOR && gPauseScreenFlag == 0)
        {
            StopMusicOrSound(&gTrackData6);
            StopMusicOrSound(&gTrackData5);
            StopMusicOrSound(&gTrackData4);
        }

        gNextOamSlot = 0;
        HudDraw();
        ParticleUpdate();
        ResetFreeOam();
        gColorFading.stage = 0;
    }
    
    return result;
}

/**
 * @brief 6e670 | 250 | Handles fading for a door transition
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_DoorTransition(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            ColorFadingStartDoorTransition();
            gColorFading.stage++;
            break;

        case 1:
            if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_FAST))
                gColorFading.stage++;

            ColorFadingGradients(0);
            break;

        case 2:
            unk_6ee8c();
            WRITE_16(PALRAM_BASE, COLOR_BLACK);
            DMA3_COPY_16(sCommonTilesPal + 1 * PAL_ROW_SIZE, PALRAM_BASE + 1 * PAL_ROW_SIZE, PAL_ROW);
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG2 | DCNT_BG3 | DCNT_WIN1));
            gSamusOnTopOfBackgrounds = 0;
            gColorFading.stage++;
            break;

        case 3:
            RoomRleDecompress(0, sDoorTransitionTilemap, gDecompBg3Map);
            DmaTransfer(3, gDecompBg3Map, VRAM_BASE + 0x3000, 0x1000, 16);
            
            if (gDoorPositionStart.x != 0)
                gBackgroundPositions.doorTransition.x = BLOCK_TO_SUB_PIXEL(4.75f);
            else
                gBackgroundPositions.doorTransition.x = BLOCK_TO_SUB_PIXEL(8.75f);

            gBackgroundPositions.doorTransition.y = BLOCK_TO_SUB_PIXEL(4) - DIV_SHIFT(BLOCK_TO_SUB_PIXEL(gDoorPositionStart.y) - gBg1YPosition, 4);
            WRITE_16(REG_BG3HOFS, gBackgroundPositions.doorTransition.x);
            WRITE_16(REG_BG3VOFS, gBackgroundPositions.doorTransition.y);
            gWrittenToBldcnt_Special = BLDCNT_BG3_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_SCREEN_SECOND_TARGET;;

            if (gCurrentRoomEntry.bg0Prop < BG_PROP_DARK_ROOM || gCurrentRoomEntry.bg0Prop > BG_PROP_DIM_ROOM)
            {
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Eva = 0;
            }

            gWrittenToBldalpha = C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva);
            gBg3CntDuringDoorTransition = CREATE_BGCNT(1, 6, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_512x256);
            gBg1CntDuringDoorTransition = READ_16(REG_BG1CNT) | BGCNT_HIGH_MID_PRIORITY;
            gWrittenToDispcnt = READ_16(REG_DISPCNT) | DCNT_BG3;
            gWrittenToDispcnt &= ~DCNT_BG0;
            gColorFading.stage = 4;
            gColorFading.unk_3 = 0;
            done = FALSE;
            break;

        case 4:
            if (gWrittenToBldalpha_Evb > 0 || gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
            {
                if (gWrittenToBldalpha_Evb > 0)
                    gWrittenToBldalpha_Evb--;
                else
                    gWrittenToBldalpha_Evb = 0;

                if (gWrittenToBldalpha_Eva < BLDY_MAX_VALUE)
                    gWrittenToBldalpha_Eva++;
                else
                    gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;

                gWrittenToBldalpha = C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva);
            }
            else
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
                gColorFading.unk_3 = 0;
                gColorFading.stage = 5;
            }
            break;

        case 5:
        default:
            done = TRUE;
            gColorFading.stage = 0;
            break;
    }

    return done;
}

/**
 * @brief 6e8c0 | 6c | Handles default color fading
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_Default(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            ColorFadingStartDoorTransition();
            if (gPauseScreenFlag == 3)
                SoundEventUpdateMusic(SEVENT_TTYPE_STARTING_NAVIGATION_CONVERSATION);

            gColorFading.stage++;
            break;

        case 1:
            if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_FASTER))
                gColorFading.stage++;

            ColorFadingGradients(0);
            break;

        case 2:
            ColorFadingFinishDoorFade();
            done = TRUE;
            break;
    }
    
    return done;
}

/**
 * @brief 6e92c | 7c | Handles fading for escaping the restricted lab
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_LabEscape(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            ColorFadingStartDoorTransition();
            gColorFading.unk_3 = 0;
            gColorFading.stage++;
            break;

        case 1:
            if (gColorFading.unk_3 > 0x1E)
            {
                if (gAnimatedPaletteAndTileset.animatedPalette != 0)
                    gAnimatedPaletteAndTileset.animatedPalette = 0;

                gColorFading.unk_3 = 0;
                gColorFading.stage++;
            }
            break;

        case 2:
            if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_SLOW))
                gColorFading.stage++;

            ColorFadingGradients(7);
            break;

        case 3:
            ColorFadingFinishDoorFade();
            ColorFadingStart(COLOR_FADING_BLACK);
            done = TRUE;
            break;
    }

    return done;
}

/**
 * @brief 6e9a8 | 98 | Handles fading for failing an escape
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_EscapeFailed(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            ColorFadingStartDoorTransition();
            gCurrentCutscene = 0;
            gPauseScreenFlag = 0;
            
            if (gEventCounter == EVENT_60_SECONDS_TO_DETACHMENT)
                gCurrentCutscene = CUTSCENE_RESTRICTED_LAB_DETACHING_DYING;
            else if (gEventCounter >= EVENT_ORBIT_CHANGE_IMPLEMENTED)
                gCurrentCutscene = 0x81;
            else
                gCurrentCutscene = CUTSCENE_BSL_EXPLODING;
            
            gColorFading.stage++;
            break;

        case 1:
            if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_SLOW))
            {
                StopAllMusicAndSounds();
                gColorFading.stage++;
            }
            break;

        case 2:
            unk_6ee8c();
            WRITE_16(PALRAM_BASE, COLOR_WHITE);
            done = TRUE;
            break;
    }

    return done;
}

/**
 * @brief 6ea40 | 64 | Handles fading for the final escape
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_FinalEscape(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            WRITE_16(PALRAM_BASE, COLOR_BLACK);
            gWrittenToDispcnt = READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
            gColorFading.stage++;
            break;

        case 1:
            unk_6ee8c();
            FadeMusic(CONVERT_SECONDS(1.75f));
            gPauseScreenFlag = 0;
            gCurrentCutscene = 0x80;
            done = TRUE;
            break;
    }

    return done;
}

/**
 * @brief 6eaa4 | 60 | Handles fading when a demo ends
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingProcess_DemoEnd(void)
{
    bools32 done;

    done = FALSE;

    switch (gColorFading.stage)
    {
        case 0:
            ColorFadingStartDoorTransition();
            DemoEnd();
            gColorFading.stage++;
            break;

        case 1:
            if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_NORMAL))
                gColorFading.stage++;

            ColorFadingGradients(3);
            break;

        case 2:
            unk_6ee8c();
            WRITE_16(PALRAM_BASE, COLOR_BLACK);
            done = TRUE;
            break;
    }

    return done;
}

/**
 * @brief 6eb04 | 1f8 | Handles updating a door transition fade
 * 
 * @return s32 bool, done
 */
bools32 ColorFadingUpdate_DoorTransition(void)
{
    bools32 done;
    s32 i;

    done = FALSE;

    if (gColorFading.unk_3 != UCHAR_MAX)
        gColorFading.unk_3++;

    switch (gColorFading.stage)
    {
        case 0:
            if (gBackgroundPositions.doorTransition.x == BLOCK_TO_SUB_PIXEL(8.75f))
                gDoorPositionStart.x = BLOCK_TO_SUB_PIXEL(4.75f);
            else
                gDoorPositionStart.x = BLOCK_TO_SUB_PIXEL(8.75f);
            i = BLOCK_TO_SUB_PIXEL(gDoorPositionStart.y);
            gDoorPositionStart.y = BLOCK_TO_SUB_PIXEL(4) - DIV_SHIFT(i - gBg1YPosition, 4);
            
            if (gUnk_3000047 == 1)
                RoomEffectCheckLockHatchesWithTimer();

            gColorFading.stage++;
            break;

        case 1:
            if (gDoorPositionStart.y > gBackgroundPositions.doorTransition.y)
            {
                gBackgroundPositions.doorTransition.y++;
            }
            else if (gDoorPositionStart.y < gBackgroundPositions.doorTransition.y)
            {
                gBackgroundPositions.doorTransition.y--;
            }
            else
            {
                gColorFading.stage++;
                gColorFading.unk_3 = 0;
            }
            break;

        case 2:
            if (gDoorPositionStart.x > gBackgroundPositions.doorTransition.x)
            {
                gBackgroundPositions.doorTransition.x += 6;
                if (gDoorPositionStart.x < gBackgroundPositions.doorTransition.x)
                {
                    gBackgroundPositions.doorTransition.x = gDoorPositionStart.x;
                }
            }
            else if (gDoorPositionStart.x < gBackgroundPositions.doorTransition.x)
            {
                gBackgroundPositions.doorTransition.x -= 6;
                if (gDoorPositionStart.x > gBackgroundPositions.doorTransition.x)
                    gBackgroundPositions.doorTransition.x = gDoorPositionStart.x;
            }
            else
            {
                DmaTransfer(3, gDecompBg3Map, VRAM_BASE + 0x3000, 0x1000, 16);
                WRITE_16(REG_BG0CNT, gIoRegisters.unk_10);
                WRITE_16(REG_BG3CNT, gIoRegisters.bg3Cnt);
                gBackgroundPositions.doorTransition.y = gBackgroundPositions.bg[3].y;
                gBackgroundPositions.doorTransition.x = gBackgroundPositions.bg[3].x;
                
                if (gHazeInfo.enabled)
                    gHazeInfo.active = TRUE;
                
                WRITE_16(REG_BLDCNT, gIoRegisters.bldcnt);
                WRITE_16(REG_DISPCNT, gIoRegisters.dispcnt);
                gColorFading.unk_3 = 0;
                gColorFading.stage++;
            }
            break;

        case 3:
            if (ColorFadingUpdate(FALSE, COLOR_FADING_SPEED_FASTER))
                gColorFading.stage++;
            break;

        case 4:
            gUnk_300144f = 0;

            for (i = 0; i < MAX_AMOUNT_OF_HATCHES; i++)
            {
                if (gLastDoorUsed == gHatchDoorIds[i])
                {
                    if (gHatchData[i].facingRight)
                        gUnk_300144f |= 8 | 0x80;
                    else
                        gUnk_300144f |= 8 | 0x40;

                    break;
                }
            }

            done = TRUE;
            gColorFading.stage = 0;
            break;
    }

    return done;
}

/**
 * @brief 6ecfc | 88 | Applies the monochrome background fading
 * 
 */
void ColorFadingApplyMonochrome(void)
{
    if (gMonochromeFading == MONOCHROME_FADING_ENDED)
        return;

    if (gMonochromeFading & MONOCHROME_FADING_ACTIVE)
    {
        if (ColorFadingUpdate(TRUE, COLOR_FADING_SPEED_FASTER))
        {
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3));
            gMonochromeFading = MONOCHROME_FADING_ENDED;
        }
    }
    else
    {
        if (gMonochromeFading == MONOCHROME_FADING_BLACK)
        {
            ColorFadingStart(COLOR_FADING_MONO_BLACK);

            if (gCurrentHazeValue != 0)
            {
                gCurrentHazeValue = 0;
                unk_6ee8c();
            }
        }
        else if (gMonochromeFading == MONOCHROME_FADING_WHITE)
        {
            ColorFadingStart(COLOR_FADING_MONO_WHITE);
        }
        else
        {
            gMonochromeFading = MONOCHROME_FADING_NONE;
        }

        ColorEffectCopyPalramToEwramPal2And1();
        gMonochromeFading |= MONOCHROME_FADING_ACTIVE;
    }
}
