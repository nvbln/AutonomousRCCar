#include "IAccelerator.h"
#include "strategies/ISpikeDetectionStrategy.h"
#include "strategies/IMotionEvaluationStrategy.h"
#include "MotionStatusEvaluator.h"
#include "MotionStatus.h"

#include <CircularBuffer.hpp>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

class MockAccelerator : public IAccelerator {
public:
    MOCK_METHOD(bool, addCallback, (Callback callback), (override));
    MOCK_METHOD(void, update, (), (override));
};

class MockSpikeDetectionStrategy : public ISpikeDetectionStrategy {
public:
    MOCK_METHOD(bool, 
                detectSpike, 
                (
                    (const std::shared_ptr<CircularBuffer<float, 50>> bufferX), 
                    (const std::shared_ptr<CircularBuffer<float, 50>> bufferY)
                ),
                (const, override)
    );
};

class MockMotionEvaluationStrategy : public IMotionEvaluationStrategy {
public:
    MOCK_METHOD(MotionStatus,
                evaluateCurrentMotion,
                (const MotionStatus status, const bool spike),
                (const, override)
    );
};

MATCHER(BufferContainsOneItem, "CircularBuffer contains one item") {
    return arg && arg->size() == 1;
}

TEST(MotionStatusEvaluatorTests, shouldUpdateInternalData) {
    auto mockAccelerator = std::make_shared<NiceMock<MockAccelerator>>();
    auto mockSpikeStrategy = std::make_shared<NiceMock<MockSpikeDetectionStrategy>>();
    auto mockMotionStrategy = std::make_shared<NiceMock<MockMotionEvaluationStrategy>>();

    IAccelerator::Callback callback;

    // Check if no data is there, and therefore the default motion is returned.
    EXPECT_CALL(*mockAccelerator, addCallback).WillOnce(::testing::DoAll(
        ::testing::SaveArg<0>(&callback),
        Return(true)
    ));

    auto evaluator = std::make_shared<MotionStatusEvaluator>(mockAccelerator,
                                                             mockSpikeStrategy,
                                                             mockMotionStrategy);
    
    EXPECT_EQ(MotionStatus::Still, evaluator->status()); 

    // Check if the first data arrived (and the default motion is still returned).     
    AccelerationData data{1, 2, 3}; 
    callback(data);

    EXPECT_CALL(*mockMotionStrategy, evaluateCurrentMotion)
            .Times(1) 
            .WillOnce(Return(MotionStatus::Still));

    EXPECT_CALL(*mockSpikeStrategy,
                detectSpike(BufferContainsOneItem(), BufferContainsOneItem())
               )
               .Times(1)
               .WillOnce(Return(false));
    
    EXPECT_EQ(MotionStatus::Still, evaluator->status());
}
