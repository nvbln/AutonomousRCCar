#pragma once

#include "IWheel.h"
#include "IPinIO.h"

#include <memory>
#include <cmath>

class RCCarWheel : public IWheel {
public:
    static constexpr int MovementVoltage = 150; // Corresponds to 2V for Arduino Nano 33.

    RCCarWheel(std::shared_ptr<IPinIO> pinIO,
               const uint8_t forwardPin,
               const uint8_t backwardPin) : 
            mPinIO(pinIO), mForwardPin(forwardPin), mBackwardPin(backwardPin) {}

    /**
     * @see IWheel::forward()
     */
    void forward() override;

    /**
     * @see IWheel::backward()
     */
    void backward() override;

    /**
     * @see IWheel::stop()
     */
    void stop() override;

private:
    std::shared_ptr<IPinIO> mPinIO;
    const uint8_t mForwardPin, mBackwardPin;
};
