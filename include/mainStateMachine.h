#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "leds.h"
#include "states.h"
#include "hardware.h"

/* ------------ Transitions ------------- */
bool oneClickTransition() {
    return rotaryButton->isPressed();
}

bool longPressTransition() {
    return rotaryButton->isLongPressed();
}

void mainStateMachineSetup() {
    mainStateMachine.addState(&mainMenuState);
    mainStateMachine.addState(&effectSelectState);
    mainStateMachine.addState(&brightnessSelectState);
    mainStateMachine.addState(&rainbowConfigScreen);
    mainStateMachine.addState(&rainbowSpeedSelector);
    mainStateMachine.addState(&rainbowDeltaHueSelector);
    mainStateMachine.addState(&solidHSVScreen);
    mainStateMachine.addState(&twinkleConfigScreen);
    mainStateMachine.addState(&twinkleDelaySelector);
    mainStateMachine.addState(&twinkleFractionSelector);
    mainStateMachine.addState(&marqueeConfigScreen);
    mainStateMachine.addState(&marqueeDelaySelector);
    mainStateMachine.addState(&marqueeBlackSpacingSelector);
    mainStateMachine.addState(&flashConfigScreen);
    mainStateMachine.addState(&flashDelaySelector);
    mainStateMachine.addState(&flashColor0Selector);
    mainStateMachine.addState(&flashColor1Selector);
    mainStateMachine.addState(&flashColor2Selector);

    mainMenuState.addMenuEntry("Effects", &effectSelectState);
    mainMenuState.addMenuEntry("Brightness", &brightnessSelectState);
    mainMenuState.addMenuEntry("Config");

    effectSelectState.addTransition(&longPressTransition, &mainMenuState);

    brightnessSelectState.addTransition(&oneClickTransition, &mainMenuState);

    rainbowConfigScreen.addTransition(&longPressTransition, &mainMenuState);
    rainbowSpeedSelector.addTransition(&oneClickTransition, &rainbowConfigScreen);
    rainbowDeltaHueSelector.addTransition(&oneClickTransition, &rainbowConfigScreen);

    solidHSVScreen.addTransition(&longPressTransition, &mainMenuState);

    twinkleConfigScreen.addTransition(&longPressTransition, &mainMenuState);
    twinkleDelaySelector.addTransition(&oneClickTransition, &twinkleConfigScreen);
    twinkleFractionSelector.addTransition(&oneClickTransition, &twinkleConfigScreen);

    marqueeConfigScreen.addTransition(&longPressTransition, &mainMenuState);
    marqueeDelaySelector.addTransition(&oneClickTransition, &marqueeConfigScreen);
    marqueeBlackSpacingSelector.addTransition(&oneClickTransition, &marqueeConfigScreen);

    flashConfigScreen.addTransition(&longPressTransition, &mainMenuState);
    flashDelaySelector.addTransition(&oneClickTransition, &flashConfigScreen);
    flashColor0Selector.addTransition(&longPressTransition, &flashConfigScreen);
    flashColor1Selector.addTransition(&longPressTransition, &flashConfigScreen);
    flashColor2Selector.addTransition(&longPressTransition, &flashConfigScreen);
}

void mainStateMachineLoop() {
    mainStateMachine.run();
}