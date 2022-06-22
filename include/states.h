#pragma once

#include <Arduino.h>
#include <StateMachine.h>

#include "menu.h"
#include "lcd.h"
#include "config.h"
#include "brightnessSelector.h"

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

class BrightnessState : public State {
    public:
        void enter() {
            brightnessSelectorSetup();
        };
        void loop() { 
            brightnessSelectorLoop();
        };
        void exit() { 
            saveConfig();
        };
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