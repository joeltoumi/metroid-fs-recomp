#ifndef PORT_DECOMP_LANGUAGE_SELECT_EU_H
#define PORT_DECOMP_LANGUAGE_SELECT_EU_H

#include "types.h"
#include "file_select.h"

/*
 * EU only: language select screen (EU ROM 0x080a1490 - 0x080a1adc).
 *
 * In the US ROM this code is reduced to SetLanguage always picking English plus
 * the unused unk_a13e0/unk_a1478/unk_a147c (port/decomp/file_select.c). The EU
 * ROM has the full screen: it is shown on the first boot (no language saved yet,
 * gSubGameMode2 0) and when "Language" is picked on the title screen
 * (TitleScreenHandler returns 2, gSubGameMode2 3).
 *
 * It reuses the file select OAM objects (FILE_SELECT_DATA.oam, FileSelectProcessOam,
 * FileSelectDrawAllOam) and these FILE_SELECT_DATA fields:
 *   textId     (0x8)  cleared on init
 *   stage      (0xA)  0 = choosing, 1 = chosen, 2 = cancelled (B, from the title screen only), 100 = done
 *   timer      (0xC)
 *   fileCursor (0xD)  language cursor, gLanguage - LANGUAGE_ENGLISH
 * No new RAM variable is used.
 */

#ifdef REGION_EU

enum LanguageSelectOamType {
    LANGUAGE_SELECT_OAM_TYPE_NONE,
    LANGUAGE_SELECT_OAM_TYPE_CURSOR_FIRST_BOOT,
    LANGUAGE_SELECT_OAM_TYPE_SELECTED,
    LANGUAGE_SELECT_OAM_TYPE_CURSOR_FROM_TITLE,
};

u32 SetLanguage(u8 fromTitleScreen);
void LanguageSelectInit(u8 fromTitleScreen);
void LanguageSelectVBlank(void);
void LanguageSelectVBlank_Empty(void);
u32 LanguageSelectProcessFirstBoot(void);
u32 LanguageSelectProcessFromTitle(void);
u8 LanguageSelectSetupOam(u8 type, u16 xPosition, u16 yPosition);
void LanguageSelectProcessCursorFirstBoot(struct FileSelectOam* pOam);
void LanguageSelectProcessCursorFromTitle(struct FileSelectOam* pOam);
void LanguageSelectProcessSelected(struct FileSelectOam* pOam);
u32 LanguageSelectCheckLanguageSet(void);

#endif /* REGION_EU */

#endif /* PORT_DECOMP_LANGUAGE_SELECT_EU_H */
