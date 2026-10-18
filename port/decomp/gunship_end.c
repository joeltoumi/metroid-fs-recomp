#include "gunship_end.h"
#include "globals.h"
#include "macros.h"
#include "gba.h"

#include "data/sprites/gunship.h"
#include "data/samus_data.h"

#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/samus.h"
#include "structs/sprite.h"

#include "sprite.h"
#include "sprite_util.h"
#include "event_checks.h"
#include "music_wrappers.h"
#include "audio_wrappers.h"
#include "color_fading.h"

#define SSPRITE_GUNSHIP_END_BEAM 0x79
#define SSPRITE_GUNSHIP_END_BOTTOM 0x7A

/**
 * @brief 56140 | 138 | Checks which gunship (end) beam should spawn
 *
 */
void GunshipEndSpawnBeams(void)
{
    u16 yPosition;
    u16 xPosition;

    yPosition = gCurrentSprite.yPosition + 0x120;
    xPosition = gCurrentSprite.xPosition;

    switch (gCurrentSprite.work2)
    {
        case 6:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 0, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0xCC, xPosition, 0);
            SoundPlay(0xFD);
            break;

        case 9:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 1, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0xB0, xPosition, 0);
            break;

        case 12:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 3, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0x98, xPosition, 0);
            break;

        case 15:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 5, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0x80, xPosition, 0);
            break;

        case 18:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 7, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0x68, xPosition, 0);
            break;

        case 21:
            SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BEAM, 9, gCurrentSprite.spritesetGfxSlot,
                gCurrentSprite.primarySpriteRamSlot, yPosition - 0x50, xPosition, 0);
            break;
    }
}

/**
 * @brief 56278 | 8c | Initializes the gunship (end)
 *
 */
void GunshipEndInit(void)
{
    gCurrentSprite.drawOrder = 12;
    gCurrentSprite.bgPriority = 3;
    gCurrentSprite.status = (gCurrentSprite.status & ~SPRITE_STATUS_NOT_DRAWN) | SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.scaling = Q_8_8(.5625f);
    gCurrentSprite.rotation = 0;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.work3 = 0;
    gCurrentSprite.work1 = 60;
    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = 0x7F;
    gCurrentSprite.drawDistanceBottom = 0x40;
    gCurrentSprite.drawDistanceHorizontal = 0xB0;

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pose = 1;

    gCurrentSprite.pOam = sGunshipEndOam_Flying;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
}

/**
 * @brief 56304 | 34 | Handles the gunship (end) waiting
 *
 */
void GunshipEndWaiting(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 2;
        PlayMusic(0x5B, 14);
        gCurrentSprite.work1 = 30;
    }
}

/**
 * @brief 56338 | b0 | Handles the gunship (end) moving to the center of the screen
 *
 */
void GunshipEndMovingUp(void)
{
    u8 inPlace;
    u16 position;

    if (gCurrentSprite.work1 != 0)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
            SoundPlay_3b1c(0x249);
    }

    inPlace = 0;

    position = (gCurrentSprite.xPosition >> 2) - (gBg1XPosition >> 2);
    if (position < 0x70)
        gCurrentSprite.xPosition++;
    else if (position > 0x80)
        gCurrentSprite.xPosition--;
    else
        inPlace = 1;

    position = (gCurrentSprite.yPosition >> 2) - (gBg1YPosition >> 2);
    if (position < 0x2C)
        gCurrentSprite.yPosition++;
    else if (position > 0x3C)
        gCurrentSprite.yPosition--;
    else
        inPlace++;

    if (inPlace > 1)
    {
        gCurrentSprite.bgPriority = 2;
        gCurrentSprite.pose = 0x17;
        gCurrentSprite.work1 = 60;
        gCurrentSprite.work4 = 0;
        gCurrentSprite.work3 = 0;
    }
}

/**
 * @brief 563e8 | 5c | Handles the gunship (end) waiting to enter the ship
 *
 */
void GunshipEndWaitingToEnter(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndIdleYMovement[offset];
    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndIdleYMovement[0];
        offset = 0;
    }
    gCurrentSprite.work4 = offset + 1;
    gCurrentSprite.yPosition += movement;

    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x18;
        gCurrentSprite.work1 = 0;
    }
}

/**
 * @brief 56444 | 158 | Handles the gunship (end) entering the ship
 *
 */
