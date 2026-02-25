#pragma once

#include "IUltrasoundSource.h"

#include <cstdint>

#include <Arduino.h>

/**
 * @class ArduinoUltrasoundSingleton
 * @brief Handles the HC-SR04 Ultrasound component.
 *
 * The HC-SR04 component works by a trigger to the
 * 'trigger pin' at which point it sends an ultrasound.
 * The distance can be measured by waiting for this ultrasound
 * to come back and deriving the distance from the time spend
 * for the sound to bounce back.
 * 
 * This class handles the triggering of the ultrasound and uses
 * an interrupt to keep track of the time that it takes for the
 * sound to travel back. As the interrupts operate in a static
 * context, the Singleton pattern is used.
 */
class ArduinoUltrasoundSingleton : public IUltrasoundSource {
public:
    // Singletons should not be cloneable or assignable.
    ArduinoUltrasoundSingleton(ArduinoUltrasoundSingleton& other) = delete;
    void operator=(const ArduinoUltrasoundSingleton&) = delete;

    // Static method that controls the access to the singleton instance.
    static ArduinoUltrasoundSingleton *instance(const uint8_t trigPin,
                                                const uint8_t echoPin);
    
    /**
     * @brief returns the time the sound wave took to travel back.
     *
     * @see IUltrasoundSource::duration()
     *
     * @return -1 if no measurement has been done, last measurement (in us) otherwise.
     */
    unsigned long duration() const;

    /**
     * @brief Starts a measurement, result is retrieved with duration().
     *
     * @see IUltrasound::measureDistance()
     *
     * The measurement is done with the help of interrupts. This method
     * triggers a measurement. The interrupt measures the time it took
     * for the ultrasound to come back (up to 40000 us). duration()
     * gives the new value as soon as the interrupt finishes.
     *
     * This function does not keep track of requests for measurement whilst
     * waiting for the previous measurement to time out. The function has to
     * be called again to trigger a new measurement after the timeout.
     */
    void measureDuration();

private:
    const uint8_t mTrigPin;
    const uint8_t mEchoPin;

    static volatile bool mIsHigh;
    static volatile unsigned long mPulseStart;
    static volatile unsigned long mPulseWidth;

    static ArduinoUltrasoundSingleton* mSingleton;

    ArduinoUltrasoundSingleton(const uint8_t trigPin, const uint8_t echoPin) : 
            mTrigPin(trigPin), mEchoPin(echoPin) {
        pinMode(mTrigPin, OUTPUT);
        pinMode(mEchoPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(mEchoPin), echoPulseTimer, CHANGE);
    }

    ~ArduinoUltrasoundSingleton() {}

    static void echoPulseTimer(); 
};
