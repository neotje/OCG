#pragma once

#include <Arduino.h>

#include <StateMachine.h>

#include "buttons.h"
#include "lcd.h"
#include "menu.h"

StateMachine menuStateMachine;


/* ------------ States ------------- */
void BrowsingState() {
    if (menuStateMachine.executeOnce) {
        menuSetup();
    }

    menuLoop();
}

void EffectsState() {
    if (menuStateMachine.executeOnce) {
        getLcd()->clear();
    }
}

void BrightnessState() {
    if (menuStateMachine.executeOnce) {
        getLcd()->clear();
    }
}

void ConfigState() {
    if (menuStateMachine.executeOnce) {
        getLcd()->clear();
    }
}

State* browsingState = menuStateMachine.addState(&BrowsingState);
State* effectsState = menuStateMachine.addState(&EffectsState);
State* brightnessState = menuStateMachine.addState(&BrightnessState);
State* configState = menuStateMachine.addState(&ConfigState);


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


void menuStateMachineSetup() {
    browsingState->addTransition(&browsingToEffectsTransition, effectsState);
    browsingState->addTransition(&browsingToBrightnessTransition, brightnessState);
    browsingState->addTransition(&browsingToConfigTransition, configState);

    effectsState->addTransition(&toBrowsingTransition, browsingState);
    brightnessState->addTransition(&toBrowsingTransition, browsingState);
    configState->addTransition(&toBrowsingTransition, browsingState);
}

void menuStateMachineLoop() {
    menuStateMachine.run();
}