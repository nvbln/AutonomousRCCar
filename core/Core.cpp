#include <Arduino.h>
#include "Core.h"

#include "IBluetooth.h"
#include "ILed.h"

#include "LedController.h"

Core::Core(std::shared_ptr<IBluetooth> bluetooth, std::shared_ptr<ILed> led) : 
    mBluetooth(bluetooth), mLed(led) {
    std::string uuid = "123456789";
    std::shared_ptr<IGattCharacteristic> gattChar = mBluetooth->createCharacteristic(uuid, 1);

    std::shared_ptr<LedController> ledController = std::make_shared<LedController>(mLed);
    gattChar->addCallback([ledController](Result<ValueBuffer> result) {
        ledController->handle(result);
    });

    mBluetooth->addCharacteristic(gattChar);
    if (mBluetooth->start()) {
        Serial.println("Started the bluetooth service");
    }
}

void Core::update() {
}
