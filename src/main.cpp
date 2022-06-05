#include <Arduino.h>
#include <FastLED.h>

#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"

void setup() {
    Serial.begin(9600);

    ledsSetup();
    lcdSetup();
    rotarySetup();

    lcdSetColor(CRGB::White);
}

void loop() {
    ledsLoop();
    rotaryLoop();

    getLcd()->setCursor(0, 0);
    getLcd()->print("P: ");
    getLcd()->print(getRotaryPosition());
    getLcd()->setCursor(0, 1);

    getLcd()->print("D: ");
    getLcd()->print(getRotaryDelta());
}