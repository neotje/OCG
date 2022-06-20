#pragma once

#include "lcd.h"
#include "rotary.h"

int currentValue = 0;
int maxValue = 255;
int minValue = 0;

int stepSize = 1;

char *label = "";

const int NUMBER_CHANGE_TIMEOUT = 200;
unsigned long lastNumberChange = 0;

int getCurrentValue() {
    return currentValue;
}

void numberSelectorDraw() {
    getLcd()->setCursor(0, 1);
    getLcd()->print(currentValue);
}

void numberSelectorSetup(char *nLabel, int nCurrentValue, int nMinValue, int nMaxValue, int nStepSize = 1) {
    label = nLabel;
    currentValue = nCurrentValue;
    minValue = nMinValue;
    maxValue = nMaxValue;
    stepSize = nStepSize;

    getLcd()->clear();
    getLcd()->print(label);

    numberSelectorDraw();
}

void numberSelectorLoop() {
    if (getRotaryDirection() != None && millis() - lastNumberChange > NUMBER_CHANGE_TIMEOUT) {
        lastNumberChange = millis();

        if (getRotaryDelta() > 0) {
            currentValue += stepSize;
        } else if (getRotaryDelta() < 0) {
            currentValue -= stepSize;
        }

        currentValue = constrain(currentValue, minValue, maxValue);
    }
}