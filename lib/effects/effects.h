#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "types.h"

#include "rainbow.h"
#include "solid.h"

Effect EFFECTS[] = {
    {rainbowEffect, "Rainbow"},
    {solidEffect, "Solid"}
};

uint8_t getEffectsCount() {
    return sizeof(EFFECTS) / sizeof(EFFECTS[0]);
}

Effect *getEffect(uint8_t index) {
    return &EFFECTS[index];
}

void setEffect(uint8_t index) {
    getConfig()->currentEffect = index;
    saveConfig();
}

void effectsLoop() {
    if (getConfig()->currentEffect < sizeof(EFFECTS) / sizeof(EFFECTS[0])) {
        const Effect *effect = getEffect(getConfig()->currentEffect);
        effect->func();
    }
}