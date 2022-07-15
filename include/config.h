#pragma once

#include "flash.h"
#include "types.h"

const char * CONFIG_FILE = "config.txt";

/** default config **/
Config config = {
    .brightness = 255,
    .color = CHSV(0, 0, 255),
    .currentEffect = 0,
    .rainbowEffect = {
        .deltaHue = 5,
        .speed = 100.0
    },
    .twinkleEffect = {
        .delay = 200,
        .fraction = 4
    },
    .marqueeEffect = {
        .delay = 100,
        .blackSpacing = 5
    }
};

File configFile;

Config * getConfig() {
    return &config;
}

bool loadConfig() {
    if (!fs.exists(CONFIG_FILE)) {
        return false;
    }

    configFile = fs.open(CONFIG_FILE, FILE_READ);

    if (!configFile) {
        return false;
    }

    configFile.read((uint8_t *)&config, sizeof(config));
    configFile.flush();
    configFile.close();

    return true;
}

bool saveConfig() {
    configFile = fs.open(CONFIG_FILE, FILE_WRITE);

    if (!configFile) {
        Serial.println("Failed to save config!");
        Serial.println(configFile.getError());
        return false;
    }

    configFile.write((uint8_t *)&config, sizeof(config));
    configFile.flush();
    configFile.close();

    return true;
}

bool resetConfig() {
    config = {
        .brightness = 255,
        .color = CHSV(0, 0, 255),
        .currentEffect = 0,
        .rainbowEffect = {
            .deltaHue = 5,
            .speed = 100.0
        },
        .twinkleEffect = {
            .delay = 200,
            .fraction = 4
        },
        .marqueeEffect = {
            .delay = 100,
            .blackSpacing = 5
        }
    };

    return saveConfig();
}

bool configSetup() {  
    if (!loadConfig()) {
        Serial.println("Could not find config");
        saveConfig();
        return false;
    }
    Serial.println("Config loaded");
    Serial.println("brightness: " + String(config.brightness));

    return true;
}