#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"
#include "buttons.h"
#include "flash.h"
#include "accelGyro.h"

#include "timing.h"
#include "effects.h"

#include "mainStateMachine.h"

void setup() {
    Serial.begin(115200);

    /* while (!Serial) {
        delay(100);
    } */

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
    //accelGyroSetup();
    
    // state machines
    mainStateMachineSetup();
    effectsSetup();

    lcdSetColor(CRGB::White);
    getLcd()->clear();

    timingSetup();
}

void loop() {
    ledsLoop();
    rotaryLoop();
    buttonsLoop();
    //accelGyroLoop();

    mainStateMachineLoop();

    timingLoop();
    effectsLoop();
}