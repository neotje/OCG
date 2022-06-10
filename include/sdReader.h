#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "pins.h"
#include "buttons.h"

void sdReaderSetup() {
    while(!SD.begin(CS_PIN)) {

        buttonsLoop();

        if (isButtonLongPressed(0)) {
            break;
        }
    }
}