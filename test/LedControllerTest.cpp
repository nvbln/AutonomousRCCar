#include "ILed.h"
#include "LedController.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockLed : public ILed {
 public:
    MOCK_METHOD(void, turn, (), (override));
    MOCK_METHOD(void, turnOn, (), (override));
    MOCK_METHOD(void, turnOff, (), (override));
};

TEST(LedControllerTests, byteNonZeroShouldTurnLedOn) {
    std::shared_ptr<MockLed> led = std::make_shared<MockLed>();
    EXPECT_CALL(*led, turnOn())
        .Times(2);

    std::unique_ptr<LedController> controller = std::make_unique<LedController>(led);
    ValueBuffer buffer{};

    buffer.data[0] = 1;
    buffer.length = 1;
    controller->handle(buffer); 

    buffer.data[0] = 5;
    controller->handle(buffer); 
}

TEST(LedControllerTests, byteZeroShouldTurnLedOff) {
    std::shared_ptr<MockLed> led = std::make_shared<MockLed>();
    EXPECT_CALL(*led, turnOff())
        .Times(1);

    std::unique_ptr<LedController> controller = std::make_unique<LedController>(led);
    ValueBuffer buffer{};

    buffer.data[0] = 0;
    buffer.length = 1;
    controller->handle(buffer); 
}
