#pragma once

#include "MotionStatus.h"

/**
 * @class IMotionEvaluationStrategy
 * @brief interface for strategies that determine the current motion of the vehicle.
 */
class IMotionEvaluationStrategy {
public:
    virtual ~IMotionEvaluationStrategy() = default;

    /**
     * @brief returns the current motion status based on the given vehicle data.
     *
     * @params status The current motion status of the vehicle.
     * @params spike Whether a spike has occurred in the most recent IMU data.
     * @return The new motion status.
     */
    virtual MotionStatus evaluateCurrentMotion(const MotionStatus status, const bool spike) const = 0;
};
