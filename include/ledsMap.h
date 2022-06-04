#pragma once

#include <Arduino.h>

#include "types.h"
#include "leds.h"

LedMap LEDS_MAP[] = {
    {0, 5, Right, false},
    {5, 10, Left, false}
};

void ledsMapSet(LedstripPosition position, uint16_t index, const CRGB &color) {
    for (uint8_t i = 0; i < sizeof(LEDS_MAP) / sizeof(LEDS_MAP[0]); i++) {
        if (LEDS_MAP[i].position == position) {
            if (index >= LEDS_MAP[i].end - LEDS_MAP[i].start) {
                return;
            }

            if (LEDS_MAP[i].reverse) {
                index = LEDS_MAP[i].end - index - 1;
            } else {
                index = LEDS_MAP[i].start + index;
            }

            ledsSetLed(index, color);
            return;
        }
    }
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