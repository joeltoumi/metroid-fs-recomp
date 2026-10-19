// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — test warp, game side (the target list and the scripted input
// are in port/src/warp.c; docs/PORT.md has the syntax).
//
// Starts a fresh game (every item, every security level, the maps) in a
// given room of a given area, or goes from a room to one of the game modes
// that are otherwise hours away: cutscenes, navigation conversations, pause
// screen, game over, ending, credits... The way in is the game's own: the
// room is entered through one of its doors, the modes are left to by the
// same fade the game uses.
#include "types.h"
#include "macros.h"
#include "globals.h"
#include "gba.h"

#include "constants/color_fading.h"
#include "constants/connection.h"
#include "constants/event.h"
#include "constants/game_state.h"
#include "constants/samus.h"

#include "data/event_data.h"

#include "structs/connection.h"
#include "structs/event.h"
#include "structs/samus.h"
#include "structs/save_file.h"

#include "sram_files.h"

extern const struct Door* sAreaDoorPointers[AREA_END];

// Must match the mode names in port/src/warp.c.
enum {
    WARP_MODE_CUTSCENE = 100,
    WARP_MODE_NAV,
    WARP_MODE_PAUSE,
    WARP_MODE_GAME_OVER,
    WARP_MODE_ENDING,
    WARP_MODE_CREDITS,
    WARP_MODE_SR388,
    WARP_MODE_SA_X_CLOSE_UP,
    WARP_MODE_SAVE,
    WARP_MODE_EVENT,
};

// PORT_WARP_SCRIPT_* in port/include/port.h.
enum {
    SCRIPT_NONE,
    SCRIPT_ROOM,
    SCRIPT_MENU,
    SCRIPT_PAUSE,
};

#define CUTSCENE_COUNT 12
// Frames of gameplay before a mode is entered from the room.
#define MODE_DELAY 40

static s32 sTarget = -1;   // index in the MF_WARP list
static s32 sValue;         // room / cutscene / event of the current target
static s32 sMode;          // area (< WARP_MODE_CUTSCENE) or mode
static s32 sPlaceRoom = -1; // room RoomReset must start in
static u32 sFrames;
static u32 sPlayingFrames;
static s32 sModeStage;
static s32 sScript = -1;
static s32 sEvent;
static s32 sStarted;
static s32 sEquipPending;

static const u8 sDefaultEvent[AREA_END] = {
    [AREA_MAIN_DECK] = EVENT_SA_X_ELEVATOR_CUTSCENE_ENDS,
    [AREA_SECTOR_1] = EVENT_NAVIGATION_ROOM_ENTERING_SRX,
    [AREA_SECTOR_2] = EVENT_NAVIGATION_ROOM_ENTERING_TRO,
    [AREA_SECTOR_3] = EVENT_NAVIGATION_ROOM_ENTERING_PYR,
    [AREA_SECTOR_4] = EVENT_NAVIGATION_ROOM_ENTERING_AQA,
    [AREA_SECTOR_5] = EVENT_NAVIGATION_ROOM_ENTERING_ARC,
    [AREA_SECTOR_6] = EVENT_NAVIGATION_ROOM_ENTERING_NOC,
    [AREA_TEST_1] = EVENT_NAVIGATION_ROOM_ENTERING_SRX,
    [AREA_TEST_2] = EVENT_NAVIGATION_ROOM_ENTERING_SRX,
    [AREA_TEST_3] = EVENT_NAVIGATION_ROOM_ENTERING_SRX,
};

// First door of `room` in `area`, or -1.
static s32 WarpFindDoor(s32 area, s32 room)
{
    const struct Door* pDoor;
    s32 i;

    if (area < 0 || area >= AREA_END)
        return -1;
    pDoor = sAreaDoorPointers[area];
    for (i = 0; pDoor[i].type != DOOR_TYPE_NONE; i++)
    {
        if (pDoor[i].srcRoom == room)
            return i;
    }
    return -1;
}