void GunshipEndEntering(void)
{
    u8 offset;
    s16 movement;
    u16 yPosition;
    u8 timer;
    u8 slot;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndIdleYMovement[offset];
    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndIdleYMovement[0];
        offset = 0;
    }
    gCurrentSprite.work4 = offset + 1;
    yPosition = gCurrentSprite.yPosition + movement;
    gCurrentSprite.yPosition = yPosition;

    timer = gCurrentSprite.work1;
    gCurrentSprite.scaling = sGunshipEndEnteringScaling[timer >> 2];

    if (timer < 0x70)
    {
        gCurrentSprite.work1 = timer + 1;
        if ((timer + 1) & 1)
            gCurrentSprite.yPosition = yPosition + 1;
        return;
    }

    gCurrentSprite.status &= ~SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.pose = 0x1A;
    gCurrentSprite.pOam = sGunshipEndOam_Landed;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.work2 = 0;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;

    slot = SpriteSpawnSecondary(SSPRITE_GUNSHIP_END_BOTTOM, gCurrentSprite.roomSlot, gCurrentSprite.spritesetGfxSlot,
        gCurrentSprite.primarySpriteRamSlot, gCurrentSprite.yPosition, gCurrentSprite.xPosition, 0);
    gCurrentSprite.work4 = slot;

    gSpriteData[slot].status &= ~SPRITE_STATUS_NOT_DRAWN;
    gSpriteData[slot].pOam = sGunshipEndBottomOam;
    gSpriteData[slot].animationDurationCounter = 0;
    gSpriteData[slot].currentAnimationFrame = 0;
    gSpriteData[slot].properties |= SP_ALWAYS_ACTIVE;
    gSpriteData[slot].drawOrder = 14;
    gSpriteData[slot].samusCollision = SSC_NONE;
    gSpriteData[slot].drawDistanceTop = 4;
    gSpriteData[slot].drawDistanceBottom = 0x38;
    gSpriteData[slot].drawDistanceHorizontal = 0x30;
    gSpriteData[slot].hitboxTop = -PIXEL_SIZE;
    gSpriteData[slot].hitboxBottom = PIXEL_SIZE;
    gSpriteData[slot].hitboxLeft = -PIXEL_SIZE;
    gSpriteData[slot].hitboxRight = PIXEL_SIZE;
    gSpriteData[slot].pose = 2;
    gSpriteData[slot].work1 = 0;
    gSpriteData[slot].work2 = 0;
    gSpriteData[slot].work3 = 0;
}

/**
 * @brief 5659c | a8 | Handles the gunship (end) waiting for samus to step on it
 *
 */
void GunshipEndWaitingForSamus(void)
{
    if (gCurrentSprite.work2 < 36)
    {
        gCurrentSprite.work2++;
        GunshipEndSpawnBeams();
        return;
    }

    if (gCurrentSprite.xPosition - 0x20 < gSamusData.xPosition &&
        gCurrentSprite.xPosition + 0x20 > gSamusData.xPosition &&
        gSamusData.yPosition == 0x2BF && !SpriteUtilCheckSamusMorphed())
    {
        if (gSamusData.invincibilityTimer != 0)
            gSamusData.invincibilityTimer = 0;

        SAMUS_SET_POSE(SPOSE_ON_SAVE_PAD);

        gSamusData.yPosition = gCurrentSprite.yPosition + 0x120;
        gSamusData.xPosition = gCurrentSprite.xPosition;

        gCurrentSprite.pose = 0x37;
        gCurrentSprite.work1 = 30;
        gCurrentSprite.drawOrder = 4;
        EventCheckAdvance(0x6D);
    }
    else
    {
        gCurrentSprite.drawOrder = 12;
    }
}

/**
 * @brief 56644 | 28 | Handles the gunship (end) locking samus
 *
 */
void GunshipEndLockingSamus(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x38;
        gCurrentSprite.work1 = 60 - 1;
    }
}

/**
 * @brief 5666c | 3c | Handles the gunship (end) pulling samus up
 *
 */
void GunshipEndMovingSamusUp(void)
{
    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 == 0)
    {
        gCurrentSprite.pose = 0x39;
        gDisableDrawingSamusAndScrollingFlag = TRUE;
    }
    else
    {
        gSamusData.yPosition -= PIXEL_SIZE;
    }
}

/**
 * @brief 566a8 | 90 | Handles the gunship (end) starting the engine (1)
 *
 */
