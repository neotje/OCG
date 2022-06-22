#pragma once

#include <Arduino.h>
#include <DFRobot_RGBLCD1602.h>
#include <FastLED.h>

DFRobot_RGBLCD1602 lcd(16, 2);

const byte ONE_FITH = 0;
const byte TWO_FITH = 1;
const byte THREE_FITH = 2;
const byte FOUR_FITH = 3;
const char FULL = (char)0xFF;

// Custom characters
byte oneFifth[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

byte twoFifth[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};

byte threeFifth[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};

byte fourFifth[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};

void lcdSetup() {
    lcd.init();

    lcd.customSymbol(ONE_FITH, oneFifth);
    lcd.customSymbol(TWO_FITH, twoFifth);
    lcd.customSymbol(THREE_FITH, threeFifth);
    lcd.customSymbol(FOUR_FITH, fourFifth);
}

void lcdSetColor(const CRGB &color) {
    lcd.setRGB(color.r, color.g, color.b);
}

void lcdDrawBar(float value) {
    byte cols = value * 80;

    for (byte i = 0; i < cols/5; i++)
    {
        lcd.print(FULL);
    }

    switch (cols % 5) {
        case 1:
            lcd.write(ONE_FITH);
            break;
        case 2:
            lcd.write(TWO_FITH);
            break;
        case 3:
            lcd.write(THREE_FITH);
            break;
        case 4:
            lcd.write(FOUR_FITH);
            break;
    };

    for (byte i = cols/5; i < 80/5; i++)
    {
        lcd.print(' ');
    }
}

DFRobot_RGBLCD1602* getLcd() {
    return &lcd;
}