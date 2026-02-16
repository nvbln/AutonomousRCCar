#pragma once

#include "IMotionEvaluationStrategy.h"

/**
 * @class SimpleMotionEvaluationStrategy
 * @brief Uses simple if-else statements to estimate the current MotionStatus
 *
 * The following strategy is used to evaluate the current MotionStatus:
 * + If a spike occurs when there is no motor movement -> vehicle started moving.
 * + If a spike occurs while the vehicle is moving -> the vehicle is blocked.
 * + If the vehicle is not blocked anymore, and there is no spike -> vehicle stands still.
 * This strategy is in no way definite, and is very likely to change.
 */
class SimpleMotionEvaluationStrategy : public IMotionEvaluationStrategy {
public:
    /**
     * @brief creates an instance of the strategy.
     */
    SimpleMotionEvaluationStrategy() {};

    /**
     * @brief implements the strategy described for this class.
     * 
     * @see IMotionEvaluationStrategy::evaluateCurrentMotion()
     */
    MotionStatus evaluateCurrentMotion(const MotionStatus status, const bool spike) const override;
};
