#include "navigation.h"

#include "globals.h"
#include "macros.h"
#include "gba.h"
#include "io.h"
#include "dma.h"
#include "text.h"
#include "audio_wrappers.h"
#include "music_wrappers.h"
#include "sound_event.h"
#include "callbacks.h"
#include "oam_id.h"
#include "syscalls.h"
#include "new_file_intro.h"
#include "menus/pause_screen_map.h"

#include "data/event_data.h"
#include "data/menus/pause_screen_map_data.h"
#include "data/sa_x_close_up.h"

#include "structs/connection.h"
#include "structs/display.h"
#include "structs/event.h"
#include "structs/minimap.h"
#include "structs/room.h"

#ifndef PLATFORM_PC
asm(".set gNavigationTargetLocation, 0x0300004c");
asm(".set gUnk_300004d, 0x0300004d");
asm(".set gUnk_300000a, 0x0300000a");
#endif

#define NAV_OAM(i) (PAUSE_SCREEN_DATA.oam[(i)])

/**
 * @brief 79afc | 600 | Processes the text of a navigation conversation
 *
 */
void NavigationConversationProcessText(void)
{
    u8* dst;
    u32 skip;
    s32 result;
    const u16* pText;
    u16 c;
    u16 hi;
    u32 idx;
    u16* pIndent;
    u32 indent;
    s32 sum;
    u32 noAdvance;

    if (PAUSE_SCREEN_DATA.unk_17 != 0)
    {
        if (!(PAUSE_SCREEN_DATA.typeFlags & 0x10))
            return;
    }
    else
    {
        if (!(PAUSE_SCREEN_DATA.typeFlags & 0x8))
            return;
    }

    dst = (u8*)VRAM_BASE + 0x7000;
    if (PAUSE_SCREEN_DATA.unk_18 != 0)
        dst = (u8*)VRAM_BASE + 0x6000;

    skip = FALSE;

    c = PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18];
    if (c == 0xFC00 || c == 0xFE00)
    {
        if (c == 0xFC00)
        {
            if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
                return;
            SoundPlay(0x203);
        }

        PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = 0;
        if (PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] > 0xE0)
            TextClearGraphics(2);
        PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] = 0xE0;

        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0xB;
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
        return;
    }

    if (c == 0xFD00)
    {
        if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
            return;
        SoundPlay(0x203);

        PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = 0;
        TextClearGraphics(1);
        PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] = 0;

        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0xB;
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
        return;
    }

    if (c == 0xE001)
    {
        if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
            PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = 0;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_1F != 0)
    {
        PAUSE_SCREEN_DATA.unk_1F--;
        return;
    }

    if (PAUSE_SCREEN_DATA.unk_1A != 0 && !(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)))
        PAUSE_SCREEN_DATA.unk_1A = 0;

    PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18]++;

    if ((gButtonInput & (KEY_A | KEY_B | KEY_DOWN)) && PAUSE_SCREEN_DATA.unk_1A == 0)
        skip = TRUE;
    else if (PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] < PAUSE_SCREEN_DATA.unk_1D)
        return;

    PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = 0;

    idx = (PAUSE_SCREEN_DATA.conversationNumber - 1) * 2;
    if (PAUSE_SCREEN_DATA.conversationNumber == gPreviousNavigationConversation)
        idx++;

    pText = sNavigationConversationTextPointers[gLanguage][idx];
    pText += PAUSE_SCREEN_DATA.unk_C;
    PAUSE_SCREEN_DATA.unk_C++;

    while (TRUE)
    {
        result = 0;
        c = *pText;
        hi = c & 0xFF00;

        switch (c >> 12)
        {
            case 0xF:
                if (c == 0xFF00)
                {
                    PAUSE_SCREEN_DATA.unk_1C = 1;
                    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 3;
                    result = 2;
                }
                else if (c == 0xFE00)
                {
                    PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = c;
                    result = 1;
                }
                else if (c == 0xFD00 || c == 0xFC00)
                {
                    PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = c;
                    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 3;
                    PAUSE_SCREEN_DATA.unk_1A = 1;
                    result = 2;
                }
                else if (c == 0xFB00)
                {
                    PAUSE_SCREEN_DATA.unk_1C = 2;
                    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 3;
                    result = 2;
                }
                break;

            case 0xE:
                if (hi == 0xE000)
                {
                    if (c == 0xE000)
                    {
                        if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                            PAUSE_SCREEN_DATA.typeFlags |= 0x400;
                    }
                    else if (c == 0xE001)
                    {
                        PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = c;
                    }
                }
                else if (hi == 0xE100)
                {
                    PAUSE_SCREEN_DATA.unk_1F = c;
                }
                else if (hi == 0xE200)
                {
                    if (*pText == 0xE201)
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x2;
                        PAUSE_SCREEN_DATA.unk_18 = 1;
                        PAUSE_SCREEN_DATA.unk_19 = 2;
                    }
                    else if (*pText == 0xE202)
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x4;
                        PAUSE_SCREEN_DATA.unk_18 = 1;
                        PAUSE_SCREEN_DATA.unk_19 = 2;
                    }
                    else
                    {
                        PAUSE_SCREEN_DATA.typeFlags |= 0x1;
                        PAUSE_SCREEN_DATA.unk_18 = 0;
                        PAUSE_SCREEN_DATA.unk_19 = 1;
                    }
                    PAUSE_SCREEN_DATA.unk_17 = *pText;
                }
                else if (hi == 0xE300)
                {
                    if (c == 0xE300)
                        PAUSE_SCREEN_DATA.typeFlags |= 0x40;
                    else if (c == 0xE301)
                        PAUSE_SCREEN_DATA.typeFlags &= ~0x40;
                }
                result = 1;
                break;

            case 0xC:
                PAUSE_SCREEN_DATA.unk_1C = 6;
                result = 1;
                break;

            case 0xB:
                if (c == 0xB001)
                {
                    PAUSE_SCREEN_DATA.unk_264 = 1;
                    result = 1;
                }
                else if (c == 0xB002)
                {
                    PAUSE_SCREEN_DATA.unk_264 = 1;
                    result = 1;
                }
                else if (c == 0xB003)
                {
                    if (PAUSE_SCREEN_DATA.unk_1C != 5 && PAUSE_SCREEN_DATA.unk_1C != 3)
                    {
                        PlayMusic(0x2A, 2);
                        SoundEventUpdate(0, 0xB);
                    }
                    result = 3;
                }
                break;

            case 0xA:
                unk_3c14(c & 0xFFF, PAUSE_SCREEN_DATA.conversationOnRepeat != 0);
                result = 3;
                break;

            case 0x9:
                unk_3bd4(c & 0xFFF, PAUSE_SCREEN_DATA.conversationOnRepeat != 0);
                result = 3;
                break;

            case 0x8:
                if (hi == 0x8000)
                {
                    PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] += c & 0xFF;
                }
                else if (hi == 0x8100)
                {
                    PAUSE_SCREEN_DATA.unk_1E = c;
                }
                else if (hi == 0x8200)
                {
                    PAUSE_SCREEN_DATA.unk_1D = c;
                    if ((u8)c == 0)
                        PAUSE_SCREEN_DATA.unk_1D = 8;
                }
                else if (hi == 0x8300)
                {
                    pIndent = &PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18];
                    if (*pIndent > 0xDF)
                        *pIndent = 0xE0;
                    else
                        *pIndent = 0;
                    *pIndent += (u8)*pText;
                }
                result = 3;
                break;
        }

        if (result != 3)
            break;

        gNonGameplayRam.pauseScreen.unk_C++;
        pText++;
    }

    if (result == 2)
    {
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
        return;
    }

    if (result == 1)
        return;

    PAUSE_SCREEN_DATA.navConvCharacterWidth = TextGetCharacterWidth(*pText);

    pIndent = &PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18];
    indent = *pIndent;
    sum = indent + PAUSE_SCREEN_DATA.navConvCharacterWidth;
    if (sum > 0x1C0)
    {
        TextClearGraphics(2);
        PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] = 0xE0;
    }
    else if (sum > 0xE0 && indent <= 0xDF)
    {
        *pIndent = 0xE0;
    }

    indent = PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18];
    if (indent > 0xDF)
    {
        dst += 0x800;
        indent -= 0xE0;
    }
    dst += (indent / 8) * 32;

    TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth,
        PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] & 7, PAUSE_SCREEN_DATA.unk_1E);

    if (!skip && *pText != 0x40)
    {
        if (PAUSE_SCREEN_DATA.unk_17 == 1)
        {
            PlayCharacterAppearingSound(*pText, 0x21);
            PAUSE_SCREEN_DATA.unk_1B = 2;
        }
        else if (PAUSE_SCREEN_DATA.unk_17 == 2)
        {
            PlayCharacterAppearingSound(*pText, 0x41);
            PAUSE_SCREEN_DATA.unk_1B = 3;
        }
        else
        {
            PlayCharacterAppearingSound(*pText, 1);
            PAUSE_SCREEN_DATA.unk_1B = 1;
        }
    }

    noAdvance = TRUE;
    if (pText[1] & 0x8000)
        noAdvance = (pText[1] & 0xF000) != 0xF000;

    if (noAdvance)
        PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] += PAUSE_SCREEN_DATA.navConvCharacterWidth;
}

