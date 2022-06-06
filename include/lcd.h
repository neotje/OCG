#pragma once

#include <Arduino.h>
#include <DFRobot_RGBLCD1602.h>
#include <FastLED.h>

DFRobot_RGBLCD1602 lcd(16, 2);

void lcdSetup() {
    lcd.init();
}

void lcdSetColor(const CRGB &color) {
    lcd.setRGB(color.r, color.g, color.b);
}

DFRobot_RGBLCD1602* getLcd() {
    return &lcd;
}