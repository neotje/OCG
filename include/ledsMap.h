#pragma once

#include <Arduino.h>

#include "types.h"
#include "leds.h"

LedMap LEDS_MAP[] = {
    {0, 5, Right, false},
    {5, 10, Left, false}
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

void ledsMapFill(LedstripPosition position, const CRGB &color) {
    for (uint8_t i = 0; i < sizeof(LEDS_MAP) / sizeof(LEDS_MAP[0]); i++) {
        if (LEDS_MAP[i].position == position) {
            ledsFill(color, LEDS_MAP[i].start, LEDS_MAP[i].end - 1);
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