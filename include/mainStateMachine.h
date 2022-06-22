#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "leds.h"
#include "buttons.h"
#include "states.h"

StateMachine menuStateMachine;

/* ------------ Transitions ------------- */
bool toBrowsingTransition() {
    return isButtonLongPressed(0);
}

bool brightnessToBrowsingTransition() {
    return isButtonPressed(0);
}

bool configToBrowsingTransition() {
    return true;
}

void mainStateMachineSetup() {
    menuStateMachine.addState(&browsingState);
    menuStateMachine.addState(&effectsState);
    menuStateMachine.addState(&brightnessState);
    menuStateMachine.addState(&configState);

    browsingState.addMenuEntry("Effects", &effectsState);
    browsingState.addMenuEntry("Brightness", &brightnessState);
    browsingState.addMenuEntry("Config", &configState);

    effectsState.addTransition(&toBrowsingTransition, &browsingState);

    brightnessState.addTransition(&brightnessToBrowsingTransition, &browsingState);

    configState.addTransition(&configToBrowsingTransition, &browsingState);
}

void mainStateMachineLoop() {
    menuStateMachine.run();
}