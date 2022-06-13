#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>

#include "ff.h"
#include "diskio.h"

#include "pins.h"

Adafruit_FlashTransport_QSPI flashTransport;
Adafruit_SPIFlash flash(&flashTransport);

FatFileSystem fs;

bool flashFormat() {
    FATFS fatfs;
    uint8_t workBuf[4096];

    Serial.println("Formatting flash...");

    FRESULT r = f_mkfs("", FM_FAT | FM_SFD, 0, workBuf, sizeof(workBuf));

    if (r != FR_OK) {
        Serial.print("Error, f_mkfs failed with error code: "); Serial.println(r, DEC);
        return false;
    }

    r = f_mount(&fatfs, "0:", 1);
    if (r != FR_OK) {
        Serial.print("Error, f_mount failed with error code: "); Serial.println(r, DEC);
        return false;
    }

    r = f_setlabel("");
    if (r != FR_OK) {
        Serial.print("Error, f_setlabel failed with error code: "); Serial.println(r, DEC);
        return false;
    }

    f_unmount("0:");

    flash.syncBlocks();

    Serial.println("Formatted flash!");

    return true;
}

void flashSetup() {
    if (!flash.begin()) {
        Serial.println("Could initialize flash");
        return;
    }

    if (!fs.begin(&flash)) {
        Serial.println("Could not mount flash");
        return;
    }

    Serial.print("JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);
    Serial.print("Flash size: "); Serial.print(flash.size() / 1024); Serial.println(" KB");
    Serial.print("Fat type: "); Serial.println(fs.fatType());
    Serial.print("File count: "); fs.ls(LS_R | LS_SIZE);
}