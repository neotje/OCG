#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "buttons.h"

const byte CS_PIN = 10;

void sdReaderSetup() {
    while(!SD.begin(CS_PIN)) {

        buttonsLoop();

        if (isButtonLongPressed(0)) {
            break;
        }
    }
}