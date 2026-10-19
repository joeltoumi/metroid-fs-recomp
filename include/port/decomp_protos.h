#ifndef PORT_DECOMP_PROTOS_H
#define PORT_DECOMP_PROTOS_H

/*
 * Prototypes of the functions translated from asm/ (port/decomp) that the
 * rest of the game calls. The full declarations (with the data and structs
 * each translation uses) are in port/decomp/*.h; only what src/ needs is
 * repeated here, so the force-included prototypes stay free of their macros.
 */

#include "types.h"

// special_cutscene.c
boolu32 CutsceneHandler(void);
boolu32 DiedFromSr388CollisionHandler(void);
void NewFileIntroInit(void);
boolu32 IntroProcessText(void);
void SpecialCutsceneProcessOam(void);
void SpecialCutsceneDrawAllOam(void);
void SpecialCutsceneFadeIn(void);
void SpecialCutsceneDestroyOamOfType(u8 type);
void SpecialCutsceneProcessMonologue(void);
boolu32 NewFileIntroCheckMonologueEnded(void);
boolu32 NewFileIntroProcessAdamText(void);
void NewFileIntroSamusGettingCuredSetupWindow(void);
void unk_98158(void);

// intro_space_view.c, new_file_intro_asm.c
boolu32 IntroSpaceView(void);
boolu32 IntroSamusShipCrashing(void);
boolu32 NewFileIntroLandingOnBsl(void);

// ending.c, ending_image.c
boolu32 EndingHandler(void);
void EndingDrawIgtAndCompletionPercentage(void);
void EndingImageUpdateLettersSpawnDelay(u32 slot);
void EndingImageLoadTextOam(u32 text);
void EndingImageDisplayLinePermanently(u32 line);

// erase_sram.c, file_select.c, game_over.c, language_select_eu.c
u8 EraseSramMenuHandler(void);
s8 FileSelectHandler(void);
u8 GameOverHandler(void);
u32 SetLanguage(u8 unused);

// navigation.c, pause_screen.c
u8 GetFlashingSectorNumber(void);
void GetMinimapData(u8 area, void* dst);
u32 PauseScreenHandler(void);
void unk_77840(u8 request);

// sram_files.c
void Sram_ReadAll(void);
void Sram_ProcessIntroSave(u8 stage);
void Sram_QuickSave(u8 stage);
void SramWrite_MostRecentSaveFile(void);
void Sram_ResetForDemo(void);
s8 Sram_ChecLoadSaveFileWithBlank(void);

#endif /* PORT_DECOMP_PROTOS_H */
