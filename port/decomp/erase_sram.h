#ifndef ERASE_SRAM_H
#define ERASE_SRAM_H

/*
 * Erase SRAM menu (boot with Up + Select + B + L)
 * (asm/disasm_0x0807e678.s, 0x080809f0 - 0x08081168).
 */

#include "types.h"
#include "oam.h"
#include "structs/menus/pause_screen.h"

/* ---------------------------------------------------------------------------------------------- */
/* Data blobs (static in src/data / src/*.c, externed here)                                       */
/* ---------------------------------------------------------------------------------------------- */

/* PORT: static in src/data/sram_pointers.c (0x08582288), must be made visible for the native build */
extern const u8 sBlob_582288_58b3cc[];
/* PORT: static in src/text.c (0x0879c170), must be made visible for the native build */
extern u8 sBlob_79c170_79c27c[];

/* 0x085822f0: object palette (0x70 colors) */
#define sEraseSramObjPal ((const u16*)(sBlob_582288_58b3cc + 0x68))
/* 0x085823d0: background palette (0x100 colors) */
#define sEraseSramBgPal ((const u16*)(sBlob_582288_58b3cc + 0x148))
/* 0x08582bbc: LZ77 object graphics (VRAM 0x6012000) */
#define sEraseSramObjGfx (sBlob_582288_58b3cc + 0x934)
/* 0x0858340c: LZ77 background graphics (VRAM 0x6001000) */
#define sEraseSramBgGfx (sBlob_582288_58b3cc + 0x1184)
/* 0x0858abe4: LZ77 BG1 tilemap */
#define sEraseSramBg1Tilemap (sBlob_582288_58b3cc + 0x895C)
/* 0x0858adf0: LZ77 BG3 tilemap */
#define sEraseSramBg3Tilemap (sBlob_582288_58b3cc + 0x8B68)
/* 0x0858b3b0: oam ids of the 4 options (yes/no of the 2 questions) */
#define sEraseSramOptionsOamIds (sBlob_582288_58b3cc + 0x9128)
/* 0x0858b3b4: sounds, indexed by the sound played by EraseSramCheckForInput (0 = none) */
#define sEraseSramSounds ((const u16*)(sBlob_582288_58b3cc + 0x912C))
/* 0x0858b3be: (x, y) position of the 2 questions */
#define sEraseSramQuestionsPositions ((const u8 (*)[2])(sBlob_582288_58b3cc + 0x9136))
/* 0x0858b3c2: (x, y) offset of the cursor for each option */
#define sEraseSramCursorOffsets ((const s8 (*)[2])(sBlob_582288_58b3cc + 0x913A))

/*
 * PORT: 0x0879c228, per language (LZ77 graphics of the text, LZ77 graphics of the text objects) pointers.
 * This blob holds raw 32-bit GBA pointers; the native port has to provide a real pointer table here.
 */
#define sEraseSramTextGfxPointers ((const u8* const (*)[2])(sBlob_79c170_79c27c + 0xB8))
/*
 * PORT: 0x0879c260, oam animations of the menu objects (indexed by oam id, 0 unused).
 * This blob holds raw 32-bit GBA pointers; the native port has to provide a real pointer table here.
 */
#define sEraseSramOam ((const struct FrameData* const*)(sBlob_79c170_79c27c + 0xF0))

/* ---------------------------------------------------------------------------------------------- */
/* Structures                                                                                      */
/* ---------------------------------------------------------------------------------------------- */

enum EraseSramObject {
    ERASE_SRAM_OBJECT_CURSOR,
    ERASE_SRAM_OBJECT_QUESTION_2, // second question options
    ERASE_SRAM_OBJECT_QUESTION_1, // first question options
    ERASE_SRAM_OBJECT_END
};

#define ERASE_SRAM_ACTION_PENDING 0x80

/* Erase SRAM menu data, overlays gNonGameplayRam */
struct EraseSramData {
    /* 0x00 */ u8 cursor; // 0 = first question yes, 1 = first question no, 2 = second question yes, 3 = second question no
    /* 0x01 */ u8 action; // new cursor | ERASE_SRAM_ACTION_PENDING
    /* 0x02 */ u8 language;
    /* 0x03 */ u8 unk_3;
    /* 0x04 */ u16 timer;
    /* 0x06 */ u16 bldcnt; // Written to REG_BLDCNT on v-blank when not 0
    /* 0x08 */ u8 targetBldy;
    /* 0x09 */ u8 unk_9[3];
    /* 0x0C */ struct MenuOam oam[ERASE_SRAM_OBJECT_END];
};

#define ERASE_SRAM_DATA (*(struct EraseSramData*)&gNonGameplayRam)

/* ---------------------------------------------------------------------------------------------- */
/* Functions                                                                                       */
/* ---------------------------------------------------------------------------------------------- */

u8 EraseSramMenuHandler(void);
s8 EraseSramProcessInput(void);
void EraseSramApplyInput(void);
u8 EraseSramCheckForInput(void);
void EraseSramMenuInit(void);
void EraseSramResetOam(void);
void EraseSramUpdateCursorPosition(void);
void EraseSramVBlank(void);
void EraseSramLoadingVBlank(void);
void EraseSramProcessOam(void);

#endif /* ERASE_SRAM_H */
