#pragma once

#include "IBLEDevice.h"
#include "ArduinoBLEService.h"
#include "ArduinoBLECharacteristic.h"
#include "ArduinoBLECentral.h"

#include <ArduinoBLE.h>

#include <memory>

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
    bool begin() override {
        return BLE.begin();
    }

    /**
     * @see IBLEDevice::end()
     */
    void end() override {
        BLE.end();
    }

    /**
     * @see IBLEDevice::setLocalName()
     */
    void setLocalName(const char* name) override {
        BLE.setLocalName(name);
    }

    /**
     * @see IBLEDevice::createService()
     */
    std::shared_ptr<IBLEService> createService(const char* uuid) const override {
        return std::make_shared<ArduinoBLEService>(uuid);
    }

    /**
     * @see IBLEDevice::createCharacteristic()
     */
    std::shared_ptr<IBLECharacteristic> createCharacteristic(const char* uuid) const override {
        return std::make_shared<ArduinoBLECharacteristic>(uuid);
    }

    /**
     * @see IBLEDevice::addService()
     */
    void addService(std::shared_ptr<IBLEService> service)  override {
        auto arduinoService = std::static_pointer_cast<ArduinoBLEService>(service);
        BLE.addService(arduinoService->mService);
    }

    /**
     * @see IBLEDevice::setAdvertisedService()
     */
    void setAdvertisedService(std::shared_ptr<IBLEService> service) override {
        auto arduinoService = std::static_pointer_cast<ArduinoBLEService>(service);
        BLE.setAdvertisedService(arduinoService->mService);
    }

    /**
     * @see IBLEDevice::advertise()
     */
    void advertise() override {
        BLE.advertise();
    }

    /**
     * @see IBLEDevice::central()
     */
    const std::shared_ptr<IBLECentral> central() const override {
        return std::make_shared<ArduinoBLECentral>(BLE.central());
    }
};