/**
 * @brief 7a0fc | 1e0 | Draws a line of the "download map / skip" question text
 *
 * @param line Line
 * @return u32 bool, ended
 */
u32 unk_7a0fc(u8 line)
{
    u32 ended;
    u32 drawn;
    const u16* pText;
    u8* dst;
    u16 c;
    u32 indent;

    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x8))
        return FALSE;

    ended = FALSE;
    drawn = FALSE;

    while (TRUE)
    {
        pText = sMessageTextPointers[gLanguage][line + 0x2B];
        dst = (u8*)VRAM_BASE + 0x7000;
        pText += PAUSE_SCREEN_DATA.unk_21;
        c = *pText;

        if (c == 0xFE00)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((c & 0xFF00) == 0x8000)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent += (u8)*pText;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if ((c & 0xFF00) == 0x8300)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            if (PAUSE_SCREEN_DATA.navConvTextIndent > 0xDF)
                PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;
            else
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent += (u8)*pText;
            if (*pText == 0x83A0)
                PAUSE_SCREEN_DATA.navConvTextIndent -= 0x10;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if (!drawn)
        {
            if (c != 0x40 && PAUSE_SCREEN_DATA.navConvTextIndent <= 0xDF)
            {
                if (PAUSE_SCREEN_DATA.unk_1A != 0 && !(gButtonInput & (KEY_A | KEY_B | KEY_DOWN)))
                    PAUSE_SCREEN_DATA.unk_1A = 0;

                PAUSE_SCREEN_DATA.unk_20++;

                if (!((gButtonInput & (KEY_A | KEY_B | KEY_DOWN)) && PAUSE_SCREEN_DATA.unk_1A == 0))
                {
                    if (PAUSE_SCREEN_DATA.unk_20 <= 7)
                        return ended;
                }
            }
            PAUSE_SCREEN_DATA.unk_20 = 0;
        }

        PAUSE_SCREEN_DATA.navConvCharacterWidth = TextGetCharacterWidth(*pText);
        indent = PAUSE_SCREEN_DATA.navConvTextIndent;
        if ((s32)(indent + PAUSE_SCREEN_DATA.navConvCharacterWidth) > 0xE0 && indent <= 0xDF)
            PAUSE_SCREEN_DATA.navConvTextIndent = 0xE0;

        if (*pText != 0x40)
        {
            PlayCharacterAppearingSound(*pText, 1);
            indent = PAUSE_SCREEN_DATA.navConvTextIndent;
            if (indent > 0xDF)
            {
                drawn = TRUE;
                dst += 0x800;
                indent -= 0xE0;
            }
            dst += (indent / 8) * 32;
            TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth,
                PAUSE_SCREEN_DATA.navConvTextIndent & 7, 0);
        }

        PAUSE_SCREEN_DATA.navConvTextIndent += PAUSE_SCREEN_DATA.navConvCharacterWidth;
        PAUSE_SCREEN_DATA.unk_21++;

        if (pText[1] == 0xFF00)
            ended = TRUE;

        if (!drawn || ended)
            break;
    }

    return ended;
}

/**
 * @brief 7a2dc | c8 | Gets the current navigation conversation
 *
 */
void NavigationConversationGetCurrentConversation(void)
{
    s32 i;

    i = gEventCounter;
    if (i > 0 && sEventLocationAndNavigationInfo[i].navConversation == 0)
    {
        do {
            i--;
        } while (i > 0 && sEventLocationAndNavigationInfo[i].navConversation == 0);
    }

    PAUSE_SCREEN_DATA.conversationNumber = sEventLocationAndNavigationInfo[i].navConversation;
    if (PAUSE_SCREEN_DATA.conversationNumber == gPreviousNavigationConversation)
        PAUSE_SCREEN_DATA.conversationOnRepeat = TRUE;
    else
        PAUSE_SCREEN_DATA.conversationOnRepeat = FALSE;

    TextClearGraphics(0);
    NavigationConversationUpdateTarget(TRUE);
    NavigationConversationSetupOam();

    PAUSE_SCREEN_DATA.unk_238 = 0;
    PAUSE_SCREEN_DATA.unk_239 = 0;
    PAUSE_SCREEN_DATA.unk_23C = 0;
    PAUSE_SCREEN_DATA.unk_23D = 0;
    PAUSE_SCREEN_DATA.unk_250 = 0;
    PAUSE_SCREEN_DATA.unk_251 = 0;
    PAUSE_SCREEN_DATA.unk_252 = 0;
}

static void NavigationConversationResetCursor(void)
{
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = 8;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition = sNavigationTextCursorYPositions[PAUSE_SCREEN_DATA.unk_18 * 2];
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0xB;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
    PAUSE_SCREEN_DATA.pauseDebugEditingValue = 1;
    PAUSE_SCREEN_DATA.timer = 0;
}

static void NavigationConversationClearText(void)
{
    TextClearGraphics(1);
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0;
    PAUSE_SCREEN_DATA.unk_1A = 1;
    PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18] = 0;
    PAUSE_SCREEN_DATA.unk_E[PAUSE_SCREEN_DATA.unk_18] = 0;
    PAUSE_SCREEN_DATA.unk_1C = 0;
    PAUSE_SCREEN_DATA.timer = 0;
}

static void NavigationConversationSetQuestionCursor(u16 xPosition)
{
    PAUSE_SCREEN_DATA.unk_24 = 2;
    PAUSE_SCREEN_DATA.unk_1A = 1;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 2;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition = 0x8C;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = xPosition;
}

static void NavigationConversationQuestionInput(u8 nextStage)
{
    u32 action;

    action = 0;
    NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition = 0x8C;

    if (gChangedInput & KEY_LEFT)
    {
        action = (PAUSE_SCREEN_DATA.unk_25 ^ 1) != 0;
        PAUSE_SCREEN_DATA.unk_25 = 1;
    }
    else if (gChangedInput & KEY_RIGHT)
    {
        if (PAUSE_SCREEN_DATA.unk_25 != 0)
            action = 1;
        PAUSE_SCREEN_DATA.unk_25 = 0;
    }
    else if (gChangedInput & KEY_A)
    {
        action = 2;
        PAUSE_SCREEN_DATA.pauseDebugEditingValue = nextStage;
        PAUSE_SCREEN_DATA.timer = 0;
    }

    if (PAUSE_SCREEN_DATA.unk_25 != 0)
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = 0x34;
    else
        NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = 0x84;

    if (action == 1)
    {
        SoundPlay(0x1FA);
    }
    else if (action == 2)
    {
        if (PAUSE_SCREEN_DATA.unk_25 != 0)
            SoundPlay(0x204);
        else
            SoundPlay(0x205);
    }
}

