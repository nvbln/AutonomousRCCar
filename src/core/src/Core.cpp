#include "Core.h"

#include "ISerial.h"
#include "IBluetooth.h"
#include "ILed.h"
#include "IAccelerator.h"
#include "IUltrasound.h"

#include "LedController.h"
#include "CarMovementController.h"

Core::Core(std::shared_ptr<ISerial> serial, 
           std::shared_ptr<IBluetooth> bluetooth,
           std::shared_ptr<ILed> led,
           std::shared_ptr<IAccelerator> accelerator,
           std::shared_ptr<IUltrasound> ultrasound,
           std::shared_ptr<IVehicleMovement> vehicleMovement) : 
        mSerial(serial), 
        mBluetooth(bluetooth),
        mLed(led),
        mAccelerator(accelerator),
        mUltrasound(ultrasound),
        mVehicleMovement(vehicleMovement) {
    std::string uuid = "19B10001-E8F2-537E-4F6C-D104768A1214";
    std::shared_ptr<IGattService> motorService = mBluetooth->createService(uuid.c_str());
    std::shared_ptr<IGattCharacteristic> motorChar = mBluetooth->createCharacteristic(uuid.c_str());
    motorService->addCharacteristic(motorChar);

    std::shared_ptr<LedController> ledController = std::make_shared<LedController>(mLed);
    motorChar->addCallback([ledController](ValueBuffer buffer) {
        ledController->handle(buffer);
    });

    mCarController = std::make_shared<CarMovementController>(
            serial, ultrasound, mVehicleMovement);
    motorChar->addCallback([this](ValueBuffer buffer) {
        mCarController->handle(buffer);
    });

    ultrasound->addCallback([serial](float distance) {
        serial->println(distance);
    });

    mBluetooth->addService(motorService);

    if (mBluetooth->start()) {
        mSerial->println("Started the bluetooth service");
    }
}

void Core::update() {
    mCarController->controlCar();
}
