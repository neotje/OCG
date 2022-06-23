#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "leds.h"
#include "buttons.h"
#include "states.h"


/* ------------ Transitions ------------- */
bool oneClickTransition() {
    return isButtonPressed(0);
}

bool longPressTransition() {
    return isButtonLongPressed(0);
}

void mainStateMachineSetup() {
    mainStateMachine.addState(&mainMenuState);
    mainStateMachine.addState(&effectSelectState);
    mainStateMachine.addState(&brightnessSelectState);
    mainStateMachine.addState(&rainbowConfigScreen);
    mainStateMachine.addState(&rainbowSpeedSelector);
    mainStateMachine.addState(&rainbowDeltaHueSelector);

    mainMenuState.addMenuEntry("Effects", &effectSelectState);
    mainMenuState.addMenuEntry("Brightness", &brightnessSelectState);
    mainMenuState.addMenuEntry("Config");

    effectSelectState.addTransition(&longPressTransition, &mainMenuState);

    brightnessSelectState.addTransition(&oneClickTransition, &mainMenuState);

    rainbowConfigScreen.addTransition(&longPressTransition, &mainMenuState);
    rainbowSpeedSelector.addTransition(&oneClickTransition, &rainbowConfigScreen);
    rainbowDeltaHueSelector.addTransition(&oneClickTransition, &rainbowConfigScreen);
}

void mainStateMachineLoop() {
    mainStateMachine.run();
}