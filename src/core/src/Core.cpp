#include "Core.h"

#include "ISerial.h"
#include "IBluetooth.h"
#include "ILed.h"
#include "IAccelerator.h"

#include "strategies/SimpleMotionEvaluationStrategy.h"
#include "strategies/SimpleVarianceSpikeDetectionStrategy.h"

#include "LedController.h"
#include "MotionStatusEvaluator.h"

Core::Core(std::shared_ptr<ISerial> serial, 
           std::shared_ptr<IBluetooth> bluetooth,
           std::shared_ptr<ILed> led,
           std::shared_ptr<IAccelerator> accelerator) : 
    mSerial(serial), mBluetooth(bluetooth), mLed(led), mAccelerator(accelerator) {
    std::string uuid = "19B10001-E8F2-537E-4F6C-D104768A1214";
    std::shared_ptr<IGattService> ledService = mBluetooth->createService(uuid.c_str());
    std::shared_ptr<IGattCharacteristic> ledChar = mBluetooth->createCharacteristic(uuid.c_str());
    ledService->addCharacteristic(ledChar);

    std::shared_ptr<LedController> ledController = std::make_shared<LedController>(mLed);
    ledChar->addCallback([ledController](ValueBuffer buffer) {
        ledController->handle(buffer);
    });

    mBluetooth->addService(ledService);
    if (mBluetooth->start()) {
        mSerial->println("Started the bluetooth service");
    }

    /*serial->println("X\tY\tZ");
    accelerator->addCallback([serial](AccelerationData data) {
        serial->print(data.x);
        serial->print('\t');
        serial->print(data.y);
        serial->print('\t');
        serial->println(data.z);
    });*/

    mMotionEvaluator = std::make_shared<MotionStatusEvaluator>(
                accelerator,
                std::make_shared<SimpleVarianceSpikeDetectionStrategy>(),
                std::make_shared<SimpleMotionEvaluationStrategy>()
    );
}

void Core::update() {
    MotionStatus status = mMotionEvaluator->status(); 
    switch(status) {
        case MotionStatus::Still:
            mSerial->println("Still");
            break;
        case MotionStatus::Moving:
            mSerial->println("Moving");
            break;
        case MotionStatus::Blocked:
            mSerial->println("Blocked");
            break;
    }
}