/**
 * @brief 7a3a4 | ab0 | Navigation conversation main loop
 *
 * @return u32 bool, ended
 */
u32 NavigationConversationHandler(void)
{
    u32 ended;
    u32 idx;
    u16 c;
    u32 pressed;
    u8 yPos;
    u16 indent;

    unk_7b674();
    NavigationConversionScrollToTarget();
    unk_7b56c();
    NavigationConversationUpdatePanel();
    unk_78c44();

    ended = FALSE;

    switch (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
    {
        case 0:
            PAUSE_SCREEN_DATA.timer = 0;
            NavigationConversationSetupOam();
            if (PAUSE_SCREEN_DATA.conversationOnRepeat)
            {
                PAUSE_SCREEN_DATA.unk_1C = 4;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x11;
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_1C = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            }
            break;

        case 1:
            PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
            PAUSE_SCREEN_DATA.unk_9 = 1;
            PAUSE_SCREEN_DATA.unk_B = 1;
            PAUSE_SCREEN_DATA.unk_1D = 8;
            PAUSE_SCREEN_DATA.unk_1E = 0;
            PAUSE_SCREEN_DATA.unk_1F = 0;

            idx = (PAUSE_SCREEN_DATA.conversationNumber - 1) * 2;
            if (PAUSE_SCREEN_DATA.conversationOnRepeat)
                idx++;

            c = *sNavigationConversationTextPointers[gLanguage][idx];
            if (c == 0xE201)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 0x2;
                PAUSE_SCREEN_DATA.unk_18 = 1;
                PAUSE_SCREEN_DATA.unk_19 = 2;
                PAUSE_SCREEN_DATA.unk_17 = 1;
            }
            else if (c == 0xE202)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 0x4;
                PAUSE_SCREEN_DATA.unk_18 = 1;
                PAUSE_SCREEN_DATA.unk_19 = 2;
                PAUSE_SCREEN_DATA.unk_17 = 2;
            }
            else
            {
                PAUSE_SCREEN_DATA.typeFlags |= 0x1;
                PAUSE_SCREEN_DATA.unk_18 = 0;
                PAUSE_SCREEN_DATA.unk_19 = 1;
                PAUSE_SCREEN_DATA.unk_17 = 0;
            }
            PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 2:
            PAUSE_SCREEN_DATA.unk_1B = 0;
            if (PAUSE_SCREEN_DATA.unk_1C == 1)
            {
                pressed = FALSE;
                if (gChangedInput & (KEY_A | KEY_B | KEY_DOWN))
                {
                    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x200))
                    {
                        if (PAUSE_SCREEN_DATA.unk_241 == 0)
                        {
                            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0;
                            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
                            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
                            TextClearGraphics(0);
                            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 3;
                            PAUSE_SCREEN_DATA.timer = 0;
                            break;
                        }
                    }
                    else
                    {
                        pressed = TRUE;
                    }
                }

                if (pressed || (PAUSE_SCREEN_DATA.typeFlags & 0x200))
                {
                    if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
                        PAUSE_SCREEN_DATA.typeFlags |= 0x400;
                    break;
                }
            }
            else if (PAUSE_SCREEN_DATA.unk_1C == 2)
            {
                if (!(PAUSE_SCREEN_DATA.typeFlags & 0x400))
                {
                    PAUSE_SCREEN_DATA.unk_24 = 0;
                    PAUSE_SCREEN_DATA.unk_25 = 1;
                    PAUSE_SCREEN_DATA.unk_1A = 1;
                    PAUSE_SCREEN_DATA.unk_1B = 0;
                    PAUSE_SCREEN_DATA.pauseDebugEditingValue = 8;
                    PAUSE_SCREEN_DATA.timer = 0;
                }
            }
            else if (PAUSE_SCREEN_DATA.unk_1C == 6)
            {
                ended = TRUE;
            }
            else
            {
                NavigationConversationProcessText();
            }

            if (NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId == 3)
            {
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = 0x74;
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition =
                    sNavigationTextCursorYPositions[PAUSE_SCREEN_DATA.unk_18 * 2 + 1];
                break;
            }

            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition = 0;
            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition = 0;
            indent = PAUSE_SCREEN_DATA.unk_E[2 + PAUSE_SCREEN_DATA.unk_18];
            if (indent > 0xDF)
            {
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition += indent - 0xD8;
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition +=
                    sNavigationTextCursorYPositions[PAUSE_SCREEN_DATA.unk_18 * 2] + 0x10;
            }
            else
            {
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).xPosition += indent + 8;
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).yPosition +=
                    sNavigationTextCursorYPositions[PAUSE_SCREEN_DATA.unk_18 * 2];
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.unk_1B = 0;
            if (PAUSE_SCREEN_DATA.conversationNumber != gPreviousNavigationConversation)
            {
                gPreviousNavigationConversation = PAUSE_SCREEN_DATA.conversationNumber;
                if (!PAUSE_SCREEN_DATA.conversationOnRepeat)
                    SoundEventUpdateForNavConversation();
            }
            PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.timer > 8)
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 5:
            PAUSE_SCREEN_DATA.dispcnt ^= DCNT_BG0;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x40;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x8)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x8;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x10)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x10;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x1 || PAUSE_SCREEN_DATA.typeFlags & 0x2 ||
                PAUSE_SCREEN_DATA.typeFlags & 0x4)
                return FALSE;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 7:
            ended = TRUE;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 8:
            if (PAUSE_SCREEN_DATA.unk_24 == 0)
            {
                if (!(gChangedInput & (KEY_A | KEY_B | KEY_DOWN)))
                    break;

                SoundPlay(0x203);
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).oamId = 0;
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
                NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
                TextClearGraphics(1);
                PAUSE_SCREEN_DATA.unk_24 = 1;
                PAUSE_SCREEN_DATA.unk_1C = 3;
                PAUSE_SCREEN_DATA.unk_20 = 0;
                PAUSE_SCREEN_DATA.unk_21 = 0;
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;
            }
            else if (PAUSE_SCREEN_DATA.unk_24 == 2)
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 9;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            else if (unk_7a0fc(0))
            {
                NavigationConversationSetQuestionCursor(0x34);
            }
            break;

        case 9:
            NavigationConversationQuestionInput(10);
            break;

        case 10:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0xC0))
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x10;
                if (PAUSE_SCREEN_DATA.unk_25 == 0)
                {
                    PAUSE_SCREEN_DATA.mapX = gMinimapX;
                    PAUSE_SCREEN_DATA.mapY = gMinimapY;
                    if (PAUSE_SCREEN_DATA.currentArea != gCurrentArea)
                    {
                        PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0xB;
                        NAV_OAM(32).oamId = 0;
                        NAV_OAM(32).animationDurationCounter = 0;
                        NAV_OAM(32).currentAnimationFrame = 0;
                    }
                    else if (NAV_OAM(31).oamId != 0)
                    {
                        PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0xF;
                    }

                    NAV_OAM(31).oamId = 0;
                    NAV_OAM(31).animationDurationCounter = 0;
                    NAV_OAM(31).currentAnimationFrame = 0;
                    PAUSE_SCREEN_DATA.unk_C = 0;
                    PAUSE_SCREEN_DATA.unk_219 = 0;
                }

                NavigationConversationClearText();
            }
            else if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
            {
                PAUSE_SCREEN_DATA.typeFlags ^= 0x40;
            }
            break;

        case 11:
            PAUSE_SCREEN_DATA.unk_250 |= 1;
            PAUSE_SCREEN_DATA.timer = 0;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0xC;
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.unk_250 & 4)
            {
                PAUSE_SCREEN_DATA.currentArea = gCurrentArea;
                unk_75988(TRUE);
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0xD;
            }
            break;

        case 13:
            if (PAUSE_SCREEN_DATA.timer > 4)
            {
                GetMinimapData(PAUSE_SCREEN_DATA.currentArea, (u8*)EWRAM_BASE + 0x34000);
                MinimapSetVisitedTilesAndCollectedItems(PAUSE_SCREEN_DATA.currentArea);
                DMA_SET(3, (u8*)EWRAM_BASE + 0x34000, (u8*)VRAM_BASE + 0xE000, C_32_2_16(DMA_ENABLE, 0x400));
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0xE;
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.unk_250 |= 8;
            }
            break;

        case 14:
            if (PAUSE_SCREEN_DATA.unk_250 == 0)
            {
                NAV_OAM(32).oamId = 1;
                NAV_OAM(32).animationDurationCounter = 0;
                NAV_OAM(32).currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x10;
            }
            break;

        case 15:
            if (NavigationConversationScrollMapToDestination(PAUSE_SCREEN_DATA.mapX, PAUSE_SCREEN_DATA.mapY))
            {
                PAUSE_SCREEN_DATA.timer = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x10;
            }
            break;

        case 16:
            if (PAUSE_SCREEN_DATA.timer > 0x10)
            {
                NavigationConversationUpdateTarget(FALSE);
                NavigationConversationResetCursor();
            }
            break;

        case 17:
            PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
            PAUSE_SCREEN_DATA.unk_1D = 8;
            PAUSE_SCREEN_DATA.unk_1E = 0;
            PAUSE_SCREEN_DATA.unk_1F = 0;
            PAUSE_SCREEN_DATA.typeFlags |= 0x1;
            PAUSE_SCREEN_DATA.unk_18 = 0;
            PAUSE_SCREEN_DATA.unk_19 = 1;
            PAUSE_SCREEN_DATA.unk_17 = 0;
            PAUSE_SCREEN_DATA.unk_24 = 1;
            NAV_OAM(1).oamId = 0;
            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).animationDurationCounter = 0;
            NAV_OAM(PAUSE_SCREEN_DATA.unk_19).currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.unk_21 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = 0;
            PAUSE_SCREEN_DATA.unk_1C = 5;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 18:
            if (PAUSE_SCREEN_DATA.unk_24 == 0)
                break;

            if (PAUSE_SCREEN_DATA.unk_24 == 2)
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x13;
                PAUSE_SCREEN_DATA.timer = 0;
                break;
            }

            if (unk_7a0fc(1))
            {
                NavigationConversationSetQuestionCursor(0x84);
                PAUSE_SCREEN_DATA.unk_25 = 0;
            }
            break;

        case 19:
            NavigationConversationQuestionInput(0x14);
            break;

        case 20:
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0x15;
            if (PAUSE_SCREEN_DATA.unk_25 == 1)
            {
                gPreviousNavigationConversation = 0xFF;
                NAV_OAM(31).oamId = 0;
                NAV_OAM(31).animationDurationCounter = 0;
                NAV_OAM(31).currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.unk_C = 0;
                PAUSE_SCREEN_DATA.unk_219 = 0;
            }
            NavigationConversationClearText();
            break;

        case 21:
            NavigationConversationResetCursor();
            break;
    }

    return ended;
}

