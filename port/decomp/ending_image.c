#include "ending_image.h"
#include "gba.h"
#include "macros.h"
#include "globals.h"

#include "constants/game_state.h"
#include "structs/ending.h"
#include "port_rom.h"

#ifdef PLATFORM_PC
#define ENDING_IMAGE_TEXT_GBA_SIZE 0xC
#define ENDING_IMAGE_TEXT_COUNT (0x9D8 / ENDING_IMAGE_TEXT_GBA_SIZE)

const struct EndingImageTextOamData* EndingImageTextNative(u32 offset)
{
    static struct EndingImageTextOamData sTexts[ENDING_IMAGE_TEXT_COUNT];
    static u8 sDecoded;
    u32 i;

    if (!sDecoded)
    {
        for (i = 0; i < ENDING_IMAGE_TEXT_COUNT; i++)
        {
            const u8* src = &sBlob_74dc48_74e620[i * ENDING_IMAGE_TEXT_GBA_SIZE];

            sTexts[i].unk_0 = src[0];
            sTexts[i].spawnDelay = src[1];
            sTexts[i].unk_2 = src[2];
            sTexts[i].xPosition = PortReadGbaU16(src + 4);
            sTexts[i].yPosition = PortReadGbaU16(src + 6);
            sTexts[i].pOam = (const u16*)PORT_GBA_PTR(src + 8);
        }
        sDecoded = TRUE;
    }
    return &sTexts[offset / ENDING_IMAGE_TEXT_GBA_SIZE];
}
#endif /* PLATFORM_PC */

/**
 * @brief a1480 | 1a8 | Draws the in game time and the completion percentage of the ending image
 *
 */
void EndingDrawIgtAndCompletionPercentage(void)
{
    s32 hoursTens;
    s32 hoursOnes;
    s32 minutesTens;
    s32 minutesOnes;
    s32 hundreds;
    s32 tens;
    s32 ones;

    hoursTens = 0;
    hoursOnes = gInGameTimer.hours;
    while (hoursOnes > 9)
    {
        hoursOnes -= 10;
        hoursTens++;
    }

    minutesTens = 0;
    minutesOnes = gInGameTimer.minutes;
    while (minutesOnes > 9)
    {
        minutesOnes -= 10;
        minutesTens++;
    }

    if (hoursTens != 0)
    {
        DMA3_COPY_16(&sEndingImageNumbersTopGfx[hoursTens * 64], VRAM_OBJ + 0x0, 0x20);
        DMA3_COPY_16(&sEndingImageNumbersBottomGfx[hoursTens * 64], VRAM_OBJ + 0x400, 0x20);
    }

    DMA3_COPY_16(&sEndingImageNumbersTopGfx[hoursOnes * 64], VRAM_OBJ + 0x40, 0x20);
    DMA3_COPY_16(&sEndingImageNumbersBottomGfx[hoursOnes * 64], VRAM_OBJ + 0x440, 0x20);

    DMA3_COPY_16(&sEndingImageNumbersTopGfx[minutesTens * 64], VRAM_OBJ + 0xA0, 0x20);
    DMA3_COPY_16(&sEndingImageNumbersBottomGfx[minutesTens * 64], VRAM_OBJ + 0x4A0, 0x20);

    DMA3_COPY_16(&sEndingImageNumbersTopGfx[minutesOnes * 64], VRAM_OBJ + 0xE0, 0x20);
    DMA3_COPY_16(&sEndingImageNumbersBottomGfx[minutesOnes * 64], VRAM_OBJ + 0x4E0, 0x20);

    hundreds = 0;
    tens = 0;
    ones = ENDING_DATA.completionPercentage;
    while (ones > 99)
    {
        ones -= 100;
        hundreds++;
    }

    while (ones > 9)
    {
        ones -= 10;
        tens++;
    }

    if (hundreds != 0)
    {
        DMA3_COPY_16(&sEndingImageNumbersTopGfx[hundreds * 64], VRAM_OBJ + 0x120, 0x20);
        DMA3_COPY_16(&sEndingImageNumbersBottomGfx[hundreds * 64], VRAM_OBJ + 0x520, 0x20);
    }

    if (hundreds != 0 || tens != 0)
    {
        DMA3_COPY_16(&sEndingImageNumbersTopGfx[tens * 64], VRAM_OBJ + 0x160, 0x20);
        DMA3_COPY_16(&sEndingImageNumbersBottomGfx[tens * 64], VRAM_OBJ + 0x560, 0x20);
    }

    DMA3_COPY_16(&sEndingImageNumbersTopGfx[ones * 64], VRAM_OBJ + 0x1A0, 0x20);
    DMA3_COPY_16(&sEndingImageNumbersBottomGfx[ones * 64], VRAM_OBJ + 0x5A0, 0x20);
}

