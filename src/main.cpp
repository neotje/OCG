#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"
#include "buttons.h"
#include "sdReader.h"

#include "menuStateMachine.h"

void setup() {
    Serial.begin(9600);
    lcdSetup();

    // init message
    lcdSetColor(CRGB::Red);
    getLcd()->print("Initializing...");

    sdReaderSetup();
    configSetup();

    // hardware
    ledsSetup();
    rotarySetup();
    buttonsSetup();

    ledsFill(CRGB::White);

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