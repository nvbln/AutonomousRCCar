#include "CarMovementController.h"
#include "IUltrasound.h"
#include "IVehicleMovement.h"
#include "MockSerial.h"
#include "ValueBuffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::SaveArg;

class MockUltrasound : public IUltrasound {
public:
  MOCK_METHOD(bool, addCallback, (IUltrasound::Callback callback), (override));
  MOCK_METHOD(void, update, (), (override));
};

class MockVehicleMovement : public IVehicleMovement {
public:
  MOCK_METHOD(void, forward, (), (override));
  MOCK_METHOD(void, backward, (), (override));
  MOCK_METHOD(void, turn, (), (override));
  MOCK_METHOD(void, stop, (), (override));
  MOCK_METHOD(MovementStatus, movementStatus, (), (const, override));
  MOCK_METHOD(void, subscribe, (Callback callback), (override));
};

class CarMovementControllerTest : public ::testing::Test {
protected:
  std::shared_ptr<NiceMock<MockSerial>> mockSerial;
  std::shared_ptr<NiceMock<MockUltrasound>> mockUltrasound;
  std::shared_ptr<NiceMock<MockVehicleMovement>> mockCarMovement;
  MovementStatus status;
  IUltrasound::Callback callback;

  void SetUp() override {
    mockSerial = std::make_shared<NiceMock<MockSerial>>();
    mockUltrasound = std::make_shared<NiceMock<MockUltrasound>>();
    mockCarMovement = std::make_shared<NiceMock<MockVehicleMovement>>();

    ON_CALL(*mockUltrasound, addCallback)
        .WillByDefault(::testing::DoAll(SaveArg<0>(&callback), Return(true)));

    status = MovementStatus::Still;

    ON_CALL(*mockCarMovement, movementStatus).WillByDefault(Invoke([this]() { return status; }));

    ON_CALL(*mockCarMovement, forward).WillByDefault(Invoke([this]() {
      status = MovementStatus::Forwards;
    }));

    ON_CALL(*mockCarMovement, backward).WillByDefault(Invoke([this]() {
      status = MovementStatus::Backwards;
    }));

    ON_CALL(*mockCarMovement, turn).WillByDefault(Invoke([this]() {
      status = MovementStatus::Turning;
    }));

    ON_CALL(*mockCarMovement, stop).WillByDefault(Invoke([this]() {
      status = MovementStatus::Still;
    }));
  }
};

TEST_F(CarMovementControllerTest, shouldStopWhenTooCloseToObstacle) {
  std::unique_ptr<CarMovementController> controller =
      std::make_unique<CarMovementController>(mockSerial, mockUltrasound, mockCarMovement);

  controller->handle(ValueBuffer{{1}, 1});

  callback(100);
  controller->controlCar();
  EXPECT_EQ(MovementStatus::Forwards, status);

  callback(5);
  controller->controlCar();
  EXPECT_EQ(MovementStatus::Still, status);
}

TEST_F(CarMovementControllerTest, shouldTurnWhenCloseToObstacle) {
  std::unique_ptr<CarMovementController> controller =
      std::make_unique<CarMovementController>(mockSerial, mockUltrasound, mockCarMovement);

  controller->handle(ValueBuffer{{1}, 1});

  callback(100);
  controller->controlCar();
  EXPECT_EQ(MovementStatus::Forwards, status);

  callback(20);
  controller->controlCar();
  EXPECT_EQ(MovementStatus::Turning, status);

  callback(100);
  controller->controlCar();
  EXPECT_EQ(MovementStatus::Forwards, status);
}
