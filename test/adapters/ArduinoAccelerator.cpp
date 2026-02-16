#include "MockSerial.h"
#include "IIMUAccelerator.h"
#include "IClock.h"
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

class MockClock : public IClock {
public:
    MOCK_METHOD(unsigned long, micros, (), (const, override));
};

TEST(ArduinoAcceleratorTests, onlyAddedCallbacksAreTriggered) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockIMUAccelerator = std::make_shared<NiceMock<MockIMUAccelerator>>();
    auto mockClock = std::make_shared<MockClock>();

    EXPECT_CALL(*mockClock, micros)
        .WillOnce(Return(0))
        .WillRepeatedly(Return(11000));

    auto arduinoAccelerator = std::make_shared<ArduinoAccelerator>(
            mockSerial,
            mockIMUAccelerator,
            mockClock
    );

    const int numCallbacks = 6; // max num callbacks is 5
    bool calledBack[numCallbacks] = { false }; 

    for (int i = 0; i < numCallbacks; i++) {
        arduinoAccelerator->addCallback([i, &calledBack](AccelerationData _) {
            calledBack[i] = true; 
        });
    }

    arduinoAccelerator->update();

    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(calledBack[i]);
    }
    EXPECT_FALSE(calledBack[5]);
}

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
