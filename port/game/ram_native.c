// SPDX-License-Identifier: GPL-3.0-or-later
// mf-android — the RAM variables that are bigger natively than on the GBA.
//
// They hold pointers (8 bytes here, 4 on the GBA), so at their linker.ld
// offset inside gPortIwram they would overlap the next variables. They are
// ordinary variables instead (tools/port/gen_ram_symbols.py leaves them out
// of ram_symbols.c: keep both lists the same), in the save state section.
// Each takes the type its game header declares.
#include "types.h"
#include "globals.h"
#include "callbacks.h"
#include "structs/audio.h"
#include "structs/bg_clip.h"
#include "structs/haze.h"
#include "structs/room.h"
#include "structs/samus.h"
#include "structs/sa_x.h"
#include "structs/sprite.h"
#include "structs/sprite_debris.h"
#include "structs/projectile.h"
#include "structs/animated_graphics.h"
#include "structs/clipdata.h"
#include "structs/scroll.h"

void* memset(void* dst, int value, unsigned long size);

#define PORT_RAM_NATIVE(name) __attribute__((section("mf_state"), aligned(16))) __typeof__(name) name

PORT_RAM_NATIVE(gHazeInfo);
PORT_RAM_NATIVE(gBackgroundsData);
PORT_RAM_NATIVE(gCurrentRoomEntry);
PORT_RAM_NATIVE(gSpriteData);
PORT_RAM_NATIVE(gCurrentSprite);
PORT_RAM_NATIVE(gSpriteDebris);
PORT_RAM_NATIVE(gCurrentSpriteDebris);
PORT_RAM_NATIVE(gSubSpriteData1);
PORT_RAM_NATIVE(gSubSpriteData2);
PORT_RAM_NATIVE(gProjectileData);
PORT_RAM_NATIVE(gCurrentProjectile);
PORT_RAM_NATIVE(gSamusGraphicsInfo);
PORT_RAM_NATIVE(gSamusEnvironmentalEffects);
PORT_RAM_NATIVE(gSaXData);
PORT_RAM_NATIVE(gNonGameplayRam);
PORT_RAM_NATIVE(gVBlankCallback);
PORT_RAM_NATIVE(gHBlankCallback);
PORT_RAM_NATIVE(gVCountCallback);
PORT_RAM_NATIVE(gSoundCodeAPointer);
PORT_RAM_NATIVE(gSoundCodeBPointer);
PORT_RAM_NATIVE(gSoundCodeCPointer);
PORT_RAM_NATIVE(gSaXElevatorSprites);
PORT_RAM_NATIVE(gTilemapAndClipPointers);
PORT_RAM_NATIVE(gClipdataCodePointer);
PORT_RAM_NATIVE(gAnimatedGraphicsData);
PORT_RAM_NATIVE(gCurrentRoomScrollDataPointer);
PORT_RAM_NATIVE(gHazeProcessCodePointer);
PORT_RAM_NATIVE(gInterruptCodePointer);

// The game clears IWRAM (except its last 0x200 bytes) at boot and on soft
// reset: clear these too.
void PortClearNativeRam(void)
{
    memset(&gHazeInfo, 0, sizeof(gHazeInfo));
    memset(&gBackgroundsData, 0, sizeof(gBackgroundsData));
    memset(&gCurrentRoomEntry, 0, sizeof(gCurrentRoomEntry));
    memset(&gSpriteData, 0, sizeof(gSpriteData));
    memset(&gCurrentSprite, 0, sizeof(gCurrentSprite));
    memset(&gSpriteDebris, 0, sizeof(gSpriteDebris));
    memset(&gCurrentSpriteDebris, 0, sizeof(gCurrentSpriteDebris));
    memset(&gSubSpriteData1, 0, sizeof(gSubSpriteData1));
    memset(&gSubSpriteData2, 0, sizeof(gSubSpriteData2));
    memset(&gProjectileData, 0, sizeof(gProjectileData));
    memset(&gCurrentProjectile, 0, sizeof(gCurrentProjectile));
    memset(&gSamusGraphicsInfo, 0, sizeof(gSamusGraphicsInfo));
    memset(&gSamusEnvironmentalEffects, 0, sizeof(gSamusEnvironmentalEffects));
    memset(&gSaXData, 0, sizeof(gSaXData));
    memset(&gNonGameplayRam, 0, sizeof(gNonGameplayRam));
    memset(&gVBlankCallback, 0, sizeof(gVBlankCallback));
    memset(&gHBlankCallback, 0, sizeof(gHBlankCallback));
    memset(&gVCountCallback, 0, sizeof(gVCountCallback));
    memset(&gSoundCodeAPointer, 0, sizeof(gSoundCodeAPointer));
    memset(&gSoundCodeBPointer, 0, sizeof(gSoundCodeBPointer));
    memset(&gSoundCodeCPointer, 0, sizeof(gSoundCodeCPointer));
    memset(&gSaXElevatorSprites, 0, sizeof(gSaXElevatorSprites));
    memset(&gTilemapAndClipPointers, 0, sizeof(gTilemapAndClipPointers));
    memset(&gClipdataCodePointer, 0, sizeof(gClipdataCodePointer));
    memset(&gAnimatedGraphicsData, 0, sizeof(gAnimatedGraphicsData));
    memset(&gCurrentRoomScrollDataPointer, 0, sizeof(gCurrentRoomScrollDataPointer));
    memset(&gHazeProcessCodePointer, 0, sizeof(gHazeProcessCodePointer));
}
