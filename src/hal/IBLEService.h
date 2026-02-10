#pragma once

#include <memory>

#include "IBLECharacteristic.h"

/**
 * @class IBLEService
 * @brief thin wrapper for the BLEService in ArduinoBLE.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 */
class IBLEService {
public:
    virtual ~IBLEService() = default;

    virtual const char* uuid() const = 0;
    virtual void addCharacteristic(std::shared_ptr<IBLECharacteristic> characteristic) = 0;
};
