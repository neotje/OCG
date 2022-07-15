#pragma once

#include <Arduino.h>

#include "types.h"
#include "leds.h"

LedMap LEDS_MAP[] = {
    {0, 98, Right, true}
    //,{50, 100, Left, false}
};

uint8_t getNumOfLedMaps() {
    return sizeof(LEDS_MAP) / sizeof(LEDS_MAP[0]);
}

LedMap *getLedMap(uint8_t index) {
    return &LEDS_MAP[index];
}

LedMap *getLedMap(LedstripPosition position) {
    for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
        if (LEDS_MAP[i].position == position) {
            return &LEDS_MAP[i];
        }
    }

    return NULL;
}

uint16_t getLedsMapLength(LedMap *ledMap) {
    return ledMap->end - ledMap->start;
}

void ledsMapSet(LedMap *ledMap, uint16_t index, const CRGB &color) {
    if (index >= ledMap->end - ledMap->start) {
        return;
    }

    uint16_t ledIndex = ledMap->start + index;
    
    if (ledMap->reverse) {
        ledIndex = ledMap->end - index - 1;
    }

    ledsSetLed(ledIndex, color);
}

void ledsMapDraw(LedMap *ledMap, float fPos, float length, const CRGB &color) {
    double firstPixel = 1.0 - (fPos - (long)(fPos));
    firstPixel = min(firstPixel, length);
    length = min(length, getLedsMapLength(ledMap)-fPos);

    if (fPos >= 0 && fPos < getLedsMapLength(ledMap)) {
        CRGB firstColor = color;
        firstColor.fadeToBlackBy(255 * (1.0 - firstPixel));
        ledsMapSet(ledMap, (uint16_t)fPos, firstColor);
    }

    fPos += firstPixel;
    length -= firstPixel;

    while (length >= 0) {
        if (fPos >= 0 && fPos < getLedsMapLength(ledMap)) {
            ledsMapSet(ledMap, (uint16_t)fPos, color);
            length -= 1.0;
        }
        fPos += 1.0;
    }

    if (length > 0.0) {
        if (fPos >= 0 && fPos < getLedsMapLength(ledMap)) {
            CRGB lastColor = color;
            lastColor.fadeToBlackBy(255 * (1.0 - firstPixel));
            ledsMapSet(ledMap, (uint16_t)fPos, lastColor);
        }
    }
}

void ledsMapFill(LedMap *ledMap, const CRGB &color) {
    ledsFill(color, ledMap->start, ledMap->end);
}

void ledsMapFill(LedstripPosition position, const CRGB &color) {
    for (uint8_t i = 0; i < sizeof(LEDS_MAP) / sizeof(LEDS_MAP[0]); i++) {
        if (LEDS_MAP[i].position == position) {
            ledsMapFill(&LEDS_MAP[i], color);
            return;
        }
    }
}

void ledsMapFill(LedstripPosition position, const CRGB &color, uint16_t start, uint16_t end) {
    for (uint8_t i = 0; i < sizeof(LEDS_MAP) / sizeof(LEDS_MAP[0]); i++) {
        if (LEDS_MAP[i].position == position) {
            ledsFill(color, start, end - 1);
            return;
        }
    }
}