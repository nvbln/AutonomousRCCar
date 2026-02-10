#pragma once

#include "IBLEService.h"
#include "IBLECentral.h"

/**
 * @class IBLEDevice
 * @brief thin wrapper for the peripheral BLEDevice class in ArduinoBLE.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 *
 * The functions called on BLE directly in the library are
 * passed on to BLEDevice behind the scenes. This BLEDevice
 * is what this class intends to represent.
 */
class IBLEDevice {
public:
    virtual ~IBLEDevice() = default;

    /**
     * @brief Initialises the BLE subsystem.
     *
     * @see the ArduinoBLE library.
     */
    virtual bool begin() = 0;

    /**
     * @brief Shuts down the BLE subsystem.
     *
     * @see the ArduinoBLE library.
     */
    virtual void end() = 0;

    /**
     * @brief Sets human-readable name that is advertised. 
     *
     * @see the ArduinoBLE library.
     */
    virtual void setLocalName(const char* name) = 0;

    /**
     * @brief Creates a new service.
     *
     * @return a newly created service using the IBLEDevice interface.
     */
    virtual std::shared_ptr<IBLEService> createService(const char* uuid) const = 0;

    /**
     * @brief Creates a new characteristic.
     *
     * @return a newly created characteristic using the IBLEDevice interface.
     */
    virtual std::shared_ptr<IBLECharacteristic> createCharacteristic(const char* uuid) const = 0;

    /**
     * @brief Registers BLE Service such that it becomes available to central devices. 
     *
     * @see the ArduinoBLE library.
     */
    virtual void addService(std::shared_ptr<IBLEService> service) = 0;

    /**
     * @brief Makes service discoverable.
     *
     * @see the ArduinoBLE library.
     */
    virtual void setAdvertisedService(std::shared_ptr<IBLEService> service) = 0;

    /**
     * @brief Starts broadcasting the device.
     *
     * @see the ArduinoBLE library.
     */
    virtual void advertise() = 0;

    /**
     * @brief Returns a snapshot of the currently connected central device.
     *
     * @see the ArduinoBLE library.
     */
    virtual const std::shared_ptr<IBLECentral> central() const = 0;
};
