#pragma once

#include "driverBase.h"

enum ButtonDriverState {
    UP,
    DOWN,
    SHORT_PRESS,
    LONG_PRESS
};

class ButtonDriver : public DriverBase {
    private:
        String name;

        bool isDown;
        bool lastState;
        int pin;
        byte downState;

        ButtonDriverState state;
        unsigned long pressStart;
    public:
        ButtonDriver(String name, int pin, byte downState = LOW);
        String getName() { return name;}
        void loop();

        bool isButtonDown();
        bool isPressed();
        bool isLongPressed();
};