#pragma once

#include <Arduino.h>

class HardwareManager;
class DriverBase {
    private:
        HardwareManager* hardwareManager;
    public:
        DriverBase() {
            this->hardwareManager = nullptr;
        }
        ~DriverBase() {}

        virtual void setHardwareManager(HardwareManager* hardwareManager) final;
        virtual HardwareManager* getHardwareManager() final;

        virtual String getName() = 0;
        virtual void loop() = 0;
};