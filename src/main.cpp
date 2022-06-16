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

#include "menuStateMachine.h"

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
    menuStateMachineSetup();

    lcdSetColor(CRGB::Gray);
    getLcd()->clear();

    timingSetup();
}

void loop() {
    ledsLoop();
    rotaryLoop();
    buttonsLoop();
    //accelGyroLoop();

    menuStateMachineLoop();

    timingLoop();
    rainbowEffect();
}