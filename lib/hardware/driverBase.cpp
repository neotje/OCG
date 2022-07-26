#include "driverBase.h"

void DriverBase::setHardwareManager(HardwareManager* hardwareManager) {
    this->hardwareManager = hardwareManager;
}

HardwareManager* DriverBase::getHardwareManager() {
    return this->hardwareManager;
}