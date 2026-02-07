#include <memory>

#include <ArduinoBLE.h>

#include "ArduinoBLEService.h"
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

std::shared_ptr<IBLEService> ArduinoBLEDevice::createService(const char* uuid) const {
    return std::make_shared<ArduinoBLEService>(uuid);
}

void ArduinoBLEDevice::addService(std::shared_ptr<IBLEService> service) {
    auto arduinoService = std::static_pointer_cast<ArduinoBLEService>(service);
    BLE.addService(arduinoService->mService);
}

void ArduinoBLEDevice::setAdvertisedService(std::shared_ptr<IBLEService> service) {
    auto arduinoService = std::static_pointer_cast<ArduinoBLEService>(service);
    BLE.setAdvertisedService(arduinoService->mService);
}

void ArduinoBLEDevice::advertise() {
    BLE.advertise();
}

const std::shared_ptr<IBLECentral> ArduinoBLEDevice::central() const {
    return std::make_shared<ArduinoBLECentral>(BLE.central());
}
