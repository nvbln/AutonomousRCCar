#pragma once

#include <cstdint>

enum class PinIOMode : uint8_t { Input, Output, InputPullup };
enum class PinIOValue : uint8_t { Low, High };

/**
 * @class IPinIO
 * @brief thin wrapper for the pin-related functions in Arduino.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 * Here, the loose pin-related functions are grouped
 * into this class.
 */
class IPinIO {
public:
    virtual ~IPinIO() = default;

    /**
     * @brief Configures the behaviour of the specified pin.
     *
     * @see the Arduino.h API.
     */
    virtual void pinMode(uint8_t pin, PinIOMode mode) const = 0;

    /**
     * @brief Sets the voltage of the pin.
     *
     * @see the Arduino.h API.
     */
    virtual void digitalWrite(uint8_t pin, PinIOValue value) const = 0;

    /**
     * @brief Listens for a pulse on the specified pin.
     *
     * @see the Arduino.h API.
     */
    virtual unsigned long pulseIn(uint8_t pin, PinIOValue value, unsigned long timeout = 1000000L) const = 0;

    /**
     * @brief Sets the voltage of the analog pin.
     *
     * @see the Arduino.h API.
     */
    virtual void analogWrite(uint8_t pin, int value) = 0;
};
