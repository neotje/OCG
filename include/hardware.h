#pragma once

#include <Arduino.h>
#include <pins.h>
#include <hardwareManager.h>

HardwareManager *hardwareManager;
ButtonDriver *rotaryButton;

void hardwareSetup() {
    hardwareManager = new HardwareManager();

    rotaryButton = new ButtonDriver("rotaryButton", BUTTON1_PIN, LOW);
    hardwareManager->addHardware(rotaryButton);
}

void hardwareLoop() {
    hardwareManager->loop();
}