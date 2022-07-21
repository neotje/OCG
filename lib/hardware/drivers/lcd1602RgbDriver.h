#pragma once

#include <Arduino.h>
#include <DFRobot_RGBLCD1602.h>
#include <Wire.h>
#include <FastLED.h>

#include "driverBase.h"

const byte ONE_FITH = 0;
const byte TWO_FITH = 1;
const byte THREE_FITH = 2;
const byte FOUR_FITH = 3;
const char FULL = (char)0xFF;

class Lcd1602RgbDriver : public DriverBase, public DFRobot_RGBLCD1602 {
    private:
        String name;
    public:
        Lcd1602RgbDriver(String name, TwoWire *wire = &Wire, uint8_t lcdAddr=LCD_ADDRESS,uint8_t RGBAddr=RGB_ADDRESS);

        String getName() { return name; }
        void loop();

        void setRGB(const CRGB &color);
        void drawBar(float value);
};