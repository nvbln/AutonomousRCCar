#pragma once

/**
 * @class IUltrasoundSource
 * @brief Abstraction layer for ultrasound sources that require direct hardware access.
 *
 * In some cases (like in the case of interrupts), existing hardware abstractions
 * (i.e. IPinIO) are not sufficient. This interface provides the necessary
 * abstraction for ultrasound sources that require direct hardware access.
 */
class IUltrasoundSource {
public:
    /**
     * @brief returns the duration that it took for the sound wave to travel back.
     *
     * @return The duration in microseconds.
     */
    virtual unsigned long duration() const = 0;

    /**
     * @brief starts an ultrasound time measurement.
     */
    virtual void measureDuration() = 0;
};
