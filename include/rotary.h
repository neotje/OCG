#pragma once

#include <Arduino.h>

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include "pins.h"
#include "types.h"


Encoder encoder(ROTARY_CLK_PIN, ROTARY_DT_PIN);

RotaryDirection currentDirection;

int32_t lastPosition;
uint32_t deltaPosition;

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
    deltaPosition = getRotaryPosition() - lastPosition;

    currentDirection = RotaryDirection::None;
}


void rotaryLoop() {
    deltaPosition = getRotaryPosition() - lastPosition;
    lastPosition = getRotaryPosition();
}