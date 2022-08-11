#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "leds.h" 
#include "ledsMap.h"
#include "flash.h"
#include "accelGyro.h"
#include "can.h"

#include "timing.h"
#include "effects.h"

#include "mainStateMachine.h"

#include "hardware.h"

void setup() {
    Serial.begin(115200);

    hardwareSetup();

    /*while (!Serial) {
        delay(100);
    }*/

    if (!flashSetup()) {
        lcdScreen->clear();
        lcdScreen->print("Storage failed!");
        delay(3000);
    }

    if (!configSetup()) {
        lcdScreen->clear();
        lcdScreen->print("Config failed!");
        lcdScreen->setCursor(0, 1);
        lcdScreen->print("Create config...");
        delay(3000);
    }

    // hardware
    ledsSetup();
    
    // state machines
    mainStateMachineSetup();
    effectsSetup();

    timingSetup();

    canSetup();
    
    lcdScreen->setRGB(CRGB::White);
    lcdScreen->clear();
}

void loop() {
    hardwareLoop();
    canLoop();

    ledsLoop();

    mainStateMachineLoop();

    timingLoop();
    effectsLoop();
}