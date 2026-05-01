#include "LedController.h"
#include "ILed.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockLed : public ILed {
public:
  MOCK_METHOD(void, turn, (), (override));
  MOCK_METHOD(void, turnOn, (), (override));
  MOCK_METHOD(void, turnOff, (), (override));
};

TEST(LedControllerTests, byteNonZeroShouldTurnLedOn) {
  MockLed led = MockLed();
  EXPECT_CALL(led, turnOn()).Times(2);

  std::unique_ptr<LedController> controller = std::make_unique<LedController>(&led);
  ValueBuffer buffer{};

  buffer.data[0] = 1;
  buffer.length = 1;
  controller->handle(buffer);

  buffer.data[0] = 5;
  controller->handle(buffer);
}

TEST(LedControllerTests, byteZeroShouldTurnLedOff) {
  MockLed led = MockLed();
  EXPECT_CALL(led, turnOff()).Times(1);

  std::unique_ptr<LedController> controller = std::make_unique<LedController>(&led);
  ValueBuffer buffer{};

  buffer.data[0] = 0;
  buffer.length = 1;
  controller->handle(buffer);
}
