#include "hardwareManager.h"

HardwareManager::HardwareManager() {
    hardwareList = new LinkedList<DriverBase*>();
}

DriverBase* HardwareManager::getByName(const char* name) {
    for (int i = 0; i < hardwareList->size(); i++)
    {
        if(hardwareList->get(i)->getName() == name)
            return hardwareList->get(i);
    }
    return nullptr;
}

bool HardwareManager::addHardware(DriverBase *hardware) {
    if (getByName(hardware->getName().c_str()) == nullptr) {
        hardwareList->add(hardware);
        hardware->setHardwareManager(this);
        return true;
    }
    return false;
}

void HardwareManager::loop() {
    for (int i = 0; i < hardwareList->size(); i++) {
        hardwareList->get(i)->loop();
    }
}