#include "data/blob_pieces.h"
#include "globals.h"
#include "new_file_intro.h"

#include "constants/game_state.h"
#include "constants/audio.h"
#include "constants/text.h"
#include "constants/new_file_intro.h"

#include "structs/cutscene.h"

#include "data/new_file_intro_data.h"
#include "data/generic_data.h"
#include "data/menus/title_screen.h"
#include "data/sprite_data.h"
#include "data/sprites/hornoad.h"
#include "data/sprites/x_parasite.h"
#include "data/projectile_data.h"
#include "data/audio.h"

extern const u8 sBlob_5dfd6c_5e116c[];
extern const u8 sBlob_6b2fac_72eee0[];

void unk_99940(void); // For V-blank callback

u8 SpecialCutsceneGetRandomNumber(void);
u8 NewFileIntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder);
boolu32 NewFileIntroSamusDrifting(void);
static void NewFileIntroSamusShipFlyingInit(void);
static boolu32 NewFileIntroSamusShipFlyingProcess(void);
static boolu32 NewFileIntroSamusShipFlying(void);
static void NewFileIntroSamusFaintingInit(void);
static boolu32 NewFileIntroSamusFaintingProcess(void);
static boolu32 NewFileIntroSamusFainting(void);
void NewFileIntroProcessOam_Empty(void);
void NewFileIntroProcessTextCursor(struct SpecialCutsceneOam* pOam);
void NewFileIntroSr388PreviewVblank(void);
u8 NewFileIntroSr388SetupOam(u8 type, s16 xPosition, s16 yPosition);
boolu32 NewFileIntroSr388Preview(void);
void NewFileIntroSetupSr388PreviewAsteroid(u8 type, s16 xPosition, s16 yPosition, s16 arg3);
void NewFileIntroInSr388Vblank(void);
u8 NewFileIntroInSr388SetupOam(IntroInSr388OamType type, s16 xPosition, s16 yPosition);
boolu32 NewFileIntroInSr388(void);
void NewFileIntroGetPositionOfOamByType(IntroInSr388OamType type, s16* pXPosition, s16* pYPosition);
void NewFileIntroSamusGettingCuredVblank(void);
u8 NewFileIntroSamusGettingCuredSetupOam(IntroSamusGettingCuredOamType type, s16 xPosition, s16 yPosition);
void NewFileIntroSamusGettingCuredNervousSystemVblank(void);
boolu32 NewFileIntroSamusGettingCured(void);
void NewFileIntroSamusGettingCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam);
u8 NewFileIntroFindOamByType(IntroSamusGettingCuredOamType type);
u8 NewFileIntroSamusFoundSetupOam(IntroSamusFoundOamType type, s16 xPosition, s16 yPosition);
void NewFileIntroSamusFoundVblank(void);
boolu32 NewFileIntroSamusFound(void);
u8 NewFileIntroSamusCuredSetupOam(IntroSamusCuredOamType type, s16 xPosition, s16 yPosition);
void NewFileIntroSamusCuredVblank(void);
boolu32 NewFileIntroSamusCured(void);
void NewFileIntroSamusCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam);
void NewFileIntroArrivingAtBslVblank(void);
boolu32 NewFileIntroArrivingAtBsl(void);
u8 NewFileIntroArrivingAtBslSetupOam(IntroArrivingAtBslOamType type, s16 xPosition, s16 yPosition);
u8 NewFileIntroGetPositionAndSlotOfOamByType(IntroArrivingAtBslOamType type, s16* pXPosition, s16* pYPosition);
void NewFileIntroArrivingAtBslProcessOam_Empty(struct SpecialCutsceneOam* pOam);

static u16* sMonologueTextPointersJapanese[19];
static u16* sMonologueTextPointersEnglish[19];
static u16* sMonologueTextPointersGerman[19];
static u16* sMonologueTextPointersFrench[19];
static u16* sMonologueTextPointersItalian[19];
static u16* sMonologueTextPointersSpanish[19];

const u8* sTitleScreenDebugTextPointer = {
    sTitleScreenDebugText,
};

const struct FrameData* sData_79C2CC[6] = {
    sOam_597ec0,
    sOam_597ed0,
    sOam_597ee0,
    sOam_597ef0,
    sOam_597ee0,
    sOam_597ed0
};

static const u16* sArray_79c2e4[12] = {
	sPal_5bf838,
	sPal_5bf8b8,
	sPal_5bf938,
	sPal_5bf9b8,
	sPal_5bfa38,
	sPal_5bfab8,
	sPal_5bfb38,
	sPal_5bfbb8,
	sPal_5bfc38,
	sPal_5bfcb8,
	sPal_5bfd38,
	sPal_5bfdb8
};

static const u16* sPalPointers_79c314[16] = {
	(const u16*)sBlob_5dfd6c_5e116c,
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x140),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x12c0),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x280),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x3c0),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x500),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x640),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x780),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x8c0),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0xa00),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0xb40),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0xc80),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0xdc0),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0xf00),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x1040),
	(const u16*)((const u8*)sBlob_5dfd6c_5e116c + 0x1180)
};

static const u16* sPalPointers_79c354[16] = {
	(const u16*)sBlob_5f6990_5fe370,
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x80))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x100))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x180))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x200))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x280))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x300))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x380))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x400))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x480))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x500))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x580))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x600))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x680))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x700))),
	(const u16*)(((const u8*)((const u8*)sBlob_5f6990_5fe370 + 0x780)))
};

const void* sPointers_79c394[13] = {
    (const void*)&sFrameData_60ac08[0],
    (const void*)&sFrameData_60ac18[0],
    (const void*)&sFrameData_60ac28[0],
    (const void*)&sFrameData_60ac38[0],
    (const void*)&sFrameData_60ac28[0],
    (const void*)&sFrameData_60ac18[0],
    (const void*)&sPointers_79ce10[0],
    (const void*)&sPointers_79ce10[225],
    (const void*)&sPointers_79ce10[447],
    (const void*)&sPointers_79ce10[672],
    (const void*)&sPointers_79ce10[897],
    (const void*)&sPointers_79ce10[1122],
    (const void*)&sPointers_79ce10[1347],
};

static const u32* sIntroSr388SurfaceBgGfxPointers[8] = {
    sIntroSr388SurfaceBgGfx0,
    sIntroSr388SurfaceBgGfx1,
    sIntroSr388SurfaceBgGfx2,
    sIntroSr388SurfaceBgGfx3,
    sIntroSr388SurfaceBgGfx4,
    sIntroSr388SurfaceBgGfx5,
    sIntroSr388SurfaceBgGfx6,
    sIntroSr388SurfaceBgGfx7
};

static const u32* sIntroSr388PlanetBgGfxPointers[5] = {
    sIntroSr388PlanetBgGfx0,
    sIntroSr388PlanetBgGfx1,
    sIntroSr388PlanetBgGfx2,
    sIntroSr388PlanetBgGfx3,
    sIntroSr388PlanetBgGfx4
};

static const u32* sIntroBslObjectGfxPointers[8] = {
    sIntroBslObjectGfx0,
    sIntroBslObjectGfx1,
    sIntroBslObjectGfx2,
    sIntroBslObjectGfx3,
    sIntroBslObjectGfx4,
    sIntroBslObjectGfx5,
    sIntroBslObjectGfx6,
    sIntroBslObjectGfx7
};

const u32* sIntroSamusSittingBgGfxPointers[5] = {
    sIntroSamusSittingBgGfx0,
    sIntroSamusSittingBgGfx1,
    sIntroSamusSittingBgGfx2,
    sIntroSamusSittingBgGfx3,
    sIntroSamusSittingBgGfx4
};

static const u32* sIntroSamusHelmetCloseupBgGfxPointers[6] = {
    sIntroSamusHelmetCloseupBgGfx0,
    sIntroSamusHelmetCloseupBgGfx1,
    sIntroSamusHelmetCloseupBgGfx2,
    sIntroSamusHelmetCloseupBgGfx3,
    sIntroSamusHelmetCloseupBgGfx4,
    sIntroSamusHelmetCloseupBgGfx5
};

const void* sPointers_79c448[87] = {
    (const void*)sBlob_64e470_65bb38,
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x738),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x101c),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x1b80),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x2404),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x2c8c),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x3350),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x3a7c),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x3d98),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x4124),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x4524),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x4764),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x5510),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x6284),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x6e30),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x7acc),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x8860),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x8f98),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x9554),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x98bc),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x9af0),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x9ce0),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0x9ff8),
    (const void*)((const u8*)sBlob_64e470_65bb38 + 0xa3d8),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)sBlob_66aa68_6719cc,
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)sBlob_66aa68_6719cc,
    (const void*)sBlob_671a04_679280,
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x20),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_66aa68_6719cc + 0x160),
    (const void*)((const u8*)sBlob_671a04_679280 + 0x160),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_6638a0_663dd0 + 0x180),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)sBlob_663eac_66aa30,
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)sBlob_663eac_66aa30,
    (const void*)((const u8*)sBlob_66aa68_6719cc + 0xabc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x200),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_663eac_66aa30 + 0x3d6c),
    (const void*)((const u8*)sBlob_66aa68_6719cc + 0x41b0),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)((const u8*)sBlob_65c268_662804 + 0x39bc),
    (const void*)sBlob_662cfc_663820,
    (const void*)((const u8*)sBlob_66aa68_6719cc + 0x220),
    (const void*)sBlob_662cfc_663820,
    (const void*)sBlob_662cfc_663820,
    (const void*)((const u8*)sBlob_66aa68_6719cc + 0x220),
    (const void*)((const u8*)sBlob_671a04_679280 + 0x220),
    (const void*)sBlob_662cfc_663820,
    (const void*)sBlob_662cfc_663820,
    (const void*)sBlob_662cfc_663820,
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_66aa30[0],
    (const void*)&sFrameData_66aa58[0],
    (const void*)&sFrameData_6719cc[0],
    (const void*)&sFrameData_6719f4[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
    (const void*)&sFrameData_663dd0[0],
    (const void*)&sFrameData_663df8[0],
};

u16** sMonologueTextPointers[LANGUAGE_COUNT] = {
    sMonologueTextPointersJapanese,
    sMonologueTextPointersJapanese,
    sMonologueTextPointersEnglish,
    sMonologueTextPointersGerman,
    sMonologueTextPointersFrench,
    sMonologueTextPointersItalian,
    sMonologueTextPointersSpanish
};

const void* sPointers_79c5c0[518] = {
    (const void*)sBlob_6b2fac_72eee0,
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x124),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x164),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x244),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x286),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x322),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x372),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x410),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x552),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x60e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x656),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x684),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x70e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x734),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x74e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x762),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x782),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x79e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x808),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x82e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x840),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x86c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x884),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x89c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x930),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x972),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa00),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa40),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xaa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xabc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xad6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xaf0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb0a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb4c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbaa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbd2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbe6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbf6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc1c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc46),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc68),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc7c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xce4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdc0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe00),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xee2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xfc0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1010),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x105e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1150),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1196),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x122c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x126e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1322),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1350),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x137e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1400),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1420),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x143c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1468),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x150c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1524),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x153c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1560),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1592),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x160c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1650),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1676),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x169a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x171a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x172c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x173c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x174a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1758),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1766),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1774),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1782),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1790),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x179e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x180c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1824),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1838),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1848),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1860),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x186e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x187c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x188a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1898),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x195a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1aa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1be0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1c5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cd0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1dbc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1e14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1e88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f06),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ff8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2064),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2150),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x223a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x232c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2428),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2518),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2548),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2582),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x25c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x25fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2666),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x26c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x26f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2718),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x274e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2796),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2822),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2888),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2966),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a20),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2acc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b66),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ba6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bc6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2be6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c06),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c42),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ca8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2cc4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ce6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2cfc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d4e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2dbc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2de8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e6e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ebc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2fa0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3012),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3082),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3156),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3242),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x333c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x33ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3400),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3472),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x354c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3640),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3720),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x378e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3802),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x386e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x38ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3966),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ad6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ce8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d20),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3dd0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ea4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4000),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4070),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4108),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4174),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4202),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4218),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4238),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4258),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4278),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4298),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4302),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x431c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4336),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4358),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4370),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x439a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4418),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4428),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x444e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x447c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4510),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x452c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x456a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4662),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x475a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x47b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4812),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4880),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x48fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4962),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4aa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bf2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ce0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4dbc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ff4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5060),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5146),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x517c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5214),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5254),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x533c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5386),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5456),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5534),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x561c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5690),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x570e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x575a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x57a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5814),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5882),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5896),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x591c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x593e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5960),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5982),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a36),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a5e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aaa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ad0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5afa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b20),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b4c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ba4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5be4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5cb2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d22),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d96),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5eee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f68),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5fcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6042),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x60ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x612c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6194),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6260),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6334),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6396),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6404),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x647c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x655c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x65cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6634),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x66a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6704),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6768),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x67d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x685e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6896),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6926),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x696c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6aa6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ae4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b7e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6bd6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6cc6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d40),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6db2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6dfa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6e4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ec4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6fa6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6fc8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6fea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x700c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x702e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7046),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7068),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x708a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x70ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x70d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x70ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7108),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7132),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x715e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x718a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x71aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x71d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x71f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7224),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7262),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7292),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x72c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x72e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7328),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x738e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x73f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7460),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x74c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7510),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7566),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x75cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7642),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x76bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x773a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x77a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x780e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x787e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x78f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x795e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x79d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7a54),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7ac6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7ba4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7c1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7c92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7cfc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7d62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7dc6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7e28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7e9e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7ee4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7f2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7f88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x7fca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8042),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x80a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x80da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8106),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8142),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x819c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x81fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x825a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x82d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8354),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x83cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8448),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8482),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x84d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8540),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x858e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x859e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x85c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x85e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8606),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8626),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8646),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8666),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8686),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x86aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x86ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8700),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x872c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8754),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x877c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x879a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x87c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x87ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8816),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8838),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8860),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8890),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x88c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8904),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8938),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8972),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8998),
};

const u16** sLocationTextPointers[LANGUAGE_COUNT] = {
    (const u16**)(((const u8*)&sPointers_79c5c0[48])),
    (const u16**)(((const u8*)&sPointers_79c5c0[122])),
    (const u16**)(((const u8*)&sPointers_79c5c0[196])),
    (const u16**)(((const u8*)&sPointers_79c5c0[270])),
    (const u16**)(((const u8*)&sPointers_79c5c0[344])),
    (const u16**)(((const u8*)&sPointers_79c5c0[418])),
    (const u16**)(((const u8*)&sPointers_79c5c0[492]))
};

u16** sMessageTextPointers[LANGUAGE_COUNT] = {
    (u16**)&sPointers_79c5c0[0],
    (u16**)(((const u8*)&sPointers_79c5c0[74])),
    (u16**)(((const u8*)&sPointers_79c5c0[148])),
    (u16**)(((const u8*)&sPointers_79c5c0[222])),
    (u16**)(((const u8*)&sPointers_79c5c0[296])),
    (u16**)(((const u8*)&sPointers_79c5c0[370])),
    (u16**)(((const u8*)&sPointers_79c5c0[444]))
};