/**
 * @brief 7ae54 | 138 | Sets up the navigation conversation objects
 *
 */
void NavigationConversationSetupOam(void)
{
    NAV_OAM(4).xPosition = 0x7C;
    NAV_OAM(4).yPosition = 0xCC;
    NAV_OAM(3).oamId = 0x4B;
    NAV_OAM(3).animationDurationCounter = 0;
    NAV_OAM(3).currentAnimationFrame = 0;

    PauseScreenSetNavigationTextPanelOam(TRUE);

    NAV_OAM(5).objMode = 1;
    NAV_OAM(1).priority = 0;
    NAV_OAM(1).objMode = 0;
    NAV_OAM(3).priority = 0;
    NAV_OAM(3).objMode = 0;
    NAV_OAM(4).priority = 0;
    NAV_OAM(4).objMode = 0;

    // Original copies 12 bytes from sBlob_5766D4_581510 (0x085766d4), which are all 0
    PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = NULL;
    PAUSE_SCREEN_DATA.currentPopUp = 0;
    PAUSE_SCREEN_DATA.unk_219 = 0;
    PAUSE_SCREEN_DATA.unk_21A = 0;
    PAUSE_SCREEN_DATA.unk_21B = 0;
    PAUSE_SCREEN_DATA.unk_21C = 0;
    PAUSE_SCREEN_DATA.unk_21D = 0;
    PAUSE_SCREEN_DATA.unk_21E = 0;
    PAUSE_SCREEN_DATA.unk_21F = 0;

    PAUSE_SCREEN_DATA.unk_1A = 0;
    PAUSE_SCREEN_DATA.typeFlags = 0;

    NAV_OAM(9).objMode = 1;
    NAV_OAM(2).priority = 0;
    NAV_OAM(2).objMode = 0;
    NAV_OAM(8).priority = 0;
    NAV_OAM(8).objMode = 0;
    NAV_OAM(7).priority = 0;
    NAV_OAM(7).objMode = 0;
    NAV_OAM(6).priority = 0;
    NAV_OAM(6).objMode = 0;

    NAV_OAM(7).xPosition = 0xD4;
    NAV_OAM(7).yPosition = 0x44;
    NAV_OAM(6).xPosition = 0xD4;
    NAV_OAM(6).yPosition = 0x44;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        NAV_OAM(5).priority = 1;
        NAV_OAM(9).priority = 1;
    }
    else
    {
        NAV_OAM(9).priority = 2;
        NAV_OAM(5).priority = 2;
    }
}

/**
 * @brief 7af8c | 70 | Updates the navigation target
 *
 * @param updateArrow Update arrow flag
 */
void NavigationConversationUpdateTarget(u8 updateArrow)
{
    u8 oamId;

    if (!NavigationConverstionFindTarget() || !updateArrow)
        return;

    NAV_OAM(31).animationDurationCounter = 0;
    NAV_OAM(31).currentAnimationFrame = 0;

    if (PAUSE_SCREEN_DATA.unk_20F == 1)
        oamId = sNavigationTargetArrowOamIds[PAUSE_SCREEN_DATA.navTargetTextDirection];
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
        oamId = 0xF;
    else
        oamId = 0xE;

    NAV_OAM(31).oamId = oamId;
}

/**
 * @brief 7affc | 15c | Finds the navigation target
 *
 * @return u32 bool, target is for the conversation on repeat
 */
u32 NavigationConverstionFindTarget(void)
{
    u32 found;
    s32 i;
    u8 x;
    u8 y;

    PAUSE_SCREEN_DATA.unk_20F = 0;
    PAUSE_SCREEN_DATA.navTargetX = 0xFF;
    PAUSE_SCREEN_DATA.navTargetY = 0xFF;
    PAUSE_SCREEN_DATA.navTargetArea = 0;
    PAUSE_SCREEN_DATA.navTargetTextDirection = 0;

    if (gPauseScreenFlag == 4)
        return FALSE;

    gNavigationTargetLocation = 0;
    found = FALSE;
    for (i = 0; i <= 0x20; i++)
    {
        if (PAUSE_SCREEN_DATA.conversationNumber == sNavigationTargetInfo[i].conversation)
        {
            found = TRUE;
            PAUSE_SCREEN_DATA.navTargetTextDirection = sNavigationTargetInfo[i].textDirection;
            break;
        }
    }

    if (!found)
        return FALSE;

    gNavigationTargetLocation = sNavigationTargetInfo[i].location;
    PAUSE_SCREEN_DATA.navTargetArea = sNavigationTargetLocationAreas[gNavigationTargetLocation];

    if (PAUSE_SCREEN_DATA.currentArea == PAUSE_SCREEN_DATA.navTargetArea)
    {
        x = sNavigationTargetInfo[i].xPosition;
        y = sNavigationTargetInfo[i].yPosition;
        PAUSE_SCREEN_DATA.unk_20F = 1;
    }
    else if (PAUSE_SCREEN_DATA.currentArea == 0)
    {
        x = sNavigationAreaNavRoomPositions[PAUSE_SCREEN_DATA.navTargetArea * 2];
        y = sNavigationAreaNavRoomPositions[PAUSE_SCREEN_DATA.navTargetArea * 2 + 1];
        PAUSE_SCREEN_DATA.unk_20F = 2;
    }
    else
    {
        x = sNavigationAreaElevatorPositions[PAUSE_SCREEN_DATA.currentArea * 2];
        y = sNavigationAreaElevatorPositions[PAUSE_SCREEN_DATA.currentArea * 2 + 1];
        if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            PAUSE_SCREEN_DATA.unk_20F = 2;
        else
            PAUSE_SCREEN_DATA.unk_20F = 3;
    }

    PAUSE_SCREEN_DATA.navTargetX = x - 1;
    PAUSE_SCREEN_DATA.navTargetY = y - 1;

    return gPreviousNavigationConversation == PAUSE_SCREEN_DATA.conversationNumber;
}

