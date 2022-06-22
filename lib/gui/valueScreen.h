#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>

#include "lcd.h"
#include "rotary.h"

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
            getLcd()->setCursor(strlen(this->name) + 2, 0);

            size_t valueLength = getLcd()->print(this->value);

            for (size_t i = 0; i < maxValueLength-valueLength; i++)
            {
                getLcd()->print(' ');
            }

            getLcd()->setCursor(0, 1);
            lcdDrawBar((float)this->value / (this->maxValue - this->minValue));
        }

        void enter() {
            this->onLoad();

            getLcd()->command(LCD_CLEARDISPLAY);
            getLcd()->print(this->name);
            getLcd()->print(": ");

            this->draw();
        }

        void loop() {
            if (getRotaryDirection() != None) {
                this->value += (getRotaryDelta() * abs(getRotaryDelta())) * stepSize
;
                this->value = constrain(this->value, this->minValue, this->maxValue);

                this->draw();
                this->onValueChanged(this->value);
            }
        }

        void exit() {
            this->onSave();
        }
};