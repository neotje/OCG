#pragma once

#include <Arduino.h>
#include <StateMachine.h>

#include "lcd.h"
#include "config.h"
#include "valueScreen.h"
#include "hsvScreen.h"
#include "rgbScreen.h"
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


class SolidHSVScreen : public HSVScreen {
    public:
        SolidHSVScreen() {}
        ~SolidHSVScreen() {}

        void onLoad() {
            setColor(getConfig()->color);
        }

        void onSave(CHSV value) {
            getConfig()->color = value;
            saveConfig();
        }

        void onColorChange(CHSV value) {
            getConfig()->color = value;
        }
};
SolidHSVScreen solidHSVScreen;


class TwinkleDelaySelector : public ValueScreen {
    public:
        TwinkleDelaySelector() : ValueScreen(1, 1000, "Delay", 1) {}
        ~TwinkleDelaySelector() {}

        void onValueChanged(int value) {
            getConfig()->twinkleEffect.delay = value;
        }

        void onLoad() {
            this->setValue(getConfig()->twinkleEffect.delay);
        }

        void onSave() {
            saveConfig();
        }
};
TwinkleDelaySelector twinkleDelaySelector;

class TwinkleFractionSelector : public ValueScreen {
    public:
        TwinkleFractionSelector() : ValueScreen(1, 20, "Fraction", 1) {}
        ~TwinkleFractionSelector() {}

        void onValueChanged(int value) {
            getConfig()->twinkleEffect.fraction = value;
        }

        void onLoad() {
            this->setValue(getConfig()->twinkleEffect.fraction);
        }

        void onSave() {
            saveConfig();
        }
};
TwinkleFractionSelector twinkleFractionSelector;

class TwinkleConfigScreen : public MenuScreen {
    public:
        TwinkleConfigScreen() {
            this->addMenuEntry("Delay", &twinkleDelaySelector);
            this->addMenuEntry("Fraction", &twinkleFractionSelector);
        }
        ~TwinkleConfigScreen() {}

        int onClick(int entryIndex) { return -1; }
};
TwinkleConfigScreen twinkleConfigScreen;


class MarqueeDelaySelector : public ValueScreen {
    public:
        MarqueeDelaySelector() : ValueScreen(1, 500, "Delay", 1) {}
        ~MarqueeDelaySelector() {}

        void onValueChanged(int value) {
            getConfig()->marqueeEffect.delay = value;
        }

        void onLoad() {
            this->setValue(getConfig()->marqueeEffect.delay);
        }

        void onSave() {
            saveConfig();
        }
};
MarqueeDelaySelector marqueeDelaySelector;

class MarqueeBlackSpacingSelector : public ValueScreen {
    public:
        MarqueeBlackSpacingSelector() : ValueScreen(3, 20, "Black space", 1) {}
        ~MarqueeBlackSpacingSelector() {}

        void onValueChanged(int value) {
            getConfig()->marqueeEffect.blackSpacing = value;
        }

        void onLoad() {
            this->setValue(getConfig()->marqueeEffect.blackSpacing);
        }

        void onSave() {
            saveConfig();
        }
};
MarqueeBlackSpacingSelector marqueeBlackSpacingSelector;

class MarqueeConfigScreen : public MenuScreen {
    public:
        MarqueeConfigScreen() {
            this->addMenuEntry("Delay", &marqueeDelaySelector);
            this->addMenuEntry("Black Spacing", &marqueeBlackSpacingSelector);
        }
        ~MarqueeConfigScreen() {}

        int onClick(int entryIndex) { return -1; }
};
MarqueeConfigScreen marqueeConfigScreen;


class FlashDelaySelector : public ValueScreen {
    public:
        FlashDelaySelector() : ValueScreen(50, 2000, "Delay", 50) {}
        ~FlashDelaySelector() {}

        void onValueChanged(int value) {
            getConfig()->flashEffect.delay = value;
        }

        void onLoad() {
            this->setValue(getConfig()->flashEffect.delay);
        }

        void onSave() {
            saveConfig();
        }
};
FlashDelaySelector flashDelaySelector;

class FlashColorSelector : public RGBScreen {
    private:
        int index;
    public:
        FlashColorSelector(int index) {
            this->index = index;
        }
        ~FlashColorSelector() {}

        void onLoad() {
            setColor(getConfig()->flashEffect.colors[index]);
        }

        void onSave(CRGB value) {
            getConfig()->flashEffect.colors[index] = value;
            saveConfig();
        }

        void onColorChange(CRGB value) {
            getConfig()->flashEffect.colors[index] = value;
        }
};
FlashColorSelector flashColor0Selector(0);
FlashColorSelector flashColor1Selector(1);
FlashColorSelector flashColor2Selector(2);

class FlashConfigScreen : public MenuScreen {
    public:
        FlashConfigScreen() {
            this->addMenuEntry("Delay", &flashDelaySelector);
            this->addMenuEntry("Color 0", &flashColor0Selector);
            this->addMenuEntry("Color 1", &flashColor1Selector);
            this->addMenuEntry("Color 2", &flashColor2Selector);
        }
        ~FlashConfigScreen() {}

        int onClick(int entryIndex) { return -1; }
};
FlashConfigScreen flashConfigScreen;

class MainMenuState : public MenuScreen {
    public:
        MainMenuState() { }
        ~MainMenuState() { }

        int onClick(int entryIndex) {
            if (entryIndex == 2) {
                switch (getConfig()->currentEffect) {
                    case 0:
                        return rainbowConfigScreen.index;
                    case 1:
                        return solidHSVScreen.index;
                    case 2:
                        return twinkleConfigScreen.index;
                    case 3:
                        return marqueeConfigScreen.index;
                    case 4:
                        return flashConfigScreen.index;
                };
            }

            return -1;
        }
};
MainMenuState mainMenuState;

class EffectSelectState : public MenuScreen {
    public:
        EffectSelectState() { }
        ~EffectSelectState() { }

        int onClick(int entryIndex) {
            setEffect(entryIndex);
            return mainMenuState.index;
        }

        void enter() {
            this->clearMenuEntries();
            
            for (uint8_t i = 0; i < getEffectsCount(); i++) {
                this->addMenuEntry(getEffect(i)->getName());
            }

            this->setSelectedEntry(getConfig()->currentEffect);
        }
};
EffectSelectState effectSelectState;

class BrightnessSelectState : public ValueScreen {
    public:
        BrightnessSelectState() : ValueScreen(0, 255, "Brightness", 1) { }
        ~BrightnessSelectState() {}

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
BrightnessSelectState brightnessSelectState;
