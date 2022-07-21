#pragma once

#include <Arduino.h>

class DriverBase {
    public:
        virtual String getName() = 0;
        virtual void loop() = 0;
};