#pragma once

#include "sdReader.h"
#include "types.h"

const char * CONFIG_FILE = "config.txt";

Config config = {
    255
};

File configFile;

Config * getConfig() {
    return &config;
}

bool loadConfig() {
    if (!SD.exists(CONFIG_FILE)) {
        return false;
    }

    configFile = SD.open(CONFIG_FILE, FILE_READ);

    if (!configFile) {
        return false;
    }

    configFile.read((byte *)&config, sizeof(config));
    configFile.close();

    Serial.println("Config loaded");

    return true;
}

bool saveConfig() {
    SD.remove(CONFIG_FILE);
    configFile = SD.open(CONFIG_FILE, FILE_WRITE);

    if (!configFile) {
        return false;
    }

    configFile.write((byte *)&config, sizeof(config));
    configFile.close();

    Serial.println("Config saved");
    
    return true;
}

void configSetup() {
    if (!loadConfig()) {
        Serial.println("Could not find config");
    }
}