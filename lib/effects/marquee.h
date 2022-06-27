#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "ledsMap.h"
#include "timing.h"
#include "config.h"
#include "Effect.h"

class MarqueeEffect : public Effect {
    private:
        byte j;
        int scroll;
        unsigned long lastUpdate;
        
    public:
        MarqueeEffect() : Effect("Marquee") {
            j = 0;
            scroll = 0;
        }
        ~MarqueeEffect() {}

        void setup() {
            this->lastUpdate = millis();
        }
        void run() {
            if (millis() - this->lastUpdate > getConfig()->marqueeEffect.delay) {

                this->lastUpdate = millis();
                
                for (uint8_t i = 0; i < getNumOfLedMaps(); i++) {
                    LedMap *ledMap = getLedMap(i);

                    j += 4;
                    byte k = j;

                    CRGB c;
                    for (int i = 0; i < getLedsMapLength(ledMap); i++)
                        ledsMapSet(ledMap, i, c.setHue(k += 8));

                    scroll++;

                    uint8_t space = getConfig()->marqueeEffect.blackSpacing;

                    for (int i = scroll % space; i < getLedsMapLength(ledMap); i += space)
                        ledsMapSet(ledMap, i, CRGB::Black);
                }
            }
        }
};