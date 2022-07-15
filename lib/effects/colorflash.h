#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "timing.h"
#include "config.h"
#include "Effect.h"

#define FLASH_COLOR_COUNT 3

class FlashEffect : public Effect {
    private:
        unsigned long lastUpdate;
        uint8_t colorI;
    public:
        FlashEffect() : Effect("Flash") { };
        ~FlashEffect() { };

        void setup() {
            this->lastUpdate = millis();
            this->colorI = 0;
        }

        void run() {
            if (millis() - this->lastUpdate > getConfig()->flashEffect.delay) {
                this->lastUpdate = millis();

                for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
                    LedMap *ledMap = getLedMap(i);

                    ledsMapFill(ledMap, getConfig()->flashEffect.colors[this->colorI]);
                }

                Serial.println(this->colorI);

                this->colorI = (this->colorI + 1) % FLASH_COLOR_COUNT;
            }
        }
};