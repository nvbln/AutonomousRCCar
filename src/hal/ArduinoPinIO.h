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
    void pinMode(uint8_t pin, PinIOMode mode) const override;

    /**
     * @see IPinIO::digitalWrite()
     */
    void digitalWrite(uint8_t pin, PinIOValue value) const override;
};
