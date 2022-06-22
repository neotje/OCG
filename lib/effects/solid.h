#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "config.h"

void solidEffect() {
    FastLED.clear();

    for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
        LedMap *ledMap = getLedMap(i);
        ledsMapFill(ledMap, getConfig()->color);
    }
}