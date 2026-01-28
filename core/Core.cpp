#include <Arduino.h>
#include "Core.h"

#include "IBluetooth.h"
#include "ILed.h"

#include "LedController.h"

Core::Core(std::shared_ptr<IBluetooth> bluetooth, std::shared_ptr<ILed> led) : 
    mBluetooth(bluetooth), mLed(led) {
    std::string uuid = "19B10001-E8F2-537E-4F6C-D104768A1214";
    std::shared_ptr<IGattService> ledService = mBluetooth->createService(uuid);
    std::shared_ptr<IGattCharacteristic> ledChar = mBluetooth->createCharacteristic(uuid, 1);
    ledService->addCharacteristic(ledChar);

    std::shared_ptr<LedController> ledController = std::make_shared<LedController>(mLed);
    ledChar->addCallback([ledController](Result<ValueBuffer> result) {
        ledController->handle(result);
    });

    mBluetooth->addService(ledService);
    if (mBluetooth->start()) {
        Serial.println("Started the bluetooth service");
    }
}

void Core::update() {
}
