#pragma once

#include <Arduino.h>
#include <StateMachine.h>

#include "lcd.h"
#include "config.h"
#include "valueScreen.h"
#include "menuScreen.h"

/* ------------ States ------------- */
class BrowsingState : public MenuScreen {
    public:
        BrowsingState() {
            this->addMenuEntry("Effects");
            this->addMenuEntry("Brightness");
            this->addMenuEntry("Config");
        }
        ~BrowsingState() {}
};

BrowsingState browsingState;

class EffectsState : public State {
    public:
        void enter() {
            getLcd()->clear();
        };
        void loop() { };
        void exit() { };
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
        void loop() { };
        void exit() { };
};

ConfigState configState;