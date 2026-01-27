#include <Arduino.h>

#include "Nano33Led.h"

Nano33Led::Nano33Led(uint8_t pin) : mPin(pin) {
    pinMode(pin, OUTPUT);

    // Always turn the led off at the start.
    turnOff();
}

void Nano33Led::turn() {
    if (mOn) {
        turnOff();
    } else {
        turnOn();
    }
}

void Nano33Led::turnOn() {
    digitalWrite(mPin, HIGH);
    mOn = true;
}

void Nano33Led::turnOff() {
    digitalWrite(mPin, LOW);
    mOn = false;
}

uint8_t Nano33Led::pin() const {
    return mPin;
}
