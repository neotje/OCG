#pragma once

#include <Arduino.h>

#ifdef ADAFRUIT_FEATHER_M4_EXPRESS

#define LEDSTRIP1_PIN 10
#define BUTTON1_PIN 9

#define ROTARY_CLK_PIN 5
#define ROTARY_DT_PIN 6

#define FLASH_SS SS
#define FLASH_SPI SPI

#else

#define LEDSTRIP1_PIN 9
#define BUTTON1_PIN 4

#define ROTARY_CLK_PIN 2
#define ROTARY_DT_PIN 3

#define SD_CS_PIN 10

#endif
