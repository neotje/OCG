#include <Arduino.h>
#include <FastLED.h>

#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"
#include "buttons.h"
#include "sdReader.h"

#include "menuStateMachine.h"

void setup() {
    lcdSetup();

    // init message
    lcdSetColor(CRGB::Red);
    getLcd()->print("Initializing...");

    Serial.begin(9600);

    // hardware
    ledsSetup();
    rotarySetup();
    buttonsSetup();
    sdReaderSetup();

    // state machines
    menuStateMachineSetup();

    lcdSetColor(CRGB::Gray);
    getLcd()->clear();
}

void loop() {
    ledsLoop();
    rotaryLoop();
    buttonsLoop();

    menuStateMachineLoop();
}