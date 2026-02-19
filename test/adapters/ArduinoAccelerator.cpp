#include "MockSerial.h"
#include "IIMUAccelerator.h"
#include "MockClock.h"
#include "ArduinoAccelerator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

class MockIMUAccelerator : public IIMUAccelerator {
public:
    MOCK_METHOD(int, begin, (), (override));
    MOCK_METHOD(int, accelerationAvailable, (), (const, override));
    MOCK_METHOD(int, readAcceleration, (float& x, float& y, float& z), (const, override));
};

TEST(ArduinoAcceleratorTests, callbacksOnlyAfter10ms) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockIMUAccelerator = std::make_shared<NiceMock<MockIMUAccelerator>>();
    auto mockClock = std::make_shared<MockClock>();

    EXPECT_CALL(*mockClock, micros())
        .WillOnce(Return(0))
        .WillOnce(Return(10000))
        .WillOnce(Return(10001));

    auto arduinoAccelerator = std::make_shared<ArduinoAccelerator>(
            mockSerial,
            mockIMUAccelerator,
            mockClock
    );

    bool calledBack = false;

    arduinoAccelerator->addCallback([&calledBack](AccelerationData _) {
        calledBack = true;
    });

    arduinoAccelerator->update();
    EXPECT_FALSE(calledBack);

    arduinoAccelerator->update();
    EXPECT_TRUE(calledBack);
}
