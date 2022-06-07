#pragma once

#include <Arduino.h>

#include "types.h"
#include "lcd.h"
#include "rotary.h"

const char *MENU_ENTRIES[] = {
    "Effects",
    "Brightness",
    "Config"
};

int8_t selectedEntry = 0;

int menuChangeTimeout = 200;
unsigned long lastMenuChange= 0;

void menuDraw() {
    getLcd()->clear();

    getLcd()->print(MENU_ENTRIES[selectedEntry]);

    if (selectedEntry != 0) {
        getLcd()->setCursor(0, 1);
        getLcd()->print("<");
    }

    if (selectedEntry != sizeof(MENU_ENTRIES) / sizeof(MENU_ENTRIES[0]) - 1) {
        getLcd()->setCursor(15, 1);
        getLcd()->print(">");
    }
}

void menuSetup() {
    menuDraw();
}

void menuLoop() {
    if (getRotaryDirection() != None && millis() - lastMenuChange > menuChangeTimeout) {
        lastMenuChange = millis();

        Serial.print("change: ");
        Serial.println(getRotaryDelta());

        if (getRotaryDelta() > 0) {
            selectedEntry++;
        } else if (getRotaryDelta() < 0) {
            selectedEntry--;
        }

        selectedEntry = constrain(selectedEntry, 0, sizeof(MENU_ENTRIES) / sizeof(MENU_ENTRIES[0]) - 1);

        menuDraw();
    }
    
}