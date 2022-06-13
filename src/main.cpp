#include <Arduino.h>
#include <FastLED.h>

//#include "config.h"
#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"
#include "buttons.h"
#include "flash.h"

#include "menuStateMachine.h"

void setup() {
    Serial.begin(115200);
    Serial.println("init");

    lcdSetup();

    // init message
    lcdSetColor(CRGB::Red);
    getLcd()->print("Initializing...");

    flashSetup();
    configSetup();

    // hardware
    ledsSetup();
    rotarySetup();
    buttonsSetup();

    ledsFill(getConfig()->color);

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