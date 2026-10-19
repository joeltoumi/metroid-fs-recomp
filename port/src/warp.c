// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — test warp: target list and scripted input (the game side is
// port/game/warp.c). See docs/PORT.md.
//
//   MF_WARP=TARGET[,TARGET...]
//     TARGET = AREA:ROOM[@EVENT]   AREA is a number (0-9) or a name (main,
//                                  s1..s6, srx, tro, pyr, aqa, arc, noc,
//                                  test1..test3); ROOM is a number or *
//                                  (every room with a door); EVENT sets the
//                                  event counter (decimal or 0x..)
//            | MODE:N|*[@EVENT]    cutscene:1-12, nav:EVENT (navigation
//                                  conversation), pause:0 (map/status),
//                                  gameover:0, ending:0, credits:0,
//                                  sr388:0 (collision ending), saxcloseup:0,
//                                  save:0 (save + reload the file),
//                                  event:N (the room where event N happens,
//                                  with the event before it)
//   MF_WARP_FRAMES=N    frames per target when there are several (default 300)
//   MF_WARP_DIRECT=1    cutscenes start right at boot instead of from a room
//   MF_WARP_MOVE=0      no scripted input (default: walk, jump, shoot, morph
//                       in rooms; press A in menus)
//
// A test tool: it skips the title screen and starts a fresh game in that room
// with every item.
#include "port.h"

#include <stdlib.h>
#include <strings.h>

enum { MAX_TARGETS = 128 };

// Must match port/game/warp.c.
enum {
    WARP_MODE_FIRST = 100,
};

static struct {
    int area;
    int room;
    int event;
} sTargets[MAX_TARGETS];
static int sCount = -1;
static unsigned sInterval;
static int sMove = 1;

static int sScript;
static unsigned sScriptFrame;
static int sFacingLeft;
static int sMirror;

static const struct {
    const char* name;
    int area;
} sAreaNames[] = {
    { "main", 0 }, { "maindeck", 0 }, { "s1", 1 }, { "srx", 1 }, { "s2", 2 }, { "tro", 2 },
    { "s3", 3 },   { "pyr", 3 },      { "s4", 4 }, { "aqa", 4 }, { "s5", 5 }, { "arc", 5 },
    { "s6", 6 },   { "noc", 6 },      { "test1", 7 }, { "test2", 8 }, { "test3", 9 },
};

// Same order as the WARP_MODE_* list in port/game/warp.c.
static const char* const sModeNames[] = {
    "cutscene", "nav", "pause", "gameover", "ending", "credits", "sr388", "saxcloseup", "save", "event",
};

static int ParseArea(const char* s, size_t len)
{
    char* end;
    long n = strtol(s, &end, 10);

    if (len != 0 && end == s + len)
        return (int)n;
    for (size_t i = 0; i < sizeof(sAreaNames) / sizeof(sAreaNames[0]); i++) {
        if (strlen(sAreaNames[i].name) == len && strncasecmp(s, sAreaNames[i].name, len) == 0)
            return sAreaNames[i].area;
    }
    for (size_t i = 0; i < sizeof(sModeNames) / sizeof(sModeNames[0]); i++) {
        if (strlen(sModeNames[i]) == len && strncasecmp(s, sModeNames[i], len) == 0)
            return WARP_MODE_FIRST + (int)i;
    }
    return -1;
}

static void Parse(void)
{
    const char* s = getenv("MF_WARP");
    const char* frames = getenv("MF_WARP_FRAMES");
    const char* move = getenv("MF_WARP_MOVE");

    sCount = 0;
    if (move && strcmp(move, "0") == 0)
        sMove = 0;
    while (s && *s && sCount < MAX_TARGETS) {
        const char* colon = strchr(s, ':');
        const char* comma = strchr(s, ',');
        if (!comma)
            comma = s + strlen(s);
        if (colon && colon < comma) {
            const int area = ParseArea(s, (size_t)(colon - s));
            const int room = colon[1] == '*' ? -1 : (int)strtol(colon + 1, NULL, 0);
            const char* at = memchr(colon, '@', (size_t)(comma - colon));
            if (area >= 0) {
                sTargets[sCount].area = area;
                sTargets[sCount].room = room;
                sTargets[sCount].event = at ? (int)strtol(at + 1, NULL, 0) : -1;
                sCount++;
            } else {
                Port_Log("MF_WARP: unknown area '%.*s'", (int)(colon - s), s);
            }
        } else {
            Port_Log("MF_WARP: expected AREA:ROOM, got '%.*s'", (int)(comma - s), s);
        }
        s = *comma ? comma + 1 : comma;
    }

    // One room stays forever; a list (or *) moves on every N frames.
    if (sCount > 1 || (sCount == 1 && sTargets[0].room < 0))
        sInterval = frames ? (unsigned)strtoul(frames, NULL, 10) : 300;
    if ((sCount > 1 || (sCount == 1 && sTargets[0].room < 0)) && sInterval == 0)
        sInterval = 300;
    if (sCount != 0)
        Port_Log("MF_WARP: %d target(s), %u frames each", sCount, sInterval);
}

