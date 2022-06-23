#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "config.h"
#include "Effect.h"

class SolidEffect : public Effect {
    private:
        double hue;

    public:
        SolidEffect() : Effect("Solid") { 
            hue = 0;
        }
        ~SolidEffect() { }

        void setup() { }
        void run() {
            FastLED.clear();

            for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
                LedMap *ledMap = getLedMap(i);
                ledsMapFill(ledMap, getConfig()->color);
            }
        }
};