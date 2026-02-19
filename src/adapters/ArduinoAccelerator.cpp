#include "ArduinoAccelerator.h"

void ArduinoAccelerator::update() {
    unsigned long currentTime = mClock->micros();
    if (currentTime - mLastSampleTime > 10000) { // 10 ms
        mLastSampleTime = currentTime;
        AccelerationData data{};
        mAccelerator->readAcceleration(data.x, data.y, data.z);
        event.notify(data);
    }
}
