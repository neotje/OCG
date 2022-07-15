#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>

#include "pins.h"

Adafruit_FlashTransport_QSPI flashTransport;
Adafruit_SPIFlash flash(&flashTransport);

FatFileSystem fs;

bool flashSetup() {
    if (!flash.begin()) {
        Serial.println("Could initialize flash");
        return false;
    }

    if (!fs.begin(&flash)) {
        Serial.println("Could not mount flash");
        return false;
    }

    Serial.print("JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);
    Serial.print("Flash size: "); Serial.print(flash.size() / 1024); Serial.println(" KB");
    Serial.print("Fat type: "); Serial.println(fs.fatType());
    Serial.print("File count: "); fs.ls(LS_R | LS_SIZE);

    return true;
}