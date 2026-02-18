#pragma once

#include <functional>

struct AccelerationData {
    float x;
    float y;
    float z;
};

/**
 * @class IAccelerator
 * @brief Interface for subscribing to acceleration data.
 *
 * This interface can be subscribed to through the callback,
 * such that the listener is updated of every new value that
 * is sampled.
 */
class IAccelerator {
public:
    /**
     * @brief Callback type used for handling newly sampled data.
     *
     * Represents a function that forwards the sampled values
     * through the AccelerationData.
     */
    using AcceleratorCallback = std::function<void(AccelerationData)>;

    virtual ~IAccelerator() = default;

    /**
     * @brief Adds the given callback to the Accelerator.
     *
     * The callback is called when the value of the
     * accelerator is updated.
     * @return whether the callback was added.
     */
    virtual bool addCallback(AcceleratorCallback callback) = 0;
    
    /**
     * @brief check if the values were updated.
     */
    virtual void update() = 0;
};
