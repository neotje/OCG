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