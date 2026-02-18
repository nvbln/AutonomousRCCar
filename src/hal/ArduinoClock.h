#pragma once

#include "IClock.h"

#include <Arduino.h>

/**
 * @class ArduinoClock
 * @brief wrapper implementation of time-related functions in Arduino.
 */
class ArduinoClock : public IClock {
public:
    ArduinoClock() {};

    /**
     * @see IClock::micros()
     */
    unsigned long micros() const override {
        return ::micros();
    }

    /**
     * @see IClock::delayMicroseconds()
     */
    void delayMicroseconds(unsigned int us) override {
        return ::delayMicroseconds(us);
    }
};
