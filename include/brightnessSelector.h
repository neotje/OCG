#pragma once

#include "lcd.h"
#include "rotary.h"
#include "leds.h"

const byte MIN_BRIGHTNESS = 0;
const byte MAX_BRIGHTNESS = 16;

const int BRIGHTNESS_CHANGE_TIMEOUT = 200;
unsigned long lastBrightnessChange = 0;

uint8_t currentBrightness = 0;

void brightnessSelectorDraw() {
    getLcd()->clear();
    getLcd()->print("Brightness:");
    
    getLcd()->setCursor(0, 1);
    for (size_t i = 0; i < MAX_BRIGHTNESS; i++) {
        if (i < currentBrightness) {
            getLcd()->print("#");
        } else {
            getLcd()->print(" ");
        }
    }
}

void brightnessSelectorSetup() {
    currentBrightness = (ledsGetBrightness() + 1)/MAX_BRIGHTNESS;

    brightnessSelectorDraw();
}

void brightnessSelectorLoop() {
    if (getRotaryDirection() != None && millis() - lastBrightnessChange > BRIGHTNESS_CHANGE_TIMEOUT) {
        lastBrightnessChange = millis();

        if (getRotaryDelta() > 0 && currentBrightness < MAX_BRIGHTNESS) {
            currentBrightness++;
        } else if (getRotaryDelta() < 0 && currentBrightness > MIN_BRIGHTNESS) {
            currentBrightness--;
        }

        currentBrightness = constrain(currentBrightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
        ledsSetBrightness(constrain(currentBrightness * MAX_BRIGHTNESS, 0, 255));

        getLcd()->setCursor(0, 1);
        for (size_t i = 0; i < MAX_BRIGHTNESS; i++) {
            if (i < currentBrightness) {
                getLcd()->print("#");
            } else {
                getLcd()->print(" ");
            }
        }
    }
}