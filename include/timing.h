#pragma once

#include <Arduino.h>

double deltaTime = 0;
unsigned long lastTimingTime = 0;

double getDeltaTime() {
    return deltaTime;
}

void timingSetup() {
    lastTimingTime = millis();
}

void timingLoop() {
    deltaTime = (double)(millis() - lastTimingTime) / 1000.0;
    lastTimingTime = millis();
}