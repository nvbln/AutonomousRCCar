#include <memory>
#include <string>

#include "IBLEDevice.h"
#include "IBLECentral.h"
#include "ISerial.h"
#include "IBluetooth.h"
#include "ArduinoBluetooth.h"
#include "ArduinoGattService.h"
#include "ArduinoGattCharacteristic.h"

bool ArduinoBluetooth::start() {
    mBLEDevice->setLocalName(mName.c_str());
    for (int i = 0; i < mNumServices; i++) {
        auto service = std::static_pointer_cast<ArduinoGattService>(mServices[i]);
        service->addServiceToBLEDevice(mBLEDevice);
        service->advertiseServiceOnBLEDevice(mBLEDevice);
    }

    BLE.advertise();

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
}

std::shared_ptr<IGattCharacteristic> ArduinoBluetooth::createCharacteristic(const char* uuid, const int valueLength) const {
    return std::make_shared<ArduinoGattCharacteristic>(mSerial, uuid, valueLength);
}

std::shared_ptr<IGattService> ArduinoBluetooth::createService(const char* uuid) const {
    std::shared_ptr<IBLEService> bleService = mBLEDevice->createService(uuid);
    return std::make_shared<ArduinoGattService>(mSerial, bleService);
}

bool ArduinoBluetooth::addService(std::shared_ptr<IGattService> service) {
    if (mNumServices >= mMaxNumServices) {
        return false;
    }
    
    mServices[mNumServices] = service;
    mNumServices++;

    return true;
}
