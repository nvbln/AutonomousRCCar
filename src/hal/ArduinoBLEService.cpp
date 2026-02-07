#include <ArduinoBLE.h>

#include "ArduinoBLEService.h"

const char* ArduinoBLEService::uuid() const {
    return mService.uuid();
}

void ArduinoBLEService::addCharacteristic(BLECharacteristic& characteristic) {
    mService.addCharacteristic(characteristic);
}
