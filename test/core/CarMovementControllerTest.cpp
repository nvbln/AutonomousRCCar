#include "MockSerial.h"
#include "IUltrasound.h"
#include "IVehicleMovement.h"
#include "CarMovementController.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

using ::testing::Return;
using ::testing::SaveArg;
using ::testing::NiceMock;
using ::testing::Invoke;

class MockUltrasound : public IUltrasound {
public:
    MOCK_METHOD(bool, addCallback, (IUltrasound::Callback callback), (override));
    MOCK_METHOD(void, update, (), (override));
};

class MockVehicleMovement : public IVehicleMovement {
public:
    MOCK_METHOD(void, forward, (), (override));
    MOCK_METHOD(void, backward, (), (override));
    MOCK_METHOD(void, turnDegrees, (int degrees), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(MovementStatus, movementStatus, (), (const, override));
};

TEST(CarMovementControllerTests, shouldStopWhenCloseToObstacle) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockUltrasound = std::make_shared<MockUltrasound>();

    IUltrasound::Callback callback;
    ON_CALL(*mockUltrasound, addCallback).WillByDefault(::testing::DoAll(
        SaveArg<0>(&callback),
        Return(true)
    ));

    auto mockCarMovement = std::make_shared<MockVehicleMovement>();
    MovementStatus status = MovementStatus::Still; 
    ON_CALL(*mockCarMovement, movementStatus).WillByDefault(Invoke([&status]() {
        return status;
    }));
    ON_CALL(*mockCarMovement, forward).WillByDefault(Invoke([&status]() {
        status = MovementStatus::Forwards;
    }));
    ON_CALL(*mockCarMovement, backward).WillByDefault(Invoke([&status]() {
        status = MovementStatus::Backwards;
    }));
    ON_CALL(*mockCarMovement, stop).WillByDefault(Invoke([&status]() {
        status = MovementStatus::Still;
    }));

    std::unique_ptr<CarMovementController> controller 
            = std::make_unique<CarMovementController>(mockSerial,
                                                      mockUltrasound,
                                                      mockCarMovement
    );

    // Set the initial distance and check if car starts driving.
    callback(100);
    controller->controlCar();
    EXPECT_EQ(MovementStatus::Forwards, status);

    // Set the distance too low and check if the car stops driving.
    callback(5);
    //ON_CALL(*mockCarMovement, movementStatus).WillByDefault(Return(MovementStatus::Forwards));
    controller->controlCar();
    EXPECT_EQ(MovementStatus::Still, status);
};
