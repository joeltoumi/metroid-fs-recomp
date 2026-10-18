#ifndef COLOR_FADING_H
#define COLOR_FADING_H

#include "types.h"

bools32 ColorFadingUpdate(boolu8 fadeOut, u8 speed);
void ColorFadingTransferPaletteOnTransition(void);
void ColorFadingTransferPaletteOnTransition_NoSaXElevator(void);
void ColorFadingFillAndTransferPalette(u16 color, boolu8 skipBgHatches, boolu8 skipObjHud);
void ColorFadingStartNoTransition(void);
void ColorFadingStartEscapeFailed_Unused(void);
void ColorFadingStartEscapeFailed(void);
void ColorFadingStartFinalEscape(void);
s32 ColorFadingExpandWindow(void);
bools32 ColorFadingCloseWindowOnSamus(void);
void ColorFadingStart(u8 type);
void ColorFadingStartDefault(void);
void ColorFadingStartDoorTransition(void);
void ColorFadingGradients(s32 delay);
void ColorFadingFinishDoorFade(void);
bools32 ColorFadingReveal(void);
s32 ColorFadingProcess(void);
bools32 ColorFadingProcess_DoorTransition(void);
bools32 ColorFadingProcess_Default(void);
bools32 ColorFadingProcess_LabEscape(void);
bools32 ColorFadingProcess_EscapeFailed(void);
bools32 ColorFadingProcess_FinalEscape(void);
bools32 ColorFadingProcess_DemoEnd(void);
bools32 ColorFadingUpdate_DoorTransition(void);
void ColorFadingApplyMonochrome(void);

#endif /* COLOR_FADING_H */
