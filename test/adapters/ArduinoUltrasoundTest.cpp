#include "MockClock.h"
#include "MockPinIO.h"
#include "ArduinoUltrasound.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

TEST(ArduinoUltrasoundTests, ultrasoundIsCorrectlyConvertedToDistance) {
    auto mockClock = std::make_shared<NiceMock<MockClock>>();
    const auto mockPinIO = std::make_shared<NiceMock<MockPinIO>>();

    auto ultrasound = std::make_shared<ArduinoUltrasound>(mockClock, mockPinIO, 9, 10);

    unsigned long measuredTime = 10000;
    EXPECT_CALL(*mockPinIO, pulseIn).WillOnce(Return(measuredTime));
    
    ultrasound->addCallback([&measuredTime](float distance) {
        EXPECT_EQ(measuredTime * 0.01715, distance);
    });

    ultrasound->update();
}