void GunshipEndStartingEngine1(void)
{
    u8 bottomSlot;

    bottomSlot = gCurrentSprite.work4;

    if (!SpriteUtilHasCurrentAnimationEnded())
        return;

    gCurrentSprite.pose = 0x3A;
    gCurrentSprite.pOam = sGunshipEndOam_Flying;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;
    gCurrentSprite.work1 = 60;
    gCurrentSprite.work2 = 0;
    gCurrentSprite.work4 = 0;
    gCurrentSprite.status |= SPRITE_STATUS_ROTATION_SCALING_WHOLE;
    gCurrentSprite.scaling = Q_8_8(1.f);
    gCurrentSprite.rotation = 0;

    gSpriteData[bottomSlot].status = 0;

    DMA3_COPY_16(&sGunshipFlashingPal[11], PALRAM_OBJ + 0x136, 5);
    SoundPlay_3b1c(0x24A);
}

/**
 * @brief 56738 | cc | Handles the gunship (end) starting the engine (2)
 *
 */
void GunshipEndStartingEngine2(void)
{
    u8 offset;
    s16 movement;

    offset = gCurrentSprite.work4;
    movement = sGunshipEndEngineYMovement[offset];
    if (movement == SHORT_MAX)
    {
        movement = sGunshipEndEngineYMovement[0];
        offset = 0;
    }
    gCurrentSprite.work4 = offset + 1;
    gCurrentSprite.yPosition += movement;

    if (gCurrentSprite.work2 == 0)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pOam = sGunshipEndOam_Engine2;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.work1 = 60;
            gCurrentSprite.work2 = 1;
        }
    }
    else if (gCurrentSprite.work2 == 1)
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pOam = sGunshipEndOam_Engine3;
            gCurrentSprite.animationDurationCounter = 0;
            gCurrentSprite.currentAnimationFrame = 0;
            gCurrentSprite.work1 = 90;
            gCurrentSprite.work2 = 2;
        }
    }
    else
    {
        gCurrentSprite.work1--;
        if (gCurrentSprite.work1 == 0)
        {
            gCurrentSprite.pose = 0x3B;
            gCurrentSprite.work1 = 0;
            gCurrentSprite.work2 = 0;
            gCurrentSprite.work3 = 0;
            gCurrentSprite.status |= SPRITE_STATUS_DOUBLE_SIZE;
        }
    }
}

/**
 * @brief 56804 | 94 | Handles the gunship (end) taking off
 *
 */
void GunshipEndTakingOff(void)
{
    u8 timer;

    timer = gCurrentSprite.work1;
    if (timer >= 0x40)
    {
        gCurrentSprite.yPosition -= 8;
        gCurrentSprite.pose = 0x3C;
        ColorFadingStartFinalEscape();
    }
    else if (timer >= 0x38)
    {
        gCurrentSprite.yPosition -= 8;
        gCurrentSprite.work1 = timer + 4;
    }
    else if (timer >= 0x30)
    {
        gCurrentSprite.yPosition -= 2;
        gCurrentSprite.work1 = timer + 4;
    }
    else if (timer >= 0x20)
    {
        gCurrentSprite.yPosition -= 1;
        gCurrentSprite.work1 = timer + 2;
    }
    else
    {
        gCurrentSprite.work1 = timer + 1;
    }

    gCurrentSprite.scaling = sGunshipEndTakingOffScaling[gCurrentSprite.work1];

    if (gCurrentSprite.work1 >= 0x20)
        gCurrentSprite.rotation = sGunshipEndTakingOffRotation[(u8)((gCurrentSprite.work1 - 0x20) >> 2)];
}

/**
 * @brief 56898 | 4 | Gunship (end) done (empty)
 *
 */
void GunshipEndDone(void)
{
    return;
}

/**
 * @brief 5689c | 74 | Handles the gunship (end) bottom part being idle (flashing palette)
 *
 */
void GunshipEndBottomIdle(void)
{
    gCurrentSprite.work3++;
    if (gCurrentSprite.work3 % 8 != 0)
        return;

    DMA3_COPY_16(&sGunshipFlashingPal[gCurrentSprite.work1 * 16 + 11], PALRAM_OBJ + 0x136, 5);

    if (gCurrentSprite.work2 != 0)
    {
        if (gCurrentSprite.work1 != 0)
        {
            gCurrentSprite.work1--;
        }
        else
        {
            gCurrentSprite.work2 = 0;
            gCurrentSprite.work1 = 1;
        }
    }
    else
    {
        if (gCurrentSprite.work1 > 5)
        {
            gCurrentSprite.work2 = 1;
            gCurrentSprite.work1 = 5;
        }
        else
        {
            gCurrentSprite.work1++;
        }
    }
}

