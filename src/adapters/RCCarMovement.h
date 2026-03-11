#pragma once

#include "Event.h"
#include "IVehicleMovement.h"
#include "IWheel.h"

#include <memory>

class RCCarMovement : public IVehicleMovement {
public:
  /**
   * @brief Creates an easy-to-use controller of the car.
   */
  RCCarMovement(std::shared_ptr<IWheel> leftWheel, std::shared_ptr<IWheel> rightWheel)
      : mLeftWheel(leftWheel), mRightWheel(rightWheel) {}

  /**
   * @see IVehicleMovement::forward()
   */
  void forward() override;

  /**
   * @see IVehicleMovement::backward()
   */
  void backward() override;

  /**
   * @see IVehicleMovement::turnDegrees()
   */
  void turn() override;

  /**
   * @see IVehicleMovement::stop()
   */
  void stop() override;

  /**
   * @see IVehicleMovement::movementStatus()
   */
  MovementStatus movementStatus() const override;

  /**
   * @see IVehicleMovement::subscribe()
   */
  void subscribe(Callback callback) override { event.subscribe(callback); }

private:
  MovementStatus mStatus = MovementStatus::Still;
  const std::shared_ptr<IWheel> mLeftWheel, mRightWheel;

  Event<Callback, 5, MovementStatus> event;

  /**
   * @brief Updates the mStatus member variable and notifies subscribers.
   */
  void updateStatus(MovementStatus status) {
    mStatus = status;
    event.notify(status);
  }
};
