#include <ArduinoBLE.h>

#include "Nano33GattCharacteristic.h"

std::string Nano33GattCharacteristic::uuid() const {
    return mUuid;
}

BLEService* Nano33GattCharacteristic::service() {
    return &mService;
}

Result<ValueBuffer> Nano33GattCharacteristic::read() {
    ValueBuffer buffer{};
    buffer.data[0] = mCharacteristic.value();
    buffer.length = 1;

    return Result<ValueBuffer>{true, buffer};
}

bool Nano33GattCharacteristic::write(const ValueBuffer& buffer) {
    if (buffer.length == 0) {
        return false;
    }
    
    mCharacteristic.writeValue(buffer.data[0]);
    return true;
}

bool Nano33GattCharacteristic::addCallback(Callback callback) {
    if (mNumCallbacks >= mMaxNumCallbacks) {
        return false;
    }
    
    mCallbacks[mNumCallbacks] = callback;
    mNumCallbacks++;

    return true;
}

void Nano33GattCharacteristic::update() {
    if (mCharacteristic.written()) {
        Result<ValueBuffer> result = read();
        
        for (int i = 0; i < mNumCallbacks; i++) {
            mCallbacks[i](result);
        }
    }
}
