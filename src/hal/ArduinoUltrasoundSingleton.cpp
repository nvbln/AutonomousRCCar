#include "ArduinoUltrasoundSingleton.h"

volatile bool ArduinoUltrasoundSingleton::mIsHigh = false;
volatile unsigned long ArduinoUltrasoundSingleton::mPulseStart = 0;
volatile unsigned long ArduinoUltrasoundSingleton::mPulseWidth = -1;

ArduinoUltrasoundSingleton* ArduinoUltrasoundSingleton::mSingleton{nullptr};

ArduinoUltrasoundSingleton* ArduinoUltrasoundSingleton::instance(const uint8_t trigPin,
                                                                 const uint8_t echoPin) {
    if (mSingleton == nullptr) {
        mSingleton = new ArduinoUltrasoundSingleton(trigPin, echoPin);
    }

    return mSingleton;
}

unsigned long ArduinoUltrasoundSingleton::duration() const {
    noInterrupts();
    unsigned long width = mPulseWidth;
    interrupts();
    return width;
}

void ArduinoUltrasoundSingleton::measureDuration() {
    // Only attempt new measurements after timeout.
    // The echo pin will lower its signal by itself when timed out.
    noInterrupts();
    bool stillMeasuring = mIsHigh;
    interrupts();

    if (!stillMeasuring) {
        digitalWrite(mTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(mTrigPin, LOW);
    }
}

void ArduinoUltrasoundSingleton::echoPulseTimer() {
    if (mIsHigh) {
        mPulseWidth = micros() - mPulseStart;
        mIsHigh = false;
    } else {
        mPulseStart = micros();
        mIsHigh = true;
    }
}
