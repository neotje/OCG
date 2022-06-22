#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>

#include "lcd.h"
#include "rotary.h"

class MenuScreen : public State {
    private:
        LinkedList<char *> * entries;
        int selectedEntry;

        void draw() {
            getLcd()->command(LCD_CLEARDISPLAY);

            getLcd()->print(this->entries->get(selectedEntry));

            if (this->selectedEntry != 0) {
                getLcd()->setCursor(0, 1);
                getLcd()->print("<");
            }

            if (this->selectedEntry != entries->size() - 1) {
                getLcd()->setCursor(15, 1);
                getLcd()->print(">");
            }
        }
    
    public:
        MenuScreen() {
            this->entries = new LinkedList<char *>();
            selectedEntry = 0;
        }
        ~MenuScreen() {}

        int getSelectedEntry() {
            return this->selectedEntry;
        }

        char * getSelectedEntryName() {
            return this->entries->get(this->selectedEntry);
        }

        void addMenuEntry(char * entry) {
            this->entries->add(entry);
        }

        void enter() {
            this->draw();
        }

        void loop() {
            if (getRotaryDirection() != None) {

                selectedEntry += getRotaryDelta();
                selectedEntry = constrain(selectedEntry, 0, this->entries->size() - 1);

                this->draw();
            }
        }

        void exit() {}
};
