#pragma once

#include <Arduino.h>
#include <Encoder.h>
#include "driverBase.h"

class RotaryDriver : public DriverBase, private Encoder {
    private:
        String name;
        int32_t deltaPosition;
        int32_t positionFraction;
    public:
        RotaryDriver(String name, int pin1, int pin2);

        String getName() { return name; }
        int32_t getDeltaPosition() { return deltaPosition; };
        void loop();
};