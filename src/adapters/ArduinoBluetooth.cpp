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
        BLEService service = *(std::static_pointer_cast<ArduinoGattService>(mServices[i])->service());
        mBLEDevice->addService(service);
        mBLEDevice->setAdvertisedService(service);
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

std::shared_ptr<IGattCharacteristic> ArduinoBluetooth::createCharacteristic(const std::string uuid, const int valueLength) const {
    std::shared_ptr<ArduinoGattCharacteristic> characteristic 
        = std::make_shared<ArduinoGattCharacteristic>(mSerial, uuid, valueLength);
    return characteristic;
}

std::shared_ptr<IGattService> ArduinoBluetooth::createService(const std::string uuid) const {
    std::shared_ptr<ArduinoGattService> service 
        = std::make_shared<ArduinoGattService>(mSerial, uuid);
    return service;
}

bool ArduinoBluetooth::addService(std::shared_ptr<IGattService> service) {
    if (mNumServices >= mMaxNumServices) {
        return false;
    }
    
    mServices[mNumServices] = service;
    mNumServices++;

    return true;
}
