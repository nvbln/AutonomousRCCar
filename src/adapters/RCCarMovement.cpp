#include "RCCarMovement.h"

void RCCarMovement::forward() {
    mLeftWheel->forward();
    mRightWheel->forward();
}

void RCCarMovement::backward() {
    mLeftWheel->backward();
    mRightWheel->backward();
}

void RCCarMovement::turnDegrees(int degrees) {
    // TODO: Implement
}

void RCCarMovement::stop() {
    mLeftWheel->stop();
    mRightWheel->stop();
}
