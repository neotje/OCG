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
    },
    .flashEffect = {
        .delay = 500,
        .colors = {
            CRGB(255, 0, 0),
            CRGB(0, 255, 0),
            CRGB(0, 0, 255)
        }
    }
};

File configFile;

Config * getConfig() {
    return &config;
}

uint8_t getConfigSize() {
    return sizeof(config);
}

bool loadConfig() {
    if (!fs.exists(CONFIG_FILE)) {
        return false;
    }

    configFile = fs.open(CONFIG_FILE, FILE_READ);

    if (!configFile) {
        return false;
    }

    configFile.read((byte *)&config, sizeof(config));
    configFile.flush();
    configFile.close();

    return true;
}

bool saveConfig() {
    configFile = fs.open(CONFIG_FILE, O_RDWR | O_CREAT);

    Serial.println("Saving config...");

    if (!configFile) {
        Serial.println("Failed to save config!");
        Serial.println(configFile.getError());
        return false;
    }

    Serial.println(configFile.write((byte *)&config, sizeof(config)));

    configFile.flush();
    
    if(!configFile.close()) {
        Serial.println("Failed to close config!");
        return false;
    }

    return true;
}

bool resetConfig() {
    Serial.println("Resetting config...");

    fs.remove(CONFIG_FILE);

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
    },
    .flashEffect = {
        .delay = 500,
        .colors = {
            CRGB(255, 0, 0),
            CRGB(0, 255, 0),
            CRGB(0, 0, 255)
        }
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