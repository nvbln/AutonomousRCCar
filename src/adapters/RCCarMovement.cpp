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

void RCCarMovement::turnDegrees(int degrees) {
    // TODO: Implement
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