const void* sPointers_79ce10[1572] = {
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x89d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8c72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8c8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8cd6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8cf2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8d08),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x8d1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9334),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x934c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9522),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9538),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9554),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9570),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9582),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9594),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x984a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9862),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9874),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9886),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9ac0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9ae8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9d90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9de6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9eb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x9f1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa10a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa14e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa886),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa8fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa9aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa9e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xa9fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xaa0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xac04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xac5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb17a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb1ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb1cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb1de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb202),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb226),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb5c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xb5f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbaa8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbafa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbb88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbbca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbbdc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xbbee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc0b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc0de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc168),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc188),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc1b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc1e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc568),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc5ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc5be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xc5d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcc3a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcc9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xce30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xce88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcf2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcf72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcf88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xcf9e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd2e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd31c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd332),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd348),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd75c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd78c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd7a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xd7b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xda92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdaec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdb70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdbba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdbcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdbde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdc0a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdc20),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdf14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdf34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdf46),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xdf58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe0e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe10e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe376),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe3b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe576),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe59e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe5c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe606),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe78e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xe7ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xea66),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xeab2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xebf0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xec50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf222),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf23a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf814),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xf828),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xfe48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xfe90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xff10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xff58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xff6a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xff7c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xffcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0xffde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10086),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1008c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x100e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x100fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1014c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1019e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x101ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10216),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10242),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1027a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x102b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1030c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1036e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x103c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1041a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10470),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x104c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10518),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10578),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x105dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10646),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x106a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10706),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10766),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x107c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1082a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1088c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x108f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1095c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1099c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x109b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10a1c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10a38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10aa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10afe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10b54),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10bae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10c18),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10c82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10cec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10d50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10d7c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10dcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10e0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10e50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10e92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10ed4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10f16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10f58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x10fb2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1100c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11066),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x110c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11120),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1117c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x111cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11228),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11290),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x112f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11360),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x113cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1142a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1147a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x114d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11520),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11580),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x115dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1163c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11698),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x116f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11750),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1176a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11784),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x117de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11838),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1189a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x118c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11926),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11984),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x119e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11a30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11a7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11aae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11b10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11b72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11bce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11c2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11c42),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11cb2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11d00),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11d4e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11d9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11dea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11e1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11e6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11eba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11ed8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11f34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11f8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x11fac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12004),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1205c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x120b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1210c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12164),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1219e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x121d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12212),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1224c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x122a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x122d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x122fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12328),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x125c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x125dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12626),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12642),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12658),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1266a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12c84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12c9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12e72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12e88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12ea4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12ec0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12ed2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x12ee4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13196),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x131ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x131c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x131d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1340c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13434),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x136dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13732),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13800),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1386a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13a5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x13a9e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x141d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14248),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x142f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14336),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14348),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1435a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1455a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x145b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14aca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14b0a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14b1c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14b2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14b52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14b76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14f1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x14f4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x153fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1544e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x154da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1551c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1552e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15540),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x159fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15a24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15aae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15ace),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15afa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15b26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15e9e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15ee2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15ef4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x15f06),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1656c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x165ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1675e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x167b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16854),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16898),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x168ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x168c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16c02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16c3c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16c52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x16c68),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1707c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x170ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x170c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x170da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x173ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17406),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1748a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x174d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x174e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x174fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17526),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1753c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1782e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1784e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17860),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17872),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17a02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17a28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17c90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17cca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17e94),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17ebc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17ede),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17f24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17f50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x17f78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x181ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18236),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18370),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x183d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18986),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1899e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18f76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x18f8a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x195a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x195ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1966e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x196b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x196c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x196da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1972a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1973c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x197e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x197ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19840),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1985c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x198ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x198fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1994a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19976),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x199ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x199e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19a1c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19a76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19ad8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19b2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19b84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19bda),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19c2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19c82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19ce2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19d46),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19db2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19e14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19e76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19eba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19f1c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19f7e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x19fe0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a04a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a0b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a0f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a106),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a172),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a18e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a1b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a20c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a262),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a2bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a326),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a390),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a3de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a43c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a468),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a4b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a4fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a53c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a57e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a5c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a602),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a644),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a69e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a6f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a752),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a7b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a80c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a868),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a8b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a914),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a97c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1a9e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1aa30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1aa98),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1aafc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ab52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1abae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1abf8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ac58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1acb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ad14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ad70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1adcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ae28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ae42),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ae5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1aeb6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1af10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1af72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1afa0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1affe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b050),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b09a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b0ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b130),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b14c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b1a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b204),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b250),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b2b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b302),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b350),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b39e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b3ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b420),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b46e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b4bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b4da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b536),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b58e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b5b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b60a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b664),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b6be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b718),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b772),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b7ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b7ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b826),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b87e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b8aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b8d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1b904),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1bcce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1bd06),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1bd92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1bdd2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1bdf8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1be1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1c926),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1c94c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cbd4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cc04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cc3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cc60),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1cc86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ccac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d058),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d07e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d0a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d0ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d470),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d4a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d872),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1d8da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1da28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1dad4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1dde2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1de48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1e814),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1e8e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1e9da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ea3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ea64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ea8a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ede2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1ee52),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f68a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f6e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f70e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f734),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f742),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1f752),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1fd7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x1fdb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20466),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x204d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x205c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2062c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20652),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20678),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20e74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20ea8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20f7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20f8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x20fc6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21000),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21500),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21568),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2158e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x215b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21dea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x21e5e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x220c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22130),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22222),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22284),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x222aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x222d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22768),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x227ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x227f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2281a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22eea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22f3c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22f62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x22f88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23450),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x234c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2357c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x235f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23618),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2363e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x236b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x236dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23c60),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23ca2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23cc8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23cee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23f94),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x23ff4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24388),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x243e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24796),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x247d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24810),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24870),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24b36),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x24be8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2503e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x250b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x25280),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x252f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x25c70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x25c94),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x26736),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x26748),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27428),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27490),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2756e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x275a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x275ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x275f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2767e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x276b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2779a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x277a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27812),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2784c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x278b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27928),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2797c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x279ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x279dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27a1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27a60),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27ad6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27b48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27bbe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27c34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27caa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27d14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27d90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27e08),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27e80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27eec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27f4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x27fa8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28006),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28078),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x280ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2815c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x281c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2823c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x282a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x282c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28336),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28354),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x283c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2843c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x284a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28506),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28566),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x285c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28626),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2869c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x286ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28754),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x287b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2881c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28880),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x288e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28948),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x289ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28a10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28a74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28ad8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28b50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28bc0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28c3c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28ca8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28d0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28d6e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28dd0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28e32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28ea4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28f0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28f7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x28fe6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2904c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x290be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29128),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29184),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x291f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29264),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x292d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x292fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29328),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29396),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29404),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2947a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x294e4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29556),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x295c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2963a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x296b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2971c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29790),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29804),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29878),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x298f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29968),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29990),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29a04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29a78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29aec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29b5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29bc8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29c30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29c98),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29d00),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29d38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29d70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29de6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29e24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29e8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29efc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29f6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x29fdc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a04c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a0a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a104),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a160),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a1bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a230),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a25a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a276),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a294),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a6de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a72c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a808),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a86c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a894),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2a8bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b714),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2b750),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ba88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bb18),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bb7e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bbbe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bbe6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2bc0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c136),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c174),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c19c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c1c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c628),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2c66e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2cb8e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2cc08),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2cdca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2ceac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d2c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2d350),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2dffa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e146),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e268),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e318),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e340),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e368),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e7a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2e878),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f2ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f39a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f3c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f3ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f3f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2f406),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2fc54),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x2fca4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3066e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30724),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30868),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30920),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30948),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x30970),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31448),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31490),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31580),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31592),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x315e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31632),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31d4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31de4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31e0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x31e34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x328ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32984),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32d2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32de0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32f1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32fce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x32ff6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3301e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x335c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x33642),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3366a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x33692),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x33fa8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34028),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34050),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34078),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x346ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34798),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x348ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34976),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3499e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x349c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34a5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x34aa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x350ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3512c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35154),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3517c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x354c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35540),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x359aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35a2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35f08),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35f58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x35f94),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36048),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36418),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36500),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36a3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36ad0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36d78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x36e32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x37b7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x37bbe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x38b96),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x38ba8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39c28),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39c8a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39db6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39ddc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39e04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39e2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39ed8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x39f16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a084),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a090),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a108),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a14a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a1c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a240),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a2b2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a310),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a36e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a3be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a3f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a452),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a4ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a524),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a57a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a5d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a63a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a6b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a734),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a7ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a826),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a888),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a8ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a94c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3a9bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3aa2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3aa9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ab16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ab92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3abf2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ac18),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ac8a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3aca8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ad1a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ad8e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ae04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ae7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3aedc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3af3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3afa0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b01a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b082),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b0fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b16a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b1da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b24a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b2ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b32a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b39a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b40c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b47e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b4f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b55c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b5d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b654),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b6c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b73e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b7a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b802),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b864),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b8da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b954),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3b9cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ba3a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3baa8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bb1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bb98),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bbf6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bc6e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bce6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bd5e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bd9a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bdd6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3be4e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bec6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bf3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3bfb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c026),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c098),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c10a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c180),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c1de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c24a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c2ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c34a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c3b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c422),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c452),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c4ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c53c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c5aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c618),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c686),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c6f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c764),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c7d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c806),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c83a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c8b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c8f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c964),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3c9de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ca58),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cad2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cb4c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cba8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cc04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cc60),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ccbc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cd34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cd7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cd96),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3cdb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d1e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d222),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d2c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d334),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d35a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3d380),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3dea6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3dede),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e1c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e1fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e23e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e276),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e29c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e2c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e672),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e6aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e6d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3e6f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ea8c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3eacc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ef26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ef98),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f0d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f194),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f4c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3f52c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x3ff90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40090),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x401a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40222),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40248),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4026e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x405a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40626),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40e4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40ed2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40ef8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40f1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40f2a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x40f38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41548),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4158e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41c92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41d14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41e0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41e8e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41eb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x41eda),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x426de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4271c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42810),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42822),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42860),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4289e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42dd2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42e4c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42e72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x42e98),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x436f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43774),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43a10),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43a84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43b82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43bfe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43c24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x43c4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x440e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4415c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44182),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x441a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44916),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44982),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x449a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x449ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44f3c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x44fb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45096),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4510e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45134),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4515a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x451d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45212),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x457a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x457e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4580e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45834),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45b00),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45b62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45f2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x45f92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46380),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x463c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46400),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46480),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46786),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46830),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46c62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46ce4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46ef4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x46f70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x47926),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4793c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x483ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x483fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x490b0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49124),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49204),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49244),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4926a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49290),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4933a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4935e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49468),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49474),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x494ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4952e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4959e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4960c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49676),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x496b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x496f6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4973a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4977c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x497ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49856),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x498c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49932),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x499a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49a08),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49a7a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49aec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49b64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49bde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49c54),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49cca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49d40),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49da2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49e02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49e64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49ede),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49f50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49fca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x49fec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a052),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a070),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a0d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a14a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a1c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a246),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a2bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a332),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a3a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a418),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a460),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a4d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a546),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a5ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a62e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a6a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a716),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a78a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a7fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a872),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a8e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a95c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4a9c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4aa34),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4aaaa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ab26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ab9c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ac12),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ac88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4acfe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ad78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ade0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ae5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4aece),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4af48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4afba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b02c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b0a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b114),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b188),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b1c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b204),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b278),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b2ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b354),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b3ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b430),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b496),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b4fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b56a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b5e6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b658),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b6ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b73c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b7b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b834),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b86e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b8e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b958),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4b9d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4ba4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bac2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bb32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bbac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bc26),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bc5e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bc96),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bd0c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bd4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bdba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4be36),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4beb2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bf2e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4bfaa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c00c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c06e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c0d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c132),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c19a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c1c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c1e2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c200),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c61c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c656),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c710),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c754),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c780),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4c7ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d2b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d2ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d55a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d59c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d5d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d608),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d634),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4d660),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4da02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4da38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4da64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4da90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4de62),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4dea6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e260),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e2ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e412),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e4d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e7de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4e82a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f236),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f326),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f442),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f4b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f4e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f50c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f82c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x4f89e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50094),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50116),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50142),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5016e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50180),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50192),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x507dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50820),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50f64),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x50fde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x510fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51178),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x511a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x511d0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51a70),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51aa8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51b6a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51b7c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51bb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x51bec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x520ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5213a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52166),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52192),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52968),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x529e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52c3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52cac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52dee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52e5c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52e88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x52eb4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53378),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x533da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53406),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53432),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53bcc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53c20),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53c4c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x53c78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5412e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54198),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5426a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x542d4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54300),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5432c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x543a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x543d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54916),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5496a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54996),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x549c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54c76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x54cd8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x550a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5510a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x554aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x554e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55522),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5558e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55882),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55920),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55d84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55df2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x55fb2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5601c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5694a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x56958),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x573da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x573ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x580bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5811c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5825c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5829a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x582c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x582f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5838e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x583ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x584b8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x584c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58530),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58570),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x585da),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5863c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58696),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x586c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x586f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58732),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58774),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x587ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58858),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x588a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x588f8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58948),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x589ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58a24),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58a88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58b04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58b72),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58bc8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58c1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58c74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58cde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58d48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58db2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58e16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58e80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58ee0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58f02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58f5e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58f82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x58fde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59048),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x590c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59130),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5919e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5920c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5927a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x592f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5933c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x593ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59410),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59474),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x594d8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5953c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x595a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59604),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59666),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x596c8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5972a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5978a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x597f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5985a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x598c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59932),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x599a2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59a12),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59a82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59afa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59b76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59bf0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59c68),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59ce0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59d56),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59db6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59e30),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59ea2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59f14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59f86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x59fc6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a006),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a072),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a0de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a140),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a1b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a22a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a2a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a316),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a390),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a3f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a452),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a4cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a546),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a5c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a63a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a66e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a6ea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a756),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a7c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a82e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a89a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a8fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a964),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5a9ce),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aa06),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aa3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aab2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aaec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ab46),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5abbc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ac32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aca8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ad1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ad80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ade2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ae44),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5aea6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5af22),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5af50),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5af6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5af88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b394),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b3e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b48e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b4d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b4fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5b522),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c18e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c1ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c482),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c4c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c508),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c564),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c58c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5c5b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ca02),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ca32),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ca5a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ca82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5cea4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5cee4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d316),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d37c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d508),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d580),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d936),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5d9a0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e59c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e6be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e7e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e85e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e886),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5e8ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ec16),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5ec96),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f660),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f6fa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f722),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f74a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f75a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5f76a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5fe9a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x5feda),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x606c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6076c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x60830),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6088e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x608b6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x608de),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61208),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61248),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61300),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61326),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6135a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6138e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x618ae),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61924),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6194c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x61974),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62228),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x622ac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x625ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6266a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62786),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62804),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6282c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62854),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62dde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62e42),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62e6a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x62e92),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x636dc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63746),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6376e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63796),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63d3e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63dca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63e78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63f04),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63f2c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63f54),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63fc4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x63fe8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64666),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x646c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x646ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64716),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64a88),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64aea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64f22),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x64f82),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6537a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x653a8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x653e8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6546e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6575e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6581a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x65ce2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x65d46),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x65f76),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x65fda),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x669be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x669d6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6746a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6747c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x681cc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6822e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6835c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6839c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x683c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x683ec),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6847a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x684a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68584),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68590),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68608),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68650),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x686ba),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68730),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6879a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x687e0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68826),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68872),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x688c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6892e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x689a6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68a18),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68a8a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68afc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68b74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68be2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68c56),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68cd0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68d4a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68dc0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68e36),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68eac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68f1e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x68f90),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69002),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69064),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x690d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69130),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69152),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x691c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x691f0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69262),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x692d2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69346),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x693bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69422),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69488),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x694ee),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6955a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x695c2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69628),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6968e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x696f4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6975a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x697c0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69826),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6988c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x698f2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69958),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x699be),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69a36),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69aa2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69b0e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69b78),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69bf4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69c60),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69ccc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69d38),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69dac),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69e14),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69e84),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69ef4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69f6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x69fde),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a04e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a0aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a11c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a18e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a200),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a228),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a250),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a2c4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a338),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a3b4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a422),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a48a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a4fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a556),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a5ca),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a648),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a6c6),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a738),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a7aa),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a80c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a86e),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a8a4),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a912),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a988),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6a9fe),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6aa74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6aaea),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ab56),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6abc8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ac3a),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ac86),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6acd2),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ad48),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ad80),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6adf8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ae74),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6aef0),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6af6c),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6afe8),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b052),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b0bc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b126),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b190),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b1fc),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b226),
    (const void*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b242),
};

static u16* sMonologueTextPointersJapanese[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b260),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b538),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b6d2),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6b868),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ba0a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6bb88),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6bd00),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c016),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c4ec),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c580),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c5c0),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c650),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c6aa),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c76e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c820),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c8ea),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6c9de),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ca86),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6cae6)
};

static u16* sMonologueTextPointersEnglish[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6cb28),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d142),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d364),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d57c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d79c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6d99e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6db9e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6e16a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6e982),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ea66),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6eb0a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ec7c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ed66),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6ef74),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f0bc),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f28c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f48c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f5a4),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f64c)
};

static u16* sMonologueTextPointersGerman[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x6f6f4),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7006a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x70378),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x70678),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x709ac),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x70c36),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x70e98),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x717b2),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7231a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x72466),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7253e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7272c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x72872),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x72ab4),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x72be8),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x72e00),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x73090),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7321a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x732fe)
};

static u16* sMonologueTextPointersFrench[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x733e0),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x73afa),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x73d52),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x73f58),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7415a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x74368),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x74576),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x74b5c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x75310),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x753fa),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x754ba),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7565c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7573c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7590e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x75a66),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x75c50),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x75e9e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x75fea),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x760a2)
};

static u16* sMonologueTextPointersItalian[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x76150),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x767e6),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x76ac2),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x76cd8),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x76f78),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x77178),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x77384),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7794a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78196),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x782a8),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7831c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7849a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x785c2),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x787fa),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7893a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78b08),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78d16),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78e0c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78e9e)
};

static u16* sMonologueTextPointersSpanish[19] = {
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x78f4c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x796f0),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x79946),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x79b56),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x79de6),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7a056),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7a266),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7a872),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b10c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b20a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b274),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b426),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b53e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b75e),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7b89c),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7ba74),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7bc4a),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7bda4),
	(u16*)((const u8*)sBlob_6b2fac_72eee0 + 0x7be70)
};

const void* sPointers_79e868[270] = {
    (const void*)&sFrameData_73c274[0],
    (const void*)&sFrameData_73c29c[0],
    (const void*)&sFrameData_73c29c[0],
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x5b3a),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x5b3a),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x5b3a),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x6212),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x690a),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x70ea),
    (const void*)((const u8*)sBlob_73421e_73c274 + 0x788e),
    (const void*)&sFrameData_740ab8[0],
    (const void*)&sFrameData_740ac8[0],
    (const void*)&sFrameData_740ad8[0],
    (const void*)&sFrameData_7408c0[0],
    (const void*)&sFrameData_7408c0[0],
    (const void*)&sFrameData_740800[0],
    (const void*)&sFrameData_740800[0],
    (const void*)&sFrameData_740820[0],
    (const void*)&sFrameData_740840[0],
    (const void*)&sFrameData_740840[0],
    (const void*)&sFrameData_740ae8[0],
    (const void*)&sFrameData_740b08[0],
    (const void*)&sFrameData_740b28[0],
    (const void*)&sFrameData_740b28[0],
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x18e8),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x18f4),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x18fa),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x18fa),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x18fa),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1900),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1906),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1912),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x191e),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1924),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1912),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x191e),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1930),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1912),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x1918),
    (const void*)((const u8*)sBlob_73c2e4_7406f8 + 0x191e),
    (const void*)&sPointers_79e868[24],
    (const void*)&sPointers_79e868[24],
    (const void*)&sPointers_79e868[30],
    (const void*)&sPointers_79e868[30],
    (const void*)&sPointers_79e868[36],
    (const void*)&sPointers_79e868[30],
    (const void*)&sPointers_79e868[42],
    (const void*)&sFrameData_740a38[0],
    (const void*)&sFrameData_7409d8[0],
    (const void*)&sFrameData_7409e8[0],
    (const void*)&sFrameData_7409f8[0],
    (const void*)&sFrameData_740a08[0],
    (const void*)&sFrameData_740a18[0],
    (const void*)&sFrameData_740a28[0],
    (const void*)&sFrameData_740a38[0],
    (const void*)&sFrameData_7409d8[0],
    (const void*)&sFrameData_7409e8[0],
    (const void*)&sFrameData_7409f8[0],
    (const void*)&sFrameData_740a08[0],
    (const void*)&sFrameData_740a18[0],
    (const void*)&sFrameData_740a28[0],
    (const void*)&sFrameData_740a38[0],
    (const void*)&sFrameData_7409d8[0],
    (const void*)&sFrameData_7409e8[0],
    (const void*)&sFrameData_7409f8[0],
    (const void*)&sFrameData_740a08[0],
    (const void*)&sFrameData_740a18[0],
    (const void*)&sFrameData_740a28[0],
    (const void*)&sFrameData_740c08[0],
    (const void*)&sFrameData_740ba8[0],
    (const void*)&sFrameData_740bb8[0],
    (const void*)&sFrameData_740bc8[0],
    (const void*)&sFrameData_740bd8[0],
    (const void*)&sFrameData_740be8[0],
    (const void*)&sFrameData_740bf8[0],
    (const void*)&sFrameData_740c78[0],
    (const void*)&sFrameData_740c18[0],
    (const void*)&sFrameData_740c28[0],
    (const void*)&sFrameData_740c38[0],
    (const void*)&sFrameData_740c48[0],
    (const void*)&sFrameData_740c58[0],
    (const void*)&sFrameData_740c68[0],
    (const void*)&sFrameData_740ce8[0],
    (const void*)&sFrameData_740c88[0],
    (const void*)&sFrameData_740c98[0],
    (const void*)&sFrameData_740ca8[0],
    (const void*)&sFrameData_740cb8[0],
    (const void*)&sFrameData_740cc8[0],
    (const void*)&sFrameData_740cd8[0],
    (const void*)&sFrameData_740cf8[0],
    (const void*)&sFrameData_7409d8[0],
    (const void*)&sFrameData_7409e8[0],
    (const void*)&sFrameData_7409f8[0],
    (const void*)&sFrameData_740a08[0],
    (const void*)&sFrameData_740a18[0],
    (const void*)&sFrameData_740a28[0],
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x200),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x232),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x25c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x27a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2bc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2ec),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x32e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x370),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x3b2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x3f4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x436),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x478),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x48e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x496),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x4aa),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x4d2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x4f2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x506),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x550),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x578),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x5c6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x5e4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x606),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x62c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x644),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x65c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x690),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x6c6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x708),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x75e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x794),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x7ee),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x848),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x8a2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x906),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x96a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x9ce),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x9e4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xa02),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xa16),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xa3e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xa5e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xa72),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xabc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xae6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xb0c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xb28),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xb52),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xb7c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xbac),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xbd4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xc10),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xc3e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xc76),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xccc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xd0c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xd6e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xdd0),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xe32),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xe90),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xeee),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xf4c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xf66),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xf88),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xfaa),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0xfd4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1002),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1020),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1048),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x107a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x10aa),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x10ce),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x10ea),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x111c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1140),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x117a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x11bc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x11e6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x122a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1278),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x12b6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1322),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x138e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x13fa),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x145a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x14ba),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x151a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x153c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1568),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1594),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x15b8),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x15ea),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1610),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1646),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x165a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x167e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x16a2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x16cc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x16ee),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1718),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1744),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x177e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x17b8),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x17f6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1846),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x187e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x18ea),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1956),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x19c2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1a26),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1a8a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1aee),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1b04),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1b24),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1b38),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1b62),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1b96),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1bbc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1c02),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1c30),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1c5c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1c7a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1ca4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1cd4),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1cf8),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1d20),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1d5e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1d86),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1db8),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1e10),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1e48),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1ea2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1efc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1f56),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x1fb2),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x200e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x206c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2082),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x209a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x20c0),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x20dc),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x20f0),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2110),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2144),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2174),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2194),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x21be),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x21e6),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x220c),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x223a),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x225e),
    (const void*)((const u8*)sBlob_740d08_7478a0 + 0x2272),
    (const void*)&sPointers_79e868[104],
    (const void*)&sPointers_79e868[104],
    (const void*)&sPointers_79e868[129],
    (const void*)&sPointers_79e868[154],
    (const void*)&sPointers_79e868[179],
    (const void*)&sPointers_79e868[204],
    (const void*)&sPointers_79e868[229],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
    (const void*)&sPointers_79e868[254],
};

/**
 * @brief 87610 | f8 | Handler for intro
 * 
 */
boolu32 IntroHandler(void) 
{
    boolu32 result;

    result = FALSE;
    
    if (gChangedInput & (KEY_START | KEY_A))
    {
        if (gSubGameMode1 == 3)
        {
            if (INTRO_DATA.unk_20E != 0)
                INTRO_DATA.unk_20E = 0;
        }
        else if (gSubGameMode1 != 0 && gSubGameMode1 != 3)
        {
            if (READ_16(REG_BLDCNT) & BLDCNT_ALPHA_BLENDING_EFFECT)
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
            
            INTRO_DATA.unk_20E = 0;
            gSubGameMode1 = 3;
            FadeAllSounds(20);
            FadeMusic(20);
        }
    }

    switch (gSubGameMode1)
    {
        case 0:
            NewFileIntroInit();
            gSubGameMode1 = 1;
            break;
        
        case 1:
            if (IntroSpaceView())
                gSubGameMode1 = 2;
            break;
        
        case 2:
            if (IntroSamusShipCrashing())
                gSubGameMode1 = 3;
            break;
        
        case 3:
            if (INTRO_DATA.unk_20E == 0)
            {
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                    gWrittenToBldy++;
                else
                    result = TRUE;
            }
            else
                INTRO_DATA.unk_20E--;
            
            SpecialCutsceneDrawAllOam(); 
    }

    return result;
}

 /**
 * @brief 87708 | 218 | Handler for new file intro
 * 
 */
