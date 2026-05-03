#include "MotionStatusEvaluator.h"
#include "IAccelerator.h"
#include "MotionStatus.h"
#include "strategies/IMotionEvaluationStrategy.h"
#include "strategies/ISpikeDetectionStrategy.h"

#include <CircularBuffer.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::NiceMock;
using ::testing::Return;

class MockAccelerator : public IAccelerator {
public:
  MOCK_METHOD(bool, addCallback, (Callback callback), (override));
  MOCK_METHOD(void, update, (), (override));
};

class MockSpikeDetectionStrategy : public ISpikeDetectionStrategy {
public:
  MOCK_METHOD(bool, detectSpike,
              ((CircularBuffer<float, 50> * bufferX), (CircularBuffer<float, 50> * bufferY)),
              (const, override));
};

class MockMotionEvaluationStrategy : public IMotionEvaluationStrategy {
public:
  MOCK_METHOD(MotionStatus, evaluateCurrentMotion, (const MotionStatus status, const bool spike),
              (const, override));
};

MATCHER(BufferContainsOneItem, "CircularBuffer contains one item") {
  return arg && arg->size() == 1;
}

TEST(MotionStatusEvaluatorTests, shouldUpdateInternalData) {
  auto mockAccelerator = NiceMock<MockAccelerator>();
  auto mockSpikeStrategy = NiceMock<MockSpikeDetectionStrategy>();
  auto mockMotionStrategy = NiceMock<MockMotionEvaluationStrategy>();

  IAccelerator::Callback callback;

  // Check if no data is there, and therefore the default motion is returned.
  EXPECT_CALL(mockAccelerator, addCallback)
      .WillOnce(::testing::DoAll(::testing::SaveArg<0>(&callback), Return(true)));

  auto evaluator = MotionStatusEvaluator(&mockAccelerator, &mockSpikeStrategy, &mockMotionStrategy);

  EXPECT_EQ(MotionStatus::Still, evaluator.status());

  // Check if the first data arrived (and the default motion is still returned).
  AccelerationData data{1, 2, 3};
  callback(data);

  EXPECT_CALL(mockMotionStrategy, evaluateCurrentMotion)
      .Times(1)
      .WillOnce(Return(MotionStatus::Still));

  EXPECT_CALL(mockSpikeStrategy, detectSpike(BufferContainsOneItem(), BufferContainsOneItem()))
      .Times(1)
      .WillOnce(Return(false));

  EXPECT_EQ(MotionStatus::Still, evaluator.status());
}
