#include "IGattCharacteristic.h"

#include "IBLEDevice.h"

#include "ArduinoGattService.h"
#include "ArduinoGattCharacteristic.h"

std::string ArduinoGattService::uuid() const {
    return mUuid;
}

void ArduinoGattService::addServiceToBLEDevice(std::shared_ptr<IBLEDevice> device) {
    device->addService(mService);
}

void ArduinoGattService::advertiseServiceOnBLEDevice(std::shared_ptr<IBLEDevice> device) {
    device->setAdvertisedService(mService);
}

bool ArduinoGattService::addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) {
    if (mNumCharacteristics >= mMaxNumCharacteristics) {
        return false;
    }

    mCharacteristics[mNumCharacteristics] = characteristic;
    mNumCharacteristics++;

    auto nanoChar = std::static_pointer_cast<ArduinoGattCharacteristic>(characteristic);
    nanoChar->addCharacteristicToService(mService);

    return true;
}

void ArduinoGattService::update() {
    for (int i = 0; i < mNumCharacteristics; i++) {
        mCharacteristics[i]->update();
    }
}

