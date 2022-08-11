#pragma once

#include <Arduino.h>
#include <neoCAN.h>
#include "config.h"
#include "effects.h"

const uint16_t DEVICE_ID = 1000;
const uint16_t CONFIG_CHANNEL = 1;
const uint16_t EFFECT_CHANNEL = 2;

NCDevice* ncDevice;
SDOHost* configHost;

void onConfigRecieve(uint8_t *data, uint8_t length) {
    if (length != getConfigSize()) return;

    memcpy(getConfig(), data, length);

    setEffect(getConfig()->currentEffect);
}

void canSetup() {
    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, LOW);

    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, HIGH);

    if (!CAN.begin(250000)) {
        Serial.println("CAN initialization failed");
    }

    ncDevice = new NCDevice(DEVICE_ID, &CAN);
    configHost = new SDOHost(ncDevice, CONFIG_CHANNEL);

    configHost->addCallback(onConfigRecieve);
    configHost->setData((uint8_t *)getConfig(), getConfigSize());
}

void canLoop() {
    ncDevice->loop();
}