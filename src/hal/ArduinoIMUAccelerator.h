#pragma once

#include "IIMUAccelerator.h"

#include "Arduino_BMI270_BMM150.h"

/**
 * @class ArduinoIMUAccelerator
 * @brief wrapper implementation of the Arduino IMU Accelerator
 *
 * This connects the IIMUAccelerator wrapper to the Arduino_BMI270_BMM150 library,
 * such that the application can run on Arduino devices.
 */
class ArduinoIMUAccelerator : public IIMUAccelerator {
public:
    ArduinoIMUAccelerator() {};

    /**
     * @see IIMUAccelerator::begin()
     */
    int begin() override {
        return IMU.begin();
    }

    /**
     * @see IIMUAccelerator::accelerationAvailable()
     */
    int accelerationAvailable() const override {
        return IMU.accelerationAvailable();
    }

    /**
     * @see IIMUAccelerator::readAcceleration()
     */
    int readAcceleration(float& x, float& y, float& z) const override {
        return IMU.readAcceleration(x, y, z);
    }
};
