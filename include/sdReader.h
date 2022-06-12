#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "pins.h"
#include "buttons.h"

void sdReaderSetup() {
    while(!SD.begin(SD_CS_PIN)) {

        buttonsLoop();

        if (isButtonLongPressed(0)) {
            Serial.println("SD card not found");
            break;
        }
    }
}