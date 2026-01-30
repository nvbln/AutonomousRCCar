#include <Arduino.h>

#include "ArduinoLed.h"

ArduinoLed::ArduinoLed(uint8_t pin) : mPin(pin) {
    pinMode(pin, OUTPUT);

    // Always turn the led off at the start.
    turnOff();
}

void ArduinoLed::turn() {
    if (mOn) {
        turnOff();
    } else {
        turnOn();
    }
}

void ArduinoLed::turnOn() {
    digitalWrite(mPin, HIGH);
    mOn = true;
}

void ArduinoLed::turnOff() {
    digitalWrite(mPin, LOW);
    mOn = false;
}
