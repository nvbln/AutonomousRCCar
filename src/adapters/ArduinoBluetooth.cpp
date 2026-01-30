#include <memory>
#include <string>

#include <ArduinoBLE.h>

#include "IBluetooth.h"
#include "ArduinoBluetooth.h"
#include "ArduinoGattService.h"
#include "ArduinoGattCharacteristic.h"

bool ArduinoBluetooth::start() {
    BLE.setLocalName(mName.c_str());
    for (int i = 0; i < mNumServices; i++) {
        BLEService service = *(std::static_pointer_cast<ArduinoGattService>(mServices[i])->service());
        BLE.addService(service);
        BLE.setAdvertisedService(service);
    }

    BLE.advertise();

    return true;
}

void ArduinoBluetooth::update() {
    BLEDevice central = BLE.central();
    if (central) {
        Serial.print("Connected to central: ");
        Serial.println(central.address());

        // Check for every service if there are changes.
        for (int i = 0; i < mNumServices; i++) {
            mServices[i]->update();
        }
    }
}

bool ArduinoBluetooth::stop() {
    BLE.end();
}

std::shared_ptr<IGattCharacteristic> ArduinoBluetooth::createCharacteristic(const std::string uuid, const int valueLength) const {
    std::shared_ptr<ArduinoGattCharacteristic> characteristic 
        = std::make_shared<ArduinoGattCharacteristic>(uuid, valueLength);
    return characteristic;
}

std::shared_ptr<IGattService> ArduinoBluetooth::createService(const std::string uuid) const {
    std::shared_ptr<ArduinoGattService> service 
        = std::make_shared<ArduinoGattService>(uuid);
    return service;
}

bool ArduinoBluetooth::addService(std::shared_ptr<IGattService> service) {
    if (mNumServices >= mMaxNumServices) {
        return false;
    }
    
    mServices[mNumServices] = service;
    mNumServices++;

    return true;
}
