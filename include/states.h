#pragma once

#include <Arduino.h>
#include <StateMachine.h>

#include "lcd.h"
#include "config.h"
#include "valueScreen.h"
#include "menuScreen.h"
#include "effects.h"

/* ------------ States ------------- */
class BrowsingState : public MenuScreen {
    public:
        BrowsingState() { }
        ~BrowsingState() { }

        void onClick(int entryIndex) { }
};

BrowsingState browsingState;

class EffectsState : public MenuScreen {
    public:
        EffectsState() { 
            for (uint8_t i = 0; i < getEffectsCount(); i++) {
                this->addMenuEntry(getEffect(i)->name);
            }
        }
        ~EffectsState() { }

        void onClick(int entryIndex) {
            setEffect(entryIndex);
        }

        void enter() {
            this->setSelectedEntry(getConfig()->currentEffect);
        }
};

EffectsState effectsState;

class BrightnessState : public ValueScreen {
    public:
        BrightnessState() : ValueScreen(0, 255, "Brightness", 255/80) { }
        ~BrightnessState() {}

        void onValueChanged(int value) {
            getConfig()->brightness = value;
        }

        void onLoad() {
            this->setValue(getConfig()->brightness);
        }

        void onSave() {
            saveConfig();
        }
};

BrightnessState brightnessState;

class ConfigState : public State {
    public:
        void enter() {
            resetConfig();
        };
        int loop() { return -1;};
        void exit() { };
};

ConfigState configState;