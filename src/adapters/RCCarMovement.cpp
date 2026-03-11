#include "RCCarMovement.h"

void RCCarMovement::forward() {
  if (mStatus != MovementStatus::Forwards) {
    mLeftWheel->forward();
    mRightWheel->forward();
    updateStatus(MovementStatus::Forwards);
  }
}

void RCCarMovement::backward() {
  if (mStatus != MovementStatus::Backwards) {
    mLeftWheel->backward();
    mRightWheel->backward();
    updateStatus(MovementStatus::Backwards);
  }
}

void RCCarMovement::turn() {
  if (mStatus != MovementStatus::Turning) {
    // Only one-directional turning is supported for now.
    mLeftWheel->forward();
    mRightWheel->backward();
    updateStatus(MovementStatus::Turning);
  }
}

void RCCarMovement::stop() {
  if (mStatus != MovementStatus::Still) {
    mLeftWheel->stop();
    mRightWheel->stop();
    updateStatus(MovementStatus::Still);
  }
}

MovementStatus RCCarMovement::movementStatus() const { return mStatus; }
