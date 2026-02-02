#ifndef ARDUINOSERIAL_H
#define ARDUINOSERIAL_H

#include "ISerial.h"

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
     * @see ISerial::print()
     */
    size_t print(const char str[]) override;

    /**
     * @see ISerial::println()
     */
    size_t println(const char str[]) override;
};
#endif
