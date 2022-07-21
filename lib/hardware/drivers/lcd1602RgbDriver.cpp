#include "lcd1602RgbDriver.h"

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

Lcd1602RgbDriver::Lcd1602RgbDriver(String name, TwoWire *wire, uint8_t lcdAddr, uint8_t RGBAddr) : DFRobot_RGBLCD1602(16, 2, wire, lcdAddr, RGBAddr) {
    this->name = name;

    init();

    setRGB(CRGB::Red);
    print("Initializing...");

    // Set custom characters
    customSymbol(ONE_FITH, oneFifth);
    customSymbol(TWO_FITH, twoFifth);
    customSymbol(THREE_FITH, threeFifth);
    customSymbol(FOUR_FITH, fourFifth);
}

void Lcd1602RgbDriver::loop() {
}

void Lcd1602RgbDriver::setRGB(const CRGB &color) {
    DFRobot_RGBLCD1602::setRGB(color.r, color.g, color.b);
}

void Lcd1602RgbDriver::drawBar(float value) {
    byte cols = value * 80;

    for (byte i = 0; i < cols/5; i++)
    {
        print(FULL);
    }

    switch (cols % 5) {
        case 1:
            write(ONE_FITH);
            break;
        case 2:
            write(TWO_FITH);
            break;
        case 3:
            write(THREE_FITH);
            break;
        case 4:
            write(FOUR_FITH);
            break;
    };

    for (byte i = cols/5; i < 80/5; i++)
    {
        print(' ');
    }
}