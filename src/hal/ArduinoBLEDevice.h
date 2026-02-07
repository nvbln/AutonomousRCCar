#ifndef ARDUINOBLEDEVICE_H
#define ARDUINOBLEDEVICE_H

#include "IBLECentral.h"
#include "IBLEDevice.h"

/**
 * @class ArduinoBLEDevice
 * @brief wrapper implementation of the ArduinoBLE BLEDevice.
 *
 * This connects the IBLEDevice wrapper to the ArduinoBLE library,
 * such that the application can run on Arduino devices.
 */
class ArduinoBLEDevice : public IBLEDevice {
public:
    ArduinoBLEDevice() {};

    /**
     * @see IBLEDevice::begin()
     */
    bool begin() override;

    /**
     * @see IBLEDevice::end()
     */
    void end() override;

    /**
     * @see IBLEDevice::setLocalName()
     */
    void setLocalName(const char* name) override;

    /**
     @see IBLEDevice::createService()
     */
    std::shared_ptr<IBLEService> createService(const char* uuid) const override;

    /**
     * @see IBLEDevice::addService()
     */
    void addService(std::shared_ptr<IBLEService> service)  override;

    /**
     * @see IBLEDevice::setAdvertisedService()
     */
    void setAdvertisedService(std::shared_ptr<IBLEService> service) override;

    /**
     * @see IBLEDevice::advertise()
     */
    void advertise() override;

    /**
     * @see IBLEDevice::central()
     */
    const std::shared_ptr<IBLECentral> central() const override;
};
#endif
