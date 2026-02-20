#pragma once

/**
 * @class IVehicleMovement
 * @brief Interface for controlling the vehicle movement.
 *
 * This interface allows for controlling the vehicle movement,
 * without any knowledge about the way that the vehicle is actually
 * moved.
 */
class IVehicleMovement {
public:
    virtual ~IVehicleMovement() = default;

    /**
     * @brief Move the vehicle forward.
     *
     * No speed setting for now.
     */
    virtual void forward() = 0;

    /**
     * @brief Move the vehicle backward.
     *
     * No speed setting for now.
     */
    virtual void backward() = 0;

    /**
     * @brief Turns the vehicle by the given degrees.
     *
     * The degrees clockwise, so 90 degrees is a turn to the
     * right, while 270 degrees is a turn to the left.
     */
    virtual void turnDegrees(int degrees) = 0;

    /**
     * @brief Stops all vehicle movement.
     */
    virtual void stop() = 0;
};
