#pragma once

#include <Arduino.h>
#include <FastLED.h>

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
    bool isLongPress;
    bool lastLongPress;
};

struct AccelGyroData {
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
    int16_t temp;
};

/****** CONFIG ******/

struct RainbowEffectConfig {
    uint8_t deltaHue;
    double speed;
};

struct TwinkleEffectConfig {
    uint32_t delay;
    uint8_t fraction;
};

struct MarqueeEffectConfig {
    uint32_t delay;
    uint8_t blackSpacing;
};

struct FlashEffectConfig {
    uint32_t delay;
    CRGB colors[3];
};

struct Config {
    uint8_t brightness;
    CHSV color;
    uint8_t currentEffect;
    RainbowEffectConfig rainbowEffect;
    TwinkleEffectConfig twinkleEffect;
    MarqueeEffectConfig marqueeEffect;
    FlashEffectConfig flashEffect;
};