boolu32 NewFileIntroHandler(void) 
{
    boolu32 result;

    result = FALSE;

    switch (gSubGameMode1)
    {
        case 0:
            StopAllMusicAndSounds();
            NewFileIntroInit();

            if (gGameCompletion.introPlayed == TRUE)
                return TRUE;
            else 
                gSubGameMode1 = 1;
            break;

        case 1:
            INTRO_DATA.timer++;
            if (INTRO_DATA.timer >= 100)
            {
                INTRO_DATA.timer = 0;
                gSubGameMode1 = 2;
            }
            break;

        case 2:
            if (NewFileIntroSr388Preview())
                gSubGameMode1 = 3;
            break;

        case 3:
            if (NewFileIntroInSr388())
                gSubGameMode1 = 4;
            break;

        case 4:
            if (NewFileIntroSamusShipFlying())
                gSubGameMode1 = 5;
            break;

        case 5:
            if (NewFileIntroSamusFainting())
                gSubGameMode1 = 6;
            break;

        case 6:
            if (NewFileIntroSamusDrifting())
                gSubGameMode1 = 7;
            break;

        case 7:
            if (NewFileIntroSamusFound())
                gSubGameMode1 = 8;
            break;

        case 8:
            if (NewFileIntroSamusGettingCured())
                gSubGameMode1 = 9;
            break;

        case 9:
            if (NewFileIntroSamusCured())
                gSubGameMode1 = 10;
            break;

        case 10:
            if (NewFileIntroArrivingAtBsl())
                gSubGameMode1 = 11;
            break;

        case 11:
            if (NewFileIntroLandingOnBsl())
            {
                INTRO_DATA.unk_20E = 0;
                gSubGameMode1 = 12;
            }
            break;
        
        case 12:
            INTRO_DATA.unk_20E++;
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.unk_20E == 1)
                {
                    INTRO_DATA.unk_20E = 0;
                    gWrittenToBldy++;
                }
            }
            else
            {
                if (INTRO_DATA.unk_20E == 1)
                {
                    Sram_ProcessIntroSave(0);
                }
                else if (INTRO_DATA.unk_20E == 2)
                {
                    Sram_ProcessIntroSave(1);
                } 
                else if (INTRO_DATA.unk_20E == 3)
                {
                    Sram_ProcessIntroSave(2);
                }
                else if (INTRO_DATA.unk_20E == 4)
                {
                    Sram_ProcessIntroSave(3);
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.unk_20E = 0;
                    result = TRUE;
                }
            }

            SpecialCutsceneDrawAllOam();
    }

    return result;
}

 /**
 * @brief 87920 | 50 | To document
 * 
 */
boolu32 unk_87920(void) 
{
    boolu32 result;
    boolu32 done;
    
    result = FALSE;

    switch (gCurrentCutscene)
    {
        default:
            result = TRUE;
            done = FALSE;
            break;

        case 1:
            done = IntroHandler();
            break;

        case 2:
            done = NewFileIntroHandler();
            break;

        case 3:
            done = EndingHandler();
            break;

        case 4:
            done = DiedFromSr388CollisionHandler();
    }

    if (done)
    {
        StopAllMusicAndSounds();
        result = TRUE;
    }
    
    return result;
}

 /**
 * @brief 87970 | 94 | V-blank for the new file intro Samus ship flying cutscene
 * 
 */
static void NewFileIntroSamusShipFlyingVblank(void) 
{
    DMA3_COPY_32(gOamData, OAM_BASE, 256);

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 87a04 | 264 | Setup for the new file intro Samus ship flying cutscene
 * 
 */
static void NewFileIntroSamusShipFlyingInit(void) 
{
    u16 i;
    
    CallbackSetVBlank(unk_99940);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sIntroSamusShipPal, PALRAM_OBJ, 5 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompWram(sIntroBslSpaceBgGfx, EWRAM_BASE + 0x10000);

    DMA3_COPY_32(EWRAM_BASE + 0x10000, VRAM_BASE, (VRAM_SIZE / 3) / 4);

    LZ77UncompVram(sIntroBslTilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSpaceTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);

    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 48;
    gBg2YPosition = -8;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    WRITE_16(REG_BG0CNT, 28 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | 2 << BGCNT_CHAR_BASE_BLOCK_SHIFT);
    WRITE_16(REG_BG2CNT, BGCNT_SIZE_512x256 << BGCNT_SCREEN_SIZE_SHIFT | 29 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_MID_PRIORITY);
    WRITE_16(REG_BG3CNT, 31 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_PRIORITY);

    NewFileIntroSetupOam(200, 250, 0, 0);
    NewFileIntroSetupOam(1, (s16)gBg2XPosition, (s16)gBg2YPosition, 0);
    NewFileIntroSetupOam(2, 160, 90, 0);
    NewFileIntroSetupOam(4, 0, 0, 1);

    for (i = 0; i < 10; i++)
        NewFileIntroSetupOam(3, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4 );

    INTRO_DATA.pText = sCutsceneTextNone;
    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG2);

    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
}

 /**
 * @brief 87C68 | 188 | Processes the new file intro Samus ship flying cutscene
 * 
 */
static boolu32 NewFileIntroSamusShipFlyingProcess(void) 
{
    boolu32 result;

    result = FALSE;

    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;
    
    INTRO_DATA.timer++;

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), 1);

            if (INTRO_DATA.timer == 99)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 100)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][10];
                INTRO_DATA.subStage = 1;
            }
            break;
        
        case 1:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), 1);

            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 2;
            }
            break;

        case 2:
            if (INTRO_DATA.timer == 30)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                result = TRUE;
            }
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();

    return result;
}

 /**
 * @brief 87df0 | a0 | Main handler for new file intro Samus ship flying cutscene
 * 
 */
static boolu32 NewFileIntroSamusShipFlying(void)
{
    boolu32 result;

    result = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusShipFlyingInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusShipFlyingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;   
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                result = TRUE;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
    }

    return result;
}

 /**
 * @brief 87e90 | 1d8 | Setup for the new file intro Samus fainting cutscene
 * 
 */
static void NewFileIntroSamusFaintingInit(void)
{
    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompVram(sIntroSamusSittingTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusSittingTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusSittingGfx, VRAM_BASE);

    DMA3_COPY_32(sIntroSamusSittingPal, PALRAM_BASE, 128);

    WRITE_16(PALRAM_BASE, 0);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 64);
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 10;
    gBg2YPosition = 2;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    WRITE_16(REG_BG0CNT, 28 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | 2 << BGCNT_CHAR_BASE_BLOCK_SHIFT);
    WRITE_16(REG_BG2CNT, 30 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_MID_PRIORITY);
    WRITE_16(REG_BG3CNT, 31 << BGCNT_SCREEN_BASE_BLOCK_SHIFT | BGCNT_LOW_PRIORITY);

    NewFileIntroSetupOam(200, 250, 0, 0);
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, VRAM_SIZE / 24 );

    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_OBJ | DCNT_BG3 | DCNT_BG2);

    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
    gWrittenToBldalpha_Eva = 12;
    gWrittenToBldalpha_Evb = 8;
}

 /**
 * @brief 88068 | 13c | Processes the new file intro Samus fainting cutscene
 * 
 */
static boolu32 NewFileIntroSamusFaintingProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;
    
    INTRO_DATA.timer += 1;
    
    switch (INTRO_DATA.subStage) 
    {
        case 0:
            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_FIRST_TARGET_PIXEL);
                NewFileIntroSetupOam(10, gBg2XPosition, gBg2YPosition, 1);
            }
            else if (INTRO_DATA.timer == 59)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][11];
                INTRO_DATA.subStage = 1;
            }
            break;
        
        case 1:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 2;
                gWrittenToBldy = 16;
            }
            break;
        
        case 2:
            if (INTRO_DATA.timer == 30) 
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.timer = 0;
                finished = TRUE;
            }
            break;
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 881a4 | 9c | Main handler for the new file intro Samus fainting cutscene
 * 
 */
static boolu32 NewFileIntroSamusFainting(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusFaintingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusFaintingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < 16)
            {
                gWrittenToBldy++;
            }
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 88240 | 26c | Setup for the 'gunship drifting away from BSL ship' cutscene
 * 
 */
void NewFileIntroSamusDriftingInit(void)
{
    u16 i;

    CallbackSetVBlank(unk_99940);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    
    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sIntroSamusShipPal, PALRAM_OBJ, 5 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);
    
    LZ77UncompWram(sIntroBslSpaceBgGfx, EWRAM_BASE + 0x10000);
    
    DMA3_COPY_32(EWRAM_BASE + 0x10000, VRAM_BASE, (VRAM_SIZE / 3) / 4);
    
    LZ77UncompVram(sIntroBslTilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSpaceTilemap, VRAM_BASE + 0xF800);
    
    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 48;
    gBg2YPosition = -8;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    NewFileIntroSetupOam(200, 250, 0, 0);
    NewFileIntroSetupOam(1, gBg2XPosition, gBg2YPosition, 0);
    NewFileIntroSetupOam(20, 160, 90, 0);
    NewFileIntroSetupOam(4, 0, 0, 1);
    
    for (i = 0; i < 10; i++)
        NewFileIntroSetupOam(3, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
}

 /**
 * @brief 884ac | c8 | V-blank for the 'Samus losing conciousness' cutscene
 * 
 */
static void NewFileIntroSamusLosingConsciousnessVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / 4);

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
    
    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;
        DMA3_COPY_32(sIntroSamusCloseupGrayscalePal, PALRAM_BASE, 4 * PAL_ROW_SIZE / 4);
    }
}

 /**
 * @brief 88574 | 1e0 | Setup for the 'Samus losing conciousness' cutscene
 * 
 */
void NewFileIntroSamusLosingConsciousnessInit(void) 
{
    u16 i;

    CallbackSetVBlank(unk_99940);
    
    DMA3_FILL_32(0, 0x030016a0, 720); // TODO: Find out what 16a0 is
    
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    for (i = 0; i < 6; i++)
        LZ77UncompVram(sIntroSamusHelmetCloseupBgGfxPointers[i], VRAM_BASE + i * 0x1000);
    
    LZ77UncompVram(sIntroSamusHelmetCloseupTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusHelmetCloseupTilemap, VRAM_BASE + 0xF800);

    DMA3_COPY_32(sIntroSamusHelmetCloseupPal, PALRAM_BASE, 4 * PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sIntroBslSpaceBgPal, PALRAM_BASE + 0x100, 8 * PAL_ROW_SIZE / 4);
    
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 10;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    NewFileIntroSetupOam(200, 250, 0, 0);
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusLosingConsciousnessVblank);
    
    gWrittenToBldy = 0;
    gWrittenToBldalpha_Eva = 12;
    gWrittenToBldalpha_Evb = 8;
}

 /**
 * @brief 88754 | 25c | Setup for the 'gunship drifting into asteroids' cutscene
 * 
 */
void NewFileIntroSamusDriftingIntoAsteroidsInit(void) 
{
    u16 i;
    void* temp1;
    u32 temp2;
    
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);
    
    CallbackSetVBlank(unk_99940);
    
    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
    
    for (i = 0; i < 8; i++)
        LZ77UncompVram(sIntroBslObjectGfxPointers[i], VRAM_OBJ + i * 0x1000);
    
    DMA3_COPY_32(sPal_612f48, PALRAM_OBJ, 16 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598150, PALRAM_OBJ + 0x100, 2 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / 4);

    LZ77UncompVram(sTitleScreenSpaceBackgroundGfx, VRAM_BASE);
    LZ77UncompVram(sTitleScreenSpaceBackgroundTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sPal_609020, PALRAM_BASE, 16 * PAL_ROW_SIZE / 4);
    DMA3_COPY_32(sPal_598a8c, PALRAM_BASE + 0x1E0, PAL_ROW_SIZE / 4);
    
    SET_BACKDROP_COLOR(COLOR_BLACK);
    
    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);
    
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;

    //WRITE_16(REG_BLDALPHA, 0); // Doesn't match
    temp1 = REG_BLDALPHA;
    temp2 = 0;
    WRITE_16(temp1, temp2);
    
    NewFileIntroSetupOam(30, 140, 140, 0);
    NewFileIntroSetupOam(31, 140, 80, 0);
    
    for (i = 0; i < 4; i++)
        NewFileIntroSetupOam(36, SpecialCutsceneGetRandomNumber(), SpecialCutsceneGetRandomNumber(), 1);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / 4);
    
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSamusShipFlyingVblank);
    
    gWrittenToBldy = 0;
}

 /**
 * @brief 889b0 | 318 | To document
 * 
 */
boolu32 NewFileIntroSamusDriftingProcess(void)
{
    boolu32 finished;
    s16 x;
    s16 y;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.unk_218)
        INTRO_DATA.unk_218 = 1;
    
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
                NewFileIntroSetupOam(3, 0, SpecialCutsceneGetRandomNumber(), TRUE);
            
            if (INTRO_DATA.timer != 149) // Why?
            {
                if (INTRO_DATA.timer == 150)
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 1;
                    gWrittenToBldy = BLDY_MAX_VALUE;
                }
            }
            break;
        
        case 1:
            NewFileIntroSamusLosingConsciousnessInit();
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 2;
            break;
        
        case 2:
            if (INTRO_DATA.timer == 1)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                NewFileIntroSetupOam(10, gBg2XPosition, gBg2YPosition, TRUE);
                gWrittenToBldy = 0;
            }
            else if (INTRO_DATA.timer == 118)
            {
                break;
            }
            else if (INTRO_DATA.timer == 120)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.unk_110 = 1;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
            break;

        case 3:
            if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
                gWrittenToBldy = 16;
            }
            break;
        
        case 4:
            NewFileIntroSamusDriftingIntoAsteroidsInit();
            INTRO_DATA.timer = 0;
            INTRO_DATA.subStage = 5;
            break;
        
        case 5:
            INTRO_DATA.timer = 0;
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;

        case 6:
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);
            
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                if (INTRO_DATA.timer == 3)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy++;
                }
            } 
            else if (INTRO_DATA.timer == 10)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 7;
                finished = TRUE;
            }
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 7:
            if (gWrittenToBldy) 
            {
                if (INTRO_DATA.timer == 6) 
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy--;
                }
            } 
            else 
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 8;
            }

            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 8:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 1)
            {
                SpecialCutsceneDestroyOamOfType(201);
                INTRO_DATA.subStage = 9;
            }
            
            if (SpecialCutsceneGetRandomNumber() < 128 && INTRO_DATA.unk_215 < 12)
            {
                x = SpecialCutsceneGetRandomNumber();
                y = SpecialCutsceneGetRandomNumber();
                NewFileIntroSetupOam(36, x, y, TRUE);
            }
            break;
        
        case 9:
            finished = TRUE;
            break;
    }
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 88cc8 | 9c | To document
 * 
 */
boolu32 NewFileIntroSamusDrifting(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusDriftingInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusDriftingProcess())
            {
                INTRO_DATA.stage = 3;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else 
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 0;
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 88d64 | 150 | To document
 * 
 */
void NewFileIntroProcessBslShip(struct SpecialCutsceneOam *pOam)
{
    s32 cos;
    s32 sin;
    
    pOam->unk_4 = pOam->xPosition;
    
    if (pOam->stage == 0) 
    {
        pOam->stage = 2;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = (((60 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((10 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;
        
        if (pOam->xPosition > 39) 
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 1) 
        {
            pOam->unk_A = 0;
            pOam->spawnX = 0;
            pOam->spawnY = 4;
            pOam->unk_8 = pOam->yPosition;
            pOam->timer = 128;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        cos = pOam->spawnX * COS(pOam->timer);
        sin = pOam->spawnY * SIN(pOam->timer);
        pOam->yPosition = ((SIN(0) * cos + COS(0) * sin) >> 16) + pOam->unk_8;
        pOam->timer++;
        
        if (pOam->unk_A != 60) // Why?
        {
            if (pOam->unk_A == 200)
            {
                pOam->unk_A = 0;
                pOam->stage = 4;
            } 
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->stage = 5;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
    } 
    else if (pOam->stage == 5)
    {    
        pOam->unk_A++;
        pOam->xPosition = (((520 - pOam->spawnX) * pOam->unk_A) >> 10) + pOam->spawnX;
        pOam->yPosition = (((100 - pOam->spawnY) * pOam->unk_A) >> 10) + pOam->spawnY;

        if (pOam->xPosition >= 520)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
    }
    
    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 88eb4 | 128 | To document
 * 
 */
void NewFileIntroProcessFlyingSamusShip(struct SpecialCutsceneOam *pOam)
{
    s32 rotation;
    s32 cos;
    s32 sin;
    s32 x;
    s32 y;

    rotation = 0;
    
    if (pOam->stage == 0)
    {
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 64;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->scaling -= 2;

        if (pOam->timer == 128)
        {
            pOam->stage = 2;
            pOam->scaling = Q_8_8(1);
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->spawnX = 0;
        pOam->spawnY = 8;
        pOam->unk_4 = pOam->xPosition;
        pOam->unk_8 = pOam->yPosition;
        pOam->stage = 3;
    }
    else if (pOam->stage == 3)
    {
        pOam->timer += 2;
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->unk_A++;
        if (pOam->unk_A == 180)
        {
            pOam->unk_A = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->spawnX = 280 - pOam->xPosition;
        pOam->spawnY = 60;
        pOam->unk_4 = pOam->xPosition + pOam->spawnX;
        pOam->unk_8 = pOam->yPosition;
        pOam->timer = 128;
        pOam->stage = 6;
    }
    else if (pOam->stage == 6)
    {
        pOam->timer++;
        if (pOam->timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
    
    cos = pOam->spawnX * COS(pOam->timer);
    sin = pOam->spawnY * SIN(pOam->timer);
    
    x = cos * COS(rotation) - sin * SIN(0);
    y = cos * SIN(0) + sin * COS(rotation);
    
    pOam->xPosition = (x >> 16) + pOam->unk_4;
    pOam->yPosition = (y >> 16) + pOam->unk_8;
}

 /**
 * @brief 88fdc | b4 | To document
 * 
 */
void NewFileIntroProcessHorizontalParticle(struct SpecialCutsceneOam *pOam)
{
    s32 rng;
    
    if (pOam->stage == 0)
    {
        rng = SpecialCutsceneGetRandomNumber() & 7;
        pOam->unk_8 = rng + 1;
        rng = SpecialCutsceneGetRandomNumber() & 3;
        pOam->unk_4 = rng;
        pOam->pOam = sData_79C2CC[pOam->unk_4];
        pOam->spawnX = pOam->xPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = ((pOam->unk_8 * pOam->unk_A) >> 4) + pOam->spawnX;
        
        pOam->timer++;
        if (pOam->timer == 8)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 5)
                pOam->unk_4++;
            else
                pOam->unk_4 = 0;
            
            pOam->pOam = sData_79C2CC[pOam->unk_4];
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    
    if (pOam->xPosition >= SCREEN_SIZE_X || pOam->yPosition >= SCREEN_SIZE_Y)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 89090 | 28 | To document
 * 
 */
void unk_89090(struct SpecialCutsceneOam *pOam) 
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 25)
    {
        pOam->animationDurationCounter = 0;
        gBg3XPosition--;
    }
}

 /**
 * @brief 890b8 | 104 | To document
 * 
 */
void NewFileIntroProcessSamusFainting(struct SpecialCutsceneOam* pOam)
{
    u8 rng1;
    u8 rng2;

    rng1 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit, 32)] / 2;
    rng2 = sRandomNumberTable[MOD_AND(gFrameCounter16Bit + 7, 32)] / 2;

    if (!pOam->unk_8)
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition < 16)
            {
                pOam->yPosition += rng2;
                if (pOam->yPosition > 15)
                {
                    pOam->yPosition = 16;
                    pOam->unk_8 = 1;
                }
            }
        }
    }
    else
    {
        pOam->timer++;
        if (pOam->timer)
        {
            pOam->timer = 0;
            if (pOam->yPosition > 0)
            {
                pOam->yPosition -= rng2;
                if (pOam->yPosition <= 0)
                {
                    pOam->yPosition = 0;
                    pOam->unk_8 = 0;
                }
            }
        }
    }

    if (!pOam->unk_4)
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition < 16)
            {
                pOam->xPosition += rng1;
                if (pOam->xPosition > 15)
                {
                    pOam->xPosition = 16;
                    pOam->unk_4 = 1;
                }
            }
        }
    }
    else
    {
        pOam->unk_A++;
        if (pOam->unk_A)
        {
            pOam->unk_A = 0;
            if (pOam->xPosition > 0)
            {
                pOam->xPosition -= rng1;
                if (pOam->xPosition <= 0)
                {
                    pOam->xPosition = 0;
                    pOam->unk_4 = 0;
                }
            }
        }
    }

    gBg2XPosition = pOam->xPosition;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 891bc | 74 | To document
 * 
 */
void NewFileIntroProcessSamusDrifting(struct SpecialCutsceneOam* pOam)
{
    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->xPosition = pOam->spawnX + (pOam->unk_A >> 1);
        pOam->yPosition = pOam->spawnY + (pOam->unk_A >> 2);

        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->scaling++;
        }
    }

    if (pOam->xPosition > (SCREEN_SIZE_X + 40) || pOam->yPosition > (SCREEN_SIZE_Y + 20))
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 89230 | 258 | To document
 * 
 */
void NewFileIntroProcessSamusDriftingIntoAsteroids(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->unk_A = 0;
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->rotation -= 4;
        pOam->scaling -= 8;
        pOam->stage = 2;
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        pOam->yPosition = (SIN(pOam->timer) >> 7) + pOam->spawnY;
        
        if (pOam->timer > 52)
        {
            pOam->unk_4++;
            if (pOam->unk_4 == 12)
            {
                pOam->rotation--;
                pOam->xPosition--;
                pOam->unk_4 = 0;
            }
            
            pOam->unk_8++;
            if (pOam->unk_8 == 10)
            {
                pOam->unk_8 = 0;
                pOam->scaling--;
            }
        }

        if (pOam->timer > 127)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3) + (SIN(pOam->timer) >> 7);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 2)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }
        
        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 3);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }
        
        if (pOam->timer == 0)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 4;
        }
        
        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 4)
    {
        pOam->timer++;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 1);
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->unk_4++;
        
        if (pOam->unk_4 == 12)
        {
            pOam->rotation--;
            pOam->unk_4 = 0;
        }
        
        pOam->unk_8++;
        if (pOam->unk_8 == 1)
        {
            pOam->unk_8 = 0;
            pOam->scaling--;
        }

        if (pOam->scaling < 3)
        {
            pOam->unk_8 = 0;
            pOam->unk_A = 0;
            pOam->unk_4 = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->unk_A = 0;
        pOam->scaling = Q_8_8(1);
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
        pOam->affineMode = OAM_AFFINE_MODE_NORMAL;
        pOam->pOam = sOam_598000;
        pOam->stage = 6;
        INTRO_DATA.subStage = 6;
    }
    else if (pOam->stage == 6)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 89488 | 64 | To document
 * 
 */
