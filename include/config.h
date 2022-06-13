#pragma once

#include "flash.h"
#include "types.h"

const char * CONFIG_FILE = "config.txt";

Config config = {
    255,
    CRGB::White
};

File configFile;

Config * getConfig() {
    return &config;
}

bool loadConfig() {
    if (!fs.exists(CONFIG_FILE)) {
        return false;
    }

    configFile = fs.open(CONFIG_FILE, O_READ);

    if (!configFile) {
        return false;
    }

    configFile.read((uint8_t *)&config, sizeof(config));
    configFile.close();

    return true;
}

bool saveConfig() {
    configFile = fs.open(CONFIG_FILE, O_WRITE);

    if (!configFile) {
        return false;
    }

    configFile.write((uint8_t *)&config, sizeof(config));
    configFile.close();

    return true;
}

void configSetup() {  
    if (!loadConfig()) {
        Serial.println("Could not find config");
        saveConfig();
    }
    Serial.println("Config loaded");
    Serial.println("brightness: " + String(config.brightness));
}