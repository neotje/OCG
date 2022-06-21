#pragma once

#include "lcd.h"
#include "rotary.h"
#include "leds.h"
#include "config.h"

const byte MIN_BRIGHTNESS = 0;
const byte MAX_BRIGHTNESS = 16;

const int BRIGHTNESS_CHANGE_TIMEOUT = 200;
unsigned long lastBrightnessChange = 0;

int currentBrightness = 0;

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
    // linear
    //currentBrightness = (getConfig()->brightness + 1)/MAX_BRIGHTNESS;

    // parabolic
    currentBrightness = round(sqrt(getConfig()->brightness));

    brightnessSelectorDraw();
}

void brightnessSelectorLoop() {
    if (getRotaryDirection() != None) {
        Serial.println(getRotaryDelta());

        currentBrightness += getRotaryDelta();
        currentBrightness = constrain(currentBrightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS);

        // linear
        //getConfig()->brightness = constrain(currentBrightness * MAX_BRIGHTNESS, 0, 255);
        
        // exponential
        //getConfig()->brightness = round(pow(1.41387, currentBrightness) - 1);

        // parabolic
        getConfig()->brightness = constrain(round(pow(currentBrightness, 2)), 0, 255);

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