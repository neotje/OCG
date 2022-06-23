#pragma once

#include <Arduino.h>

class Effect {
    private:
        const char *name;

    public:
        Effect(const char *name) {
            this->name = name;
        }
        ~Effect() { }

        const char* getName() {
            return name;
        }

        virtual void setup() = 0;
        virtual void run() = 0;
};