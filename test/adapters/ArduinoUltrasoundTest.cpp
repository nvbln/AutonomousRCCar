#include "ArduinoUltrasound.h"
#include "IUltrasoundSource.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

class MockUltrasoundSource : public IUltrasoundSource {
public:
    MOCK_METHOD(unsigned long, duration, (), (const, override));
    MOCK_METHOD(void, measureDuration, (), (override));
};

TEST(ArduinoUltrasoundTests, ultrasoundIsCorrectlyConvertedToDistance) {
    auto mockUltrasoundSource = NiceMock<MockUltrasoundSource>();

    auto ultrasound = std::make_shared<ArduinoUltrasound>(&mockUltrasoundSource);

    unsigned long measuredTime = 10000;
    EXPECT_CALL(mockUltrasoundSource, duration).WillOnce(Return(measuredTime));
    
    ultrasound->addCallback([&measuredTime](float distance) {
        EXPECT_EQ(measuredTime * 0.01715, distance);
    });

    ultrasound->update();
}
