#pragma once

#include <cstdint>

#include "IPinIO.h"

/**
 * @class ArduinoPinIO
 * @brief wrapper implementation of pin-related functions in Arduino.
 */
class ArduinoPinIO : public IPinIO {
public:
    ArduinoPinIO() {};

    /**
     * @see IPinIO::pinMode()
     */
    void pinMode(uint8_t pin, PinIOMode mode) const override {
        switch (mode) {
            case PinIOMode::Input: ::pinMode(pin, INPUT); break;
            case PinIOMode::Output: ::pinMode(pin, OUTPUT); break;
            case PinIOMode::InputPullup: ::pinMode(pin, INPUT_PULLUP); break;
            default: ::pinMode(pin, OUTPUT); break;
        }
    }

    /**
     * @see IPinIO::digitalWrite()
     */
    void digitalWrite(uint8_t pin, PinIOValue value) const override {
        ::digitalWrite(pin, convertPinIOValue(value));
    }

    /**
     * @see IPinIO::pulseIn()
     */
    unsigned long pulseIn(uint8_t pin, PinIOValue value, unsigned long timeout) const override {
        return ::pulseIn(pin, convertPinIOValue(value), timeout);
    }
private:
    PinStatus convertPinIOValue(PinIOValue value) const {
        switch (value) {
            case PinIOValue::Low: return LOW;
            case PinIOValue::High: return HIGH;
            default: return LOW; break;
        }
    }
};
