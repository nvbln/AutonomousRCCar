#include "IGattCharacteristic.h"

#include "Nano33GattService.h"
#include "Nano33GattCharacteristic.h"

std::string Nano33GattService::uuid() const {
    return mUuid;
}

BLEService* Nano33GattService::service() {
    return &mService; 
}

bool Nano33GattService::addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) {
    if (mNumCharacteristics >= mMaxNumCharacteristics) {
        return false;
    }

    mCharacteristics[mNumCharacteristics] = characteristic;
    mNumCharacteristics++;

    BLEByteCharacteristic nanoChar = *(std::static_pointer_cast<Nano33GattCharacteristic>(characteristic)->characteristic());
    mService.addCharacteristic(nanoChar);

    return true;
}

void Nano33GattService::update() {
    for (int i = 0; i < mNumCharacteristics; i++) {
        mCharacteristics[i]->update();
    }
}