/**
 * @brief 7b158 | 36c | Scrolls the map to the navigation target
 *
 */
void NavigationConversionScrollToTarget(void)
{
    u8 oamId;

    PAUSE_SCREEN_DATA.unk_8++;

    switch (PAUSE_SCREEN_DATA.unk_9)
    {
        case 1:
            if (PAUSE_SCREEN_DATA.navTargetX == 0xFF || PAUSE_SCREEN_DATA.navTargetY == 0xFF ||
                NAV_OAM(31).oamId == sNavigationTargetArrowOamIds[0] ||
                NAV_OAM(31).oamId == sNavigationTargetArrowOamIds[1] ||
                NAV_OAM(31).oamId == sNavigationTargetArrowOamIds[2] ||
                NAV_OAM(31).oamId == sNavigationTargetArrowOamIds[3] ||
                NAV_OAM(31).oamId == 0xE || NAV_OAM(31).oamId == 0xF)
            {
                PAUSE_SCREEN_DATA.unk_9 = 0xC;
                break;
            }

            PAUSE_SCREEN_DATA.unk_9 = 2;
            PAUSE_SCREEN_DATA.typeFlags |= 0x100 | 0x200;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 3:
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9 = 4;
            break;

        case 4:
        case 11:
            if (PAUSE_SCREEN_DATA.unk_8 > 0x1E)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9 = 5;
                SoundPlay(0x119);
            }
            break;

        case 5:
            if (!NavigationConversationScrollMapToDestination(PAUSE_SCREEN_DATA.navTargetX, PAUSE_SCREEN_DATA.navTargetY))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                oamId = sNavigationTargetArrowOamIds[PAUSE_SCREEN_DATA.navTargetTextDirection];
            else if (PAUSE_SCREEN_DATA.currentArea == 0)
                oamId = 0xF;
            else
                oamId = 0xE;

            NAV_OAM(31).oamId = oamId;
            NAV_OAM(31).animationDurationCounter = 0;
            NAV_OAM(31).currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;

            if (PAUSE_SCREEN_DATA.unk_20F == 1)
                PAUSE_SCREEN_DATA.unk_9 = 0xC;
            else
                PAUSE_SCREEN_DATA.unk_9 = 6;

            SoundStop(0x119);
            PAUSE_SCREEN_DATA.mapViewX = PAUSE_SCREEN_DATA.navTargetX;
            PAUSE_SCREEN_DATA.mapViewY = PAUSE_SCREEN_DATA.navTargetY;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.unk_8 > 0x3C)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
            }
            break;

        case 7:
            PAUSE_SCREEN_DATA.unk_250 = 1;
            NAV_OAM(31).oamId = 0;
            NAV_OAM(32).oamId = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 8:
            if (!(PAUSE_SCREEN_DATA.unk_250 & 4))
                break;

            if (PAUSE_SCREEN_DATA.unk_20F == 3)
                PAUSE_SCREEN_DATA.navTargetArea = 0;

            if (PAUSE_SCREEN_DATA.navTargetArea == 0)
            {
                PAUSE_SCREEN_DATA.mapX = sNavigationAreaNavRoomPositions[PAUSE_SCREEN_DATA.currentArea * 2] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavigationAreaNavRoomPositions[PAUSE_SCREEN_DATA.currentArea * 2 + 1] - 1;
            }
            else
            {
                PAUSE_SCREEN_DATA.mapX = sNavigationAreaElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea * 2] - 1;
                PAUSE_SCREEN_DATA.mapY = sNavigationAreaElevatorPositions[PAUSE_SCREEN_DATA.navTargetArea * 2 + 1] - 1;
            }

            PAUSE_SCREEN_DATA.currentArea = PAUSE_SCREEN_DATA.navTargetArea;
            GetMinimapData(PAUSE_SCREEN_DATA.currentArea, (u8*)EWRAM_BASE + 0x34000);
            MinimapSetVisitedTilesAndCollectedItems(PAUSE_SCREEN_DATA.currentArea);
            DMA_SET(3, (u8*)EWRAM_BASE + 0x34000, (u8*)VRAM_BASE + 0xE000, C_32_2_16(DMA_ENABLE, 0x400));
            unk_75988(TRUE);
            NavigationConversationUpdateTarget(FALSE);
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 9:
            if (PAUSE_SCREEN_DATA.unk_8 > 8)
            {
                PAUSE_SCREEN_DATA.unk_8 = 0;
                PAUSE_SCREEN_DATA.unk_9++;
                PAUSE_SCREEN_DATA.unk_250 |= 8;
            }
            break;

        case 10:
            if (PAUSE_SCREEN_DATA.unk_250 != 0)
                break;

            if (PAUSE_SCREEN_DATA.navTargetArea != 0 && PAUSE_SCREEN_DATA.currentArea != 0)
                oamId = 0xF;
            else
                oamId = 0xE;

            NAV_OAM(32).oamId = oamId;
            NAV_OAM(32).animationDurationCounter = 0;
            NAV_OAM(32).currentAnimationFrame = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x200)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x200;
            if (PAUSE_SCREEN_DATA.typeFlags & 0x400)
                PAUSE_SCREEN_DATA.typeFlags ^= 0x400;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9++;
            break;
    }
}

/**
 * @brief 7b4c4 | a8 | Scrolls the map towards a destination
 *
 * @param xPosition X position (in minimap tiles)
 * @param yPosition Y position (in minimap tiles)
 * @return u32 bool, reached
 */
