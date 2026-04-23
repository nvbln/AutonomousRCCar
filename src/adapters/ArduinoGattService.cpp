#include "IGattCharacteristic.h"

#include "IBLEDevice.h"

#include "ArduinoGattCharacteristic.h"
#include "ArduinoGattService.h"

void ArduinoGattService::addServiceToBLEDevice(IBLEDevice *device) {
  device->addService(mService.get());
}

void ArduinoGattService::advertiseServiceOnBLEDevice(IBLEDevice *device) {
  device->setAdvertisedService(mService.get());
}

bool ArduinoGattService::addCharacteristic(IGattCharacteristic *characteristic) {
  if (mNumCharacteristics >= mMaxNumCharacteristics) {
    return false;
  }

  mCharacteristics[mNumCharacteristics] = characteristic;
  mNumCharacteristics++;

  auto arduinoChar = static_cast<ArduinoGattCharacteristic *>(characteristic);
  arduinoChar->addCharacteristicToService(mService.get());

  return true;
}

void ArduinoGattService::update() {
  for (int i = 0; i < mNumCharacteristics; i++) {
    mCharacteristics[i]->update();
  }
}
