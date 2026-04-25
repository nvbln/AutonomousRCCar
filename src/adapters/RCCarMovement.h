#pragma once

#include "Event.h"
#include "IVehicleMovement.h"
#include "IWheel.h"

class RCCarMovement : public IVehicleMovement {
public:
  /**
   * @brief Creates an easy-to-use controller of the car.
   */
  RCCarMovement(IWheel *leftWheel, IWheel *rightWheel)
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
  IWheel *const mLeftWheel, *const mRightWheel;

  Event<Callback, 5, MovementStatus> event;

  /**
   * @brief Updates the mStatus member variable and notifies subscribers.
   */
  void updateStatus(MovementStatus status) {
    mStatus = status;
    event.notify(status);
  }
};