u32 NavigationConversationScrollMapToDestination(u8 xPosition, u8 yPosition)
{
    u32 reached;
    s32 targetX;
    s32 targetY;
    s32 distX;
    s32 distY;
    s32 speedX;
    s32 speedY;
    u16 bgX;
    u16 bgY;

    reached = TRUE;

    targetX = 0x200 - (0xF - xPosition) * 8;
    targetY = 0x200 - (0xA - yPosition) * 8;

    bgX = gBackgroundPositions.bg[3].x;
    distX = bgX - targetX;
    distY = gBackgroundPositions.bg[3].y - targetY;
    if (distX < 0)
        distX = -distX;
    if (distY < 0)
        distY = -distY;

    speedX = (distX >> 4) + 1;
    speedY = (distY >> 4) + 1;

    distX = bgX - targetX;
    if (distX != 0)
    {
        reached = FALSE;
        if (distX > 0)
        {
            gBackgroundPositions.bg[3].x = bgX - speedX;
            if (gBackgroundPositions.bg[3].x < targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
        else if (distX < 0)
        {
            gBackgroundPositions.bg[3].x = bgX + speedX;
            if (gBackgroundPositions.bg[3].x > targetX)
                gBackgroundPositions.bg[3].x = targetX;
        }
    }

    bgY = gBackgroundPositions.bg[3].y;
    distY = bgY - targetY;
    if (distY != 0)
    {
        reached = FALSE;
        if (distY > 0)
        {
            gBackgroundPositions.bg[3].y = bgY - speedY;
            if (gBackgroundPositions.bg[3].y < targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
        else if (distY < 0)
        {
            gBackgroundPositions.bg[3].y = bgY + speedY;
            if (gBackgroundPositions.bg[3].y > targetY)
                gBackgroundPositions.bg[3].y = targetY;
        }
    }

    return reached;
}

/**
 * @brief 7b56c | 108 | Handles the navigation pop-up sequence
 *
 */
void unk_7b56c(void)
{
    PAUSE_SCREEN_DATA.unk_A++;

    switch (PAUSE_SCREEN_DATA.unk_B)
    {
        case 1:
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.typeFlags & 0x40)
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 3:
            NAV_OAM(15).oamId = 0x41;
            NAV_OAM(15).animationDurationCounter = 0;
            NAV_OAM(15).currentAnimationFrame = 0;
            SoundPlay(0x11C);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 4:
            if (PAUSE_SCREEN_DATA.unk_A > 0x1E)
            {
                PAUSE_SCREEN_DATA.currentPopUp = 1;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
                PAUSE_SCREEN_DATA.typeFlags |= 0x80;
            }
            break;

        case 5:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x40))
            {
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;

        case 6:
            PAUSE_SCREEN_DATA.currentPopUp = 3;
            NAV_OAM(15).oamId = 0x42;
            NAV_OAM(15).animationDurationCounter = 0;
            NAV_OAM(15).currentAnimationFrame = 0;
            SoundPlay(0x11D);
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B++;
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.unk_A > 0x1E)
            {
                PAUSE_SCREEN_DATA.typeFlags &= ~0x80;
                PAUSE_SCREEN_DATA.unk_A = 0;
                PAUSE_SCREEN_DATA.unk_B++;
            }
            break;
    }
}

/**
 * @brief 7b674 | 260 | Handles the map transition effect (mosaic / window) of the navigation
 *
 */
void unk_7b674(void)
{
    s32 speed;
    s32 size;

    if (!(PAUSE_SCREEN_DATA.unk_250 & 3))
        return;

    PAUSE_SCREEN_DATA.unk_252++;

    switch (PAUSE_SCREEN_DATA.unk_251)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.unk_250 & 1)
                PAUSE_SCREEN_DATA.unk_251 = 1;
            else if (PAUSE_SCREEN_DATA.unk_250 & 2)
                PAUSE_SCREEN_DATA.unk_251 = 4;

            gPreviousArea = 0xFF;
            PAUSE_SCREEN_DATA.unk_252 = 0;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.unk_252 & 7)
            {
                gWrittenToMosaic_L += 0x11;
                if (gWrittenToMosaic_L == *sNavigationMosaicTarget)
                {
                    PAUSE_SCREEN_DATA.unk_252 = 0;
                    PAUSE_SCREEN_DATA.unk_251++;
                    PAUSE_SCREEN_DATA.unk_250 |= 4;
                }
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_252 & 7)
            {
                gWrittenToMosaic_L -= 0x11;
                if (gWrittenToMosaic_L == 0)
                {
                    PAUSE_SCREEN_DATA.unk_251 = 8;
                    PAUSE_SCREEN_DATA.unk_252 = 0;
                }
            }
            break;

        case 4:
            PAUSE_SCREEN_DATA.window1Size = 0;
            PAUSE_SCREEN_DATA.unk_251 = 5;
            PAUSE_SCREEN_DATA.unk_252 = 0;
            break;

        case 5:
            speed = (0x50 - PAUSE_SCREEN_DATA.window1Size) >> 4;
            if (speed <= 3)
                speed = 4;
            PAUSE_SCREEN_DATA.window1Size += speed;
            if (PAUSE_SCREEN_DATA.window1Size > 0x50)
            {
                PAUSE_SCREEN_DATA.window1Size = 0x50;
                PAUSE_SCREEN_DATA.unk_252 = 0;
                PAUSE_SCREEN_DATA.unk_251++;
                PAUSE_SCREEN_DATA.unk_250 |= 4;
            }
            WRITE_16(REG_WIN1V, (PAUSE_SCREEN_DATA.window1Size << 8) | (0xA0 - PAUSE_SCREEN_DATA.window1Size));
            break;

        case 2:
        case 6:
            if (PAUSE_SCREEN_DATA.unk_250 & 8)
            {
                PAUSE_SCREEN_DATA.unk_251++;
                PAUSE_SCREEN_DATA.unk_252 = 0;
            }
            break;

        case 7:
            speed = (0x50 - PAUSE_SCREEN_DATA.window1Size) >> 4;
            if (speed <= 3)
                speed = 4;
            size = PAUSE_SCREEN_DATA.window1Size - speed;
            if (size < 0)
            {
                PAUSE_SCREEN_DATA.window1Size = 0;
                PAUSE_SCREEN_DATA.unk_251 = 8;
                PAUSE_SCREEN_DATA.unk_252 = 0;
            }
            else
            {
                PAUSE_SCREEN_DATA.window1Size = size;
            }
            WRITE_16(REG_WIN1V, (PAUSE_SCREEN_DATA.window1Size << 8) | (0xA0 - PAUSE_SCREEN_DATA.window1Size));
            break;

        case 8:
            PAUSE_SCREEN_DATA.unk_252 = 0;
            PAUSE_SCREEN_DATA.unk_251 = 0;
            PAUSE_SCREEN_DATA.unk_250 = 0;
            break;
    }
}

/**
 * @brief Draws a line of text in a text buffer (shared by the pause screen and easy sleep texts)
 *
 * @param pText Text
 * @param dst Destination
 */
static void NavigationDrawTextLine(const u16* pText, u8* dst)
{
    s32 indent;
    u32 width;
    u32 draw;
    s32 sum;
    s32 x;
    s32 offset;

    indent = 0;

    while (*pText != 0xFF00)
    {
        draw = TRUE;

        if ((*pText & 0xFF00) == 0x8000)
        {
            width = *pText & 0xFF;
            draw = FALSE;
        }
        else if ((*pText & 0xFF00) == 0x8300)
        {
            width = 0;
            indent = *pText & 0xFF;
            draw = FALSE;
        }
        else if (*pText == 0xFE00)
        {
            width = 0;
            if (indent > 0xE0)
                return;
            indent = 0xE0;
            draw = FALSE;
        }

        if (draw)
        {
            width = TextGetCharacterWidth(*pText);
            sum = indent + width;
            if (sum > 0xE0 && indent <= 0xDF)
                indent = 0xE0;
            else if (sum > 0x1C0)
                return;

            if (indent > 0xDF)
            {
                offset = 0x800;
                x = indent - 0xE0;
            }
            else
            {
                offset = 0;
                x = indent;
            }

            TextDrawCharacter(*pText, (u32*)(dst + offset + (x >> 3) * 32), width, x & 7, 0);
        }

        pText++;
        indent += width;
        if (indent > 0x1BF)
            return;
    }
}

/**
 * @brief 7b8d4 | 11c | Draws the pause screen text (current objective) in EWRAM
 *
 */
void ProcessPauseScreenText(void)
{
    BitFill(3, 0, (u8*)EWRAM_BASE + 0xC000, 0x1000, 16);
    NavigationDrawTextLine(sPauseScreenTextPointers[gLanguage][gEventCounter], (u8*)EWRAM_BASE + 0xC000);
}

/**
 * @brief 7b9f0 | 200 | Draws the easy sleep texts in EWRAM
 *
 */
void ProcessEasySleepText(void)
{
    s32 i;
    u8* dst;
    const u16* pText;
    s32 indent;
    u32 width;

    BitFill(3, 0, (u8*)EWRAM_BASE + 0xD000, 0x1000, 16);
    BitFill(3, 0, (u8*)EWRAM_BASE + 0xE000, 0x1000, 16);
    BitFill(3, 0, (u8*)EWRAM_BASE + 0xF000, 0x800, 16);

    for (i = 0; i <= 1; i++)
    {
        dst = (u8*)EWRAM_BASE + 0xE000;
        if (i == 0)
            dst = (u8*)EWRAM_BASE + 0xD000;

        NavigationDrawTextLine(sMessageTextPointers[gLanguage][i + 0x2D], dst);
    }

    dst = (u8*)EWRAM_BASE + 0xF000;
    pText = sMessageTextPointers[gLanguage][0x2F];
    indent = 0;

    while (*pText != 0xFF00)
    {
        if (*pText == 0xFE00)
        {
            width = 0;
            if (indent > 0x70)
                return;
            indent = 0x70;
        }
        else if (*pText & 0x8000)
        {
            width = 0;
        }
        else
        {
            width = TextGetCharacterWidth(*pText);
            if ((s32)(indent + width) > 0x1C0)
                return;
            TextDrawCharacter(*pText, (u32*)(dst + (indent >> 3) * 32), width, indent & 7, 0);
        }

        pText++;
        indent += width;
        if (indent > 0x1BF)
            return;
    }
}

