#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "config.h"
#include "Effect.h"

static const CRGB TWINKLE_COLORS[5] = {
    CRGB::Red,
    CRGB::Blue,
    CRGB::Purple,
    CRGB::Green,
    CRGB::Yellow
};

class TwinkleEffect : public Effect {
    private:
        int passCount;
        int ledsCount;

        unsigned long lastUpdate;

        void setRandomLed(CRGB color) {
            LedMap* ledMap = getLedMap(random(getNumOfLedMaps()));
            uint16_t ledIndex = random(getLedsMapLength(ledMap));

            ledsMapSet(ledMap, ledIndex, color);
        }

    public:
        TwinkleEffect() : Effect("Twinkle") { 
            this->passCount = 0;
            this->ledsCount = 0;
        }
        ~TwinkleEffect() { }

        void setup() { 
            this->passCount = 0;
            
            for (size_t i = 0; i < getNumOfLedMaps(); i++) {
                this->ledsCount += getLedsMapLength(getLedMap(i));
            }
            
        }
        void run() {
            if (millis() - this->lastUpdate > getConfig()->twinkleEffect.delay) {
                this->lastUpdate = millis();
                
                for (size_t i = 0; i < getConfig()->twinkleEffect.fraction; i++) {
                    setRandomLed(CRGB::Black);
                }
                

                setRandomLed(TWINKLE_COLORS[random(0, sizeof(TWINKLE_COLORS)/sizeof(TWINKLE_COLORS[0]))]);
            }
        }
};