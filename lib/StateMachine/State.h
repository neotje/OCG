#pragma once

#include <Arduino.h>
#include "Condition.h"

class State {
    private:
        // array of pointers to conditions
        Condition** conditions;
        uint8_t conditionsCount;

    public:
        State() {};

        /**
         * @brief Adds a condition to the state.
         * 
         * @param condition condition to add
         */
        void addCondition(Condition* condition) {
            conditions = (Condition**)realloc(conditions, sizeof(Condition*) * (conditionsCount + 1));
            conditions[conditionsCount] = condition;
            conditionsCount++;
        }

        Condition** getConditions() {
            return conditions;
        }

        uint8_t getConditionsCount() {
            return conditionsCount;
        }

        virtual void onEntry() = 0;
        virtual void onLoop() = 0;
        virtual void onExit()= 0;
};