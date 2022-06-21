#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "config.h"
#include "leds.h"
#include "buttons.h"
#include "lcd.h"
#include "menu.h"
#include "brightnessSelector.h"

StateMachine menuStateMachine;

/* ------------ States ------------- */
class BrowsingState : public State {
    public:
        void enter() {
            menuSetup();
        };
        void loop() {
            menuLoop();
        };
        void exit() {

        };
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

/* ------------ Transitions ------------- */
bool browsingToEffectsTransition() {
    return isButtonPressed(0) && getMenuSelectedEntry() == 0;
}

bool browsingToBrightnessTransition() {
    return isButtonPressed(0) && getMenuSelectedEntry() == 1;
}

bool browsingToConfigTransition() {
    return isButtonPressed(0) && getMenuSelectedEntry() == 2;
}

bool toBrowsingTransition() {
    return isButtonLongPressed(0);
}

bool brightnessToBrowsingTransition() {
    return isButtonPressed(0);
}

bool configToBrowsingTransition() {
    return true;
}


void menuStateMachineSetup() {
    menuStateMachine.addState(&browsingState);
    menuStateMachine.addState(&effectsState);
    menuStateMachine.addState(&brightnessState);
    menuStateMachine.addState(&configState);

    browsingState.addTransition(&browsingToEffectsTransition, &effectsState);
    browsingState.addTransition(&browsingToBrightnessTransition, &brightnessState);
    browsingState.addTransition(&browsingToConfigTransition, &configState);

    effectsState.addTransition(&toBrowsingTransition, &browsingState);

    brightnessState.addTransition(&brightnessToBrowsingTransition, &browsingState);

    configState.addTransition(&configToBrowsingTransition, &browsingState);
}

void menuStateMachineLoop() {
    menuStateMachine.run();
}