/**
 * @brief 56910 | 74 | Initializes a gunship (end) beam
 *
 */
void GunshiEndpBeamInit(void)
{
    gCurrentSprite.status &= ~SPRITE_STATUS_NOT_DRAWN;
    gCurrentSprite.properties |= SP_ALWAYS_ACTIVE;
    gCurrentSprite.samusCollision = SSC_NONE;

    gCurrentSprite.drawDistanceTop = 4;
    gCurrentSprite.drawDistanceBottom = 4;
    gCurrentSprite.drawDistanceHorizontal = 0x10;

    gCurrentSprite.hitboxTop = -PIXEL_SIZE;
    gCurrentSprite.hitboxBottom = PIXEL_SIZE;
    gCurrentSprite.hitboxLeft = -PIXEL_SIZE;
    gCurrentSprite.hitboxRight = PIXEL_SIZE;

    gCurrentSprite.pOam = sGunshipEndBeamOam;
    gCurrentSprite.animationDurationCounter = 0;
    gCurrentSprite.currentAnimationFrame = 0;

    gCurrentSprite.pose = 2;
    gCurrentSprite.drawOrder = 13;
    gCurrentSprite.work1 = 9;
}

/**
 * @brief 56984 | 70 | Handles a gunship (end) beam moving down
 *
 */
void GunshipEndBeamMovingDown(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    // The room slot is used as a delay timer
    if (gCurrentSprite.roomSlot != 0)
    {
        gCurrentSprite.roomSlot--;
        gCurrentSprite.yPosition += PIXEL_SIZE;
        return;
    }

    gCurrentSprite.work1--;
    if (gCurrentSprite.work1 != 0)
    {
        gCurrentSprite.yPosition += PIXEL_SIZE;
    }
    else
    {
        gCurrentSprite.yPosition -= HALF_BLOCK_SIZE;
        gCurrentSprite.work1 = 9;
    }

    if (gSpriteData[ramSlot].pose == 0x37)
    {
        gCurrentSprite.pose = 0x18;
        gCurrentSprite.drawOrder = 5;
    }
}

/**
 * @brief 569f4 | 54 | Handles a gunship (end) beam moving up
 *
 */
void GunshipEndBeamMovingUp(void)
{
    u8 ramSlot;

    ramSlot = gCurrentSprite.primarySpriteRamSlot;

    gCurrentSprite.work1++;
    if (gCurrentSprite.work1 > 8)
    {
        gCurrentSprite.work1 = 0;
        gCurrentSprite.yPosition += HALF_BLOCK_SIZE;
    }
    else
    {
        gCurrentSprite.yPosition -= PIXEL_SIZE;
    }

    if (gSpriteData[ramSlot].pose == 0x39)
        gCurrentSprite.status = 0;
}

/**
 * @brief 56a48 | 168 | Gunship (end) AI
 *
 */
void GunshipEnd(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case 0:
            GunshipEndInit();
            break;

        case 1:
            GunshipEndWaiting();
            break;

        case 2:
            GunshipEndMovingUp();
            break;

        case 0x17:
            GunshipEndWaitingToEnter();
            break;

        case 0x18:
            GunshipEndEntering();
            break;

        case 0x1A:
            GunshipEndWaitingForSamus();
            break;

        case 0x37:
            GunshipEndLockingSamus();
            break;

        case 0x38:
            GunshipEndMovingSamusUp();
            break;

        case 0x39:
            GunshipEndStartingEngine1();
            break;

        case 0x3A:
            GunshipEndStartingEngine2();
            break;

        case 0x3B:
            GunshipEndTakingOff();
            break;

        case 0x3C:
            GunshipEndDone();
            break;
    }
}

/**
 * @brief 56bb0 | 20 | Gunship (end) bottom AI
 *
 */
void GunshipEndBottom(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    if (gCurrentSprite.pose == 2)
        GunshipEndBottomIdle();
}

/**
 * @brief 56bd0 | 54 | Gunship (end) beam AI
 *
 */
void GunshipEndBeam(void)
{
    gCurrentSprite.ignoreSamusCollisionTimer = 1;

    switch (gCurrentSprite.pose)
    {
        case 0:
            GunshiEndpBeamInit();

        case 2:
            GunshipEndBeamMovingDown();
            break;

        case 0x18:
            GunshipEndBeamMovingUp();
            break;
    }

    if (gCurrentSprite.roomSlot == 0 && gCurrentSprite.status == 0)
        SoundStop(0xFD);
}
