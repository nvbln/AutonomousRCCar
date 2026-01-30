#include <memory>
#include <string>

#include <ArduinoBLE.h>

#include "IBluetooth.h"
#include "Nano33Bluetooth.h"
#include "Nano33GattService.h"
#include "Nano33GattCharacteristic.h"

bool Nano33Bluetooth::start() {
    BLE.setLocalName(mName.c_str());
    for (int i = 0; i < mNumServices; i++) {
        BLEService service = *(std::static_pointer_cast<Nano33GattService>(mServices[i])->service());
        BLE.addService(service);
        BLE.setAdvertisedService(service);
    }

    BLE.advertise();

    return true;
}

void Nano33Bluetooth::update() {
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

bool Nano33Bluetooth::stop() {
    BLE.end();
}

std::shared_ptr<IGattCharacteristic> Nano33Bluetooth::createCharacteristic(const std::string uuid, const int valueLength) const {
    std::shared_ptr<Nano33GattCharacteristic> characteristic 
        = std::make_shared<Nano33GattCharacteristic>(uuid, valueLength);
    return characteristic;
}

std::shared_ptr<IGattService> Nano33Bluetooth::createService(const std::string uuid) const {
    std::shared_ptr<Nano33GattService> service 
        = std::make_shared<Nano33GattService>(uuid);
    return service;
}

bool Nano33Bluetooth::addService(std::shared_ptr<IGattService> service) {
    if (mNumServices >= mMaxNumServices) {
        return false;
    }
    
    mServices[mNumServices] = service;
    mNumServices++;

    return true;
}
