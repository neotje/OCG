#pragma once

#include <Arduino.h>
#include <LinkedList.h>

#include "driverBase.h"
#include "drivers/buttonDriver.h"
#include "drivers/rotaryDriver.h"

class HardwareManager {
    private:
        LinkedList<DriverBase*> *hardwareList;
    public:
        HardwareManager();

        bool addHardware(DriverBase *hardware);
        DriverBase* getByName(const char* name);

        void loop();
};