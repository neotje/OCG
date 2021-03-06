#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>

#include "hardware.h"

class ValueScreen : public State {
    private:
        int minValue;
        int maxValue;
        int value;
        int stepSize;
        char * name;

        size_t maxValueLength;

    public:
        ValueScreen(int minValue, int maxValue, char * name, int stepSize) {
            this->minValue = minValue;
            this->maxValue = maxValue;
            this->name = name;
            this->stepSize = stepSize;
            this->value = 0;

            this->maxValueLength = String(maxValue).length();
        }
        ~ValueScreen() {}

        void setValue(int value) {
            value = constrain(value, this->minValue, this->maxValue);
            this->value = value;
        }

        virtual void onValueChanged(int value) = 0;
        virtual void onLoad() = 0;
        virtual void onSave() = 0;

        void draw() {
            lcdScreen->setCursor(strlen(this->name) + 2, 0);

            size_t valueLength = lcdScreen->print(this->value);

            for (size_t i = 0; i < maxValueLength-valueLength; i++)
            {
                lcdScreen->print(' ');
            }

            lcdScreen->setCursor(0, 1);
            lcdScreen->drawBar((float)this->value / (this->maxValue - this->minValue));
        }

        void enter() {
            this->onLoad();

            lcdScreen->command(LCD_CLEARDISPLAY);
            lcdScreen->print(this->name);
            lcdScreen->print(": ");

            this->draw();
        }

        int loop() {
            if (rotaryEncoder->getDeltaPosition() != 0) {
                this->value += (rotaryEncoder->getDeltaPosition() * abs(rotaryEncoder->getDeltaPosition())) * stepSize
;
                this->value = constrain(this->value, this->minValue, this->maxValue);

                this->draw();
                this->onValueChanged(this->value);
            }

            return -1;
        }

        void exit() {
            this->onSave();
        }
};