/**
 * @brief 7bbf0 | a8 | Gets the sector number that should flash (sector of the current navigation target)
 *
 * @return u8 Sector number
 */
u8 GetFlashingSectorNumber(void)
{
    s32 i;
    s32 j;
    u32 found;

    gUnk_300004d = 0;

    i = gEventCounter;
    if (i > 0 && sEventLocationAndNavigationInfo[i].navConversation == 0)
    {
        do {
            i--;
        } while (i > 0 && sEventLocationAndNavigationInfo[i].navConversation == 0);
    }

    if (gPreviousNavigationConversation != sEventLocationAndNavigationInfo[i].navConversation)
        return gUnk_300004d;

    found = FALSE;
    for (j = 0; j <= 0x20; j++)
    {
        if (gPreviousNavigationConversation == sNavigationTargetInfo[j].conversation)
        {
            found = TRUE;
            break;
        }
    }

    if (found)
        gUnk_300004d = sNavigationTargetLocationAreas[sNavigationTargetInfo[j].location];

    return gUnk_300004d;
}

/**
 * @brief Finds the pop-up entry of the current conversation
 *
 * @return s32 Entry + 1, 0 if none
 */
static s32 NavigationConversationFindPopUps(void)
{
    s32 i;

    i = 3;
    if (PAUSE_SCREEN_DATA.conversationNumber != sNavigationPopUpConversations[2].conversation)
    {
        do {
            i--;
        } while (i > 0 && PAUSE_SCREEN_DATA.conversationNumber != sNavigationPopUpConversations[i - 1].conversation);
    }

    return i;
}

/**
 * @brief 7bc98 | f8 | Loads the graphics of the pop-ups of the current conversation
 *
 */
void NavigationConversationLoadPopUpGraphics(void)
{
    s32 i;
    const struct NavigationPopUpConversation* pEntry;
    u8* dst;

    i = NavigationConversationFindPopUps();
    if (i == 0)
        return;

    pEntry = &sNavigationPopUpConversations[i - 1];

    if (pEntry->popUps[0] != 0)
        LZ77UncompVram(sNavigationPopUps[pEntry->popUps[0]].pGraphics, (u8*)EWRAM_BASE + 0x0);
    if (pEntry->popUps[1] != 0)
        LZ77UncompVram(sNavigationPopUps[pEntry->popUps[1]].pGraphics, (u8*)EWRAM_BASE + 0x4000);
    if (pEntry->popUps[2] != 0)
        LZ77UncompVram(sNavigationPopUps[pEntry->popUps[2]].pGraphics, (u8*)EWRAM_BASE + 0x8000);

    dst = (u8*)VRAM_BASE + 0x15700;
    for (i = 5; i >= 0; i--)
    {
        BitFill(3, -1, dst, 0x100, 32);
        dst -= 0x400;
    }

    DMA3_FILL_32(0, (u8*)PALRAM_BASE + 0x3E0, PAL_ROW_SIZE);
}

/* Original reads these from sBlob_79c170_79c27c (0x0879c170) */
static void (*const sNavigationPopUpFunctions[3])(void) = {
    unk_7bde0,
    NavigationConversationUpdateXParasitePopUp,
    NavigationConversationClearPopUpGraphics,
};

/**
 * @brief 7bd90 | 50 | Updates the current navigation pop-up
 *
 */
void NavigationConversationUpdatePopUp(void)
{
    if (PAUSE_SCREEN_DATA.currentPopUp == 0)
        return;

    PAUSE_SCREEN_DATA.unk_21B++;
    sNavigationPopUpFunctions[PAUSE_SCREEN_DATA.currentPopUp - 1]();

    if (PAUSE_SCREEN_DATA.unk_21D != 0)
        NavigationConversationFadeInPopUpPalette();
}

/**
 * @brief Gets the graphics buffer of the current pop-up
 *
 */
static u8* NavigationConversationGetPopUpBuffer(void)
{
    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        return (u8*)EWRAM_BASE + 0x4000;
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        return (u8*)EWRAM_BASE + 0x8000;
    else
        return (u8*)EWRAM_BASE + 0x0;
}

/**
 * @brief Transfers the current pop-up frame to VRAM
 *
 * @param pInfo Pop-up info
 * @param src Source
 */
static void NavigationConversationTransferPopUpFrame(const struct NavigationPopUpInfo* pInfo, u8* src, u32 type)
{
    s32 rows;
    u8* dst;

    rows = pInfo->tiles & 0xF;
    if (rows <= 0)
        return;

    src += rows * 0x400;
    if (type == 8)
        dst = (u8*)VRAM_BASE + 0x14300 + (pInfo->tiles >> 4) * 0x400 + rows * 0x400;
    else
        dst = (u8*)VRAM_BASE + 0x14340 + (pInfo->tiles >> 4) * 0x400 + rows * 0x400;

    do {
        src -= 0x400;
        dst -= 0x400;
        rows--;
        if (type == 8)
            DMA_SET(3, src, dst, C_32_2_16(DMA_ENABLE, 0x80))
        else
            DMA_SET(3, src, dst, C_32_2_16(DMA_ENABLE, 0x40))
    } while (rows > 0);
}

/**
 * @brief 7bde0 | 1f4 | Starts the current navigation pop-up
 *
 */
void unk_7bde0(void)
{
    s32 i;
    const u8* pEntry;
    const struct NavigationPopUpInfo* pInfo;
    u32 type;

    PAUSE_SCREEN_DATA.unk_21A = 0xFF;

    i = NavigationConversationFindPopUps();
    i--;
    // PORT: the original checks i == 0xFF (never true), so for a conversation without pop-ups
    // this reads the 4 bytes before sNavigationPopUpConversations (end of sNavigationPopUps[4].pGraphics)
    pEntry = (const u8*)sNavigationPopUpConversations + i * 4;

    if (PAUSE_SCREEN_DATA.unk_219 == 1)
        PAUSE_SCREEN_DATA.unk_21A = pEntry[2];
    else if (PAUSE_SCREEN_DATA.unk_219 == 2)
        PAUSE_SCREEN_DATA.unk_21A = pEntry[3];
    else
        PAUSE_SCREEN_DATA.unk_21A = pEntry[1];

    if (PAUSE_SCREEN_DATA.unk_21A == 0)
    {
        PAUSE_SCREEN_DATA.currentPopUp = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_229 = 0;
    PAUSE_SCREEN_DATA.unk_228 = 0;
    PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = (const u32*)NavigationConversationGetPopUpBuffer();

    pInfo = &sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A];
    type = pInfo->type & 0xF;
    if (type == 8 || type == 4)
        NavigationConversationTransferPopUpFrame(pInfo, (u8*)PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer, type);

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundPlay(0x125);

    PAUSE_SCREEN_DATA.unk_21D = 1;
    PAUSE_SCREEN_DATA.currentPopUp++;
    PAUSE_SCREEN_DATA.unk_21B = 0;
}

/**
 * @brief 7bfd4 | fc | Fades in the palette of the current pop-up
 *
 */
