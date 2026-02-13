#include "ArduinoAccelerator.h"

bool ArduinoAccelerator::addCallback(AcceleratorCallback callback) {
    if (mNumCallbacks >= mMaxNumCallbacks) {
        return false;
    }
    
    mCallbacks[mNumCallbacks] = callback;
    mNumCallbacks++;

    return true;
}

void ArduinoAccelerator::update() {
    unsigned long currentTime = mClock->micros();
    if (currentTime - mLastSampleTime > 10000) { // 10 ms
        mLastSampleTime = currentTime;
        AccelerationData data{};
        mAccelerator->readAcceleration(data.x, data.y, data.z);
        for (int i = 0; i < mNumCallbacks; i++) {
            mCallbacks[i](data);
        }
    }
}
