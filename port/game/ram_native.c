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
