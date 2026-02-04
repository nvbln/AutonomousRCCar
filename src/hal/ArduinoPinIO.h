#ifndef ARDUINOPINIO
#define ARDUINOPINIO

#include <cstdint>

#include "IPinIO.h"

/**
 * @class ArduinoPinIO
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
#endif
