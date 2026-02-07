#include <ArduinoBLE.h>

#include "IBLEService.h"
#include "ArduinoGattCharacteristic.h"

std::string ArduinoGattCharacteristic::uuid() const {
    return mUuid;
}

void ArduinoGattCharacteristic::addCharacteristicToService(std::shared_ptr<IBLEService> service) {
    service->addCharacteristic(mCharacteristic);
}

Result<ValueBuffer> ArduinoGattCharacteristic::read() {
    ValueBuffer buffer{};
    buffer.data[0] = mCharacteristic.value();
    buffer.length = 1;

    return Result<ValueBuffer>{true, buffer};
}

bool ArduinoGattCharacteristic::write(const ValueBuffer& buffer) {
    if (buffer.length == 0) {
        return false;
    }
    
    mCharacteristic.writeValue(buffer.data[0]);
    return true;
}

bool ArduinoGattCharacteristic::addCallback(Callback callback) {
    if (mNumCallbacks >= mMaxNumCallbacks) {
        return false;
    }
    
    mCallbacks[mNumCallbacks] = callback;
    mNumCallbacks++;

    return true;
}

void ArduinoGattCharacteristic::update() {
    if (mCharacteristic.written()) {
        Result<ValueBuffer> result = read();
        
        // Only send callbacks if the reading was actually successful.
        if (result.success) {
            for (int i = 0; i < mNumCallbacks; i++) {
                mCallbacks[i](result.data);
            }
        } else {
            mSerial->println("There was a problem reading the input value");
        }
    }
}
