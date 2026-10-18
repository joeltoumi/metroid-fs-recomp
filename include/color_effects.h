#ifndef COLOR_EFFECTS_H
#define COLOR_EFFECTS_H

#include "types.h"

void ColorEffectCopyPalramToEwramPal2And1(void);
void ColorEffectCopyPalramToEwramPal2(void);
void ColorEffectCopyPalramToEwramPal1(void);
void ColorEffectCopyEwramPal2ToEwramPal1(void);
void ColorEffectCopyEwramPal3ToEwramPal1(void);
void ColorEffectCopyBgPal3AndObjPal2ToPal1(void);
void ColorEffectMakePaletteMonochrome(void);
void ColorEffectCheckTransferFadedPalette_All(void);
void ColorEffectCheckTransferFadedPalette_SkipSamus(void);
void ColorEffectFadePalette_SkipHud(boolu8 fadeOut, u8 step);
void ColorEffectFadePalette_All(boolu8 fadeOut, u8 step);
void ColorEffectFadePalette_SkipSamus(boolu8 fadeOut, u8 step);
bools32 ColorEffectUpdateBgCrossFade(boolu8 startPal3, s8 speed);
void ColorEffectMakeObjPaletteMonochrome(u8 startRow);
void ColorEffectPowerBombYellowTint(u8 startRow);
void ColorEffectMakeBgPaletteMonochrome(void);
s32 ColorEffectBlendFromWhite(u8 red, u8 green, u8 blue, u8 step);
s32 ColorEffectBlendToWhite(u8 red, u8 green, u8 blue, u8 step);
s32 ColorEffectBlendFromBlack(u8 red, u8 green, u8 blue, u8 step);
s32 ColorEffectBlendToBlack(u8 red, u8 green, u8 blue, u8 step);

#endif /* COLOR_EFFECTS_H */
