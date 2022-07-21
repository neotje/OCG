#pragma once

#include <Arduino.h>
#include <pins.h>
#include <hardwareManager.h>

HardwareManager *hardwareManager;
ButtonDriver *rotaryButton;
RotaryDriver *rotaryEncoder;

void hardwareSetup() {
    hardwareManager = new HardwareManager();

    rotaryButton = new ButtonDriver("rotaryButton", BUTTON1_PIN, LOW);
    hardwareManager->addHardware(rotaryButton);

    rotaryEncoder = new RotaryDriver("rotaryEncoder", ROTARY_CLK_PIN, ROTARY_DT_PIN);
    hardwareManager->addHardware(rotaryEncoder);
}

void hardwareLoop() {
    hardwareManager->loop();
}