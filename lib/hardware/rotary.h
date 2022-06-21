#pragma once

#include <Arduino.h>

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "pins.h"
#include "types.h"


Encoder encoder(ROTARY_CLK_PIN, ROTARY_DT_PIN);

RotaryDirection currentDirection;

int32_t lastPosition;
int32_t deltaPosition;

int32_t positionFraction;

RotaryDirection getRotaryDirection() {
    if (deltaPosition > 0) {
        return Clockwise;
    } else if (deltaPosition < 0) {
        return CounterClockwise;
    } else {
        return None;
    }
}

int32_t getRotaryPosition() {
    return encoder.read();
}

int32_t getRotaryDelta() {
    return deltaPosition;
}

void rotarySetup() {
    encoder.write(0);
    
    lastPosition = getRotaryPosition();
    deltaPosition = 0;
    positionFraction = 0;

    currentDirection = RotaryDirection::None;
}


void rotaryLoop() {
    positionFraction += getRotaryPosition() - lastPosition;
    lastPosition = getRotaryPosition();

    deltaPosition = 0;
    if (positionFraction != 0 && positionFraction % 4 == 0) {
        deltaPosition = positionFraction / 4;
        positionFraction = 0;
    } 
}