#pragma once

#include <Arduino.h>
#include "types.h"

const byte ROTARY_CLK_PIN = 11;
const byte ROTARY_DT_PIN = 10;

byte previousStateClk;
byte currentStateClk;

RotaryDirection currentDirection = None;
int32_t position = 0;

byte readClk() {
    return digitalRead(ROTARY_CLK_PIN);
}

byte readDt() {
    return digitalRead(ROTARY_DT_PIN);
}

RotaryDirection getRotaryDirection() {
    return currentDirection;
}

int32_t getRotaryPosition() {
    return position;
}

void rotarySetup() {
    pinMode(ROTARY_CLK_PIN, INPUT);
    pinMode(ROTARY_DT_PIN, INPUT);

    previousStateClk = readClk();
}


void rotaryLoop() {
    currentStateClk = readClk();

    if (currentStateClk != previousStateClk) {
        if (readDt() != currentStateClk) {
            currentDirection = CounterClockwise;
            position--;
        } else {
            currentDirection = Clockwise;
            position++;
        }
    } else {
        currentDirection = None;
    }

    previousStateClk = currentStateClk;
}