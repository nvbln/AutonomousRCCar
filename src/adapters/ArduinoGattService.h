#pragma once

#include <memory>

#include "IBLEDevice.h"
#include "IBLEService.h"
#include "IGattService.h"
#include "ISerial.h"

/**
 * @class ArduinoGattService
 * @brief IGattService implementation for Arduino
 */
class ArduinoGattService : public IGattService {
public:
  /**
   * @brief Creates a GATT Service for grouping Characteristics
   *
   * @param serial The Arduino Serial interface for printing messages.
   * @param uuid The ID that the service is identified by.
   */
  ArduinoGattService(const ISerial *serial, std::unique_ptr<IBLEService> service)
      : mSerial(serial), mService(std::move(service)){};

  /**
   * @brief adds the service to the BLE device.
   *
   * Adding the service to the BLEDevice makes it available
   * to central devices that connect to the peripheral.
   *
   * @param device The BLE peripheral device.
   */
  void addServiceToBLEDevice(IBLEDevice *device);

  /**
   * @brief Makes the service discoverable by central devices.
   *
   * @param device the BLE peripheral device.
   */
  void advertiseServiceOnBLEDevice(IBLEDevice *device);

  /**
   * @see IGattService::addCharacteristic()
   */
  bool addCharacteristic(IGattCharacteristic *characteristic) override;

  /**
   * @see IGattService::update()
   */
  void update() override;

private:
  const ISerial *mSerial;
  const std::unique_ptr<IBLEService> mService;
  static const int mMaxNumCharacteristics = 5;
  int mNumCharacteristics = 0;
  IGattCharacteristic *mCharacteristics[mMaxNumCharacteristics];
};
