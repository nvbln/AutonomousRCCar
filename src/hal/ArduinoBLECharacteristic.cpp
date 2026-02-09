#include <ArduinoBLE.h>

#include "ArduinoBLECharacteristic.h"

void ArduinoBLECharacteristic::writeValue(const uint8_t value) {
    mCharacteristic.writeValue(value);
}

uint8_t ArduinoBLECharacteristic::read() {
    return mCharacteristic.read();
}

uint8_t ArduinoBLECharacteristic::value() {
    return mCharacteristic.value();
}

bool ArduinoBLECharacteristic::written() {
    return mCharacteristic.written();
}
