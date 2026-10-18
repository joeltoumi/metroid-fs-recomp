#include "animated_palette.h"

#include "globals.h"

#include "data/animated_graphics_data.h"
#include "data/animated_palette_data.h"

#include "constants/event.h"
#include "constants/room.h"

#include "structs/animated_graphics.h"
#include "structs/event.h"
#include "structs/room.h"

#define CURR_ANIM_PAL_DATA sAnimatedPaletteEntries[gAnimatedPaletteAndTileset.animatedPalette]

/**
 * @brief 6fec8 | 144 | Updates the animated palette
 * 
 */
void AnimatedPaletteUpdate(void)
{
    s32 update;
    s32 newRow;
    s32 row;

    if (gAnimatedPaletteAndTileset.animatedPalette == 0)
        return;

    update = FALSE;

    APPLY_DELTA_TIME_INC(gAnimatedPaletteTiming.timer1);
    
    switch (CURR_ANIM_PAL_DATA.type)
    {
        case ANIMATED_PALETTE_TYPE_NONE:
            // No type, so no palette
            break;

        case ANIMATED_PALETTE_TYPE_NORMAL:
            if (CURR_ANIM_PAL_DATA.framesPerState <= gAnimatedPaletteTiming.timer1)
            {
                gAnimatedPaletteTiming.timer1 = 0;
                gAnimatedPaletteTiming.row1++;

                if (CURR_ANIM_PAL_DATA.numberOfStates <= gAnimatedPaletteTiming.row1)
                {
                    if (gUnk_3004e3a != 0)
                        update = 1;

                    gAnimatedPaletteTiming.row1 = 0;
                }

                update++;
            }
            break;

        case ANIMATED_PALETTE_TYPE_ALTERNATE:
            if (CURR_ANIM_PAL_DATA.framesPerState <= gAnimatedPaletteTiming.timer1)
            {
                gAnimatedPaletteTiming.timer1 = 0;
                gAnimatedPaletteTiming.row1++;

                if (CURR_ANIM_PAL_DATA.numberOfStates <= gAnimatedPaletteTiming.row1)
                {
                    if (gUnk_3004e3a != 0)
                        update = 1;

                    newRow = CURR_ANIM_PAL_DATA.numberOfStates - 1;
                    gAnimatedPaletteTiming.row1 = -newRow;
                }
                update += 1;
            }
            break;

        case ANIMATED_PALETTE_TYPE_REVERSE:
            if (CURR_ANIM_PAL_DATA.framesPerState <= gAnimatedPaletteTiming.timer1)
            {
                gAnimatedPaletteTiming.timer1 = 0;
                gAnimatedPaletteTiming.row1--;
                if (gAnimatedPaletteTiming.row1 < 0)
                    gAnimatedPaletteTiming.row1 = CURR_ANIM_PAL_DATA.numberOfStates - 1;
                update = 1;
            }
            break;
    }

    if (update != 0)
    {
        row = gAnimatedPaletteTiming.row1;
        if (row < 0)
            row = -row;

        if (gSubGameMode1 == 2)
        {
            DMA3_COPY_16(&CURR_ANIM_PAL_DATA.pPalette[row * PAL_ROW],
                PALRAM_BASE + PAL_ROW_SIZE * 15, PAL_ROW);
        }
        else
        {
            DMA3_COPY_16(&CURR_ANIM_PAL_DATA.pPalette[row * PAL_ROW],
                gBackgroundPalette2 + PAL_ROW_SIZE * 15, PAL_ROW);
        }
        
        if (update == 2)
            gAnimatedPaletteAndTileset.animatedPalette = 0;
    }
}

/**
 * @brief 7000c | 6c | Checks if the animated palette should be disabled when loading a room
 * 
 */
void AnimatedPaletteCheckDisableOnTransition(void)
{
    gAnimatedPaletteTiming = sAnimatedPaletteTiming_Empty;
    gHatchFlashAnimation = sAnimatedPaletteTiming_Empty;
    gUnk_3004e3a = 0;
    
    if (AnimatedPaletteCheckDisabledFromEvent() == TRUE)
        gAnimatedPaletteAndTileset.animatedPalette = 0;
    
    if (gAnimatedPaletteAndTileset.animatedPalette != 0)
    {
        DMA3_COPY_16(CURR_ANIM_PAL_DATA.pPalette, PALRAM_BASE + 15 * PAL_ROW_SIZE, PAL_ROW);
    }
}

/**
 * @brief 70078 | 44 | Checks if the animated palette should be disabled due to an event
 * 
 * @return s32 bool, disabled
 */
bools32 AnimatedPaletteCheckDisabledFromEvent(void)
{
    bools32 disabled;

    disabled = FALSE;

    if (gCurrentRoomEntry.tilesetNumber == 0x2A) // Heated Sector 3
    {
        // Check not during meltdown
        if (gEventCounter < EVENT_ICE_MISSILE_DATA_DOWNLOADED || gEventCounter >= EVENT_COOLING_UNIT_OPERATIONAL)
            disabled = TRUE;
    }
    else if (gCurrentRoomEntry.bg0Prop == BG_PROP_DISABLE_TRANSPARENCY)
    {
        // Check during power outage
        if (gEventCounter >= EVENT_POWER_OUTAGE && gEventCounter < EVENT_AUXILARY_POWER_ENGAGED)
            disabled = TRUE;
    }

    return disabled;
}
