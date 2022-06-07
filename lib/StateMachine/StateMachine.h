#pragma once

#include "State.h"

class StateMachine {
    private:
        State* currentState;

    public:
        StateMachine() {
            currentState = NULL;
        };

        /**
         * @brief Sets the current state of the state machine.
         * 
         * calls onEntry() on the new state
         * calls onExit() on the old state
         * 
         * @param state state to set to
         */
        void setState(State* state) {
            if (currentState != NULL) {
                currentState->onExit();
            }
            currentState = state;
            currentState->onEntry();
        };

        void loop() {
            if (currentState == NULL) return;

            for (uint8_t i = 0; i < currentState->getConditionsCount(); i++) {
                Condition *condition = currentState->getConditions()[i];
                if (condition->isMet()) {
                    setState((State *)condition->getTo());
                    break;
                }
            }

            currentState->onLoop();
        };
};