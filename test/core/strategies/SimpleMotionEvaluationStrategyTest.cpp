#include "strategies/SimpleMotionEvaluationStrategy.h"
#include "MotionStatus.h"

#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(SimpleMotionEvaluationStrategyTests, WhenStillAndSpikedShouldReturnMoving) {
    auto strategy = std::make_shared<SimpleMotionEvaluationStrategy>();

    EXPECT_EQ(MotionStatus::Moving, 
            strategy->evaluateCurrentMotion(MotionStatus::Still, true));
}

TEST(SimpleMotionEvaluationStrategyTests, WhenMovingAndSpikedShouldReturnBlocked) {
    auto strategy = std::make_shared<SimpleMotionEvaluationStrategy>();

    EXPECT_EQ(MotionStatus::Blocked, 
            strategy->evaluateCurrentMotion(MotionStatus::Moving, true));
}

TEST(SimpleMotionEvaluationStrategyTests, WhenBlockedAndNoSpikeShouldReturnStill) {
    auto strategy = std::make_shared<SimpleMotionEvaluationStrategy>();

    EXPECT_EQ(MotionStatus::Still, 
            strategy->evaluateCurrentMotion(MotionStatus::Blocked, false));
}

TEST(SimpleMotionEvaluationStrategyTests, WhenNoSpikeAndNotBlockedShouldReturnSame) {
    auto strategy = std::make_shared<SimpleMotionEvaluationStrategy>();

    EXPECT_EQ(MotionStatus::Still, 
            strategy->evaluateCurrentMotion(MotionStatus::Still, false));

    EXPECT_EQ(MotionStatus::Moving, 
            strategy->evaluateCurrentMotion(MotionStatus::Moving, false));
}

TEST(SimpleMotionEvaluationStrategyTests, WhenBlockedAndSpikedShouldReturnBlocked) {
    auto strategy = std::make_shared<SimpleMotionEvaluationStrategy>();

    EXPECT_EQ(MotionStatus::Blocked, 
            strategy->evaluateCurrentMotion(MotionStatus::Blocked, true));
}
