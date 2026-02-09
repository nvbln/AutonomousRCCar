#include <ArduinoBLE.h>

#include "ArduinoBLECharacteristic.h"
#include "ArduinoBLEService.h"

const char* ArduinoBLEService::uuid() const {
    return mService.uuid();
}

void ArduinoBLEService::addCharacteristic(std::shared_ptr<IBLECharacteristic> characteristic) {
    auto arduinoChar = std::static_pointer_cast<ArduinoBLECharacteristic>(characteristic);
    mService.addCharacteristic(arduinoChar->mCharacteristic);
}
