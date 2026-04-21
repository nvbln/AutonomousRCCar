#include "Core.h"

#include "IAccelerator.h"
#include "IBluetooth.h"
#include "ILed.h"
#include "ISerial.h"
#include "IUltrasound.h"

#include "CarMovementController.h"
#include "LedController.h"

static constexpr const char *DRIVE_LOCK_CHAR_ID = "19B10001-E8F2-537E-4F6C-D104768A1214";
static constexpr const char *MOVEMENT_STATUS_CHAR_ID = "A92E318E-9EC4-4DB5-A861-7D0B6B77A2A1";
static constexpr const char *ULTRASOUND_CHAR_ID = "16B31004-5930-47DF-82EE-A24F976AA56D";

Core::Core(std::shared_ptr<ISerial> serial, std::shared_ptr<IBluetooth> bluetooth,
           std::shared_ptr<ILed> led, std::shared_ptr<IAccelerator> accelerator,
           std::shared_ptr<IUltrasound> ultrasound,
           std::shared_ptr<IVehicleMovement> vehicleMovement)
    : mSerial(serial), mBluetooth(bluetooth), mLed(led), mAccelerator(accelerator),
      mUltrasound(ultrasound), mVehicleMovement(vehicleMovement) {
  std::shared_ptr<IGattService> motorService = mBluetooth->createService(DRIVE_LOCK_CHAR_ID);
  std::shared_ptr<IGattService> movementService =
      mBluetooth->createService(MOVEMENT_STATUS_CHAR_ID);
  std::shared_ptr<IGattService> ultrasoundService = mBluetooth->createService(ULTRASOUND_CHAR_ID);

  std::shared_ptr<IGattCharacteristic> motorChar =
      mBluetooth->createCharacteristic(DRIVE_LOCK_CHAR_ID);
  motorService->addCharacteristic(motorChar);

  std::shared_ptr<IGattCharacteristic> movementChar =
      mBluetooth->createCharacteristic(MOVEMENT_STATUS_CHAR_ID);
  movementService->addCharacteristic(movementChar);

  std::shared_ptr<IGattCharacteristic> ultrasoundChar =
      mBluetooth->createCharacteristic(ULTRASOUND_CHAR_ID);
  ultrasoundService->addCharacteristic(ultrasoundChar);
  ultrasound->subscribe([ultrasoundChar](float distanceCm) {
    ultrasoundChar->write(ValueBuffer{{static_cast<uint8_t>(distanceCm)}, 1});
  });

  std::shared_ptr<LedController> ledController = std::make_shared<LedController>(mLed);
  motorChar->addCallback([ledController](ValueBuffer buffer) { ledController->handle(buffer); });

  mVehicleMovement->subscribe([movementChar](MovementStatus status) {
    movementChar->write(ValueBuffer{{static_cast<uint8_t>(status)}, 1});
  });
  mCarController = std::make_shared<CarMovementController>(serial, ultrasound, mVehicleMovement);
  motorChar->addCallback([this](ValueBuffer buffer) { mCarController->handle(buffer); });

  ultrasound->subscribe([serial](float distance) { serial->println(distance); });

  mBluetooth->addService(motorService.get());
  mBluetooth->addService(movementService.get());

  if (mBluetooth->start()) {
    mSerial->println("Started the bluetooth service");
  }
}

void Core::update() { mCarController->controlCar(); }
