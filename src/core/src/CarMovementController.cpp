#include "CarMovementController.h"
#include "IVehicleMovement.h"
#include "ValueBuffer.h"

void CarMovementController::controlCar() {
  if (mMotorsLocked) {
    return;
  }

  MovementStatus status = mCarMovement->movementStatus();

  bool canMove = mDistance == 0 || mDistance > 50;

  // Stop the car if it is about to hit something.
  if (mDistance != 0 && mDistance < 10) {
    mSerial->println("Stopping the car.");
    mCarMovement->stop();
    return;
  }

  // Turn the car if it approaches an obstacle.
  if (status == MovementStatus::Forwards && !canMove) {
    mSerial->println("Turning the car.");
    mCarMovement->turn();
    return;
  }

  // Drive forwards if there is no obstacle.
  if ((status == MovementStatus::Still || status == MovementStatus::Turning) && canMove) {
    mSerial->println("Driving the car forwards.");
    mCarMovement->forward();
    return;
  }
}

void CarMovementController::handle(ValueBuffer buffer) { mMotorsLocked = !buffer.data[0]; };
