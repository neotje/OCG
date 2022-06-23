#pragma once

#include <Arduino.h>
#include <StateMachine.h>

#include "lcd.h"
#include "config.h"
#include "valueScreen.h"
#include "menuScreen.h"
#include "effects.h"

StateMachine mainStateMachine;

/* ------------ States ------------- */

class RainbowSpeedSelector : public ValueScreen {
    public:
        RainbowSpeedSelector() : ValueScreen(1, 500, "Speed", 1) {}
        ~RainbowSpeedSelector() {}

        void onValueChanged(int value) {
            getConfig()->rainbowEffect.speed = (double)value;
        }

        void onLoad() {
            this->setValue(getConfig()->rainbowEffect.speed);
        }

        void onSave() {
            saveConfig();
        }
};
RainbowSpeedSelector rainbowSpeedSelector;

class RainbowDeltaHueSelector : public ValueScreen {
    public:
        RainbowDeltaHueSelector() : ValueScreen(1, 255, "Delta Hue", 1) {}
        ~RainbowDeltaHueSelector() {}

        void onValueChanged(int value) {
            getConfig()->rainbowEffect.deltaHue = value;
        }

        void onLoad() {
            this->setValue(getConfig()->rainbowEffect.deltaHue);
        }

        void onSave() {
            saveConfig();
        }
};
RainbowDeltaHueSelector rainbowDeltaHueSelector;

class RainbowConfigScreen : public MenuScreen {
    public:
        RainbowConfigScreen() {
            this->addMenuEntry("Speed", &rainbowSpeedSelector);
            this->addMenuEntry("Delta Hue", &rainbowDeltaHueSelector);
        }
        ~RainbowConfigScreen() {}

        int onClick(int entryIndex) { return -1; }
};
RainbowConfigScreen rainbowConfigScreen;


class MainMenuState : public MenuScreen {
    public:
        MainMenuState() { }
        ~MainMenuState() { }

        int onClick(int entryIndex) {
            if (entryIndex == 2) {
                switch (getConfig()->currentEffect) {
                    case 0:
                        return rainbowConfigScreen.index;
                };
            }

            return -1;
        }
};
MainMenuState mainMenuState;

class EffectsState : public MenuScreen {
    public:
        EffectsState() { }
        ~EffectsState() { }

        int onClick(int entryIndex) {
            setEffect(entryIndex);
            return -1;
        }

        void enter() {
            this->clearMenuEntries();
            
            for (uint8_t i = 0; i < getEffectsCount(); i++) {
                this->addMenuEntry(getEffect(i)->getName());
            }

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
