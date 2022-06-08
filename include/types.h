#pragma once

#include <Arduino.h>

enum LedstripPosition {
    Right,
    Left
};

struct LedMap {
    uint16_t start;
    uint16_t end;
    LedstripPosition position;
    bool reverse;
};

enum RotaryDirection {
    None,
    Clockwise,
    CounterClockwise
};

struct Button {
    byte pin;

    unsigned long pressStart;
    
    bool lastState;
    bool isDown;
    bool isPressed;
};

struct Config {
    uint8_t brightness;
};