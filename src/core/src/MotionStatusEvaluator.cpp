#include "MotionStatusEvaluator.h"

#include <CircularBuffer.hpp>

MotionStatus MotionStatusEvaluator::status() {
    if (!mHasNewData) {
        return mCurrentStatus;
    }
    mHasNewData = false;

    bool spike = mSpikeStrategy->detectSpike(mBufferX, mBufferY);
    mCurrentStatus = mMotionStrategy->evaluateCurrentMotion(mCurrentStatus, spike);
    return mCurrentStatus;
}

void MotionStatusEvaluator::updateData(AccelerationData data) {
    mBufferX->push(data.x * 9.8); // converts g to m/s2 
    mBufferY->push(data.y * 9.8); // converts g to m/s2

    mHasNewData = true;
}
