#pragma once

#include "ISerial.h"
#include "IIMUAccelerator.h"
#include "IAccelerator.h"
#include "IClock.h"
#include "Event.h"

#include <cstdint>
#include <memory>

/**
 * @class ArduinoAccelerator
 * @brief Accelerator implementation for the Arduino.
 */
class ArduinoAccelerator : public IAccelerator {
public:
    /**
     * @brief Creates an object representing the accelerator in the board.
     */
     ArduinoAccelerator(std::shared_ptr<ISerial> serial,
                        std::shared_ptr<IIMUAccelerator> accelerator,
                        std::shared_ptr<IClock> clock) : 
            mSerial(serial), mAccelerator(accelerator), mClock(clock) {
        mAccelerator->begin();
        mLastSampleTime = mClock->micros();
     }

     /**
      * @see IAccelerator::addCallback()
      */
     bool addCallback(Callback callback) override {
        return event.subscribe(callback);
     }

     /**
      * @see IAccelerator::update()
      */
     void update() override;

private:
   std::shared_ptr<ISerial> mSerial;
   std::shared_ptr<IIMUAccelerator> mAccelerator;
   std::shared_ptr<IClock> mClock;
   unsigned long mLastSampleTime;

   Event<Callback, 5, AccelerationData> event;
};
