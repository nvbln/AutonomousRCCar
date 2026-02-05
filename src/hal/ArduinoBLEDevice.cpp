#include <memory>

#include <ArduinoBLE.h>

#include "ArduinoBLECentral.h"

#include "ArduinoBLEDevice.h"

bool ArduinoBLEDevice::begin() {
    return BLE.begin(); 
}

void ArduinoBLEDevice::end() {
    BLE.end(); 
}

void ArduinoBLEDevice::setLocalName(const char* name) {
    BLE.setLocalName(name);
}

void ArduinoBLEDevice::addService(BLEService& service) {
    BLE.addService(service);
}

void ArduinoBLEDevice::setAdvertisedService(BLEService& service) {
    BLE.setAdvertisedService(service);
}

void ArduinoBLEDevice::advertise() {
    BLE.advertise();
}

const std::shared_ptr<IBLECentral> ArduinoBLEDevice::central() const {
    return std::make_shared<ArduinoBLECentral>(BLE.central());
}
