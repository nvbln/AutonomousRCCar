#pragma once

/**
 * @class IBLECentral
 * @brief thin wrapper for the central BLEDevice class in ArduinoBLE.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 *
 * Just like the central object in ArduinoBLE, this interface
 * represents a snapshot of the central BLEDevice that is
 * connected at the time of the central() call.
 */
class IBLECentral {
public:
    virtual ~IBLECentral() = default;

    /**
     * @brief Returns the MAC address of the connected central device.
     *
     * @see the ArduinoBLE library.
     */
    virtual const char* address() const = 0;

    /**
     * @brief Indicates whether the central device is currently connected to the peripheral. 
     *
     * @see the ArduinoBLE library.
     */
    virtual bool connected() const = 0;
};
