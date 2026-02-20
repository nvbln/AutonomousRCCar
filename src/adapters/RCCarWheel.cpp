#include "RCCarWheel.h"

void RCCarWheel::forward() {
    stop();
    mPinIO->analogWrite(mForwardPin, MovementVoltage);
}

void RCCarWheel::backward() {
    stop();
    mPinIO->analogWrite(mBackwardPin, MovementVoltage);
}

void RCCarWheel::stop() {
    mPinIO->analogWrite(mForwardPin, 0);
    mPinIO->analogWrite(mBackwardPin, 0);
}
