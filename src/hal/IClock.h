#pragma once

/**
 * @class IClock
 * @brief thin wrapper for the time-related functions in Arduino.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 * Here, the loose time-related functions are grouped into this class.
 */
class IClock {
public:
    virtual ~IClock() = default;

    /**
     * @brief returns the current time in microseconds.
     * 
     * @see the Arduino.h API.
     * @return the current time in microseconds.
     */
    virtual unsigned long micros() const = 0;

    /**
     * @brief delays the time in microseconds.
     *
     * @see the Arduino.h API
     */
    virtual void delayMicroseconds(unsigned int us) = 0;
};