static s32 WarpRoomCount(s32 area)
{
    const struct Door* pDoor;
    s32 i;
    s32 count;

    if (area < 0 || area >= AREA_END)
        return 0;
    pDoor = sAreaDoorPointers[area];
    count = 0;
    for (i = 0; pDoor[i].type != DOOR_TYPE_NONE; i++)
    {
        if (pDoor[i].srcRoom + 1 > count)
            count = pDoor[i].srcRoom + 1;
    }
    return count;
}

// Next value >= `from` of a "*" target, or -1 when there are no more.
static s32 WarpNextValue(s32 mode, s32 from)
{
    s32 i;

    if (from < 0)
        from = 0;
    if (mode < WARP_MODE_CUTSCENE)
    {
        for (i = from; i < WarpRoomCount(mode); i++)
        {
            if (WarpFindDoor(mode, i) >= 0)
                return i;
        }
        return -1;
    }
    if (mode == WARP_MODE_CUTSCENE)
    {
        if (from < 1)
            from = 1;
        return from <= CUTSCENE_COUNT ? from : -1;
    }
    if (mode == WARP_MODE_NAV)
    {
        // Every event with a conversation. The last event (escaped on the
        // ship) is never current in a room: the game reads the event after
        // the current one.
        for (i = from; i < EVENT_END - 1; i++)
        {
            if (sEventLocationAndNavigationInfo[i].navConversation > 0)
                return i;
        }
        return -1;
    }
    if (mode == WARP_MODE_EVENT)
    {
        // Every event that happens in a room (bosses, abilities, SA-X,
        // escapes...).
        for (i = from < 1 ? 1 : from; i < EVENT_END - 1; i++)
        {
            if (sEventLocationAndNavigationInfo[i].area < AREA_NORMAL_COUNT &&
                WarpFindDoor(sEventLocationAndNavigationInfo[i].area, sEventLocationAndNavigationInfo[i].room) >= 0)
                return i;
        }
        return -1;
    }
    return from == 0 ? 0 : -1;
}

// Fresh game state, as starting a new file does.
static void WarpNewFile(void)
{
    gFileSelectFileInfo[gMostRecentSaveFile].exists = FALSE;
    Sram_CheckLoadSaveFile();
    gLanguage = LANGUAGE_ENGLISH;

    gAbilityCount = ABILITY_COUNT_END - 1;
    if (Port_WarpAbilities() >= 0 && Port_WarpAbilities() < ABILITY_COUNT_END)
        gAbilityCount = Port_WarpAbilities();
    gSecurityHatchLevelBackup = SECURITY_LEVEL_4;
    gEventCounter = sEvent;
    sEquipPending = TRUE;
    gDisableDrawingSamusAndScrollingFlag = FALSE;

    gUnk_3000be3 = FALSE;
    gCurrentCutscene = 0;
    gPreviousCutscene = 0;
    gPauseScreenFlag = 0;
    gSubGameMode1 = 0;
    gSubGameMode2 = 0;
}

