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

    lcdSetup();

    // init message
    lcdSetColor(CRGB::Red);
    getLcd()->print("Initializing...");
    Serial.println("init");

    /*while (!Serial) {
        delay(100);
    }*/

    if (!flashSetup()) {
        getLcd()->clear();
        getLcd()->print("Storage failed!");
        delay(3000);
    }

    if (!configSetup()) {
        getLcd()->clear();
        getLcd()->print("Config failed!");
        getLcd()->setCursor(0, 1);
        getLcd()->print("Create config...");
        delay(3000);
    }

    // hardware
    ledsSetup();
    rotarySetup();
    buttonsSetup();
    //accelGyroSetup();
    
    // state machines
    mainStateMachineSetup();
    effectsSetup();

    timingSetup();
    
    lcdSetColor(CRGB::White);
    getLcd()->clear();
}

void loop() {
    ledsLoop();
    rotaryLoop();
    buttonsLoop();
    //accelGyroLoop();

    mainStateMachineLoop();

    timingLoop();
    effectsLoop();

    if(isButtonDown(0) && millis() - getButtonPressStart(0) > LONG_PRESS_TIME) {
        lcdSetColor(CRGB::Red);
    } else {
        lcdSetColor(CRGB::White);
    }
}