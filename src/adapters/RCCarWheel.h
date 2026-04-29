#pragma once

#include "IPinIO.h"
#include "IWheel.h"

#include <cmath>

class RCCarWheel : public IWheel {
public:
  static constexpr int MovementVoltage = 75; // Corresponds to 1V for Arduino Nano 33.

  RCCarWheel(IPinIO *pinIO, const uint8_t forwardPin, const uint8_t backwardPin)
      : mPinIO(pinIO), mForwardPin(forwardPin), mBackwardPin(backwardPin) {}

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
  IPinIO *mPinIO;
  const uint8_t mForwardPin, mBackwardPin;
};