void unk_89488(struct SpecialCutsceneOam *pOam) 
{
    if (pOam->stage == 0)
    {
        NewFileIntroSetupOam(32, pOam->xPosition + 122, pOam->yPosition, FALSE);
        NewFileIntroSetupOam(33, pOam->xPosition + 50, pOam->yPosition + 1, FALSE);
        NewFileIntroSetupOam(34, pOam->xPosition + 36, pOam->yPosition, FALSE);
        NewFileIntroSetupOam(35, pOam->xPosition, pOam->yPosition, FALSE);
        pOam->type = 0;
    }
}

 /**
 * @brief 894ec | c4 | To document
 * 
 */
void NewFileIntroProcessSidewaysBslShip(struct SpecialCutsceneOam* pOam)
{
    if (pOam->stage == 0)
    {
        pOam->timer++;
        if (pOam->timer == 20)
        {
            pOam->spawnX++;
            pOam->timer = 0;

            if (pOam->unk_A == 4)
                pOam->unk_A = 0;

            if (pOam->unk_A < 2)
                pOam->yPosition++;
            else if (pOam->unk_A < 4)
                pOam->yPosition--;
                
            pOam->unk_A++;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->unk_A = 0;
        pOam->stage = 2;
    }
    else if (pOam->stage == 2)
    {
        pOam->timer++;
        if (pOam->timer == 2)
        {
            pOam->unk_A++;
            pOam->timer = 0;
        }

        pOam->xPosition = (((900 - pOam->spawnX) * pOam->unk_A) >> 12) + pOam->spawnX;
        pOam->yPosition = (((pOam->unk_4 - pOam->spawnY) * pOam->unk_A) >> 11) + pOam->spawnY;

        if (pOam->xPosition > 320)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 3;
        }
    }
}

 /**
 * @brief 895b0 | c4 | To document
 * 
 */
void NewFileIntroProcessDepthParticle(struct SpecialCutsceneOam* pOam)
{
    s32 x;
    s32 y;
    s32 divisor;
    
    pOam->unk_4 = pOam->unk_A;

    if (pOam->stage == 0)
    {
        pOam->spawnX = (pOam->xPosition - SCREEN_X_MIDDLE) * 100;
        pOam->spawnY = (pOam->yPosition - SCREEN_Y_MIDDLE) * 100;
        pOam->stage = 1;
    }
    else
    {
        if ((s16)pOam->unk_A < 100)
        {
            if ((s16)pOam->unk_A == 25)
                pOam->pOam = sOam_597ed0;
            else if ((s16)pOam->unk_A == 50)
                pOam->pOam = sOam_597ee0;
            else if ((s16)pOam->unk_A == 70)
                pOam->pOam = sOam_597ef0;

            divisor = -pOam->unk_4 + 100;
            x = pOam->spawnX / divisor;
            pOam->xPosition = x + SCREEN_X_MIDDLE;
            y = pOam->spawnY / divisor + SCREEN_Y_MIDDLE;
            pOam->yPosition = y;

            if ((u16)(x + 128) > 256 || (s16)y > 168 || (s16)y < -8)
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
        else
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
    
    pOam->unk_A++;
}

 /**
 * @brief 89674 | 400 | To document
 * 
 */
u8 NewFileIntroSetupOam(u8 type, s16 xPosition, s16 yPosition, boolu8 descendingSearchOrder)
{
    s8 slot;

    if (!descendingSearchOrder)
    {
        for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }
        
        if (slot > 19)
            return 20;
    }
    else
    {
        for (slot = ARRAY_SIZE(INTRO_DATA.oam) - 1; slot >= 0; slot--)
        {
            if (INTRO_DATA.oam[slot].type == 0)
                break;
        }
        
        if (slot < 0)
            return 20;
    }
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], 36);

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == 1)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslShip;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].pOam = sOam_597f50;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessFlyingSamusShip;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sOam_597ec0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHorizontalParticle;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_89090;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFainting;
    }
    else if (type == 20)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].pOam = sOam_597f50;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusDrifting;
    }
    else if (type == 30)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_AFFINE;
        INTRO_DATA.oam[slot].pOam = sOam_597f88;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusDriftingIntoAsteroids;
    }
    else if (type == 31)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pOam = sOam_597f88;
        INTRO_DATA.oam[slot].pFunction = unk_89488;
    }
    else if (type == 32)
    {
        INTRO_DATA.oam[slot].unk_4 = -40;
        INTRO_DATA.oam[slot].pOam = sOam_597fe0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 33)
    {
        INTRO_DATA.oam[slot].unk_4 = -30;
        INTRO_DATA.oam[slot].pOam = sOam_597fd0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 34)
    {
        INTRO_DATA.oam[slot].unk_4 = -20;
        INTRO_DATA.oam[slot].pOam = sOam_597fc0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 35)
    {
        INTRO_DATA.oam[slot].unk_4 = -10;
        INTRO_DATA.oam[slot].pOam = sOam_597fb0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSidewaysBslShip;
    }
    else if (type == 36)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_597ec0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessDepthParticle;
    }
    else if (type == 200)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    else if (type == 201)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessOam_Empty;
    }
    
    return slot;
}

 /**
 * @brief 89a74 | 3c | To document
 * 
 */
void unk_89a74(u8 type, s16 xPos, s16 yPos, s16 arg3) 
{
    u8 slot;
    
    slot = NewFileIntroSetupOam(type, xPos, yPos, TRUE);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 89ab0 | 4 | To document
 * 
 */
void NewFileIntroProcessOam_Empty(void) 
{
    return;
}

 /**
 * @brief 89ab4 | 248 | To document
 * 
 */
void NewFileIntroSr388PreviewInit(void)
{
    u16 i;
    
    CallbackSetVBlank(unk_99940);
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));
    
    LZ77UncompVram(sIntroSr388SpaceAndSurfaceObjGfx, VRAM_OBJ);
    
    DMA3_COPY_32(sIntroSr388SpaceAndSurfaceObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));
    
    CallbackSetVBlank(unk_99940);

    for (i = 0; i < ARRAY_SIZE(sIntroSr388SurfaceBgGfxPointers); i++)
        LZ77UncompVram(sIntroSr388SurfaceBgGfxPointers[i], VRAM_BASE + i * 0x1000);

    LZ77UncompVram(sIntroSr388SurfaceTilemap, VRAM_BASE + 0xE800);

    for (i = 0; i < ARRAY_SIZE(sIntroSr388PlanetBgGfxPointers); i++)
        LZ77UncompVram(sIntroSr388PlanetBgGfxPointers[i], VRAM_BASE + 0x8000 + i * 0x1000);
    
    LZ77UncompVram(sIntroSr388SpaceBgTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSr388PlanetTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    
    DMA3_COPY_32(sSr388SpaceAndSurfacePal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    
    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    gBg1XPosition = 0;
    gBg1YPosition = 0;
    gBg2XPosition = 16;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;
    
    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    
    NewFileIntroSr388SetupOam(50, 250, 200);
    NewFileIntroSr388SetupOam(1, 0, 0);
    NewFileIntroSr388SetupOam(2, gBg2XPosition, 0);
    
    NewFileIntroSetupSr388PreviewAsteroid(3, 250, 100, -12);
    NewFileIntroSetupSr388PreviewAsteroid(4, 150, 10, -8);
    NewFileIntroSetupSr388PreviewAsteroid(5, 50, 60, -6);
    NewFileIntroSetupSr388PreviewAsteroid(6, 190, 130, -20);
    NewFileIntroSetupSr388PreviewAsteroid(5, 280, 30, -10);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    PlayMusic(MUSIC_SECTOR_1, 13);
    
    WRITE_16(REG_DISPCNT, DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    
    CallbackSetVBlank(NewFileIntroSr388PreviewVblank);
}

 /**
 * @brief 89cfc | 348 | To document
 * 
 */
boolu32 NewFileIntroSr388PreviewProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == 1)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == 50)
            {
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][8];
            }
            else if (INTRO_DATA.timer == 58)
            {
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 59)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL);
            }
            else if (INTRO_DATA.timer == 60)
            {
                INTRO_DATA.timer = 0;
                NewFileIntroSr388SetupOam(9, gBg2XPosition + 92, 64);
                INTRO_DATA.subStage = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Eva++;
            }

            if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
                INTRO_DATA.unk_218 = 1;

            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva == 0)
                {
                    SpecialCutsceneDestroyOamOfType(9);
                    INTRO_DATA.subStage = 3;
                }
                else
                {
                    gWrittenToBldalpha_Eva--;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 3:
            if (INTRO_DATA.timer == 1)
            {
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
            }
            else if (INTRO_DATA.timer == 2)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL 
                         | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 4:
            if (gWrittenToBldalpha_Eva == BLDALPHA_MAX_VALUE)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~(DCNT_BG2 | DCNT_BG3));
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.subStage = 5;
                NewFileIntroSr388SetupOam(10, 128, 210);
            }
            else if (gWrittenToBldalpha_Eva == 2)
            {
                NewFileIntroSr388SetupOam(7, 0, 0);
            }

            if (INTRO_DATA.timer == 7)
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                {
                    gWrittenToBldalpha_Eva++;
                    gWrittenToBldalpha_Evb--;
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == 70)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 6;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            INTRO_DATA.unk_213++;
            if (INTRO_DATA.unk_213 == 4)
            {
                INTRO_DATA.unk_213 = 0;

                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 0;
                    finished = TRUE;
                }
            }

            if (gWrittenToBldy >= BLDY_MAX_VALUE)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8A044 | ac | To document
 * 
 */
boolu32 NewFileIntroSr388Preview(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSr388PreviewInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();

            INTRO_DATA.timer++;

            if (gWrittenToBldy)
            {
                if (INTRO_DATA.timer > 1)
                {
                    INTRO_DATA.timer = 0;
                    gWrittenToBldy--;
                }
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.stage = 2;
            }
            break;

        case 2:
            if (NewFileIntroSr388PreviewProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8a0f0 | 40 | To document
 * 
 */
void unk_8a0f0(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 36)
        pOam->animationDurationCounter = 0;

    gBg3XPosition = pOam->xPosition;

    if (INTRO_DATA.subStage == 5)
    {
        gBg3XPosition = 0;
        pOam->type = 0;
    }
}

 /**
 * @brief 8a130 | 40 | To document
 * 
 */
void unk_8a130(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 29)
        pOam->animationDurationCounter = 0;

    gBg2XPosition = pOam->xPosition;

    if (INTRO_DATA.subStage == 5)
    {
        gBg2XPosition = 0;
        pOam->type = 0;
    }
}

 /**
 * @brief 8a170 | 6c | To document
 * 
 */
void NewFileIntroProcessSr388PreviewAsteroid(struct SpecialCutsceneOam *pOam)
{
    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        pOam->unk_A++;
        pOam->xPosition = ((pOam->unk_8 * pOam->unk_A) >> 6) + pOam->spawnX;
        
        if (pOam->xPosition < -40)
        {
            pOam->spawnX = 280;
            pOam->unk_A = 0;
        }
    }
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8a1dc | 28 | To document
 * 
 */
void unk_8a1dc(struct SpecialCutsceneOam* pOam)
{
    pOam->animationDurationCounter++;
    if (pOam->animationDurationCounter == 3)
    {
        pOam->animationDurationCounter = 0;
        pOam->unk_4++;
        gBg1YPosition = pOam->unk_4;
    }
}

 /**
 * @brief 8a204 | 64 | To document
 * 
 */
void unk_8a204(struct SpecialCutsceneOam *pOam)
{
    pOam->unk_A++;
    
    pOam->timer++;
    if (pOam->timer == 21)
        pOam->timer = 0;
    
    if (pOam->unk_A == 110)
        NewFileIntroSr388SetupOam(9, pOam->xPosition + 24, pOam->yPosition);
    else if (pOam->unk_A > 1000)
        pOam->unk_A = 1000;
    
    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8a268 | 38 | To document
 * 
 */
void NewFileIntroProcessSunReflection(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 29)
        pOam->timer = 0;

    if (INTRO_DATA.subStage == 5)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8a2a0 | 30 | To document
 * 
 */
void NewFileIntroProcessSr388Rocks(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 1)
    {
        pOam->timer = 0;
        pOam->yPosition--;
    }

    if (pOam->yPosition <= 160)
        pOam->pOam = sOam_59a0f0;
}

 /**
 * @brief 8a2d0 | 29c | To document
 * 
 */
u8 NewFileIntroSr388SetupOam(u8 type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;
    
    if (type == 1)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8a0f0;
    }
    else if (type == 2)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8a130;
    }
    else if (type == 3)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_59a0a0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 4)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_59a0b0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 5)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_59a0c0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 6)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_59a0d0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388PreviewAsteroid;
    }
    else if (type == 7)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8a1dc;
    }
    else if (type == 8)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sOam_59a100;
        INTRO_DATA.oam[slot].pFunction = unk_8a204;
    }
    else if (type == 9)
    {
        INTRO_DATA.oam[slot].unk_18_3 = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sOam_59a0e0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSunReflection;
    }
    else if (type == 10)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sOam_59a168;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSr388Rocks;
    }
    else if (type == 50)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    
    return slot;
}

 /**
 * @brief 8a56c | 38 | To document
 * 
 */
void NewFileIntroSetupSr388PreviewAsteroid(u8 type, s16 xPosition, s16 yPosition, s16 arg3)
{
    u8 slot;
    
    slot = NewFileIntroSr388SetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8a5a4 | 94 | V-blank for the SR388 preview cutscene
 * 
 */
void NewFileIntroSr388PreviewVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 8a638 | 254 | Setup for the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroInSr388Init(void)
{
    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroHornoadEncounterObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroHornoadEncounterObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroHornoadEncounterBgGfx, VRAM_BASE);
    LZ77UncompVram(sTilemap_5a86c8, VRAM_BASE + 0xE800);
    LZ77UncompVram(sTilemap_5a83b8, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);
    LZ77UncompVram(sTilemap_5a9044, VRAM_BASE + 0xC000);

    DMA3_COPY_32(sPal_5a8e44, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 24, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_512x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    
    gBg2XPosition = 136;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg1XPosition = gBg3XPosition + 392;
    gBg1YPosition = gBg2YPosition - 96;

    gUnk_3001234 = 560;
    gUnk_3001236 = -40;

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);

    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_NEXT_PAGE_ARROW, 250, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_UNK_255, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_UNK_255, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SAMUS, 234, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_LEFT_RESEARCHER, 288, 200);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_RIGHT_RESEARCHER, 312, 100);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_UNK_11, 0, 0);
    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_CAVE_ENTRANCE_BG, 304 - gBg2XPosition, 200);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));
    
    INTRO_DATA.pText = sCutsceneTextNone;
    
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroInSr388Vblank);
}

 /**
 * @brief 8a88c | 344 | Processes the 'hornoad encounter in SR388' cutscene
 * 
 */
boolu32 NewFileIntroInSr388Process(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;
    
    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            INTRO_DATA.unk_213++;
            if (INTRO_DATA.unk_213 == 4)
            {
                INTRO_DATA.unk_213 = 0;
            
                if (gWrittenToBldy)
                    gWrittenToBldy--;
            }
        
            if (INTRO_DATA.timer == 2)
            {
                INTRO_DATA.timer = 0;
                
                gBg2YPosition++;
                if (gBg2YPosition == 96)
                    INTRO_DATA.subStage = 2;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.unk_216;
            break;
        
        case 1:
        case 2:
            INTRO_DATA.timer = 0;
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.unk_216;
            break;
        
        case 3:
            if (INTRO_DATA.timer == 1)
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.unk_216;
            break;
        
        case 4:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            
            gBg2XPosition += INTRO_DATA.unk_216;
            INTRO_DATA.timer = 0;
            break;
        
        case 5:
            if (INTRO_DATA.timer == 1)
            {
                INTRO_DATA.unk_110 = 1;
            }
            else if (INTRO_DATA.timer == 30)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][9];
                INTRO_DATA.subStage = 6;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            if (INTRO_DATA.timer == 10)
            {
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
            }
            else if (INTRO_DATA.timer == 11)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_20C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][10];
                INTRO_DATA.subStage = 8;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            INTRO_DATA.timer = 0;
        
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
        
            gBg2XPosition += INTRO_DATA.unk_216;
        
            if (INTRO_DATA.timer > 50)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                finished = TRUE;
            }
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8abd0 | 98 | Main handler for the 'hornoad encounter in SR388' cutscene
 * 
 */
