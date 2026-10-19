#include "data/blob_pieces.h"
#ifndef PORT_DECOMP_CUTSCENES_2_H
#define PORT_DECOMP_CUTSCENES_2_H

// Cutscenes (second half of asm/disasm_0x0808F5C4.s, from unk_9c04c to the end):
// restricted lab detaching (end), BSL exploding, cutscene monologue helpers,
// generic cutscene fades/OAM.
// Also owns the shared cutscene RAM structs (used by cutscenes_1.c too).

#include "types.h"
#include "oam.h"
#include "globals.h"

struct CutsceneOam;
struct CutsceneMonologueOam;

typedef void (*CutsceneOamFunc_T)(struct CutsceneOam*);
typedef void (*CutsceneMonologueOamFunc_T)(struct CutsceneMonologueOam*);

// Generic cutscene oam, 0x24 bytes on GBA (gNonGameplayRam + 0x18, 16 entries)
struct CutsceneOam {
    s16 xPosition;                      // 0x0
    s16 yPosition;                      // 0x2
    s16 scaling;                        // 0x4
    s16 unk_6;                          // 0x6
    s16 unk_8;                          // 0x8
    s16 unk_A;                          // 0xA
    s16 unk_C;                          // 0xC
    u16 unk_E;                          // 0xE
    u8 type;                            // 0x10
    u8 currentAnimationFrame;           // 0x11
    u8 animationDurationCounter;        // 0x12
    u8 timer;                           // 0x13
    u8 stage;                           // 0x14
    u8 rotation;                        // 0x15
    u8 exists:1;                        // 0x16 bit 0 (drawn)
    u8 affineMode:2;                    // bits 1-2 (0 normal, 1 affine, 3 affine double size)
    u8 objMode:2;                       // bits 3-4
    u8 unk_16_5:1;                      // bit 5
    u8 xFlip:1;                         // bit 6
    u8 yFlip:1;                         // bit 7
    u8 tileOffsetLow;                   // 0x17
    u8 tileOffsetHigh:2;                // 0x18 bits 0-1
    u8 priority:2;                      // bits 2-3
    u8 paletteOffset:4;                 // bits 4-7
    u8 unk_19;                          // 0x19
    u8 unk_1A;                          // 0x1A
    u8 unk_1B;                          // 0x1B
    const struct FrameData* pOam;       // 0x1C
    CutsceneOamFunc_T pFunction;        // 0x20
};

#define CUTSCENE_OAM_COUNT 16

// Generic cutscene data (overlays gNonGameplayRam)
struct CutsceneData {
    u16 stage;                          // 0x0
    u16 unk_2;                          // 0x2
    u16 unk_4;                          // 0x4
    u16 unk_6;                          // 0x6
    u16 timer;                          // 0x8
    s16 unk_A;                          // 0xA (palette update flag / misc)
    s16 unk_C;                          // 0xC (palette index / misc)
    u16 unk_E;                          // 0xE
    u8 subStage;                        // 0x10
    u8 unk_11;                          // 0x11
    u8 oamCount;                        // 0x12 (number of processed oam, set by CutsceneProcessOam)
    u8 unk_13[5];                       // 0x13
    struct CutsceneOam oam[CUTSCENE_OAM_COUNT]; // 0x18
};

// Cutscene monologue oam, 0x18 bytes on GBA (gNonGameplayRam + 0x214, 5 entries)
struct CutsceneMonologueOam {
    u16 xPosition;                      // 0x0
    u16 yPosition;                      // 0x2
    u8 process;                         // 0x4 (pFunction is called)
    u8 draw;                            // 0x5
    u8 currentAnimationFrame;           // 0x6
    u8 animationDurationCounter;        // 0x7
    u8 timer;                           // 0x8
    u8 stage;                           // 0x9
    u8 objMode;                         // 0xA
    u8 priority;                        // 0xB
    u8 xFlip;                           // 0xC
    u8 paletteOffset;                   // 0xD
    u16 tileOffset;                     // 0xE
    const struct FrameData* pOam;       // 0x10
    CutsceneMonologueOamFunc_T pFunction; // 0x14
};

#define CUTSCENE_MONOLOGUE_OAM_COUNT 5
#define CUTSCENE_MONOLOGUE_TEXT_ROWS 9
#define CUTSCENE_MONOLOGUE_TEXT_COLUMNS 28

