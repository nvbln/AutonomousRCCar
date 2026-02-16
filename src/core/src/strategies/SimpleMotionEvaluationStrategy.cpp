#include "SimpleMotionEvaluationStrategy.h"

MotionStatus SimpleMotionEvaluationStrategy::evaluateCurrentMotion(
        const MotionStatus status, 
        const bool spike) const {
    if (status == MotionStatus::Still && spike) {
        return MotionStatus::Moving;
    }

    if (status == MotionStatus::Moving && spike) {
        return MotionStatus::Blocked;
    }

    if (status == MotionStatus::Blocked && !spike) {
        return MotionStatus::Still;
    }

    return status;
};