void NavigationConversationFadeInPopUpPalette(void)
{
    const u16* src;
    u16* dst;
    s32 i;
    s32 j;
    u8 target[4];
    u8 current[4];

    src = sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A].pPalette;
    dst = (u16*)((u8*)PALRAM_BASE + 0x3E0);

    for (i = 0; i < 16; i++)
    {
        target[0] = *src & 0x1F;
        target[1] = (*src & 0x3E0) >> 5;
        target[2] = (*src & 0x7C00) >> 10;
        current[0] = *dst & 0x1F;
        current[1] = (*dst & 0x3E0) >> 5;
        current[2] = (*dst & 0x7C00) >> 10;

        for (j = 0; j <= 2; j++)
        {
            if (target[j] > current[j])
                current[j]++;
            else if (target[j] < current[j])
                current[j]--;
        }

        *dst = current[0] | current[1] << 5 | current[2] << 10;
        src++;
        dst++;
    }

    if (PAUSE_SCREEN_DATA.unk_21D > 0x20)
        PAUSE_SCREEN_DATA.unk_21D = 0;
    else
        PAUSE_SCREEN_DATA.unk_21D++;
}

/**
 * @brief 7c0d0 | 248 | Updates the animation of the current pop-up
 *
 */
void NavigationConversationUpdateXParasitePopUp(void)
{
    const struct NavigationPopUpInfo* pInfo;
    const u8* pFrames;
    u32 type;
    u8* src;
    u8 frame;

    unk_7c3b4();

    pInfo = &sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A];
    type = pInfo->type & 0xF;
    if (type != 8 && type != 4)
        return;

    pFrames = pInfo->pFrames;
    if (PAUSE_SCREEN_DATA.unk_21B < pFrames[PAUSE_SCREEN_DATA.unk_21C * 2 + 1])
        return;

    PAUSE_SCREEN_DATA.unk_21B = 0;
    PAUSE_SCREEN_DATA.unk_21C++;
    if (PAUSE_SCREEN_DATA.unk_21C >= sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A].frameCount)
        PAUSE_SCREEN_DATA.unk_21C = 0;

    PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = (const u32*)NavigationConversationGetPopUpBuffer();

    pInfo = &sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A];
    frame = pFrames[PAUSE_SCREEN_DATA.unk_21C * 2];
    src = (u8*)PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer;
    if (type == 8)
        src += (frame & 3) * 0x100 + (frame >> 2) * 0x1800;
    else
        src += (frame & 7) * 0x80 + (frame >> 3) * 0x1000;
    PAUSE_SCREEN_DATA.pNavConvPopUpGraphicsPointer = (const u32*)src;

    NavigationConversationTransferPopUpFrame(pInfo, src, type);
}

/**
 * @brief 7c318 | 9c | Clears the pop-up graphics and ends the pop-up
 *
 */
void NavigationConversationClearPopUpGraphics(void)
{
    s32 i;
    u8* dst;

    dst = (u8*)VRAM_BASE + 0x15700;
    for (i = 5; i >= 0; i--)
    {
        BitFill(3, -1, dst, 0x100, 32);
        dst -= 0x400;
    }

    DMA3_FILL_32(0, (u8*)PALRAM_BASE + 0x3E0, PAL_ROW_SIZE);

    if (PAUSE_SCREEN_DATA.unk_21A == 3)
        SoundStop(0x125);

    PAUSE_SCREEN_DATA.currentPopUp = 0;
    PAUSE_SCREEN_DATA.unk_21C = 0;
    PAUSE_SCREEN_DATA.unk_21B = 0;
    PAUSE_SCREEN_DATA.unk_21D = 0;
    PAUSE_SCREEN_DATA.unk_219++;
}

/**
 * @brief 7c3b4 | 8c | Updates the flashing color of the current pop-up
 *
 */
void unk_7c3b4(void)
{
    const u16* pColors;
    const u16* pColor;

    if (sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A].flashingColorDelay == 0)
        return;

    PAUSE_SCREEN_DATA.unk_229++;
    if (PAUSE_SCREEN_DATA.unk_229 < sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A].flashingColorDelay)
        return;

    PAUSE_SCREEN_DATA.unk_229 = 0;
    pColors = sNavigationPopUps[PAUSE_SCREEN_DATA.unk_21A].pFlashingColors;
    pColor = &pColors[PAUSE_SCREEN_DATA.unk_228];
    if (*pColor == 0)
    {
        PAUSE_SCREEN_DATA.unk_228 = 0;
        pColor = pColors;
    }

    *(u16*)((u8*)PALRAM_BASE + 0x3FE) = *pColor;

    PAUSE_SCREEN_DATA.unk_228++;
    if (PAUSE_SCREEN_DATA.unk_228 > 0xF)
        PAUSE_SCREEN_DATA.unk_228 = 0;
}

/**
 * @brief 7c440 | 174 | Updates the navigation palette animations
 *
 */
void unk_7c440(void)
{
    u16* dst;
    u16 i;
    u16 j;

    PAUSE_SCREEN_DATA.unk_225++;
    if (PAUSE_SCREEN_DATA.unk_225 >= sNavigation_57beb4[PAUSE_SCREEN_DATA.unk_224])
    {
        PAUSE_SCREEN_DATA.unk_225 = 0;
        PAUSE_SCREEN_DATA.unk_224++;
        if (PAUSE_SCREEN_DATA.unk_224 > 3)
            PAUSE_SCREEN_DATA.unk_224 = 0;

        dst = (u16*)PALRAM_BASE;
        dst[0x24 / 2] = sNavigation_57bcd4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x26 / 2] = sNavigation_57bcd4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x44 / 2] = sNavigation_57bcf4[PAUSE_SCREEN_DATA.unk_224];
        dst[0x46 / 2] = sNavigation_57bcf4[PAUSE_SCREEN_DATA.unk_224];
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
        return;

    if (PAUSE_SCREEN_DATA.unk_0 == 1)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D < sNavigation_57beb8[PAUSE_SCREEN_DATA.unk_22C])
            return;

        PAUSE_SCREEN_DATA.unk_22D = 0;
        PAUSE_SCREEN_DATA.unk_22C++;
        if (PAUSE_SCREEN_DATA.unk_22C > 3)
            PAUSE_SCREEN_DATA.unk_22C = 0;

        dst = (u16*)((u8*)PALRAM_BASE + 0x138);
        j = PAUSE_SCREEN_DATA.unk_22C * 16 + 0xC;
        for (i = 0; i <= 3; i++, j++)
            *dst++ = sNavigation_57bd34[j];
    }
    else if (PAUSE_SCREEN_DATA.unk_0 == 2)
    {
        PAUSE_SCREEN_DATA.unk_22D++;
        if (PAUSE_SCREEN_DATA.unk_22D < sNavigation_57bebc[PAUSE_SCREEN_DATA.unk_22C])
            return;

        PAUSE_SCREEN_DATA.unk_22D = 0;
        PAUSE_SCREEN_DATA.unk_22C++;
        if (PAUSE_SCREEN_DATA.unk_22C > 7)
            PAUSE_SCREEN_DATA.unk_22C = 0;

        dst = (u16*)((u8*)PALRAM_BASE + 0x194);
        j = PAUSE_SCREEN_DATA.unk_22C * 16 + 0xA;
        for (i = 0; i <= 5; i++, j++)
            *dst++ = sNavigation_57bdb4[j];
    }
}

/**
 * @brief 7c5b4 | 7c | Loads the graphics of the special navigation conversations
 *
 */
void NavigationConversationLoadSpecialGraphics(void)
{
    if (PAUSE_SCREEN_DATA.conversationNumber == 0x35)
    {
        LZ77UncompVram(sNavigation_57c0c4, (u8*)EWRAM_BASE + 0x0);
        LZ77UncompVram(sNavigation_57fca0, (u8*)EWRAM_BASE + 0x6000);
        LZ77UncompVram(sNavigation_580238, (u8*)EWRAM_BASE + 0x6800);
        LZ77UncompVram(sNavigation_5807d0, (u8*)EWRAM_BASE + 0x7000);
        LZ77UncompVram(sNavigation_580d68, (u8*)EWRAM_BASE + 0x7800);
    }
    else if (PAUSE_SCREEN_DATA.conversationNumber == 0xE)
    {
        LZ77UncompVram(sSaXCloseUpGfx, (u8*)EWRAM_BASE + 0x0);
    }
}
