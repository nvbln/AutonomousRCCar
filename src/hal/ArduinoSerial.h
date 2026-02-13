#pragma once

#include "ISerial.h"

#include <Arduino.h>

/**
 * @class ArduinoSerial
 * @brief wrapper implementation for the Arduino library.
 *
 * This connects the ISerial wrapper to the Arduino library,
 * such that the application can run on Arduino devices.
 */
class ArduinoSerial : public ISerial {
public:
    ArduinoSerial() {};

    /**
    * @see ISerial::begin()
    */
    void begin(unsigned long baud) const override {
        Serial.begin(baud);
    }

    /**
     * @see ISerial::print()
     */
    size_t print(const char* str) const override {
        return Serial.print(str);
    }

    /**
     * @see ISerial::print()
     */
    size_t print(float value, int digits = 2) const override {
        return Serial.print(value, digits);
    }

    /**
     * @see ISerial::println()
     */
    size_t println(const char* str) const override {
        return Serial.println(str);
    }

    /**
     * @see ISerial::println()
     */
    size_t println(float value, int digits = 2) const override {
        return Serial.println(value, digits);
    }

    /**
     * @see ISerial::ready()
     */
    bool ready() const override {
        return Serial;
    }
};
