#include <Arduino.h>
#include <cstdint>

#include "ArduinoPinIO.h"

void ArduinoPinIO::pinMode(uint8_t pin, PinIOMode mode) const {
    switch (mode) {
        case PinIOMode::Input: ::pinMode(pin, INPUT); break;
        case PinIOMode::Output: ::pinMode(pin, OUTPUT); break;
        case PinIOMode::InputPullup: ::pinMode(pin, INPUT_PULLUP); break;
        default: ::pinMode(pin, OUTPUT); break;
    }
}

void ArduinoPinIO::digitalWrite(uint8_t pin, PinIOValue value) const {
    switch (value) {
        case PinIOValue::Low: ::digitalWrite(pin, LOW); break;
        case PinIOValue::High: ::digitalWrite(pin, HIGH); break;
        default: ::digitalWrite(pin, LOW); break;
    }
}
