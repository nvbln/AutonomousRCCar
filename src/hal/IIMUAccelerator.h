#pragma once

/**
 * @class IIMUAccelerator
 * @brief thin wrapper for the IMU sensor on the Arduino BLE Sense Rev2.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 */
class IIMUAccelerator {
public:
    virtual ~IIMUAccelerator() = default;

    /**
     * @brief Initialises the sensor and loads the configuration.
     *
     * @see the Arduino_BMI270_BMM150 library.
     * @return whether the initialisation was successful.
     *         0 on success and negative error codes on failure.
     */
    virtual int begin() = 0;

    /**
     * @brief reports whether the accelerometer is enabled and initialised.
     *
     * @see the Arduino_BMI_270_BMM150 library.
     * @return 1 if the accelerometer is active and can be read.
     *         0 if the accelerometer is not available.
     */
    virtual int accelerationAvailable() const = 0;

    /**
     * @brief returns the current IMU acceleration values.
     *
     * @see the Arduino_BMI270_BMM150 library.
     *
     * @param x The variable to store the x-axis acceleration.
     * @param y The variable to store the y-axis acceleration.
     * @param z The variable to store the z-axis acceleration.
     * @return whether the readout was successful.
     *         0 on success and negative error codes on failure.
     */
    virtual int readAcceleration(float& x, float& y, float& z) const = 0;
};
