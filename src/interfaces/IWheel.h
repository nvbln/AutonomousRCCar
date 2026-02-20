#pragma once

/**
 * @class IWheel
 * @brief Interface for controlling wheels.
 */
class IWheel {
public:
    virtual ~IWheel() = default;

    /**
     * @brief Tells the wheel to move forward.
     *
     * No speed setting for now.
     */
    virtual void forward() = 0;

    /**
     * @brief Tells the wheel to move backward.
     *
     * No speed setting for now.
     */
    virtual void backward() = 0;

    /**
     * @brief Stops any movement of the wheel.
     */
    virtual void stop() = 0;
};
