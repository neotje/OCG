#pragma once

#include <Arduino.h>
#include <StateMachine.h>
#include <LinkedList.h>

#include "lcd.h"
#include "rotary.h"
#include "hardware.h"

struct MenuEntry {
    const char* name;
    State* state;
};

class MenuScreen : public State {
    private:
        LinkedList<MenuEntry *> * entries;
        int selectedEntry;

        void draw() {
            getLcd()->command(LCD_CLEARDISPLAY);

            getLcd()->print(this->entries->get(selectedEntry)->name);

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
            this->entries = new LinkedList<MenuEntry *>();
            selectedEntry = 0;
        }
        ~MenuScreen() {}

        int getSelectedEntry() {
            return this->selectedEntry;
        }

        void setSelectedEntry(int entry) {
            this->selectedEntry = entry;
            this->draw();
        }

        const char * getSelectedEntryName() {
            return (this->entries->get(this->selectedEntry))->name;
        }

        State * getSelectedEntryState() {
            return (this->entries->get(this->selectedEntry))->state;
        }

        void addMenuEntry(const char * entryName, State * state = NULL) {
            MenuEntry * menuEntry = new MenuEntry{entryName, state};
            this->entries->add(menuEntry);
        }

        void clearMenuEntries() {
            this->entries->clear();
        }

        void enter() {
            this->draw();
        }

        int loop() {
            if (getRotaryDirection() != None) {

                selectedEntry += getRotaryDelta();
                selectedEntry = constrain(selectedEntry, 0, this->entries->size() - 1);

                this->draw();
            }

            int result = -1;

            if (rotaryButton->isPressed()) {
                result = this->onClick(selectedEntry);

                if (result != -1) {
                    return result;
                }

                if (getSelectedEntryState() != NULL) {
                    result = getSelectedEntryState()->index;
                }
            }
            
            return result;
        }

        void exit() {}

        virtual int onClick(int entryIndex) = 0;
};
