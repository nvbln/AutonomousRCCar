#include "RCCarMovement.h"
#include "IWheel.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// TODO: Add test for turnDegrees once it's implemented.

using ::testing::NiceMock;

class MockWheel : public IWheel {
public:
  MOCK_METHOD(void, forward, (), (override));
  MOCK_METHOD(void, backward, (), (override));
  MOCK_METHOD(void, stop, (), (override));
};

TEST(RCCarMovementTests, turnsAndStopsWheels) {
  const auto mockWheel1 = std::make_shared<MockWheel>();
  const auto mockWheel2 = std::make_shared<MockWheel>();

  auto rcCarMovement = std::make_shared<RCCarMovement>(mockWheel1, mockWheel2);

  // Check if wheels are turned forwards.
  EXPECT_CALL(*mockWheel1, forward).Times(1);
  EXPECT_CALL(*mockWheel2, forward).Times(1);
  rcCarMovement->forward();

  // Check if wheels are turned backwards.
  EXPECT_CALL(*mockWheel1, backward).Times(1);
  EXPECT_CALL(*mockWheel2, backward).Times(1);
  rcCarMovement->backward();

  // Check if wheels are stopped.
  EXPECT_CALL(*mockWheel1, stop).Times(1);
  EXPECT_CALL(*mockWheel2, stop).Times(1);
  rcCarMovement->stop();
}

TEST(RCCarMovementTests, reportsMovementStatusChanges) {
  const auto mockWheel1 = std::make_shared<NiceMock<MockWheel>>();
  const auto mockWheel2 = std::make_shared<NiceMock<MockWheel>>();

  std::vector<MovementStatus> expected = {MovementStatus::Forwards, MovementStatus::Backwards,
                                          MovementStatus::Turning, MovementStatus::Still};
  std::vector<MovementStatus> received;
  auto rcCarMovement = std::make_shared<RCCarMovement>(mockWheel1, mockWheel2);
  rcCarMovement->subscribe([&received](MovementStatus status) { received.push_back(status); });

  rcCarMovement->forward();
  rcCarMovement->backward();
  rcCarMovement->turn();
  rcCarMovement->stop();

  EXPECT_EQ(expected, received);
}
