#include "IClock.h"
#include "IPinIO.h"

#include "ArduinoUltrasound.h"

void ArduinoUltrasound::update() {
    mPinIO->digitalWrite(mTrigPin, PinIOValue::High);
    mClock->delayMicroseconds(10); // make a 10 uS pulse to activate scanning.
    mPinIO->digitalWrite(mTrigPin, PinIOValue::Low);

    // Timeout limits the sensing range to ~120cm.
    float duration = mPinIO->pulseIn(mEchoPin, PinIOValue::High, 10000);
    float distance = duration * 0.01715; // sound of speed in cm/us divided by 2.

    event.notify(distance);
}