int Port_WarpTarget(int index, int* area, int* room, int* event)
{
    if (sCount < 0)
        Parse();
    if (index < 0 || index >= sCount)
        return 0;
    *area = sTargets[index].area;
    *room = sTargets[index].room;
    *event = sTargets[index].event;
    return 1;
}

int Port_WarpDirect(void)
{
    const char* direct = getenv("MF_WARP_DIRECT");
    return direct && strcmp(direct, "1") == 0;
}

unsigned int Port_WarpInterval(void)
{
    if (sCount < 0)
        Parse();
    return sInterval;
}

void Port_WarpFacing(int left)
{
    sFacingLeft = left;
}

void Port_WarpScript(int script)
{
    sScript = script;
    sScriptFrame = 0;
}

// Run forward shooting, jump, run back, jump, morph and lay bombs, stand
// up, aim up and shoot. `c` is the frame in the 320-frame cycle.
static uint16_t RoomKeys(unsigned c, uint16_t fwd, uint16_t back)
{
    if (c < 90)
        return fwd | ((c & 8) ? PORT_KEY_B : 0);
    if (c < 110)
        return fwd | PORT_KEY_A;
    if (c < 200)
        return back | ((c & 8) ? PORT_KEY_B : 0);
    if (c < 220)
        return back | PORT_KEY_A;
    if (c < 226)
        return PORT_KEY_DOWN;
    if (c < 232)
        return 0;
    if (c < 238)
        return PORT_KEY_DOWN;
    if (c < 270)
        return (c & 8) ? PORT_KEY_B : 0;
    if (c < 280)
        return PORT_KEY_UP;
    if (c < 300)
        return PORT_KEY_UP | ((c & 4) ? PORT_KEY_B : 0);
    return (c & 4) ? PORT_KEY_R | PORT_KEY_B : PORT_KEY_R;
}

// Scripted input, read once per frame with the host's keys.
uint16_t Port_WarpKeys(void)
{
    const unsigned t = sScriptFrame++;
    unsigned c;

    if (!sMove)
        return 0;
    switch (sScript) {
    case PORT_WARP_SCRIPT_ROOM:
        // Starts the way Samus faces, so she sees the room before going back
        // through the door she came in by.
        if (t < 30)
            return 0;
        if (t == 30)
            sMirror = sFacingLeft;
        c = (t - 30) % 320;
        return sMirror ? RoomKeys(c, PORT_KEY_LEFT, PORT_KEY_RIGHT)
                       : RoomKeys(c, PORT_KEY_RIGHT, PORT_KEY_LEFT);
    case PORT_WARP_SCRIPT_MENU:
        // Advance text and menus.
        return (t % 40) == 39 ? PORT_KEY_A : 0;
    case PORT_WARP_SCRIPT_PAUSE:
        // Map screen, then the status screen and back (L/R in Fusion's
        // pause screen), move the cursor around.
        c = t % 240;
        if (c == 60 || c == 61)
            return PORT_KEY_R;
        if (c >= 80 && c < 120)
            return (c & 8) ? PORT_KEY_DOWN : PORT_KEY_RIGHT;
        if (c == 150 || c == 151)
            return PORT_KEY_L;
        if (c >= 170 && c < 200)
            return (c & 8) ? PORT_KEY_UP : PORT_KEY_LEFT;
        return 0;
    default:
        return 0;
    }
}
