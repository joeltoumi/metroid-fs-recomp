// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — test warp target list (the game side is port/game/warp.c).
//
//   MZM_WARP=AREA:ROOM[,AREA:ROOM...]   AREA is a number (0-6) or a name
//                                       (brinstar, kraid, norfair, ridley,
//                                       tourian, crateria, chozodia); ROOM
//                                       is a number or * (every room)
//   MZM_WARP=cutscene:N|*, tourianescape:0, chozodiaescape:0, credits:0
//                                       game modes instead of a room
//   MZM_WARP_FRAMES=N                   frames per room when there are
//                                       several (default 300)
//
// A test tool: it skips the intro and starts a fresh game in that room with
// every item.
#include "port.h"

#include <stdlib.h>
#include <strings.h>

enum { MAX_TARGETS = 64 };

static struct {
    int area;
    int room;
} sTargets[MAX_TARGETS];
static int sCount = -1;
static unsigned sInterval;

static const char* const sAreaNames[] = {
    "brinstar", "kraid", "norfair", "ridley", "tourian", "crateria", "chozodia",
};

// Same order as PORT_WARP_CUTSCENE...
static const char* const sModeNames[] = {
    "cutscene", "tourianescape", "chozodiaescape", "credits",
};

static int ParseArea(const char* s, size_t len)
{
    char* end;
    long n = strtol(s, &end, 10);

    if (end == s + len)
        return (int)n;
    for (size_t i = 0; i < sizeof(sAreaNames) / sizeof(sAreaNames[0]); i++) {
        if (strlen(sAreaNames[i]) == len && strncasecmp(s, sAreaNames[i], len) == 0)
            return (int)i;
    }
    for (size_t i = 0; i < sizeof(sModeNames) / sizeof(sModeNames[0]); i++) {
        if (strlen(sModeNames[i]) == len && strncasecmp(s, sModeNames[i], len) == 0)
            return PORT_WARP_CUTSCENE + (int)i;
    }
    return -1;
}

static void Parse(void)
{
    const char* s = getenv("MZM_WARP");
    const char* frames = getenv("MZM_WARP_FRAMES");

    sCount = 0;
    while (s && *s && sCount < MAX_TARGETS) {
        const char* colon = strchr(s, ':');
        const char* comma = strchr(s, ',');
        if (!comma)
            comma = s + strlen(s);
        if (colon && colon < comma) {
            int area = ParseArea(s, (size_t)(colon - s));
            int room = colon[1] == '*' ? -1 : atoi(colon + 1);
            if (area >= 0) {
                sTargets[sCount].area = area;
                sTargets[sCount].room = room;
                sCount++;
            } else {
                Port_Log("MZM_WARP: unknown area '%.*s'", (int)(colon - s), s);
            }
        }
        s = *comma ? comma + 1 : comma;
    }

    // One room stays forever; a list moves on every N frames.
    if (sCount > 1 || (sCount == 1 && sTargets[0].room < 0))
        sInterval = frames ? (unsigned)strtoul(frames, NULL, 10) : 300;
    if (sCount > 1 && sInterval == 0)
        sInterval = 300;
}

int Port_WarpTarget(int index, int* area, int* room)
{
    if (sCount < 0)
        Parse();
    if (index < 0 || index >= sCount)
        return 0;
    *area = sTargets[index].area;
    *room = sTargets[index].room;
    return 1;
}

unsigned int Port_WarpInterval(void)
{
    if (sCount < 0)
        Parse();
    return sInterval;
}
