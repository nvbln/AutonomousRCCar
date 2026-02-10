#pragma once

#include <memory>

#include <ArduinoBLE.h>
#include "ArduinoBLEDevice.h"
#include "IBLECharacteristic.h"
#include "IBLEService.h"

/**
 * @class ArduinoBLEService
 * @brief wrapper implementation of the ArduinoBLE BLEService
 *
 * This connects the IBLEService to the ArduinoBLE library,
 * such that the application can run on Arduino devices.
 */
class ArduinoBLEService : public IBLEService {
public:
    ArduinoBLEService(const char* uuid) : mService(uuid) {};

    /**
     * @see IBLEService::uuid()
     */
    const char* uuid() const override;

    /**
     * @see IBLEService::addCharacteristic()
     */
    void addCharacteristic(std::shared_ptr<IBLECharacteristic> characteristic) override;
private:
    friend class ArduinoBLEDevice;
    BLEService mService;
};
