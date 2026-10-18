#ifndef PORT_DECOMP_GAME_OVER_H
#define PORT_DECOMP_GAME_OVER_H

#include "types.h"
#include "oam.h"

/*
 * Game over screen (asm/disasm_0x0809deb4.s, 0x0809deb4 - 0x0809e598).
 * US behaviour; the language only picks the "CONTINUE / QUIT" text graphics.
 */

struct GameOverOam;
typedef void (*GameOverOamFunc_T)(struct GameOverOam*);

// 0x18 bytes on GBA
struct GameOverOam {
    u16 xPosition;                  // 0x0
    u16 yPosition;                  // 0x2
    u8 type;                        // 0x4 (0 = free slot)
    u8 drawn;                       // 0x5
    u8 currentAnimationFrame;       // 0x6
    u8 animationDurationCounter;    // 0x7
    u8 unk_8;                       // 0x8
    u8 stage;                       // 0x9
    u8 objMode;                     // 0xA
    u8 priority;                    // 0xB
    u8 xFlip;                       // 0xC
    u8 paletteOffset;               // 0xD
    u16 tileOffset;                 // 0xE
    const struct FrameData* pOam;   // 0x10
    GameOverOamFunc_T pFunc;        // 0x14
};

struct GameOverData {
    u8 unk_0;                       // 0x0
    u8 optionChosen;                // 0x1
    u8 afterChoiceTimer;            // 0x2
    u8 selectedOption;              // 0x3 (1 = continue, 2 = quit)
    struct GameOverOam oam[3];      // 0x4
};

#define GAME_OVER_DATA (*(struct GameOverData*)&gNonGameplayRam)

#define GAME_OVER_OAM_TYPE_CURSOR 1
#define GAME_OVER_OAM_TYPE_FOLLOW_CURSOR 2

// Static data blob of src/data/sa_x_close_up.c (sBlob_73421e_7478a0, ROM 0x0873421e)
extern const u8 sBlob_73421e_7478a0[];
#define BLOB_73421E(off) (&sBlob_73421e_7478a0[(off)])

// PORT: the frame data below lives inside a raw binary blob and holds GBA ROM pointers,
// it must be decoded into real struct FrameData arrays for a native build.
#define sGameOverOam_Cursor           ((const struct FrameData*)BLOB_73421E(0x8056)) // 0x0873c274
#define sGameOverOam_CursorSelected   ((const struct FrameData*)BLOB_73421E(0x807e)) // 0x0873c29c
#define sGameOverOamXWidthTable       BLOB_73421E(0x2)    // 0x08734220, u8[3][4] width in tiles by shape/size
#define sGameOverObjGfx               BLOB_73421E(0x585a) // 0x08739a78 (LZ77)
#define sGameOverObjPal               BLOB_73421E(0x82c6) // 0x0873c4e4
#define sGameOverBgGfx                BLOB_73421E(0xe)    // 0x0873422c (LZ77)
#define sGameOverBg3TileTable         BLOB_73421E(0x84c6) // 0x0873c6e4 (LZ77)
#define sGameOverBg1TileTable         BLOB_73421E(0x8a8a) // 0x0873cca8 (LZ77)
#define sGameOverBgPal                BLOB_73421E(0x80c6) // 0x0873c2e4

u8 GameOverHandler(void);
void GameOverInit(void);
u8 GameOverAfterOptionDelay(void);
u8 GameOverSetupOam(u8 type, u16 xPosition, u16 yPosition);
void GameOverProcessCursor(struct GameOverOam* pOam);
void unk_9e2cc(struct GameOverOam* pOam);
void GameOverResetOam(u8 slot);
void GameOverProcessOam(void);
void GameOverDrawAllOam(void);
void GameOverDrawOam(struct GameOverOam* pOam);
u16 GameOverGetPositionAndSlotOfOamByType(u8 type, u16* pX, u16* pY);
void GameOverVblank(void);
void unk_9e58c(void);

#endif /* PORT_DECOMP_GAME_OVER_H */
