#include <Arduino.h>
#include <FastLED.h>

#include "leds.h" 
#include "ledsMap.h"
#include "lcd.h"
#include "rotary.h"
#include "buttons.h"

#include "menuStateMachine.h"

void setup() {
    Serial.begin(9600);

    ledsSetup();
    lcdSetup();
    lcdSetColor(CRGB::Gray);
    rotarySetup();
    buttonsSetup();

    menuStateMachineSetup();
}

void loop() {
    ledsLoop();
    rotaryLoop();
    buttonsLoop();

    menuStateMachineLoop();
}