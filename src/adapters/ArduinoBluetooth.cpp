#include <memory>
#include <string>

#include "ArduinoBluetooth.h"
#include "ArduinoGattCharacteristic.h"
#include "ArduinoGattService.h"
#include "IBLECentral.h"
#include "IBLEDevice.h"
#include "ISerial.h"

bool ArduinoBluetooth::start() {
  mBLEDevice->setLocalName(mName.c_str());
  for (int i = 0; i < mNumServices; i++) {
    auto service = static_cast<ArduinoGattService *>(mServices[i]);
    service->addServiceToBLEDevice(mBLEDevice);
    service->advertiseServiceOnBLEDevice(mBLEDevice);
  }

  mBLEDevice->advertise();

  return true;
}

void ArduinoBluetooth::update() {
  std::shared_ptr<IBLECentral> central = mBLEDevice->central();
  if (central->connected()) {
    mSerial->print("Connected to central: ");
    mSerial->println(central->address());

    // Check for every service if there are changes.
    for (int i = 0; i < mNumServices; i++) {
      mServices[i]->update();
    }
  }
}

bool ArduinoBluetooth::stop() {
  mBLEDevice->end();
  return true;
}

std::shared_ptr<IGattCharacteristic>
ArduinoBluetooth::createCharacteristic(const char *uuid) const {
  std::shared_ptr<IBLECharacteristic> bleCharacteristic = mBLEDevice->createCharacteristic(uuid);
  return std::make_shared<ArduinoGattCharacteristic>(mSerial, bleCharacteristic);
}

std::shared_ptr<IGattService> ArduinoBluetooth::createService(const char *uuid) const {
  std::shared_ptr<IBLEService> bleService = mBLEDevice->createService(uuid);
  return std::make_shared<ArduinoGattService>(mSerial, bleService);
}

bool ArduinoBluetooth::addService(IGattService *service) {
  if (mNumServices >= mMaxNumServices) {
    return false;
  }

  mServices[mNumServices] = service;
  mNumServices++;

  return true;
}
