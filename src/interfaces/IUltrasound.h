#pragma once

#include <functional>

/**
 * @class IUltrasound
 * @brief Interface for subscribing to Ultrasound distance data.
 *
 * This interface can be subscribed to through the callback,
 * such that the listener is updated of every new value that
 * is sampled.
 */
class IUltrasound {
public:
    /**
     * @brief Callback type used for handling newly sampled data.
     */
    using Callback = std::function<void(float distanceCm)>;

    virtual ~IUltrasound() = default;

    /**
     * @brief Adss the callback to the Ultrasound.
     *
     * The callback is called when the value of the
     * accelerator is updated.
     * @return whether the callback was added.
     */
    virtual bool addCallback(Callback callback) = 0;

    /**
     * @brief make a new measurement.
     */
    virtual void update() = 0;
};
