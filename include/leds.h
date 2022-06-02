#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "types.h"

const uint8_t LEDSTRIP1_PIN = 12;

const uint16_t NUM_LEDS = 100;
CRGB leds[NUM_LEDS];

void ledsSetup() {
    FastLED.addLeds<WS2812B, LEDSTRIP1_PIN, RGB>(leds, NUM_LEDS);
}

/**
 * @brief constrain led index to range [0, NUM_LEDS)
 * 
 * @param index led index
 * @return uint16_t constrained led index
 */
uint16_t ledsIndexConstrain(uint16_t index) {
    return constrain(index, 0, NUM_LEDS - 1);
}

/**
 * @brief set specific led to specific color
 * 
 * @param index led index
 * @param color color to set to
 */
void ledsSetLed(uint16_t index, const CRGB &color) {
    index = ledsIndexConstrain(index);
    leds[index] = color;
}

/**
 * @brief Get color of an led.
 * 
 * @param index led index
 * @return CRGB& 
 */
CRGB &ledsGetLed(uint16_t index) {
    index = ledsIndexConstrain(index);
    return leds[index];
}

/**
 * @brief Set all leds to a specific color.
 * 
 * @param color color to set to
 */
void ledsFill(const CRGB &color) {
    for (byte i = 0; i < NUM_LEDS; i++) {
        ledsSetLed(i, color);
    }
}

/**
 * @brief Set all leds to a specific color within a range.
 * 
 * @param color color to set to.
 * @param start starting led.
 * @param end ending led.
 */
void ledsFill(const CRGB &color, uint16_t start, uint16_t end) {
    start = ledsIndexConstrain(start);
    end = ledsIndexConstrain(end);

    for (byte i = start; i < end; i++) {
        ledsSetLed(i, color);
    }
}

void ledsClear() {
    FastLED.clear();
}

void ledsSetBrightness(byte brightness) {
    FastLED.setBrightness(brightness);
}

uint8_t ledsGetBrightness() {
    return FastLED.getBrightness();
}

void ledsLoop() {
    FastLED.show();
}