static void WarpStart(void)
{
    s32 area;

    sFrames = 0;
    sPlayingFrames = 0;
    sModeStage = 0;
    sPlaceRoom = -1;

    StopAllMusicAndSounds();

    area = AREA_MAIN_DECK;
    if (sMode < WARP_MODE_CUTSCENE)
    {
        area = sMode;
        sPlaceRoom = sValue;
    }
    else if (sMode == WARP_MODE_NAV)
    {
        // The navigation room of that conversation.
        s32 nav = sEventLocationAndNavigationInfo[sValue].navRoom;
        if (nav > 0 && nav < NAV_ROOM_COUNT && sNavigationRoomLocations[nav][0] < AREA_NORMAL_COUNT &&
            sNavigationRoomLocations[nav][1] != 0)
        {
            area = sNavigationRoomLocations[nav][0];
            sPlaceRoom = sNavigationRoomLocations[nav][1] - 1;
        }
    }

    else if (sMode == WARP_MODE_EVENT)
    {
        // The room of that event, just before it happens.
        if (sEventLocationAndNavigationInfo[sValue].area < AREA_NORMAL_COUNT)
        {
            area = sEventLocationAndNavigationInfo[sValue].area;
            sPlaceRoom = sEventLocationAndNavigationInfo[sValue].room;
        }
        if (sEvent < 0)
            sEvent = sValue - 1;
    }

    if (sEvent < 0)
    {
        if (sMode == WARP_MODE_NAV)
            sEvent = sValue;
        else
            sEvent = sDefaultEvent[area];
    }

    Port_Log("warp: target %d: %s %d:%d event %d", sTarget,
        sMode < WARP_MODE_CUTSCENE ? "room" : "mode", sMode, sValue, sEvent);

    WarpNewFile();
    gCurrentArea = area;
    gPreviousArea = area;
    gMainGameMode = GAME_MODE_IN_GAME;

    if (sMode == WARP_MODE_CREDITS)
        gMainGameMode = GAME_MODE_CREDITS;

    if (sMode == WARP_MODE_CUTSCENE && Port_WarpDirect())
    {
        // Straight from the boot, no room first (to compare with an
        // emulator where the same variables are poked).
        gCurrentCutscene = sValue;
        gMainGameMode = GAME_MODE_CUTSCENE;
        sModeStage = 1;
    }
}

// Moves to the next target (or the next room of a "*" target).
static void WarpNext(void)
{
    s32 area;
    s32 room;
    s32 event;

    if (sTarget >= 0 && Port_WarpTarget(sTarget, &area, &room, &event) && room < 0)
    {
        s32 next = WarpNextValue(sMode, sValue + 1);
        if (next >= 0)
        {
            sValue = next;
            sEvent = event;
            WarpStart();
            return;
        }
    }

    for (;;)
    {
        sTarget++;
        if (!Port_WarpTarget(sTarget, &area, &room, &event))
        {
            Port_Log("warp: done");
            Port_RequestQuit();
            return;
        }
        sMode = area;
        sValue = room >= 0 ? room : WarpNextValue(area, 0);
        sEvent = event;
        if (sValue >= 0)
            break;
    }
    WarpStart();
}

void Port_WarpBoot(void)
{
    s32 area;
    s32 room;
    s32 event;

    if (sStarted)
    {
        // Soft reset: after a save, the game boots to the title screen and
        // the menu script loads the file. Anything else moves on.
        if (sMode == WARP_MODE_SAVE && sModeStage == 6)
            sModeStage = 7;
        else
            WarpNext();
        return;
    }
    if (!Port_WarpTarget(0, &area, &room, &event))
        return;
    sStarted = TRUE;
    WarpNext();
}

void Port_WarpRoomReset(void)
{
    s32 door;

    if (sEquipPending)
    {
        // SamusInit just emptied gEquipment; the beams, missiles and suits
        // come from gAbilityCount (SetAbilityCount, right after this).
        gEquipment.maxEnergy = gEquipment.currentEnergy = MAX_ENERGY_AMOUNT;
        gEquipment.maxMissiles = gEquipment.currentMissiles = MAX_MISSILE_AMOUNT;
        gEquipment.maxPowerBombs = gEquipment.currentPowerBombs = MAX_POWER_BOMB_AMOUNT;
        gEquipment.securityHatchLevel = SECURITY_LEVEL_4;
        gEquipment.downloadedMaps = UCHAR_MAX;
        sEquipPending = FALSE;
    }

    if (sPlaceRoom < 0)
        return;
    door = WarpFindDoor(gCurrentArea, sPlaceRoom);
    if (door >= 0)
        gLastDoorUsed = door;
    else
        Port_Log("warp: area %d has no room %d", gCurrentArea, sPlaceRoom);
    sPlaceRoom = -1;
}

