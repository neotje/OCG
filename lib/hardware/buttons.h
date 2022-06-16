#pragma once

#include <Arduino.h>

#include "pins.h"
#include "types.h"

const byte DOWN_STATE = 0;
const byte UP_STATE = 1;
const int LONG_PRESS_TIME = 1000;

Button buttons[] = {
    {BUTTON1_PIN, 0, false, false, false}
};


bool isButtonDown(byte buttonIndex) {
    return buttons[buttonIndex].isDown;
}

bool isButtonPressed(byte buttonIndex) {
    return buttons[buttonIndex].isPressed;
}

bool isButtonLongPressed(byte buttonIndex) {
    return buttons[buttonIndex].isDown && millis() - buttons[buttonIndex].pressStart > LONG_PRESS_TIME;
}

void buttonsSetup() {
    for (byte i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        pinMode(buttons[i].pin, INPUT);
    }
}

void buttonsLoop() {
    for (byte i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        buttons[i].isDown = digitalRead(buttons[i].pin) == DOWN_STATE;
        buttons[i].isPressed = false;

        // press started
        if (!buttons[i].lastState && buttons[i].isDown) {
            buttons[i].pressStart = millis();
        }

        // press ended
        if (buttons[i].lastState && !buttons[i].isDown) {
            buttons[i].isPressed = millis() - buttons[i].pressStart < 500;
        }

        // save last state
        buttons[i].lastState = buttons[i].isDown;
    }
}