boolu32 NewFileIntroInSr388(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroInSr388Init();
            
            INTRO_DATA.stage = 2;
            break;
        
        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroInSr388Process())
            {
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
                gWrittenToBldy = 0;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8ac68 | 5d8 | Processes Samus in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessSamusInSr388(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            pOam->yPosition = 240 - gBg2YPosition;
            pOam->xPosition--;
        }
        
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage == 1)
    {
        pOam->yPosition = 240 - gBg2YPosition;
        
        if (pOam->stage == 0)
        {
            if (pOam->timer < 20)
            {
                pOam->xPosition--;
            }
            else if (pOam->timer < 70)
            {
                INTRO_DATA.unk_216 = -1;
            }
            else if (pOam->timer == 70)
            {
                INTRO_DATA.unk_216 = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 1;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningRight;
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleRight;
                pOam->stage = 3;
                INTRO_DATA.unk_20C = 0;
            }
        }
        else if (pOam->stage == 3)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningLeft;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 0;
                INTRO_DATA.subStage = 2;
            }
        }
    }
    else if (INTRO_DATA.subStage == 2)
    {
        pOam->stage = 3;
        INTRO_DATA.subStage = 3;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 0)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingRight;
                pOam->stage = 1;
                pOam->xPosition++;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->xPosition < 260)
            {
                pOam->xPosition++;
            }
            else
            {
                pOam->xPosition = 260;
                pOam->timer = 0;
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            if (pOam->timer == 1)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
                pOam->stage = 3;
            }
        }
        else if (pOam->stage == 3)
        {
            if (pOam->xPosition > 140)
            {
                pOam->xPosition--;
            }
            else if (gBg2XPosition > 108)
            {
                INTRO_DATA.unk_216 = -1;
            }
            else
            {
                INTRO_DATA.unk_216 = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
            
            if (gBg2XPosition > 40)
            {
                INTRO_DATA.unk_216 = -1;
                
                if (gBg2XPosition == 56)
                    NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_HORNOAD, 0, 128);
            }
            else
            {
                INTRO_DATA.unk_216 = 0;
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 6;
            }
        }
        else if (pOam->stage == 6)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningRight;
                pOam->stage = 7;
            }
        }
        else if (pOam->stage == 7)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleRight;
                pOam->stage = 8;
            }
        }
        else if (pOam->stage == 8)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_TurningLeft;
                pOam->stage = 9;
            }
        }
        else if (pOam->stage == 9)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                pOam->stage = 10;
            }
        }
        else if (pOam->stage == 10)
        {
            if (pOam->timer == 30)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
                pOam->stage = 11;
            }
        }
        else if (pOam->stage == 11)
        {
            pOam->pOam = sIntroInSr388SamusOam_WalkingLeft;
            
            if (pOam->timer == 1)
            {
                if (gBg2XPosition != 0)
                {
                    INTRO_DATA.unk_216 = -1;
                }
                else
                {
                    INTRO_DATA.unk_216 = 0;
                    pOam->timer = 0;
                    pOam->animationDurationCounter = 0;
                    pOam->currentAnimationFrame = 0;
                    pOam->pOam = sIntroInSr388SamusOam_IdleLeft;
                    INTRO_DATA.subStage = 4;
                    pOam->stage = 0;
                }
            }
            else
            {
                pOam->timer = 0;
                INTRO_DATA.unk_216 = 0;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        if (pOam->stage == 0)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedLeft;
                pOam->stage = 1;
            }
        }
        else if (pOam->stage == 1)
        {
            if (pOam->timer == 60)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 22);
                
                pOam->stage = 2;
            }
        }
        else if (pOam->stage == 2)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedLeft;
                pOam->stage = 3;
            }
        }
        else if (pOam->stage == 3)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);
            
            if (x == 300)
            {
                pOam->timer = 0;
                pOam->stage = 4;
            }
        }
        else if (pOam->stage == 4)
        {
            if (pOam->timer == 8)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                return;
            }
            else if (pOam->timer == 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 5;
            }
        }
        else if (pOam->stage == 5)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 6;
            }
        }
        else if (pOam->stage == 6)
        {
            if (pOam->timer == 130)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 7;
            }
        }
        else if (pOam->stage == 7)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 8;
            }   
        }
        else if (pOam->stage == 8)
        {
            if (pOam->timer == 78)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_FiringMissileUpLeft;
                
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE, pOam->xPosition - 20, pOam->yPosition - 40);
                
                pOam->stage = 9;
            }
        }
        else if (pOam->stage == 9)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388SamusOam_MissileArmedUpLeft;
                pOam->stage = 10;
            }
        }
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 8b240 | 20c | Processes the left BSL guy in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewfileIntroProcessLeftBiologicalResearcher(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            pOam->xPosition = x + pOam->unk_8;
            pOam->yPosition = y;
        }
        
        pOam->timer = 0;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 1 || INTRO_DATA.subStage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
        
        pOam->xPosition = x + pOam->unk_8;
        pOam->yPosition = y;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 16)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition < x)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 17;
            }
        }
        else if (pOam->stage == 17)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Turning;
                pOam->stage = 18;
            }
        }
        else if (pOam->stage == 18)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 19;
            }
        }
        else if (pOam->stage == 19)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + pOam->unk_8)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 20;
            }
        }
        else if (pOam->stage == 20)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition <= x + pOam->unk_8 - 7)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 21;
            }
            else
            {
                pOam->xPosition--;
            }
        }
        else if (pOam->stage == 21)
        {
            if (gBg2XPosition < 98)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 22;
            }
        }
        else if (pOam->stage == 22)
        {
            if (gBg2XPosition > 45)
            {
                pOam->xPosition--;
            }
            else
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 23;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
    
    pOam->xPosition -= INTRO_DATA.unk_216;
}

 /**
 * @brief 8b44c | 214 | Processes the right BSL guy in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewfileIntroProcessRightBiologicalResearcher(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (INTRO_DATA.subStage == 0)
    {
        if (gBg2YPosition > 47)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            pOam->xPosition = x + pOam->unk_8;
            pOam->yPosition = y;
        }
        
        pOam->timer = 0;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 1 || INTRO_DATA.subStage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
        
        pOam->xPosition = x + pOam->unk_8;
        pOam->yPosition = y;
        pOam->stage = 20;
    }
    else if (INTRO_DATA.subStage == 3)
    {
        if (pOam->stage == 16)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition < x)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->stage = 17;
            }
        }
        else if (pOam->stage == 17)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Turning;
                pOam->stage = 18;
            }
        }
        else if (pOam->stage == 18)
        {
            frame = &pOam->pOam[pOam->currentAnimationFrame];
            if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 19;
            }
        }
        else if (pOam->stage == 19)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition > x + pOam->unk_8 + 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 20;
            }
        }
        else if (pOam->stage == 20)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);
            
            if (pOam->xPosition <= x + pOam->unk_8 - 10)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 21;
            }
            else
            {
                pOam->xPosition--;
            }
        }
        else if (pOam->stage == 21)
        {
            if (gBg2XPosition < 103)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Walking;
                pOam->stage = 22;
            }
        }
        else if (pOam->stage == 22)
        {
            if (gBg2XPosition > 52)
            {
                pOam->xPosition--;
            }
            else
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388BslResearcherOam_Idle;
                pOam->stage = 23;
            }
        }
    }
    else if (INTRO_DATA.subStage == 4)
    {
        pOam->timer = 0;
    }
    else if (INTRO_DATA.subStage > 4)
    {
        pOam->animationDurationCounter = 0;
    }
    
    pOam->xPosition -= INTRO_DATA.unk_216;
}

 /**
 * @brief 8b660 | 174 | Processes the hornoad in the SR388 cutscene (unused?)
 * 
 */
void unk_8b660(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    u32 timer;
    u8 tmp;
    s16 y;
    
    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam-> yPosition;
        pOam->unk_4 = 0;
        pOam->pOam = sIntroInSr388HornoadOam_IdleUnused;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->pOam = sIntroInSr388HornoadOam_JumpingUnused;

        if (pOam->unk_8 == 0)
        {
            timer = pOam->timer;
            y = sHornoadJumpVelocityHigh[pOam->unk_4] * timer >> 2;
        }
        else
        {
            timer = pOam->timer;
            tmp = timer; // From permuter
            y = sHornoadJumpVelocityLow[pOam->unk_4] * tmp >> 2;
        }
        
        pOam->yPosition = pOam->spawnY + y;
        if (pOam->yPosition > 144)
        {
            pOam->yPosition = 144;
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_BouncingUnused;
            pOam->stage = 2;
        }

        if (y < 0)
            pOam->xPosition += 2;
        else
            pOam->xPosition += 1;

        if (pOam->animationDurationCounter == 4 && pOam->currentAnimationFrame == 2)
            pOam->xPosition += 8;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = pOam->yPosition;
            pOam->unk_4++;

            if (pOam->unk_4 == 10)
                pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;

        if (pOam->timer == sArray_59db00[pOam->unk_A])
        {
            pOam->unk_A++;
            if (pOam->unk_A == 6)
                pOam->unk_A = 0;

            if (!pOam->unk_8)
                pOam->unk_8 = 1;
            else
                pOam->unk_8 = 0;

            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->stage = 0;
        }
    }

    pOam->xPosition -= INTRO_DATA.unk_216;
    if (pOam->xPosition > 260)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8b7d4 | 4c8 | Processes the hornoad in the SR388 cutscene
 * 
 */
void NewFileIntroProcessHornoad(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 var0;
    s16 var1;
    s32 var2;
    s32 spawnY;
    s32 xPos;
    s16 x;
    s16 y;

    pOam->timer++;

    if (pOam->stage == 0)
    {
        pOam->spawnY = pOam->yPosition;

        if (pOam->timer == 150)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Chomping;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->spawnY = pOam->yPosition;

        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Chomping;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);

        pOam->spawnY = pOam->yPosition;

        if (x - pOam->xPosition < 25)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Biting;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->pOam = sIntroInSr388HornoadOam_Jumping;

        var0 = pOam->timer * sHornoadJumpVelocityHigh[pOam->unk_4] >> 2;
        var2 = var0 + (u16)pOam->spawnY;
        pOam->yPosition = var2;

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = var2;

            pOam->unk_4++;
            if (pOam->unk_4 == 5)
            {
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_MidAir;
            }
            else if (pOam->unk_4 > 10)
            {
                pOam->unk_4 = 10;
            }
        }

        if (pOam->yPosition > 128)
        {
            pOam->spawnY = 128;
            pOam->yPosition = 128;
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Bouncing;
            pOam->unk_4 = 0;
            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Panting;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE, &x, &y);

        if (x == 300)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388HornoadOam_Biting;
            pOam->stage = 6;
        }
    }
    else if (pOam->stage == 6)
    {
        pOam->pOam = sIntroInSr388HornoadOam_Jumping;

        var0 = pOam->timer * sHornoadJumpVelocityHigh[pOam->unk_4] >> 1;
        do { pOam->spawnY += 0; } while (0);
        spawnY = (u16)pOam->spawnY;
        var2 = var0;
        pOam->yPosition = var2 + spawnY;
        pOam->xPosition++;

        if (pOam->currentAnimationFrame == 2 && pOam->animationDurationCounter == 4)
        {
            xPos = (u16)pOam->xPosition;
            xPos += 8;
            pOam->xPosition = xPos;
        }
        else
        {
            var0 += 0;
        }

        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            pOam->spawnY = pOam->yPosition;

            pOam->unk_4++;
            if (pOam->unk_4 == 5)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_MidAir;
            }
            else if (pOam->unk_4 > 10)
            {
                pOam->unk_4 = 10;
            }
        }

        if (pOam->unk_4 > 1)
        {
            NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE, &x, &y);

            if (pOam->xPosition >= x && pOam->yPosition >= y)
            {
                NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_EXPLOSION_BIG, pOam->xPosition, pOam->yPosition);

                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388HornoadOam_Shaking;
                pOam->unk_4 = 1;
                WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[1] * 16);
                pOam->unk_18_5 = 1;
                pOam->stage = 7;
            }
        }
    }
    else if (pOam->stage == 7)
    {
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->unk_4++;
            WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[pOam->unk_4] * 16);
        }

        if (pOam->unk_A == 1)
        {
            if (pOam->unk_4 == 15)
            {
                pOam->timer = 0;
                pOam->animationDurationCounter = 0;
                pOam->currentAnimationFrame = 0;
                pOam->pOam = sIntroInSr388XParasiteOam_Floating;
                pOam->xPosition -= 4;
                pOam->yPosition -= 10;
                pOam->unk_A = 0;
                pOam->stage = 8;
            }
        }
        else
        {
            if (pOam->unk_4 == 29)
            {
                pOam->unk_A++;
                pOam->unk_4 = 1;
            }
        }
    }
    else if (pOam->stage == 8)
    {
        if (pOam->timer == 2)
        {
            pOam->timer = 0;
            pOam->unk_4++;
            WRITE_16(REG_MOSAIC, sXParasiteMosaicValues[pOam->unk_4] * 16);
        }

        if (pOam->unk_A == 1)
        {
            if (pOam->unk_4 == 29)
            {
                pOam->timer = 0;
                pOam->unk_18_5 = 0;

                NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_SAMUS, &x, &y);

                pOam->spawnY = pOam->yPosition;
                pOam->spawnX = x;
                pOam->unk_4 = x - pOam->xPosition;
                pOam->unk_A = 63;
                pOam->stage = 9;
            }
        }
        else
        {
            if (pOam->unk_4 == 29)
            {
                pOam->unk_A++;
                pOam->unk_4 = 1;
            }
        }
    }
    else if (pOam->stage == 9)
    {
        if (pOam->timer != 10)
        {
            if (pOam->timer > 30)
            {
                pOam->timer = 0;
                pOam->stage = 10;
            }
        }
    }
    else if (pOam->stage == 10)
    {
        pOam->unk_A++;
        if (pOam->unk_A > 255)
            pOam->unk_A -= 256;

        var0 = pOam->unk_A;
        var1 = pOam->unk_A * 2;
        if (var1 > 255)
            var1 -= 256;

        pOam->xPosition = pOam->spawnX + ((pOam->unk_4 * COS(var1) * SIN(var0)) >> 16);
        pOam->yPosition = pOam->spawnY + ((pOam->unk_4 * COS(var1) * COS(var0)) >> 16);

        if (pOam->unk_A > 159)
        {
            pOam->unk_A = 0;
            pOam->timer = 0;
            pOam->unk_4 = 0;
            pOam->spawnY = 0;
            pOam->spawnX = 0;
            pOam->stage = 11;
        }
        else if (pOam->unk_A > 155)
        {
            pOam->spawnX--;
            pOam->spawnY++;
        }
        else if (pOam->unk_A > 119)
        {
            pOam->spawnY++;
        }
    }
    else if (pOam->stage == 11)
    {
        pOam->affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;

        pOam->scaling += Q_8_8(0.5f);
        if (pOam->scaling >= Q_8_8(2))
            pOam->stage = 12;
    }
    else if (pOam->stage == 12)
    {
        pOam->scaling -= Q_8_8(1.f / 16);
        if (pOam->scaling <= Q_8_8(0.56f))
        {
            INTRO_DATA.subStage = 5;
            pOam->stage = 13;
        }
    }
    else if (pOam->stage == 13)
    {
        pOam->animationDurationCounter = 0;
    }

    pOam->xPosition -= INTRO_DATA.unk_216;
}

 /**
 * @brief 8bc9c | b4 | Processes the horizontal missile in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessHorizontalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * sNormalMissileVelocity[pOam->unk_4] >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 12, pOam->yPosition + 2);
        }
        
        if (pOam->xPosition < 32)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388MissileExplosionOam_Small;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 8bd50 | c8 | Processes the first diagonal missile in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessFirstDiagonalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 10, pOam->yPosition + 12);
        }

        NewFileIntroGetPositionOfOamByType(INTRO_IN_SR388_OAM_TYPE_HORNOAD, &x, &y);

        if (pOam->xPosition <= x - 2 && pOam->yPosition <= y - 2)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 8be18 | 2c | To document
 * 
 */
void unk_8be18(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8be44 | d8 | To document
 * 
 */
void unk_8be44(struct SpecialCutsceneOam *pOam)
{
    if (pOam->stage == 0)
    {
        pOam->yPosition = gBg2YPosition;
        pOam->xPosition = gBg2XPosition;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->yPosition + 1 < gBg2YPosition)
        {
            pOam->yPosition = gBg2YPosition;
            gBg3YPosition++;
        }
        
        if (pOam->xPosition - 1 > gBg2XPosition)
        {
            pOam->xPosition = gBg2XPosition;
            gBg3XPosition--;
        }
    }
    
    if (pOam->unk_4 == 0)
    {
        gBg1XPosition = gBg2XPosition + 256;
        gBg1YPosition = gBg2YPosition - 96;
        
        if (gBg1XPosition < 120)
        {
            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            
            gWrittenToBldalpha_Eva = gWrittenToBldalpha_Evb = 0;
            pOam->unk_4 = 1;
        }
    }
    
    if (gBg2XPosition == 0)
        pOam->type = 0;
}

 /**
 * @brief 8bf1c | 4c | To document
 * 
 */
void unk_8bf1c(struct SpecialCutsceneOam* pOam)
{
    if (gBg2YPosition > 23)
        pOam->yPosition = 216 - gBg2YPosition;

    pOam->xPosition -= INTRO_DATA.unk_216;
    if (pOam->xPosition > 302)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8bf68 | 48 | To document
 * 
 */
void unk_8bf68(struct SpecialCutsceneOam* pOam)
{
    if (gBg2YPosition > 23)
        pOam->yPosition = 216 - gBg2YPosition;

    pOam->xPosition -= INTRO_DATA.unk_216;
    if (pOam->xPosition > 250)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8bfb0 | d4 | Processes the second and subsequent diagonal missiles in the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroProcessSecondDiagonalMissile(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;

    pOam->timer++;
    
    if (pOam->stage == 0)
    {
        pOam->xPosition = pOam->spawnX - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        pOam->yPosition = pOam->spawnY - (pOam->timer * (sNormalMissileVelocity[pOam->unk_4] + 1) >> 2);
        
        if (pOam->timer == 4)
        {
            pOam->timer = 0;
            
            if (pOam->unk_4 < 6)
                pOam->unk_4++;
            
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
        }
        else if (pOam->timer == 1)
        {
            NewFileIntroInSr388SetupOam(INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL, pOam->xPosition + 10, pOam->yPosition + 12);
        }
        
        if (pOam->yPosition < 50)
        {
            pOam->timer = 0;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroInSr388MissileExplosionOam_Small;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 8c084 | 8 | To document
 * 
 */
void unk_8c084(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

 /**
 * @brief 8c08c | 478 | Spawns an object for the 'hornoad encounter in SR388' cutscene
 * 
 */
u8 NewFileIntroInSr388SetupOam(IntroInSr388OamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == INTRO_IN_SR388_OAM_TYPE_SAMUS)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388SamusOam_WalkingLeft;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusInSr388;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_LEFT_RESEARCHER)
    {
        INTRO_DATA.oam[slot].unk_8 = 38;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BslResearcherOam_Walking;
        INTRO_DATA.oam[slot].pFunction = NewfileIntroProcessLeftBiologicalResearcher;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_RIGHT_RESEARCHER)
    {
        INTRO_DATA.oam[slot].unk_8 = 72;
        INTRO_DATA.oam[slot].currentAnimationFrame = 1;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BslResearcherOam_Walking;
        INTRO_DATA.oam[slot].pFunction = NewfileIntroProcessRightBiologicalResearcher;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD_UNUSED)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_IdleUnused;
        INTRO_DATA.oam[slot].pFunction = unk_8b660;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD_UNUSED_2)
    {
        INTRO_DATA.oam[slot].unk_8 = 1;
        INTRO_DATA.oam[slot].unk_A = 2;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_IdleUnused;
        INTRO_DATA.oam[slot].pFunction = unk_8b660;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORIZONTAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Horizontal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHorizontalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_FIRST_DIAGONAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Diagonal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessFirstDiagonalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_MISSILE_TRAIL)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileTrailOam;
        INTRO_DATA.oam[slot].pFunction = unk_8be18;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_HORNOAD)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388HornoadOam_Panting;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessHornoad;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_MISSILE_EXPLOSION_BIG)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileExplosionOam_Big;
        INTRO_DATA.oam[slot].pFunction = unk_8be18;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_UNK_11)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8be44;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_CAVE_ENTRANCE_BG)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388CaveEntranceBgOam;
        INTRO_DATA.oam[slot].pFunction = unk_8bf1c;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_BLACK_RECTANGLE)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388BlackRectangeOam;
        INTRO_DATA.oam[slot].pFunction = unk_8bf68;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_SECOND_DIAGONAL_MISSILE)
    {
        INTRO_DATA.oam[slot].spawnX = xPosition;
        INTRO_DATA.oam[slot].spawnY = yPosition;
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroInSr388MissileOam_Diagonal;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSecondDiagonalMissile;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    else if (type == INTRO_IN_SR388_OAM_TYPE_UNK_255)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8c084;
    }

    return slot;
}

 /**
 * @brief 8c504 | 38 | To document
 * 
 */
