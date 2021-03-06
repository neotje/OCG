#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include <LinkedList.h>

#include "Effect.h"

#include "rainbow.h"
#include "solid.h"
#include "twinkle.h"
#include "marquee.h"
#include "colorflash.h"

LinkedList<Effect*> effects;

uint8_t getEffectsCount() {
    return effects.size();
}

Effect *getEffect(uint8_t index) {
    if (index >= getEffectsCount()) {
        return NULL;
    }
    return effects.get(index);
}

void setEffect(uint8_t index) {
    if (index < getEffectsCount()) {
        getConfig()->currentEffect = index;
        getEffect(getConfig()->currentEffect)->setup();
        saveConfig();
    }
}

void effectsSetup() {
    effects.add(new RainbowEffect());
    effects.add(new SolidEffect());
    effects.add(new TwinkleEffect());
    effects.add(new MarqueeEffect());
    effects.add(new FlashEffect());

    Serial.print("Current effect: ");
    Serial.println(getConfig()->currentEffect);

    setEffect(getConfig()->currentEffect);
}

void effectsLoop() {
    if (getConfig()->currentEffect < getEffectsCount()) {
        Effect *effect = getEffect(getConfig()->currentEffect);

        effect->run();
    }
}