#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "timing.h"

void rainbowEffect() {
    static double hue = 0;

    FastLED.clear();

    for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
        LedMap *ledMap = getLedMap(i);

        CHSV hsv;
        hsv.hue = hue;
        hsv.sat = 255;
        hsv.val = 255;

        for (uint16_t j = 0; j < getLedsMapLength(ledMap); j++) {
            ledsMapSet(ledMap, j, hsv);
            hsv.hue += 5;
        }
    }

    hue += getDeltaTime() * 100.0;
    if (hue > 255) {
        hue = 0;
    }
}