void unk_8c504(IntroInSr388OamType type, s16 xPosition, s16 yPosition, u16 arg3)
{
    u8 slot;
    
    slot = NewFileIntroInSr388SetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8c53c | 4 | Empty function
 * 
 */
void NewFileIntro_Empty(void)
{
    return;
}

 /**
 * @brief 8c540 | 54 | Returns the X and Y position of a new file intro OAM
 * 
 */
void NewFileIntroGetPositionOfOamByType(IntroInSr388OamType type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
            
            return;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
}

 /**
 * @brief 8c594 | dc | V-blank for the 'hornoad encounter in SR388' cutscene
 * 
 */
void NewFileIntroInSr388Vblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));

    WRITE_16(REG_BLDY, gWrittenToBldy);

    WRITE_16(REG_BG1HOFS, gBg1XPosition);
    WRITE_16(REG_BG1VOFS, gBg1YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;

        DMA3_COPY_32(sPal_5a9440, PALRAM_OBJ, 15 * PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(sPal_5a9260, PALRAM_BASE, 15 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8c670 | 204 | Setup for the new file intro Metroid vaccine cutscene
 * 
 */
void NewFileIntroSamusGettingCuredInit(void)
{
    const u16* pText2;

    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    pText2 = INTRO_DATA.pText2; // Preserve second text pointer
    
    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    INTRO_DATA.pText2 = pText2;

    LZ77UncompVram(sIntroMetroidVaccineObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroMetroidVaccineObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroMetroidVaccineBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroMetroidVaccineBg1Tilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroMetroidVaccineBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroMetroidVaccineBg3Tilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroMetroidVaccineBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
    
    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_DOUBLE_HELIX, 192, 96);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_BG_TEXT, 0, 0);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusGettingCuredVblank);
}

 /**
 * @brief 8c874 | 158 | Processes the new file intro Metroid vaccine cutscene
 * 
 */
boolu32 NewFileIntroSamusGettingCuredOperationProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;

    INTRO_DATA.timer++;
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1))
            {
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = INTRO_DATA.pText2;
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(2 + 2.f / 3))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(3))
            {
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_TEXTBOXES, 108, 64);
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_ELECTROCARDIOGRAM, 128, 68);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(6 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
        
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
                INTRO_DATA.unk_218 = 0;
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.subStage = 3;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = TRUE;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8c9cc | 20 | H-blank code for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemHblank(void)
{
    s16 val;

    val = READ_16(REG_VCOUNT) * 2; // * 2, / 2 shenanigans are needed for match
    WRITE_16(REG_WIN0H, ((u16*)(EWRAM_BASE + 0x2000))[val / 2]);
}

 /**
 * @brief 8c9ec | 320 | Setup for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemInit(void)
{
    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));

    INTRO_DATA.unk_218 = 0;

    LZ77UncompVram(sIntroSamusNervousSystemObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroSamusNervousSystemObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroSamusNervousSystemBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusNervousSystemBg1Tilemap, VRAM_BASE + 0xE800);
    LZ77UncompVram(sIntroSamusNervousSystemBg2Tilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusNervousSystemBg3Tilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusNervousSystemBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    SET_BACKDROP_COLOR(COLOR_GREEN);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG1CNT, CREATE_BGCNT(0, 29, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Evb = gWrittenToBldalpha_Eva = 0;

    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10, 0, 0);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_CORNER_TEXT, 172, 158);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NERVE_PARTS, 120, 80);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1, 195, 97);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2, 128, 128);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3, 145, 28);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4, 100, 72);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5, 44, 30);
    NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6, 62, 121);

    INTRO_DATA.unk_110 = 0;
    INTRO_DATA.unk_111 = 0;

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_WIN0V, C_16_2_8(0, SCREEN_SIZE_Y));

    INTRO_DATA.unk_1F3 = 70;
    INTRO_DATA.unk_1F4 = 120;
    INTRO_DATA.unk_1F5 = 78;

    NewFileIntroSamusGettingCuredSetupWindow();
    NewFileIntroSamusGettingCuredSetupWindow();

    DMA3_COPY_32(NewFileIntroSamusGettingCuredNervousSystemHblank, INTRO_DATA.hBlankCode, sizeof(INTRO_DATA.hBlankCode) / sizeof(u32));
    INTRO_DATA.hBlankCodePointer = INTRO_DATA.hBlankCode + 1;
    CallbackSetHBlank(INTRO_DATA.hBlankCodePointer);

    WRITE_16(REG_IE, READ_16(REG_IE) | IF_HBLANK);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) | DSTAT_IF_HBLANK);
    WRITE_16(REG_WININ, WIN0_BG0 | WIN0_BG1 | WIN0_BG3 | WIN0_OBJ | WIN0_COLOR_EFFECT);
    WRITE_16(REG_WINOUT, WIN0_ALL);
    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);
    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_WIN0);
    
    CallbackSetVBlank(NewFileIntroSamusGettingCuredNervousSystemVblank);
}

 /**
 * @brief 8cd0c | 274 | Processes the new file intro Samus nervous system cutscene
 * 
 */
boolu32 NewFileIntroSamusGettingCuredNervousSystemProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.unk_218)
        INTRO_DATA.unk_218 = 1;

    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);

    switch (INTRO_DATA.subStage)
    {
        case 0:
            NewFileIntroSamusGettingCuredNervousSystemInit();
            INTRO_DATA.subStage = 1;
            break;
        
        case 1:
            if (gWrittenToBldy)
            {
                gWrittenToBldy -= 2;
            }
            else
            {
                gWrittenToBldy = 0;
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL 
                         | BLDCNT_OBJ_SECOND_TARGET_PIXEL | BLDCNT_BACKDROP_SECOND_TARGET_PIXEL);
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (gWrittenToBldalpha_Eva < 12)
            {
                gWrittenToBldalpha_Eva++;
                gWrittenToBldalpha_Evb++;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][16];
                INTRO_DATA.subStage = 4;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.pText2 = INTRO_DATA.pText;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 5;
            }
            else if (INTRO_DATA.unk_218 == 4)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 5;
                INTRO_DATA.pText2 = INTRO_DATA.pText;
                INTRO_DATA.pText = sCutsceneTextNone;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 5:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_28, 0, 0);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(7.5f))
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 4;
                INTRO_DATA.subStage = 7;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            if (gWrittenToBldalpha_Eva)
            {
                gWrittenToBldalpha_Eva -= 2;
                gWrittenToBldalpha_Evb -= 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                INTRO_DATA.subStage = 7;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
            
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 2;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 0;
                finished = 1;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8cf80 | dc | Main handler for the new file intro Samus getting cured cutscenes
 * 
 */
boolu32 NewFileIntroSamusGettingCured(void)
{
    boolu32 finished;

    finished = FALSE;
    
    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusGettingCuredInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusGettingCuredOperationProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (NewFileIntroSamusGettingCuredNervousSystemProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 4;
            }
            break;

        case 4:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8d05c | 10 | Processes the new file intro Metroid vaccine background text OAM
 * 
 */
void NewFileIntroProcessVaccineBackgroundText(struct SpecialCutsceneOam* pOam)
{
    WRITE_16(REG_BG2VOFS, pOam->yPosition--);
}

 /**
 * @brief 8d06c | 10 | To document
 * 
 */
void unk_8d06c(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
    pOam->unk_18_0 = 0;
}

 /**
 * @brief 8d07c | e0 | Processes the first X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_1(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 4)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 5)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 20)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_1, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 220)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d15c | 6c | Processes the new file intro X lock-on OAM
 * 
 */
void NewFileIntroProcessXLockOn(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    if (INTRO_DATA.oam[pOam->unk_8].type != 0)
    {
        pOam->xPosition = INTRO_DATA.oam[pOam->unk_8].xPosition;
        pOam->yPosition = INTRO_DATA.oam[pOam->unk_8].yPosition;
    }

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 8d1c8 | e4 | Processes the second X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_2(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 4)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 4)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 4)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 20)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_2, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 220)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d2ac | f0 | Processes the third X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_3(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 6)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 1)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 3)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 40)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_3, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 240)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d39c | e4 | Processes the fourth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_4(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 5)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 5)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 5)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 40)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_4, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 240)
        {
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d480 | f0 | Processes the fifth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_5(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX - 1)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 4)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 60)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_5, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 260)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d570 | f0 | Processes the sixth X parasite in the Samus nervous system cutscene
 * 
 */
void NewFileIntroProcessXInNervousSystem_6(struct SpecialCutsceneOam *pOam)
{
    u8 rng;

    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        pOam->stage = 1;
    }

    rng = SpecialCutsceneGetRandomNumber();
    if (rng < 80)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->xPosition < pOam->spawnX + 5)
                pOam->xPosition++;
        }
        else if (pOam->xPosition > pOam->spawnX)
        {
            pOam->xPosition--;
        }
    }
    else if (rng < 160)
    {
        if (MOD_AND(rng, 2))
        {
            if (pOam->yPosition < pOam->spawnY + 3)
                pOam->yPosition++;
        }
        else if (pOam->yPosition > pOam->spawnY - 3)
        {
            pOam->yPosition--;
        }
    }
    
    if (gNonGameplayRam.intro.subStage == 5)
    {
        pOam->unk_A++;
        if (pOam->unk_A == 60)
        {
            NewFileIntroSamusGettingCuredSetupOam(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_6, pOam->xPosition, pOam->yPosition);
        }
        else if (pOam->unk_A > 260)
        {
            pOam->affineMode = OAM_AFFINE_MODE_AFFINE;
            pOam->scaling -= 2;
            if (pOam->scaling < Q_8_8(1.f/ 8))
            {
                pOam->type = 0;
                pOam->unk_18_0 = 0;
            }
        }
    }
}

 /**
 * @brief 8d660 | 94 | To document
 * 
 */
void unk_8d660(struct SpecialCutsceneOam *pOam)
{
    u8 value;
    
    pOam->unk_A++;

    if (pOam->stage == 0)
    {
        if (pOam->unk_A > 20)
        {
            pOam->unk_A = 0;
            INTRO_DATA.unk_110 = 1;
            INTRO_DATA.unk_111 = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1 && LOW_BYTE(sArray_5a9620[pOam->unk_8]) == pOam->unk_A)
    {
        pOam->unk_A = 0;

        if (pOam->unk_8 < 29)
            pOam->unk_8++;

        value = HIGH_BYTE(sArray_5a9620[pOam->unk_8]);
        INTRO_DATA.unk_111 = value;
        INTRO_DATA.unk_110 = 1;
    }
}

 /**
 * @brief 8d6f4 | 6d0 | Spawns an OAM for a new file intro Samus getting cured cutscene
 * 
 */
u8 NewFileIntroSamusGettingCuredSetupOam(IntroSamusGettingCuredOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot > 19)
        return 20;
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));
    
    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_DOUBLE_HELIX)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineDoubleHelixOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_TEXTBOXES)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineTextboxesOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_ELECTROCARDIOGRAM)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroMetroidVaccineElectrocardiogramOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_VACCINE_BG_TEXT)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessVaccineBackgroundText;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_10)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8d06c;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_COUNTDOWN_FAST)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCountdownOam_Fast;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_COUNTDOWN_SLOW)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCountdownOam_Slow;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NUMBER_281)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemNumber281Oam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_CORNER_TEXT)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemCornerTextOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NERVE_PARTS)
    {
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemNervePartsOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusGettingCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.25f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_1;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_2;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_3;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.25f);
        INTRO_DATA.oam[slot].affineMode = OAM_AFFINE_MODE_DOUBLE_SIZED;
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_4;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_4;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_5;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_5;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1);
        INTRO_DATA.oam[slot].priority = 3;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXParasiteOam_6;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXInNervousSystem_6;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_1)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_1);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_1;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_2)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_2);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_2;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_3)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_3);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_3;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_4)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_4);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_4;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_5)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_5);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_5;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_LOCK_ON_6)
    {
        INTRO_DATA.oam[slot].unk_8 = NewFileIntroFindOamByType(INTRO_SAMUS_GETTING_CURED_OAM_TYPE_X_PARASITE_6);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusNervousSystemXLockOnOam_6;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessXLockOn;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_UNK_28)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_8d660;
    }
    else if (type == INTRO_SAMUS_GETTING_CURED_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }
    
    return slot;
}

 /**
 * @brief 8ddc4 | 38 | Spawns an OAM for a new file intro Samus getting cured cutscene with an additional argument
 * 
 */
void unk_8ddc4(IntroSamusGettingCuredOamType type, s16 xPosition, s16 yPosition, s16 arg3)
{
    u8 slot;

    slot = NewFileIntroSamusGettingCuredSetupOam(type, xPosition, yPosition);
    INTRO_DATA.oam[slot].unk_8 = arg3;
}

 /**
 * @brief 8ddfc | 3c | Returns the OAM slot of the specified Samus getting cured cutscene OAM
 * 
 */
u8 NewFileIntroFindOamByType(IntroSamusGettingCuredOamType type)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
            return slot;
    }

    // Default value if not found
    return ARRAY_SIZE(INTRO_DATA.oam);
}

 /**
 * @brief 8de38 | 4c | V-blank code for the new file intro Metroid vaccine cutscene
 * 
 */
void NewFileIntroSamusGettingCuredVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
}

 /**
 * @brief 8de84 | a8 | V-blank code for the new file intro Samus nervous system cutscene
 * 
 */
void NewFileIntroSamusGettingCuredNervousSystemVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);

    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;

        DMA3_COPY_32(sArray_79c2e4[INTRO_DATA.unk_111], PALRAM_OBJ, 4 * PAL_ROW_SIZE / sizeof(u32));
        DMA3_COPY_32(sArray_79c2e4[INTRO_DATA.unk_111], PALRAM_BASE, 4 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8df2c | 4 | Empty OAM handler function for the 'Samus getting cured' cutscenes 
 * 
 */
void NewFileIntroSamusGettingCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 8df30 | 210 | Setup for the intro Samus found cutscene
 * 
 */
void NewFileIntroSamusFoundInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 0x1E0, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroHazmatTeamGfx, VRAM_BASE);
    LZ77UncompVram(sIntroVariaSuitCoveredInXParasitesGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroHazmatTeamTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroVariaSuitCoveredInXParasitesTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusFoundPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroSuitRemovalSurgeryGfx, EWRAM_BASE);
    LZ77UncompWram(sIntroMetroidVaccineVialGfx, EWRAM_BASE + 0x8000);
    LZ77UncompWram(sIntroSuitRemovalSurgeryTilemap, EWRAM_BASE + 0xD000);
    LZ77UncompWram(sIntroMetroidVaccineVialTilemap, EWRAM_BASE + 0xD800);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_INCREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    
    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusFoundVblank);
}

 /**
 * @brief 8e140 | 594 | Processes the intro Samus found cutscene
 * 
 */
boolu32 NewFileIntroSamusFoundProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && !INTRO_DATA.unk_218)
        INTRO_DATA.unk_218 = 1;
    
    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][12];
                INTRO_DATA.subStage = 1;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            INTRO_DATA.timer = 0;
            gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
            gWrittenToBldalpha_Evb = 0;

            if (INTRO_DATA.unk_218 == 2)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 2;
            }
            else if (INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 2;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f) - DELTA_TIME)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN, 16, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 3;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 3:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f) - DELTA_TIME)
            {
                SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN);
                gWrittenToBldalpha_Eva = 0;
                gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                DMA3_COPY_32(EWRAM_BASE + 0xD000, VRAM_BASE + 0xF000, 0x200);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f) + DELTA_TIME)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX, 0, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 2.f / 3) - DELTA_TIME)
            {
                // Empty
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 4;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            INTRO_DATA.timer = 0;
            gWrittenToBldalpha_Eva = 0;
            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING, 0, 0);
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG2);
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 5;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 5:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
                INTRO_DATA.timer = 0;
                SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING);
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
                INTRO_DATA.subStage = 6;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 6:
            if (INTRO_DATA.timer == ONE_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][13];
                INTRO_DATA.subStage = 7;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 7:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 8;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][14];
                INTRO_DATA.subStage = 9;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
                INTRO_DATA.subStage = 10;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 10:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG3);
                DMA3_COPY_32(EWRAM_BASE + 0xD800, VRAM_BASE + 0xF800, 0x200);
            }
            else if (INTRO_DATA.timer == 2 * DELTA_TIME)
            {
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX_2, 0, 0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.25f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE, 0, 0);
                NewFileIntroSamusFoundSetupOam(INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING, 0, gBg2YPosition);
                INTRO_DATA.subStage = 11;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 11:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1.5f))
            {
	            gWrittenToBldalpha_Eva = 0;
	            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
	            INTRO_DATA.timer = 0;
	            SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE);
	            SpecialCutsceneDestroyOamOfType(INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING);
	            INTRO_DATA.subStage = 12;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
        
	    case 12:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
	            INTRO_DATA.timer = 0;
	            DMA3_FILL_32(0, VRAM_BASE + 0xD000, 0x1000);
	            INTRO_DATA.unk_212 = 0;
	            INTRO_DATA.unk_E = 0;
	            INTRO_DATA.unk_C = 0;
	            INTRO_DATA.pText = sMonologueTextPointers[gLanguage][15];
	            INTRO_DATA.subStage = 13;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
	
	    case 13:
	        INTRO_DATA.timer = 0;
            
	        if (INTRO_DATA.unk_218 == 2)
            {
                INTRO_DATA.unk_218 = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
	            INTRO_DATA.pText = sCutsceneTextNone;
	            INTRO_DATA.subStage = 14;
            }
            else if (INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
	            INTRO_DATA.pText2 = INTRO_DATA.pText;
	            INTRO_DATA.pText = sCutsceneTextNone;
	            INTRO_DATA.subStage = 14;
            }
            
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
	
	    case 14:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
	            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
	            WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
	            gWrittenToBldy = 0;
	            INTRO_DATA.timer = 0;
	            INTRO_DATA.subStage = 0;
	            finished = TRUE;
	        }
	
	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
    }
    
    IntroProcessText();
    
    return finished;
}

 /**
 * @brief 8e6d4 | a8 | Main handler of the intro Samus found cutscene
 * 
 */
boolu32 NewFileIntroSamusFound(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusFoundInit();
            INTRO_DATA.stage = 1;
            break;

        case 1:
            APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
            if (INTRO_DATA.timer == CONVERT_SECONDS(.1f))
            {
                INTRO_DATA.timer = 0;

                if (gWrittenToBldy)
                    gWrittenToBldy--;
                else
                    INTRO_DATA.stage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (NewFileIntroSamusFoundProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    return finished;
}

 /**
 * @brief 8e77c | 6c | Fades in the Varia suit covered in X parasites screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeIn(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == 4)
    {
        pOam->timer = 0;

        if (pOam->xPosition > 0)
            pOam->xPosition--;
    }

    gBg3XPosition = pOam->xPosition;
    gBg3YPosition = 0;

    pOam->unk_A++;
    if (pOam->unk_A == 5)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva)
        {
            gWrittenToBldalpha_Eva--;
            gWrittenToBldalpha_Evb++;
        }
    }
}

 /**
 * @brief 8e7e8 | 48 | Copies intro Samus found cutscene graphics from EWRAM into VRAM
 * 
 */
void NewFileIntroProcessSamusLayingLoading(struct SpecialCutsceneOam* pOam)
{
    u32 offset;

    offset = pOam->unk_A * 0x1000;
    DMA3_COPY_32(EWRAM_BASE + offset, VRAM_BASE + offset, 0x1000 / sizeof(u32));

    pOam->unk_A++;
    if (pOam->unk_A == pOam->unk_8 + pOam->unk_4)
        pOam->type = 0;
}

 /**
 * @brief 8e830 | 6c | Fades in the intro Varia suit removal surgery screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeInSamusLaying(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 3)
    {
        pOam->timer = 0;
        
        if (pOam->yPosition < 96)
            pOam->yPosition++;
    }

    gBg2XPosition = 0;
    gBg2YPosition = pOam->yPosition;

    pOam->unk_A++;
    if (pOam->unk_A == 4)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
        {
            gWrittenToBldalpha_Eva++;
            gWrittenToBldalpha_Evb--;
        }
    }
}

 /**
 * @brief 8e89c | 6c | Fades in the intro Metroid vaccine closeup screen
 * 
 */
void NewFileIntroProcessSamusFoundFadeInVaccineCloseUp(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 4)
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
            pOam->xPosition++;
    }

    gBg3XPosition = pOam->xPosition;
    gBg3YPosition = 0;

    pOam->unk_A++;
    if (pOam->unk_A == 5)
    {
        pOam->unk_A = 0;

        if (gWrittenToBldalpha_Eva)
        {
            gWrittenToBldalpha_Eva--;
            gWrittenToBldalpha_Evb++;
        }
    }
}

 /**
 * @brief 8e908 | 3c | Handles the downward scrolling of the intro Varia suit removal surgery screen
 * 
 */