// Leaves the room the way the game does: fade, then the game mode handler
// moves on (gPauseScreenFlag / gCurrentCutscene, see AgbMain).
static void WarpLeaveRoom(void)
{
    ColorFadingStart(COLOR_FADING_BLACK);
    gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
}

static void WarpEnterMode(void)
{
    switch (sMode)
    {
        case WARP_MODE_CUTSCENE:
            gCurrentCutscene = sValue;
            WarpLeaveRoom();
            break;

        case WARP_MODE_NAV:
            gPauseScreenFlag = 3;
            WarpLeaveRoom();
            break;

        case WARP_MODE_PAUSE:
            if (ProcessPauseButtonPress())
            {
                gPauseScreenFlag = 2;
                gSubGameMode1 = SUB_GAME_MODE_LOADING_ROOM;
            }
            break;

        case WARP_MODE_GAME_OVER:
            gEquipment.currentEnergy = 0;
            SamusSetHurtPose();
            break;

        case WARP_MODE_ENDING:
            gCurrentCutscene = 0x80;
            WarpLeaveRoom();
            break;

        case WARP_MODE_SR388:
            gCurrentCutscene = 0x81;
            WarpLeaveRoom();
            break;

        case WARP_MODE_SA_X_CLOSE_UP:
            gPauseScreenFlag = 6;
            WarpLeaveRoom();
            break;
    }
}

static s32 WarpScriptForMode(void)
{
    if (sMode == WARP_MODE_SAVE && sModeStage >= 7 && gMainGameMode != GAME_MODE_IN_GAME)
        return SCRIPT_MENU;
    if (gMainGameMode == GAME_MODE_IN_GAME)
        return (sMode < WARP_MODE_CUTSCENE || sMode == WARP_MODE_SAVE || sMode == WARP_MODE_EVENT) ?
            SCRIPT_ROOM : SCRIPT_NONE;
    if (gMainGameMode == GAME_MODE_MAP_SCREEN && gPauseScreenFlag == 2)
        return SCRIPT_PAUSE;
    return SCRIPT_MENU;
}

void Port_WarpFrame(void)
{
    u32 interval;
    s32 script;

    if (!sStarted)
        return;

    sFrames++;
    interval = Port_WarpInterval();
    if (interval != 0 && sFrames >= interval)
    {
        WarpNext();
        return;
    }

    if (gMainGameMode == GAME_MODE_IN_GAME && gSubGameMode1 == SUB_GAME_MODE_PLAYING)
        sPlayingFrames++;

    if (sMode >= WARP_MODE_CUTSCENE && sModeStage == 0 && sPlayingFrames >= MODE_DELAY &&
        gSubGameMode1 == SUB_GAME_MODE_PLAYING && gMainGameMode == GAME_MODE_IN_GAME)
    {
        if (sMode == WARP_MODE_SAVE)
        {
            sModeStage = 1;
        }
        else if (sMode != WARP_MODE_CREDITS && sMode != WARP_MODE_EVENT)
        {
            WarpEnterMode();
            if (gSubGameMode1 != SUB_GAME_MODE_PLAYING)
                sModeStage = 1;
        }
    }
    else if (sMode == WARP_MODE_SAVE && sModeStage >= 1 && sModeStage <= 4)
    {
        // What the save pad's message banner does, one step per frame.
        Sram_QuickSave(sModeStage - 1);
        sModeStage++;
    }
    else if (sMode == WARP_MODE_SAVE && sModeStage == 5)
    {
        Port_Log("warp: saved, resetting");
        sModeStage = 6;
        gMainGameMode = GAME_MODE_SOFT_RESET;
    }

    Port_WarpFacing((gSamusData.direction & KEY_LEFT) != 0);
    script = WarpScriptForMode();
    if (script != sScript)
    {
        sScript = script;
        Port_WarpScript(script);
    }
}
