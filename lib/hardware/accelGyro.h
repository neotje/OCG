#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "types.h"

const int MPU_ADDRESS = 0x68;

AccelGyroData accelGyroData = {
    0, 0, 0, 0, 0, 0, 0
};

AccelGyroData *getAccelGyroData() {
    return &accelGyroData;
}

char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void accelGyroSetup() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);
}

void accelGyroLoop() {
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 14, true);

    accelGyroData.accelX = Wire.read() << 8 | Wire.read();
    accelGyroData.accelY = Wire.read() << 8 | Wire.read();
    accelGyroData.accelZ = Wire.read() << 8 | Wire.read();
    accelGyroData.temp = Wire.read() << 8 | Wire.read();
    accelGyroData.gyroX = Wire.read() << 8 | Wire.read();
    accelGyroData.gyroY = Wire.read() << 8 | Wire.read();
    accelGyroData.gyroZ = Wire.read() << 8 | Wire.read();
}