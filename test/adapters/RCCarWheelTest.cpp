#include "RCCarWheel.h"
#include "MockPinIO.h"

#include <gtest/gtest.h>

using ::testing::NiceMock;

TEST(RCCarWheelTests, turnsAndStopsWheel) {
  auto mockPinIO = NiceMock<MockPinIO>();
  const uint8_t forwardPin = 1;
  const uint8_t backwardPin = 2;

  auto rcCarWheel = RCCarWheel(&mockPinIO, forwardPin, backwardPin);

  // Check if wheel is turned forwards.
  EXPECT_CALL(mockPinIO, analogWrite(backwardPin, 0)).Times(1);
  EXPECT_CALL(mockPinIO, analogWrite(forwardPin, 0)).Times(::testing::AnyNumber());
  EXPECT_CALL(mockPinIO, analogWrite(forwardPin, ::testing::Gt(0))).Times(1);
  rcCarWheel.forward();

  // Check if wheel is turned backwards.
  EXPECT_CALL(mockPinIO, analogWrite(forwardPin, 0)).Times(1);
  EXPECT_CALL(mockPinIO, analogWrite(backwardPin, 0)).Times(::testing::AnyNumber());
  EXPECT_CALL(mockPinIO, analogWrite(backwardPin, ::testing::Gt(0))).Times(1);
  rcCarWheel.backward();

  // Check if wheel stops.
  EXPECT_CALL(mockPinIO, analogWrite(forwardPin, 0)).Times(1);
  EXPECT_CALL(mockPinIO, analogWrite(backwardPin, 0)).Times(1);
  rcCarWheel.stop();
}
