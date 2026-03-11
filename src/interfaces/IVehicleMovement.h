#pragma once

#include <cstdint>
#include <functional>

enum class MovementStatus : uint8_t { Forwards = 0, Backwards = 1, Turning = 2, Still = 3 };

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
  /**
   * @brief Calls the subscriber with the current MovementStatus on every change.
   */
  using Callback = std::function<void(MovementStatus)>;

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
   * @brief Turns the vehicle until stopped.
   */
  virtual void turn() = 0;

  /**
   * @brief Stops all vehicle movement.
   */
  virtual void stop() = 0;

  /**
   * @brief Gives the current movement being done (and Still if not).
   *
   * @return an enum containing the current status of the movement.
   */
  virtual MovementStatus movementStatus() const = 0;

  /**
   * @brief Subscribes to changes of the MovementStatus of the vehicle.
   */
  virtual void subscribe(Callback callback) = 0;
};