void NewFileIntroProcessSamusFoundScreenScrolling(struct SpecialCutsceneOam* pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);
    if (pOam->timer == 3)
    {
        pOam->timer = 0;
        
        if (pOam->yPosition < 96)
            pOam->yPosition++;
    }

    gBg2XPosition = 0;
    gBg2YPosition = pOam->yPosition;
}

 /**
 * @brief 8e944 | 1bc | Spawns an OAM for a new file intro Samus found cutscene
 * 
 */
u8 NewFileIntroSamusFoundSetupOam(IntroSamusFoundOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeIn;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX)
    {
        INTRO_DATA.oam[slot].unk_A = 0;
        INTRO_DATA.oam[slot].unk_8 = 0;
        INTRO_DATA.oam[slot].unk_4 = 8;
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusLayingLoading;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_LAYING)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeInSamusLaying;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_LOAD_GFX_2)
    {
        INTRO_DATA.oam[slot].unk_A = 8;
        INTRO_DATA.oam[slot].unk_8 = 8;
        INTRO_DATA.oam[slot].unk_4 = 5;
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusLayingLoading;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_FADE_IN_VACCINE)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundFadeInVaccineCloseUp;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_SCREEN_SCROLLING)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusFoundScreenScrolling;
    }
    else if (type == INTRO_SAMUS_FOUND_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }

    return slot;
}

 /**
 * @brief 8eb00 | 7c | V-blank for the intro Samus found cutscene
 * 
 */
void NewFileIntroSamusFoundVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
}

 /**
 * @brief 8eb7c | 4 | Empty function
 * 
 */
void NewFileIntroSamusFound_Empty(void)
{
    return;
}

 /**
 * @brief 8eb80 | 250 | Setup for the intro Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredInit(void)
{
    const u16* pText2;
    
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    pText2 = INTRO_DATA.pText2;

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    INTRO_DATA.pText2 = pText2;

    LZ77UncompVram(sIntroApproachingBslObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroApproachingBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(sNextPageArrowGfx, VRAM_OBJ + 0x7FE0, 8);
    DMA3_COPY_32(sNextPageArrowPal, PALRAM_OBJ + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroSamusRebornBgTopGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusRebornBgBottomGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroSamusRebornBgTopTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusRebornBgBottomTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroSamusRebornBgPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));
    DMA3_COPY_32(&sIntroSamusFoundPal[15 * PAL_ROW], PALRAM_BASE + 15 * PAL_ROW_SIZE, PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompWram(sIntroSamusMonologueBgTilemap, EWRAM_BASE);
    LZ77UncompWram(sIntroSamusMonologueBgGfx, EWRAM_BASE + 0x1000);

    WRITE_16(REG_BG0HOFS, -8);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(2, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);

    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 256;

    NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_NEXT_PAGE_ARROW, 260, 0);
    NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_SCROLLER, 0, 0);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroSamusCuredVblank);
}

 /**
 * @brief 8edd0 | 428 | Processes the Samus cured cutscene
 * 
 */
boolu32 NewFileIntroSamusCuredProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;
    
    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);
    
    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (gWrittenToBldy)
            {
                gWrittenToBldy--;
            }
            else
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 1;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 1:
            if (INTRO_DATA.timer == CONVERT_SECONDS(4 + 2.f / 3))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = INTRO_DATA.pText2;
                INTRO_DATA.subStage = 3;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 3:
	        INTRO_DATA.timer = 0;
	
	        if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
	        {
	            INTRO_DATA.unk_218 = 0;
	        }
	        else if (INTRO_DATA.unk_218 == 3)
	        {
	            INTRO_DATA.unk_218 = 0;
	            INTRO_DATA.subStage = 4;
	        }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 4:
            if (INTRO_DATA.timer == ONE_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));
                INTRO_DATA.subStage = 5;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

	    case 5:
	        INTRO_DATA.unk_213++;
	        if (INTRO_DATA.unk_213 < 6)
	        {
	            DMA3_COPY_32(EWRAM_BASE + INTRO_DATA.unk_213 * 0x1000, VRAM_BASE + 0x7000 + INTRO_DATA.unk_213 * 0x1000, 0x1000 / sizeof(u32));
	        }
	        else if (INTRO_DATA.unk_213 == 6)
	        {
	            DMA3_COPY_32(sPalPointers_79c354[0], PALRAM_BASE, 2 * PAL_ROW);
	            DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0xF000, 0x800 / sizeof(u32));
	            gWrittenToBldalpha_Eva = 0;
	            gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;
	            gBg2YPosition = 0;
	        }
	        else
	        {
	            INTRO_DATA.unk_213 = 10;
	        }
	
	        if (INTRO_DATA.timer == DELTA_TIME)
	        {
	            INTRO_DATA.timer = 0;
	
	            if (INTRO_DATA.unk_111 < 15)
	            {
	                INTRO_DATA.unk_111++;
	                INTRO_DATA.unk_110 = 1;
	            }
	            else
	            {
	                WRITE_16(REG_BLDCNT, BLDCNT_BG2_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT 
	                         | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
	                INTRO_DATA.unk_213 = 0;
	                INTRO_DATA.subStage = 6;
	            }
	        }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
	    case 6:
	        if (INTRO_DATA.timer == CONVERT_SECONDS(1 + 1.f / 6))
            {
	            WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG2);
	            INTRO_DATA.timer = 0;
	            INTRO_DATA.subStage = 7;
	        }

	        SpecialCutsceneProcessOam();
	        SpecialCutsceneDrawAllOam();
	        break;
        
	    case 7:
	        INTRO_DATA.unk_213++;
	        if (INTRO_DATA.unk_213 == 8)
	        {
	            INTRO_DATA.unk_213 = 0;
	
	            if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
	            {
	                gWrittenToBldalpha_Eva++;
	                gWrittenToBldalpha_Evb--;
	            }
	            else
	            {
	                INTRO_DATA.timer = 0;
	                INTRO_DATA.subStage = 8;
	            }
	        }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 8:
            if (INTRO_DATA.timer == CONVERT_SECONDS(2.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (INTRO_DATA.unk_12D < 15)
                {
                    INTRO_DATA.unk_12D++;
                    INTRO_DATA.unk_12C = 1;
                }
                else
                {
                    gWrittenToBldy = 0;
                    INTRO_DATA.subStage = 9;
                }
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 9:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_SCREEN_FIRST_TARGET);
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][17];
                INTRO_DATA.subStage = 10;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 10:
            INTRO_DATA.timer = 0;

            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
	        {
	            INTRO_DATA.unk_218 = 0;
	        }
	        else if (INTRO_DATA.unk_218 == 3)
	        {
	            INTRO_DATA.unk_218 = 0;
	            INTRO_DATA.subStage = 11;
	        }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 11:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                NewFileIntroSamusCuredSetupOam(INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_GLARE, SCREEN_X_MIDDLE, 64);
            }
            else if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = BLDY_MAX_VALUE;
                INTRO_DATA.subStage = 12;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
        
        case 12:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
                gWrittenToBldy++;
            else
                finished = TRUE;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }

    IntroProcessText();

    return finished;
}

 /**
 * @brief 8f1f8 | 88 | Main handler for the intro Samus cured cutscene
 * 
 */
boolu32 NewFileIntroSamusCured(void)
{
    boolu32 finished;

    finished = FALSE;

    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroSamusCuredInit();
            INTRO_DATA.stage = 2;
            break;

        case 1:
            SpecialCutsceneFadeIn();

            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;

        case 2:
            if (NewFileIntroSamusCuredProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;

        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
        
    return finished;
}

 /**
 * @brief 8f280 | 104 | Processes the screen scrolling in the Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredProcessScrolling(struct SpecialCutsceneOam *pOam)
{
    APPLY_DELTA_TIME_INC(pOam->timer);

    if (pOam->stage == 0)
    {
        pOam->xPosition = gBg2XPosition;
        pOam->yPosition = gBg2YPosition;
        pOam->spawnX = gBg3XPosition;
        pOam->spawnY = gBg3YPosition;
        pOam->unk_A = 0x5000;
        pOam->timer = 0;
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        if (pOam->timer == CONVERT_SECONDS(1.f / 6))
        {
            pOam->timer = 0;
            pOam->stage = 2;
        }
    }
    else if (INTRO_DATA.subStage == 1)
    {
        if (pOam->timer == DELTA_TIME)
        {
            pOam->timer = 0;
            
            if (pOam->yPosition > -SCREEN_SIZE_Y)
            {
                pOam->yPosition--;
                pOam->unk_8++;
            }
            
            if (pOam->spawnY > 0)
                pOam->spawnY--;

            gBg2YPosition = pOam->yPosition;
            gBg3YPosition = pOam->spawnY;
        }
        
        if (pOam->unk_8 == 9)
        {
            pOam->unk_8 = 0;
            
            if (pOam->unk_A)
            {
                pOam->unk_A -= 0x400;
                DMA3_FILL_32(0, VRAM_BASE + 0x8000 + pOam->unk_A, 0x400);
            }
        }
    }
    else
    {
        pOam->timer = 0;
    }
}

 /**
 * @brief 8f384 | 140 | Spawns an OAM for the intro Samus cured cutscene
 * 
 */
u8 NewFileIntroSamusCuredSetupOam(IntroSamusCuredOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);

    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_SCROLLER)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusCuredProcessScrolling;
    }
    else if (type == INTRO_SAMUS_CURED_OAM_TYPE_SCREEN_GLARE)
    {
        SoundPlay(SOUND_12D);
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusCuredScreenGlareOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroSamusCuredProcessOam_Empty;
    }
    else if (type == INTRO_SAMUS_CURED_OAM_TYPE_NEXT_PAGE_ARROW)
    {
        INTRO_DATA.oam[slot].pOam = sIntroNextPageArrowOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessTextCursor;
    }

    return slot;
}

 /**
 * @brief 8f4c4 | fc | V-blank for the Samus cured cutscene
 * 
 */
void NewFileIntroSamusCuredVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);

    if (INTRO_DATA.unk_110 == 1)
    {
        INTRO_DATA.unk_110 = 0;
        DMA3_COPY_32(sPalPointers_79c314[INTRO_DATA.unk_111], PALRAM_BASE + 5 * PAL_ROW_SIZE, 10 * PAL_ROW_SIZE / sizeof(u32));
    }

    if (INTRO_DATA.unk_12C == 1)
    {
        INTRO_DATA.unk_12C = 0;
        DMA3_COPY_32(sPalPointers_79c354[INTRO_DATA.unk_12D], PALRAM_BASE, 4 * PAL_ROW_SIZE / sizeof(u32));
    }
}

 /**
 * @brief 8f5c0 | 4 | Intro Samus cured OAM handler (empty)
 * 
 */
void NewFileIntroSamusCuredProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief 8f5c4 | 230 | Setup for the arriving at BSL cutscene
 * 
 */
void NewFileIntroArrivingAtBslInit(void)
{
    WRITE_16(REG_IME, FALSE);
    WRITE_16(REG_DISPSTAT, READ_16(REG_DISPSTAT) & ~DSTAT_IF_HBLANK);
    WRITE_16(REG_IE, READ_16(REG_IE) & ~IF_HBLANK);
    WRITE_16(REG_IME, TRUE);

    CallbackSetVBlank(unk_99940);

    DMA3_FILL_32(0, &gNonGameplayRam, sizeof(gNonGameplayRam));

    LZ77UncompVram(sIntroApproachingBslObjGfx, VRAM_OBJ);

    DMA3_COPY_32(sIntroApproachingBslObjPal, PALRAM_OBJ, 16 * PAL_ROW_SIZE / sizeof(u32));

    LZ77UncompVram(sIntroArrivingAtBslSpaceMapBgGfx, VRAM_BASE);
    LZ77UncompVram(sIntroSamusMonologueBgGfx, VRAM_BASE + 0x8000);
    LZ77UncompVram(sIntroArrivingAtBslSpaceMapTilemap, VRAM_BASE + 0xF000);
    LZ77UncompVram(sIntroSamusMonologueBgTilemap, VRAM_BASE + 0xF800);
    LZ77UncompVram(sIntroSamusShipFlyingTextTilemap, VRAM_BASE + 0xE000);

    DMA3_COPY_32(sIntroArrivingAtBslSpaceMapPal, PALRAM_BASE, 16 * PAL_ROW_SIZE / sizeof(u32));

    SET_BACKDROP_COLOR(COLOR_BLACK);

    LZ77UncompWram(sIntroTilemap_662804, EWRAM_BASE);
    LZ77UncompWram(sIntroFlyingToBslObjGfx, EWRAM_BASE + 0x1000);
    LZ77UncompWram(sIntroFlyingToBslBgGfx, EWRAM_BASE + 0x9000);

    WRITE_16(REG_BG0HOFS, 0);
    WRITE_16(REG_BG0VOFS, 0);
    WRITE_16(REG_BG1HOFS, 0);
    WRITE_16(REG_BG1VOFS, 0);
    WRITE_16(REG_BG2HOFS, 0);
    WRITE_16(REG_BG2VOFS, 0);
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    gBg0XPosition = -8;
    gBg0YPosition = 8;
    gBg2XPosition = 0;
    gBg2YPosition = 0;
    gBg3XPosition = 0;
    gBg3YPosition = 0;

    WRITE_16(REG_BG0CNT, CREATE_BGCNT(2, 28, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BG3CNT, CREATE_BGCNT(2, 31, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
    WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);

    gWrittenToBldy = BLDY_MAX_VALUE;
    WRITE_16(REG_BLDY, BLDY_MAX_VALUE);
    gWrittenToBldalpha_Eva = 0;
    gWrittenToBldalpha_Evb = BLDALPHA_MAX_VALUE;

    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY, 112, 80);
    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP, 112, 80);

    SpecialCutsceneProcessOam();
    SpecialCutsceneDrawAllOam();

    INTRO_DATA.pText = sCutsceneTextNone;

    DMA3_FILL_32(0, VRAM_BASE + 0xD000, (VRAM_SIZE / 6) / sizeof(u32));

    WRITE_16(REG_DISPCNT, DCNT_BG0 | DCNT_BG2 | DCNT_OBJ);

    CallbackSetVBlank(NewFileIntroArrivingAtBslVblank);
}

 /**
 * @brief 8f7f4 | 750 | Processes the arriving at BSL cutscene
 * 
 */
boolu32 NewFileIntroArrivingAtBslProcess(void)
{
    boolu32 finished;

    finished = FALSE;
    
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW && gChangedInput & KEY_A && INTRO_DATA.unk_218 == 0)
        INTRO_DATA.unk_218 = 1;

    APPLY_DELTA_TIME_INC(INTRO_DATA.timer);

    switch (INTRO_DATA.subStage)
    {
        case 0:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.subStage = 2;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 1:
            if (INTRO_DATA.timer == CONVERT_SECONDS(.05f))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb > 8)
                    gWrittenToBldalpha_Evb--;
                
                if (gWrittenToBldalpha_Eva < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Eva += 2;
                else
                    INTRO_DATA.subStage = 2;
                
                if (gWrittenToBldalpha_Eva == 8)
                {
                    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY, 112, 80);
                    NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP, 112, 80);
                }
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 2:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL_POPUP, 198, 36);
            }
            else if (INTRO_DATA.timer == TWO_THIRD_SECOND)
            {
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_UNK_255, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_TEXT_CURSOR, 20, 192);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_FRAME, 128, 192);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_BACKGROUND, 128, 192);
                INTRO_DATA.subStage = 3;
                INTRO_DATA.timer = 0;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            NewFileIntroProcessAdamText();
            break;

        case 3:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
                SoundPlay(SOUND_203);
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~ DCNT_BG0);
                INTRO_DATA.unk_218 = 0;
                SoundPlay(SOUND_203);
                INTRO_DATA.subStage = 4;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            NewFileIntroProcessAdamText();
            break;

        case 4:
            INTRO_DATA.timer = 0;
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 5:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                ApplyMusicSoundFading(sMusicTrackDataRom[sSoundDataEntries[580].trackGroupNumber].pTrack, 0);
            }
            else if (INTRO_DATA.timer > CONVERT_SECONDS(.5f))
            {
                if (gWrittenToBldy < BLDY_MAX_VALUE)
                {
                    gWrittenToBldy++;
                }
                else
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG2);
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                    DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                    INTRO_DATA.timer = 0;
                    INTRO_DATA.subStage = 6;
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 6:
            INTRO_DATA.timer = 0;
            
            if (gWrittenToBldy)
                gWrittenToBldy--;
            else
                INTRO_DATA.subStage = 7;
            break;

        case 7:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                DMA3_FILL_32(0, VRAM_BASE, 0x4800);
            }
            else if (INTRO_DATA.timer == 2 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE, VRAM_BASE + 0x4800, 0x800 / sizeof(u32));
                DMA3_COPY_32(sIntroPal_663820, PALRAM_BASE + 12 * PAL_ROW_SIZE, 4 * PAL_ROW_SIZE / sizeof(u32));
                gBg0XPosition = 0;
                gBg0YPosition = 4;
            }
            else if (INTRO_DATA.timer == 3 * DELTA_TIME)
            {
                WRITE_16(REG_BG0CNT, CREATE_BGCNT(0, 9, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG0);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1))
            {
                INTRO_DATA.timer = 0;
                INTRO_DATA.unk_12 = 0;
                INTRO_DATA.unk_10 = 0;
                INTRO_DATA.unk_E = 0;
                INTRO_DATA.unk_C = 0;
                INTRO_DATA.unk_212 = 0;
                INTRO_DATA.pText = sMonologueTextPointers[gLanguage][0];
                INTRO_DATA.subStage = 8;
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_MONOLOGUE_CURSOR, 260, 0);
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 8:
            INTRO_DATA.timer = 0;
            
            if (INTRO_DATA.unk_218 == 2 || INTRO_DATA.unk_218 == 4)
            {
                INTRO_DATA.unk_218 = 0;
            }
            else if (INTRO_DATA.unk_218 == 3)
            {
                INTRO_DATA.unk_218 = 0;
                INTRO_DATA.subStage = 9;
            }
            
            if (NewFileIntroCheckMonologueEnded())
            {
                INTRO_DATA.subStage = 9;
                INTRO_DATA.unk_218 = 0;
            }
            
            if (INTRO_DATA.unk_213 == 0)
            {
                INTRO_DATA.unk_213 = 100;
            }
            else if (INTRO_DATA.unk_213 == 1)
            {
                INTRO_DATA.unk_213 = 100;
                SpecialCutsceneProcessMonologue();
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 9:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                gWrittenToBldalpha_Evb = 0;
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                FadeMusic(256);
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 6))
            {
                INTRO_DATA.timer = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_BG0_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG3_SECOND_TARGET_PIXEL);
                INTRO_DATA.subStage = 10;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 10:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;
                
                if (gWrittenToBldalpha_Eva)
                    gWrittenToBldalpha_Eva--;
                
                if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE && !gWrittenToBldalpha_Eva)
                {
                    WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG0);
                    INTRO_DATA.subStage = 11;
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 11:
            if (INTRO_DATA.timer == DELTA_TIME)
            {
                DMA3_FILL_32(0, &INTRO_DATA.oam, sizeof(INTRO_DATA.oam));
                gWrittenToBldalpha_Eva = BLDALPHA_MAX_VALUE;
                gWrittenToBldalpha_Evb = 0;
            }
            else if (INTRO_DATA.timer < 6 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE - 0x3000 + INTRO_DATA.timer * 0x2000, VRAM_BASE + 0xC000 + INTRO_DATA.timer * 0x2000, 0x2000 / sizeof(u32));
            }
            else if (INTRO_DATA.timer < 10 * DELTA_TIME)
            {
                DMA3_COPY_32(EWRAM_BASE - 0x3000 + INTRO_DATA.timer * 0x2000, VRAM_BASE - 0xC000 + INTRO_DATA.timer * 0x2000, 0x2000 / sizeof(u32));
            }
            else if (INTRO_DATA.timer == 10 * DELTA_TIME)
            {
                LZ77UncompVram(sIntroTilemap_5f65d8, VRAM_BASE + 0xE800);
            }
            else if (INTRO_DATA.timer == 11 * DELTA_TIME)
            {
                LZ77UncompVram(sIntroTilemap_5f5454, VRAM_BASE + 0xF000);
                WRITE_16(REG_BG1CNT, CREATE_BGCNT(2, 31, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG1);
            }
            else if (INTRO_DATA.timer == 12 * DELTA_TIME)
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG3);
                WRITE_16(REG_BG2CNT, CREATE_BGCNT(0, 29, BGCNT_LOW_MID_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_BG3CNT, CREATE_BGCNT(0, 30, BGCNT_LOW_PRIORITY, BGCNT_SIZE_256x256));
                WRITE_16(REG_BLDCNT, BLDCNT_BG1_FIRST_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_SECOND_TARGET_PIXEL 
                        | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_OBJ_SECOND_TARGET_PIXEL);
                DMA3_COPY_32(sPal_5f4ed4, PALRAM_BASE + 4 * PAL_ROW_SIZE, 12 * PAL_ROW_SIZE / sizeof(u32));
                gBg2XPosition = 0;
                gBg2YPosition = 0;
                gBg3XPosition = 0;
                gBg3YPosition = 0;
            }
            else if (INTRO_DATA.timer == CONVERT_SECONDS(.5f))
            {
                WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) | DCNT_BG3);
                INTRO_DATA.timer = 0;
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_UNK_255, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_1, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3, 208, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP, 196, 100);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, 6, 78);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG3_SCROLLER, 0, 0);
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG2_SCROLLER, 0, 0);
                SoundPlay_3b1c(SOUND_245);
                INTRO_DATA.subStage = 12;
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 12:
            if (INTRO_DATA.timer == CONVERT_SECONDS(1.f / 15))
            {
                INTRO_DATA.timer = 0;
                
                if (gWrittenToBldalpha_Evb < BLDALPHA_MAX_VALUE)
                    gWrittenToBldalpha_Evb++;
                
                if (gWrittenToBldalpha_Eva)
                    gWrittenToBldalpha_Eva--;

                if (gWrittenToBldalpha_Evb == BLDALPHA_MAX_VALUE)
                {
                    if (!gWrittenToBldalpha_Eva)
                    {
                        WRITE_16(REG_DISPCNT, READ_16(REG_DISPCNT) & ~DCNT_BG1);
                        INTRO_DATA.subStage = 13;
                    }
                }
            }
            
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 13:
            INTRO_DATA.timer = 0;

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;

        case 14:
            if (INTRO_DATA.timer == CONVERT_SECONDS(4.f / 3))
            {
                INTRO_DATA.timer = 0;
                gWrittenToBldy = 0;
                WRITE_16(REG_BLDCNT, BLDCNT_SCREEN_FIRST_TARGET | BLDCNT_BRIGHTNESS_DECREASE_EFFECT);
                finished = TRUE;
            }

            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    return finished;
}

 /**
 * @brief 8ff44 | 90 | Main handler of the arriving at BSL cutscene
 * 
 */