/**
 * @brief a1628 | 3c | Updates the spawn delay of a letter of the ending image text
 *
 * @param slot Letter slot
 */
void EndingImageUpdateLettersSpawnDelay(u32 slot)
{
    // unk_124[slot + 30] is the spawn delay array at 0x142 (same out of bounds indexing as src/ending.c)
    if (ENDING_DATA.unk_124[slot] != 0 && ENDING_DATA.unk_124[slot + 30] != 0)
    {
        ENDING_DATA.unk_124[slot + 30]--;
        if (ENDING_DATA.unk_124[slot + 30] == 0)
            ENDING_DATA.unk_124[slot]++;
    }
}

/**
 * @brief a1664 | 4fc | Loads the letters of a text of the ending image (slots 6 and up)
 *
 * @param text Text number
 */
void EndingImageLoadTextOam(u32 text)
{
    const struct EndingImageTextOamData* pData;
    s32 count;
    s32 i;

    switch (gLanguage)
    {
        case LANGUAGE_GERMAN:
            if (text == 0)
            {
                pData = sEndingImageText0_German;
                count = 13;
            }
            else
            {
                pData = sEndingImageText1_German;
                count = 14;
            }
            break;

        case LANGUAGE_FRENCH:
            if (text == 0)
            {
                pData = sEndingImageText0_French;
                count = 16;
            }
            else
            {
                pData = sEndingImageText1_French;
                count = 20;
            }
            break;

        case LANGUAGE_ITALIAN:
            if (text == 0)
            {
                pData = sEndingImageText0_Italian;
                count = 18;
            }
            else if (text == 1)
            {
                pData = sEndingImageText1_Italian;
                count = 11;
            }
            else
            {
                pData = sEndingImageText2_Italian;
                count = 17;
            }
            break;

        case LANGUAGE_SPANISH:
            if (text == 0)
            {
                pData = sEndingImageText0_Spanish;
                count = 15;
            }
            else
            {
                pData = sEndingImageText1_Spanish;
                count = 19;
            }
            break;

        default:
            if (text == 0)
            {
                pData = sEndingImageText0_Default;
                count = 9;
            }
            else if (text == 1)
            {
                pData = sEndingImageText1_Default;
                count = 11;
            }
            else
            {
                pData = sEndingImageText2_Default;
                count = 17;
            }
            break;
    }

    ENDING_DATA.unk_9B = count + 6;

    // Same (out of bounds) indexing as the readers in src/ending.c
    for (i = 0; i < count; i++, pData++)
    {
        ENDING_DATA.unk_124[6 + i] = pData->unk_0;
        ENDING_DATA.unk_124[6 + i + 30] = pData->spawnDelay;
        ENDING_DATA.unk_160[6 + i] = pData->unk_2;
        ENDING_DATA.oamXPositions[6 + i] = pData->xPosition;
        ENDING_DATA.oamYPositions[6 + i] = pData->yPosition;
        ENDING_DATA.oamFramePointers[6 + i] = (u16*)pData->pOam;
    }
}

/**
 * @brief a1b60 | 124 | Displays a line of the ending image permanently (slots 0-5) and clears the letters
 *
 * @param line Line number
 */
void EndingImageDisplayLinePermanently(u32 line)
{
    const struct EndingImageTextOamData* pData;
    s32 i;

    switch (gLanguage)
    {
        case LANGUAGE_GERMAN:
            pData = sEndingImageLines_German;
            break;

        case LANGUAGE_FRENCH:
            pData = sEndingImageLines_French;
            break;

        case LANGUAGE_ITALIAN:
            pData = sEndingImageLines_Italian;
            break;

        case LANGUAGE_SPANISH:
            pData = sEndingImageLines_Spanish;
            break;

        default:
            pData = sEndingImageLines_Default;
            break;
    }

    pData = &pData[line];
    ENDING_DATA.unk_124[line] = pData->unk_0;
    ENDING_DATA.unk_124[line + 30] = pData->spawnDelay;
    ENDING_DATA.unk_160[line] = pData->unk_2;
    ENDING_DATA.oamXPositions[line] = pData->xPosition;
    ENDING_DATA.oamYPositions[line] = pData->yPosition;
    ENDING_DATA.oamFramePointers[line] = (u16*)pData->pOam;

    for (i = 0; i < ENDING_DATA.unk_9B - 6; i++)
        ENDING_DATA.unk_124[6 + i] = 0;

    ENDING_DATA.unk_9B = 6;
}
