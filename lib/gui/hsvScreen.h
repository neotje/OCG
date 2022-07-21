#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>
#include <FastLED.h>

#include "hardware.h"

class HSVScreen : public State {
    private:
        CHSV color;
        CRGB lcdColor = CRGB::White;

        int currentSelected;
        bool editing;

        char components[3] = {
            'H', 'S', 'V'
        };
    
    public:
        HSVScreen() {
            this->color = CHSV(0, 0, 0);
        }
        ~HSVScreen() {}

        void setColor(CHSV color) {
            this->color = color;
        }

        virtual void onLoad() = 0;
        virtual void onColorChange(CHSV color) = 0;
        virtual void onSave(CHSV color) = 0;

        void drawTop() {
            lcdScreen->setCursor(1, 0);

            char selectedChar = '-'; 
            if (this->editing) {
                selectedChar = '|';
            }

            for (size_t i = 0; i < 3; i++) {
                if(this->currentSelected == i) {
                    lcdScreen->print(selectedChar);
                    lcdScreen->print(this->components[i]);
                    lcdScreen->print(selectedChar);
                } else {
                    lcdScreen->print(" ");
                    lcdScreen->print(this->components[i]);
                    lcdScreen->print(" ");
                }

                lcdScreen->print("  ");
            }
            
        }

        void drawBottom() {
            int x = 2;

            for (size_t i = 0; i < 3; i++) {
                lcdScreen->setCursor(x, 1);

                size_t valueLength = lcdScreen->print(this->color[i]);

                for (size_t i = 0; i < 3-valueLength; i++)
                {
                    lcdScreen->print(' ');
                }

                x += 5;
            }
            
        }

        void enter() {
            this->currentSelected = 0;
            this->editing = false;

            this->onLoad();

            lcdScreen->clear();

            drawTop();
            drawBottom();
        }

        int loop() {
            if (this->editing) {
                if (rotaryEncoder->getDeltaPosition() != 0) {
                    this->color[this->currentSelected] += rotaryEncoder->getDeltaPosition();

                    this->onColorChange(this->color);

                    drawBottom();

                    lcdScreen->setRGB(lcdColor.setHSV(this->color.hue, this->color.sat, constrain(this->color.val, 60, 255)));
                }

                if (rotaryButton->isPressed()) {
                    this->editing = false;
                    this->onSave(this->color);
                    drawTop();
                    lcdScreen->setRGB(CRGB::Gray);
                }
            } else {
                if (rotaryEncoder->getDeltaPosition() != 0) {
                    this->currentSelected += rotaryEncoder->getDeltaPosition();

                    if (this->currentSelected < 0) {
                        this->currentSelected = 2;
                    } else if (this->currentSelected > 2) {
                        this->currentSelected = 0;
                    }

                    drawTop();
                }

                if (rotaryButton->isPressed()) {
                    this->editing = true;
                    drawTop();
                }
            }

            return -1;
        }

        void exit() {
            this->onSave(this->color);
        }
};