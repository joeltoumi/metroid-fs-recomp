#ifndef PORT_RAM_UNALIGNED_H
#define PORT_RAM_UNALIGNED_H

/*
 * mf-android, native build only (force-included through port/prototypes.h,
 * before any declaration).
 *
 * linker.ld places these arrays at their GBA addresses, which are not
 * multiples of 16. On x86-64, an array of 16 bytes or more is assumed to be
 * 16-byte aligned, so clang uses aligned SSE moves (movaps) on it and the game
 * crashes. Each name is turned into "the array a pointer points to": the
 * declarations in the headers then declare that pointer, and the accesses go
 * through it with only the element type's alignment. The pointers are defined
 * in port/game/ram_symbols.c (tools/port/gen_ram_symbols.py, same list).
 */
#ifdef PLATFORM_PC
#define gSpritesetSpriteGfxSlots (*gSpritesetSpriteGfxSlots_PortPtr)
#define gCurrentScrolls (*gCurrentScrolls_PortPtr)
#define gSpriteDebris (*gSpriteDebris_PortPtr)
#define gParticleEffects (*gParticleEffects_PortPtr)
#define gAmmoDigitsGfx (*gAmmoDigitsGfx_PortPtr)
#define gFileSelectFileInfo (*gFileSelectFileInfo_PortPtr)
#define gInterruptCode (*gInterruptCode_PortPtr)
#define gOamData (*gOamData_PortPtr)
#define gSaXElevatorBgCnt (*gSaXElevatorBgCnt_PortPtr)
#define gPrevious64Positions (*gPrevious64Positions_PortPtr)
#define gDemoInputs (*gDemoInputs_PortPtr)
#define gDemoInputDurations (*gDemoInputDurations_PortPtr)
#define gSaXElevatorSprites (*gSaXElevatorSprites_PortPtr)
#define gSamusPalette (*gSamusPalette_PortPtr)
#define gHatchData (*gHatchData_PortPtr)
#define gBombChains (*gBombChains_PortPtr)
#define gVerticalTilemap (*gVerticalTilemap_PortPtr)
#define gAnimatedGraphicsData (*gAnimatedGraphicsData_PortPtr)
#endif

#endif /* PORT_RAM_UNALIGNED_H */
