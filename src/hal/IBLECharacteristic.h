#ifndef IBLECHARACTERISTIC_H
#define IBLECHARACTERISTIC_H

#include <cstdint>

/**
 * @class IBLECharacteristic
 * @brief thin wrapper for the BLECharacteristic class in ArduinoBLE.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 */
class IBLECharacteristic {
public:
    virtual ~IBLECharacteristic() = default;
    
    /**
     * @brief sets the Characteristic to the given value.
     *
     * @param value The value to set the Characteristic to.
     * @see the ArduinoBLE library.
     */
    virtual void writeValue(const uint8_t value) = 0;

    /**
     * @brief retrieves and returns the current value of the Characteristic.
     *
     * @see the ArduinoBLE library.
     */
    virtual uint8_t read() = 0;

    /**
     * @brief returns the current value of the Characteristic.
     *
     * @see the ArduinoBLE library.
     */
    virtual uint8_t value() = 0;

    /**
     * @brief checks whether the value of the Characteristic was changed by a central device.
     *
     * @see the ArduinoBLE library.
     */
    virtual bool written() = 0;
};
#endif
