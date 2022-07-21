#include "buttonDriver.h"

ButtonDriver::ButtonDriver(String name, int pin, byte downState) {
    this->name = name;
    this->isDown = false;
    this->pin = pin;
    this->downState = downState;
    this->state = UP;

    pinMode(pin, INPUT);
}

void ButtonDriver::loop() {
    lastState = isDown;
    isDown = digitalRead(pin) == downState;

    switch (state)
    {
    case UP:
        if (isDown && !lastState) {
            state = DOWN;
            pressStart = millis();
        }
        break;
    case DOWN:
        if (!isDown && millis() - pressStart < 500) {
            state = SHORT_PRESS;
        } else if (isDown && millis() - pressStart > 1000) {
            state = LONG_PRESS;
        }
        break;
    case SHORT_PRESS:
        state = UP;
        break;
    case LONG_PRESS:
        state = UP;
        break;
    }
}

bool ButtonDriver::isButtonDown() {
    return isDown;
}

bool ButtonDriver::isPressed() {
    return state == SHORT_PRESS;
}

bool ButtonDriver::isLongPressed() {
    return state == LONG_PRESS;
}