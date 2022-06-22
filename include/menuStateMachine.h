#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "leds.h"
#include "buttons.h"
#include "states.h"

StateMachine menuStateMachine;

/* ------------ Transitions ------------- */
bool browsingToEffectsTransition() {
    return isButtonPressed(0) && browsingState.getSelectedEntry() == 0;
}

bool browsingToBrightnessTransition() {
    return isButtonPressed(0) && browsingState.getSelectedEntry() == 1;
}

bool browsingToConfigTransition() {
    return isButtonPressed(0) && browsingState.getSelectedEntry() == 2;
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