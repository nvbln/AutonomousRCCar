#include <memory>
#include <string>

#include <ArduinoBLE.h>

#include "IBluetooth.h"
#include "Nano33Bluetooth.h"
#include "Nano33GattCharacteristic.h"


bool Nano33Bluetooth::start() {
    BLE.setLocalName(mName.c_str());
    for (int i = 0; i < mNumCharacteristics; i++) {
        std::shared_ptr<Nano33GattCharacteristic> nanoCharacteristic = std::static_pointer_cast<Nano33GattCharacteristic>(mCharacteristics[i]);
        BLEService service = *(nanoCharacteristic->service());
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

        // Check for every characteristic if their value changed.
        for (int i = 0; i < mNumCharacteristics; i++) {
            mCharacteristics[i]->update();
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

bool Nano33Bluetooth::addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) {
    if (mNumCharacteristics >= mMaxNumCharacteristics) {
        return false;
    }
    
    mCharacteristics[mNumCharacteristics] = characteristic;
    mNumCharacteristics++;

    return true;
}