boolu32 NewFileIntroArrivingAtBsl(void)
{
    boolu32 finished;

    finished = FALSE;
    
    switch (INTRO_DATA.stage)
    {
        case 0:
            NewFileIntroArrivingAtBslInit();
            INTRO_DATA.stage = 1;
            break;
        
        case 1:
            gWrittenToBldy = 0;
            SoundPlay(SOUND_244);
            
            if (!gWrittenToBldy)
                INTRO_DATA.stage = 2;
            break;
        
        case 2:
            if (NewFileIntroArrivingAtBslProcess())
            {
                INTRO_DATA.subStage = 0;
                INTRO_DATA.unk_213 = 0;
                INTRO_DATA.stage = 3;
            }
            break;
        
        case 3:
            if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy++;
            }
            else
            {
                INTRO_DATA.stage = 0;
                finished = TRUE;
            }
        
            SpecialCutsceneProcessOam();
            SpecialCutsceneDrawAllOam();
            break;
    }
    
    return finished;
}

 /**
 * @brief 8ffd4 | 270 | Processes Samus' ship in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBsl(struct SpecialCutsceneOam *pOam)
{
    const struct FrameData* frame;
    s16 x;
    s16 y;

    pOam->unk_A++;
    
    if (pOam->stage == 0)
    {
        pOam->spawnX = pOam->xPosition;
        pOam->spawnY = pOam->yPosition;
        
        if (pOam->unk_A == 20)
        {
            pOam->unk_A = 0;
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->timer++;
        if (pOam->timer == CONVERT_SECONDS(1.f / 30))
        {
            pOam->timer = 0;
            pOam->scaling--;
        }

        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 3);
        
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->spawnX = pOam->spawnX - (pOam->unk_A >> 3);
            pOam->spawnY = pOam->yPosition;
            pOam->timer = 0;
            pOam->unk_A = 0;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (pOam->unk_A == 2)
        {
            NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_EXPLOSION, pOam->xPosition, pOam->yPosition);
            pOam->rotation -= 1;
        }
        else if (pOam->unk_A == 4)
        {
            pOam->unk_A = 0;
            pOam->stage = 3;
            pOam->rotation -= 1;
        }
        
        pOam->scaling--;
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 3)
    {
        pOam->scaling -= 2;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if (pOam->rotation > Q_8_8(15.f / 16))
            pOam->rotation--;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 1);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 1);

        if (pOam->unk_A == 10)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 4;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 4)
    {
        pOam->scaling -= 4;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if (pOam->rotation > Q_8_8(15.f / 16))
            pOam->rotation--;
        
        pOam->yPosition = pOam->spawnY - pOam->unk_A;
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 2);
        
        if (x - pOam->xPosition > -20)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 5;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 5)
    {
        pOam->scaling -= 2;
        
        NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL, &x, &y);
        
        if ((u8)(pOam->rotation - Q_8_8(.04f)) > Q_8_8(.745f))
            pOam->rotation++;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 1);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A << 1);
        
        if (x - pOam->xPosition > 10)
        {
            pOam->unk_A = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 6;
        }
        
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 6)
    {
        pOam->scaling--;

        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->xPosition = pOam->spawnX - (pOam->unk_A >> 1);
    
        if ((u8)(pOam->rotation - Q_8_8(.04f)) > Q_8_8(.745f))
        {
            pOam->rotation++;
        }
        else
        {
            pOam->unk_A = 0;
            pOam->timer = 0;
            pOam->spawnX = pOam->xPosition;
            pOam->spawnY = pOam->yPosition;
            pOam->stage = 7;
        }
    
        pOam->animationDurationCounter = 0;
    }
    else if (pOam->stage == 7)
    {
        if ((u8)(pOam->rotation - Q_8_8(1.f / 16)) > Q_8_8(.72f))
        {
            pOam->timer++;
            if (pOam->timer == CONVERT_SECONDS(.05f))
            {
                pOam->timer = 0;
                pOam->rotation++;
            }
        }
        
        pOam->yPosition = pOam->spawnY - (pOam->unk_A >> 2);
        pOam->xPosition = (pOam->unk_A >> 1) + pOam->spawnX;
        
        pOam->scaling -= 2;
        if (pOam->scaling < Q_8_8(1.f / 8))
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
            INTRO_DATA.subStage = 14;
        }
        
        pOam->animationDurationCounter = 0;
    }
    
    if (pOam->scaling <= Q_8_8(1))
        pOam->affineMode = 1;
}

 /**
 * @brief 90244 | 20 | Processes the BSL in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessBslPreview(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == CONVERT_SECONDS(1.f / 10))
    {
        pOam->timer = 0;
        pOam->xPosition++;
    }
}

 /**
 * @brief 90264 | 1ac | Processes the ship's thrusters in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBslThrusters(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    u8 slot;
    s16 x;
    s16 y;

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->currentAnimationFrame = 0;
        pOam->animationDurationCounter = 0;
    }

    pOam->timer++;
    if (pOam->timer == 4)
    {
        pOam->timer = 0;

        switch (pOam->type)
        {
            case 3:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->unk_18_0 = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;
                pOam->xPosition = x;
                pOam->yPosition = y;
                break;

            case 4:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->unk_18_0 = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;
                pOam->xPosition = x;
                pOam->yPosition = y;
                break;

            case 5:
                slot = NewFileIntroGetPositionAndSlotOfOamByType(INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP, &x, &y);
                if (slot == ARRAY_SIZE(INTRO_DATA.oam))
                {
                    pOam->type = 0;
                    pOam->unk_18_0 = 0;
                    break;
                }

                pOam->scaling = INTRO_DATA.oam[slot].scaling;
                pOam->affineMode = INTRO_DATA.oam[slot].affineMode;

                if (INTRO_DATA.oam[slot].stage < 2)
                {
                    pOam->yPosition = y;

                    switch (INTRO_DATA.oam[slot].currentAnimationFrame)
                    {
                        case 0:
                            pOam->xPosition = x + 12;
                            break;
                
                        case 1:
                            pOam->xPosition = x + 10;
                            break;
                
                        case 2:
                            pOam->xPosition = x + 8;
                            break;
                
                        case 3:
                            pOam->xPosition = x + 6;
                            break;
                
                        case 4:
                            pOam->xPosition = x + 5;
                            break;
                
                        case 5:
                            pOam->xPosition = x + 4;
                            break;
                
                        case 6:
                            pOam->xPosition = x + 3;
                            break;
                
                        case 7:
                            pOam->xPosition = x + 2;
                            break;
                
                        case 8:
                            pOam->xPosition = x + 1;
                            break;

                        default:
                            pOam->xPosition = x;
                            break;
                    }
                }
                else
                {
                    pOam->yPosition = y;
                    pOam->xPosition = x;
                }
                break;
        }
    }
}

 /**
 * @brief 90410 | 2c | Processes the ship's thrusters flaring up in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusShipArrivingAtBslThrusterExplosion(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;
    
    frame = &pOam->pOam[pOam->currentAnimationFrame];
    if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
    {
        pOam->type = 0;
        pOam->unk_18_0 = 0;
    }
}

 /**
 * @brief 9043c | 8 | To document
 * 
 */
void unk_9043c(struct SpecialCutsceneOam* pOam)
{
    pOam->type = 0;
}

 /**
 * @brief 90444 | 34 | Processes the background scrolling in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusArrivingAtBslBg3Scrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == TWO_THIRD_SECOND)
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
        {
            pOam->xPosition++;
            gBg3XPosition++;
        }
    }
}

 /**
 * @brief 90478 | 34 | Processes the BG2 scrolling in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessSamusArrivingAtBslBg2Scrolling(struct SpecialCutsceneOam* pOam)
{
    pOam->timer++;
    if (pOam->timer == CONVERT_SECONDS(.5f))
    {
        pOam->timer = 0;
        
        if (pOam->xPosition < 16)
        {
            pOam->xPosition++;
            gBg2XPosition--;
        }
    }
}

 /**
 * @brief 904ac | 19c | Processes the Adam panel in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamPanel(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    if (pOam->stage == 0)
    {
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
            
        if (pOam->yPosition > 128)
        {
            pOam->yPosition -= 8;
            return;
        }
            
        pOam->yPosition = 128;
            
        if (pOam->type == 20)
            SoundPlay(SOUND_20A);
            
        pOam->stage = 1;
    }
    else if (pOam->stage == 1)
    {
        frame = &pOam->pOam[pOam->currentAnimationFrame];
        if (frame[0].timer == pOam->animationDurationCounter)
        {
            if (frame[1].timer == 0)
            {
                pOam->animationDurationCounter = 0;
                pOam->stage = 2;
            }
            
            if (pOam->type != 20)
                return;

            if (pOam->currentAnimationFrame == 10)
                NewFileIntroArrivingAtBslSetupOam(INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_LENS, pOam->xPosition, pOam->yPosition);
        }
        
        if (pOam->type == 20)
        {
            if (pOam->currentAnimationFrame == 11)
            {
                if (pOam->animationDurationCounter == 15)
                {
                    INTRO_DATA.unk_212 = 0;
                    INTRO_DATA.unk_E = 0;
                    INTRO_DATA.unk_C = 0;
                    INTRO_DATA.pText = sMonologueTextPointers[gLanguage][18];
                }
            }
        }
    }
    else if (pOam->stage == 2)
    {
        pOam->animationDurationCounter = 0;
        pOam->timer++;
        if (pOam->timer == 1)
        {
            pOam->timer = 0;
            pOam->stage = 3;
        }
    }
    else if (pOam->stage == 3)
    {
        pOam->animationDurationCounter = 0;
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->currentAnimationFrame = 0;
            
            if (pOam->type == 20)
            {
                pOam->pOam = sIntroArrivingAtBslAdamPanelFrameOam_Closing;
                SoundPlay(SOUND_20B);
            }
            else if (pOam->type == 21)
            {
                pOam->pOam = sIntroArrivingAtBslAdamPanelBackgroundOam_Closing;
            }

            pOam->stage = 4;
        }
    }
    else if (pOam->stage == 4)
    {
        if (pOam->currentAnimationFrame == 11 && pOam->animationDurationCounter == 3)
        {
            if (pOam->type == 20)
                SpecialCutsceneDestroyOamOfType(22);
            
            pOam->animationDurationCounter = 0;
            pOam->stage = 5;
        }
    }
    else if (pOam->stage == 5)
    {
        pOam->animationDurationCounter = 0;
        
        if (pOam->yPosition < 192)
        {
            pOam->yPosition += 8;
        }
        else
        {
            if (pOam->type == 20)
                INTRO_DATA.subStage = 5;

            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 90648 | 88 | Processes Adam's lens in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamLens(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];

    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 3)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Glowing;
            pOam->stage = 1;
        }
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 1)
    {
        if (INTRO_DATA.subStage == 4)
        {
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamLensOam_Closing;
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
            pOam->animationDurationCounter = 0;
    }
}

 /**
 * @brief 906d0 | 8c | Processes the Adam text cursor in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessAdamTextCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_TERMINATOR)
    {
        pOam->xPosition = 290;
    }
    else if (*INTRO_DATA.pText != CHAR_NEW_LINE)
    {
        if (*INTRO_DATA.pText == CHAR_NEW_PAGE)
        {
            pOam->xPosition = 290;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslAdamTextCursorOam;
        }
        else if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
        {
            pOam->xPosition = SCREEN_X_MIDDLE;
            pOam->yPosition = 154;
            pOam->pOam = sIntroArrivingAtBslMonologueCursorOam;
        }
        else
        {
            pOam->xPosition = INTRO_DATA.unk_C * 8 + INTRO_DATA.unk_212 + 14;
            pOam->yPosition = INTRO_DATA.unk_E * 8 + 132;
            pOam->animationDurationCounter = 0;
            pOam->currentAnimationFrame = 0;
        }
    }
    else
    {
        pOam->xPosition = INTRO_DATA.unk_C * 8 + INTRO_DATA.unk_212 + 14;
        pOam->yPosition = INTRO_DATA.unk_E * 8 + 132;
        pOam->animationDurationCounter = 0;
        pOam->currentAnimationFrame = 0;
    }
}

 /**
 * @brief 9075c | 9c | Processes the BSL preview popup in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessBslPopUp(struct SpecialCutsceneOam* pOam)
{
    const struct FrameData* frame;

    frame = &pOam->pOam[pOam->currentAnimationFrame];
    
    if (pOam->stage == 0)
    {
        if (pOam->currentAnimationFrame == 1 && pOam->animationDurationCounter == 1)
            SoundPlay(SOUND_11C);

        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->animationDurationCounter = 0;
            pOam->stage = 1;
        }
    }
    else if (pOam->stage == 1)
    {
        pOam->animationDurationCounter = 0;
        
        if (INTRO_DATA.subStage == 4)
        {
            pOam->currentAnimationFrame = 0;
            pOam->pOam = sIntroArrivingAtBslBslPopupOam_Closing;
            SoundPlay(SOUND_11D);
            pOam->stage = 2;
        }
    }
    else if (pOam->stage == 2)
    {
        if (frame[0].timer == pOam->animationDurationCounter && frame[1].timer == 0)
        {
            pOam->type = 0;
            pOam->unk_18_0 = 0;
        }
    }
}

 /**
 * @brief 907f8 | 30 | Processes the monologue cursor in the arriving at BSL cutscene
 * 
 */
void NewFileIntroProcessMonologueCursor(struct SpecialCutsceneOam* pOam)
{
    if (*INTRO_DATA.pText == CHAR_NEXT_PAGE_ARROW)
    {
        pOam->xPosition = 118;
        pOam->yPosition = INTRO_DATA.unk_E * 8 + 24;
    }
    else
    {
        pOam->xPosition = 260;
    }
}

 /**
 * @brief 90828 | 438 | Spawns an OAM for the intro arriving at BSL cutscene
 * 
 */
u8 NewFileIntroArrivingAtBslSetupOam(IntroArrivingAtBslOamType type, s16 xPosition, s16 yPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == 0)
            break;
    }

    if (slot >= ARRAY_SIZE(INTRO_DATA.oam))
        return ARRAY_SIZE(INTRO_DATA.oam);
    
    DMA3_FILL_32(0, &INTRO_DATA.oam[slot], sizeof(struct SpecialCutsceneOam));

    INTRO_DATA.oam[slot].xPosition = xPosition;
    INTRO_DATA.oam[slot].yPosition = yPosition;
    INTRO_DATA.oam[slot].type = type;
    INTRO_DATA.oam[slot].unk_18_0 = 1;

    if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].affineMode = 3;
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslSamusShipOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBsl;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslBslOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslPreview;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_1)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = 3;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_2)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = 3;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_3)
    {
        INTRO_DATA.oam[slot].scaling = Q_8_8(1.5f);
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].affineMode = 3;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrustersOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusters;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_THRUSTER_EXPLOSION)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslThrusterExplosionOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusShipArrivingAtBslThrusterExplosion;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG3_SCROLLER)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusArrivingAtBslBg3Scrolling;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BG2_SCROLLER)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessSamusArrivingAtBslBg2Scrolling;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_FRAME)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamPanelFrameOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamPanel;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_PANEL_BACKGROUND)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamPanelBackgroundOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamPanel;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_LENS)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamLensOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamLens;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_ADAM_TEXT_CURSOR)
    {
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslAdamTextCursorOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessAdamTextCursor;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SHIP_TRAJECTORY)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslShipTrajectoryOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_PLANETS_AND_SHIP)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslPlanetsAndShipOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_BSL_POPUP)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslBslPopupOam_Opening;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessBslPopUp;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_SCREEN_GLARE)
    {
        INTRO_DATA.oam[slot].priority = 2;
        INTRO_DATA.oam[slot].pOam = sIntroSamusCuredScreenGlareOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroArrivingAtBslProcessOam_Empty;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_MONOLOGUE_CURSOR)
    {
        INTRO_DATA.oam[slot].priority = 1;
        INTRO_DATA.oam[slot].pOam = sIntroArrivingAtBslMonologueCursorOam;
        INTRO_DATA.oam[slot].pFunction = NewFileIntroProcessMonologueCursor;
    }
    else if (type == INTRO_ARRIVING_AT_BSL_OAM_TYPE_UNK_255)
    {
        INTRO_DATA.oam[slot].unk_18_0 = 0;
        INTRO_DATA.oam[slot].pFunction = unk_9043c;
    }

    return slot;
}

 /**
 * @brief 90c60 | 9c | V-blank for the arriving at BSL cutscene
 * 
 */
void NewFileIntroArrivingAtBslVblank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));
    
    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_BG0HOFS, gBg0XPosition);
    WRITE_16(REG_BG0VOFS, gBg0YPosition);
    WRITE_16(REG_BG2HOFS, gBg2XPosition);
    WRITE_16(REG_BG2VOFS, gBg2YPosition);
    WRITE_16(REG_BG3HOFS, gBg3XPosition);
    WRITE_16(REG_BG3VOFS, gBg3YPosition);
    
    unk_98158();
}

 /**
 * @brief 90cfc | 60 | Returns slot, X and Y position of a new file intro OAM
 * 
 */
u8 NewFileIntroGetPositionAndSlotOfOamByType(IntroArrivingAtBslOamType type, s16* pXPosition, s16* pYPosition)
{
    u8 slot;

    for (slot = 0; slot < ARRAY_SIZE(INTRO_DATA.oam); slot++)
    {
        if (INTRO_DATA.oam[slot].type == type)
        {
            *pXPosition = INTRO_DATA.oam[slot].xPosition;
            *pYPosition = INTRO_DATA.oam[slot].yPosition;
        
            return slot;
        }
    }

    // Default values if not found
    *pXPosition = 300;
    *pYPosition = 200;
        
    return ARRAY_SIZE(INTRO_DATA.oam);
}

 /**
 * @brief 90d5c | 4 | Empty OAM handler function
 * 
 */
void NewFileIntroArrivingAtBslProcessOam_Empty(struct SpecialCutsceneOam* pOam)
{
    return;
}

 /**
 * @brief  |  | To document
 * 
 */