// Cutscene monologue data (overlays gNonGameplayRam)
struct CutsceneMonologueData {
    u16 column;                         // 0x0 (current text tile column)
    u16 line;                           // 0x2 (current text line, in tiles, 2 per row)
    u16 unk_4;                          // 0x4 (reveal column)
    u16 unk_6;                          // 0x6 (reveal line)
    u16 stage;                          // 0x8
    u16 unk_A;                          // 0xA (text index)
    const u16* pText;                   // 0xC
    u16 timer;                          // 0x10
    u16 unk_12;                         // 0x12
    u16 unk_14;                         // 0x14
    u8 unk_16;                          // 0x16 (fade sub timer)
    u8 unk_17;                          // 0x17
    u8 indent;                          // 0x18 (pixel offset inside the current tile)
    u8 unk_19[3];                       // 0x19
    u8 unk_1C[CUTSCENE_MONOLOGUE_TEXT_ROWS][CUTSCENE_MONOLOGUE_TEXT_COLUMNS];   // 0x1C (tile reveal counters)
    u8 unk_118[CUTSCENE_MONOLOGUE_TEXT_ROWS][CUTSCENE_MONOLOGUE_TEXT_COLUMNS];  // 0x118 (tile reveal timers)
    struct CutsceneMonologueOam oam[CUTSCENE_MONOLOGUE_OAM_COUNT]; // 0x214
};

#define CUTSCENE_DATA (*(struct CutsceneData*)&gNonGameplayRam)
#define MONOLOGUE_DATA (*(struct CutsceneMonologueData*)&gNonGameplayRam)

// RAM without a linker.ld name: u8 at 0x03001238, next free affine matrix group for cutscene oam
extern u8 gUnk_3001238;

// Static blobs of src/data/new_file_intro_data.c (need to be made non-static for the native build)

// Prototypes of functions from cutscenes_1.c
u8 CutsceneRestrictedLabDetachingSetupOam(u8 type, u16 xPosition, u16 yPosition);

// Functions
void unk_9c04c(struct CutsceneOam* pOam);
void unk_9c080(u8 type, s16 xPosition, s16 yPosition, u16 unk_C);
void unk_9c0b4(u8 type, s16 xPosition, s16 yPosition, u16 unk_C, u16 unk_A);
void CutsceneRestrictedLabDetachingGetPositionOfOamByType(u8 type, s16* pXPosition, s16* pYPosition);
void CutsceneRestrictedLabDetachingVblank(void);
void unk_9c1bc(void);
boolu8 CutsceneBslExploding(void);
void CutsceneBslExplodingInit(void);
boolu8 CutsceneBslExplodingProcess(void);
void CutsceneBslExplodingProcessScrolling(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessBslFar(struct CutsceneOam* pOam);
void CutsceneBslExplodingProcessExplosions(struct CutsceneOam* pOam);
u8 CutsceneBslExplodingSetupOam(u8 type, u16 xPosition, u16 yPosition, boolu8 fromEnd);
u8 CutsceneBslExplodingGetOamInfoByType(u8 type, s16* pXPosition, s16* pYPosition, s16* pScaling);
void CutsceneBslExplodingVblank(void);
void unk_9c92c(void);
void CutsceneMonologueProcessCursor(struct CutsceneMonologueOam* pOam);
boolu8 CutsceneMonologueProcessSpecialTextCharacters(void);
void CutsceneMonologueProcessText(void);
void unk_9cc4c(void);
void CutsceneMonologueFadeIn(void);
void CutsceneMonologueFadeOut(void);
void CutsceneMonologueProcessOam(void);
void CutsceneMonologueDrawAllOam(void);
void CutsceneMnologueDrawOam(struct CutsceneMonologueOam* pOam);
void CutsceneMonologueResetOam(u8 slot);
void unk_9d09c(struct CutsceneMonologueOam* pOam);
void unk_9d0a0(void);
void unk_9d1c4(void);
void CutsceneMonologueDestroyOamOfType(u8 type);
void CutsceneFadeIn(void);
void CutsceneFadeOut(void);
void CutsceneDestroyOamOfType(u8 type);
void CutsceneProcessOam(void);
void CutsceneDrawAllOam(void);
void CutsceneDrawOam(struct CutsceneOam* pOam);
void unk_9db70(struct CutsceneOam* pOam);

#endif /* PORT_DECOMP_CUTSCENES_2_H */
