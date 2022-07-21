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
        DriverBase(HardwareManager* hardwareManager) {
            this->hardwareManager = hardwareManager;
        }
        ~DriverBase() {}

        void setHardwareManager(HardwareManager* hardwareManager) {
            this->hardwareManager = hardwareManager;
        }
        HardwareManager* getHardwareManager() {
            return this->hardwareManager;
        }

        virtual String getName() = 0;
        virtual void loop() = 0;
};