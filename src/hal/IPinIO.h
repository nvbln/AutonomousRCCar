#ifndef IPINIO
#define IPINIO

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

    virtual void pinMode(uint8_t pin, PinIOMode mode) const = 0;
    virtual void digitalWrite(uint8_t pin, PinIOValue value) const = 0;
};
#endif
