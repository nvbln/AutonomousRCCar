#pragma once

#include "ArduinoBLECharacteristic.h"
#include "ArduinoBLEDevice.h"
#include "IBLECharacteristic.h"
#include "IBLEService.h"
#include <ArduinoBLE.h>

/**
 * @class ArduinoBLEService
 * @brief wrapper implementation of the ArduinoBLE BLEService
 *
 * This connects the IBLEService to the ArduinoBLE library,
 * such that the application can run on Arduino devices.
 */
class ArduinoBLEService : public IBLEService {
public:
  ArduinoBLEService(const char *uuid) : mService(uuid){};

  /**
   * @see IBLEService::uuid()
   */
  const char *uuid() const override { return mService.uuid(); }

  /**
   * @see IBLEService::addCharacteristic()
   */
  void addCharacteristic(IBLECharacteristic *characteristic) override {
    auto arduinoChar = static_cast<ArduinoBLECharacteristic *>(characteristic);
    mService.addCharacteristic(arduinoChar->mCharacteristic);
  }

private:
  friend class ArduinoBLEDevice;
  BLEService mService;
};
