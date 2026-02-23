#include "RCCarMovement.h"

void RCCarMovement::forward() {
    if (mStatus != MovementStatus::Forwards) {
        mLeftWheel->forward();
        mRightWheel->forward();
        mStatus = MovementStatus::Forwards;
    }
}

void RCCarMovement::backward() {
    if (mStatus != MovementStatus::Backwards) {
        mLeftWheel->backward();
        mRightWheel->backward();
        mStatus = MovementStatus::Backwards;
    }
}

void RCCarMovement::turn() {
    if (mStatus != MovementStatus::Turning) {
        // Only one-directional turning is supported for now.
        mLeftWheel->forward();
        mRightWheel->backward();
        mStatus = MovementStatus::Turning;
    }
}

void RCCarMovement::stop() {
    if (mStatus != MovementStatus::Still) {
        mLeftWheel->stop();
        mRightWheel->stop();
        mStatus = MovementStatus::Still;
    }
}

MovementStatus RCCarMovement::movementStatus() const {
    return mStatus;
}
