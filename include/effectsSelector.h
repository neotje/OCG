#pragma once

#include "lcd.h"
#include "rotary.h"
#include "effects.h"
#include "config.h"
#include "numberSelector.h"

void effectsSelectorDraw() {  
    getLcd()->setCursor(0, 1);
    getLcd()->print(getEffect(getConfig()->currentEffect)->name);
}

void effectsSelectorSetup() {
    getLcd()->clear();
    getLcd()->print("Effects:");

    effectsSelectorDraw();
}

void effectsSelectorLoop() {

}