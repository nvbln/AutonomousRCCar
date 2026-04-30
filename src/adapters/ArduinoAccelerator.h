#pragma once

#include "Event.h"
#include "IAccelerator.h"
#include "IClock.h"
#include "IIMUAccelerator.h"
#include "ISerial.h"

#include <cstdint>

/**
 * @class ArduinoAccelerator
 * @brief Accelerator implementation for the Arduino.
 */
class ArduinoAccelerator : public IAccelerator {
public:
  /**
   * @brief Creates an object representing the accelerator in the board.
   */
  ArduinoAccelerator(ISerial *serial, IIMUAccelerator *accelerator, IClock *clock)
      : mSerial(serial), mAccelerator(accelerator), mClock(clock) {
    mAccelerator->begin();
    mLastSampleTime = mClock->micros();
  }

  /**
   * @see IAccelerator::addCallback()
   */
  bool addCallback(Callback callback) override { return event.subscribe(callback); }

  /**
   * @see IAccelerator::update()
   */
  void update() override;

private:
  ISerial *mSerial;
  IIMUAccelerator *mAccelerator;
  IClock *mClock;
  unsigned long mLastSampleTime;

  Event<Callback, 5, AccelerationData> event;
};
