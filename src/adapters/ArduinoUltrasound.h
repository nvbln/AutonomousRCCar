#pragma once

#include "IUltrasound.h"
#include "IClock.h"
#include "IPinIO.h"

#include <memory>

/**
 * @class ArduinoUltrasound
 * @brief implements the communication with the ultrasound component.
 */
class ArduinoUltrasound : public IUltrasound {
public:
    /**
     * @brief creates an object that handles the Ultrasound distance measurements.
     *
     */
    ArduinoUltrasound(std::shared_ptr<IClock> clock,
                      std::shared_ptr<IPinIO> pinIO,
                      uint8_t trigPin,
                      uint8_t echoPin) :
            mClock(clock), mPinIO(pinIO), mTrigPin(trigPin), mEchoPin(echoPin) {
        mPinIO->pinMode(mTrigPin, PinIOMode::Output);
        mPinIO->pinMode(mEchoPin, PinIOMode::Input);
    }

    /**
     * @see IUltrasound::addCallback()
     */
    bool addCallback(UltrasoundCallback callback) override;

    /**
     * @see IUltrasound::update()
     */
    void update() override;
private:
    const std::shared_ptr<IClock> mClock;
    const std::shared_ptr<IPinIO> mPinIO;
    const uint8_t mTrigPin, mEchoPin;

    static const uint8_t mMaxNumCallbacks = 5;
    uint8_t mNumCallbacks = 0;
    UltrasoundCallback mCallbacks[mMaxNumCallbacks];
};
