#include "rotaryDriver.h"

RotaryDriver::RotaryDriver(String name, int pin1, int pin2): Encoder(pin1, pin2) {
    this->name = name;

    write(0);
}

void RotaryDriver::loop() {
    positionFraction += readAndReset();

    deltaPosition = 0;
    if (positionFraction != 0 && positionFraction % 4 == 0) {
        deltaPosition = positionFraction / 4;
        positionFraction = 0;
    }
}