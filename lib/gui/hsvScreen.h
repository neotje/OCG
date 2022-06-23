#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>
#include <FastLED.h>

#include "lcd.h"
#include "rotary.h"
#include "buttons.h"

class HSVScreen : public State {
    private:
        CHSV color;

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
            getLcd()->setCursor(1, 0);

            char selectedChar = '-'; 
            if (this->editing) {
                selectedChar = '|';
            }

            for (size_t i = 0; i < 3; i++) {
                if(this->currentSelected == i) {
                    getLcd()->print(selectedChar);
                    getLcd()->print(this->components[i]);
                    getLcd()->print(selectedChar);
                } else {
                    getLcd()->print(" ");
                    getLcd()->print(this->components[i]);
                    getLcd()->print(" ");
                }

                getLcd()->print("  ");
            }
            
        }

        void drawBottom() {
            int x = 2;

            for (size_t i = 0; i < 3; i++) {
                getLcd()->setCursor(x, 1);

                size_t valueLength = getLcd()->print(this->color[i]);

                for (size_t i = 0; i < 3-valueLength; i++)
                {
                    getLcd()->print(' ');
                }

                x += 5;
            }
            
        }

        void enter() {
            this->currentSelected = 0;
            this->editing = false;

            this->onLoad();

            getLcd()->clear();

            drawTop();
            drawBottom();
        }

        int loop() {
            if (this->editing) {
                if (getRotaryDirection() != None) {
                    this->color[this->currentSelected] += getRotaryDelta();

                    this->onColorChange(this->color);

                    drawBottom();
                }

                if (isButtonPressed(0)) {
                    this->editing = false;
                    this->onSave(this->color);
                    drawTop();
                }
            } else {
                if (getRotaryDirection() != None) {
                    this->currentSelected += getRotaryDelta();

                    if (this->currentSelected < 0) {
                        this->currentSelected = 2;
                    } else if (this->currentSelected > 2) {
                        this->currentSelected = 0;
                    }

                    drawTop();
                }

                if (isButtonPressed(0)) {
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