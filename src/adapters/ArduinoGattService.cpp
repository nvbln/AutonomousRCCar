#include "IGattCharacteristic.h"

#include "ArduinoGattService.h"
#include "ArduinoGattCharacteristic.h"

std::string ArduinoGattService::uuid() const {
    return mUuid;
}

BLEService* ArduinoGattService::service() {
    return &mService; 
}

bool ArduinoGattService::addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) {
    if (mNumCharacteristics >= mMaxNumCharacteristics) {
        return false;
    }

    mCharacteristics[mNumCharacteristics] = characteristic;
    mNumCharacteristics++;

    BLEByteCharacteristic nanoChar = *(std::static_pointer_cast<ArduinoGattCharacteristic>(characteristic)->characteristic());
    mService.addCharacteristic(nanoChar);

    return true;
}

void ArduinoGattService::update() {
    for (int i = 0; i < mNumCharacteristics; i++) {
        mCharacteristics[i]->update();
    }
}

