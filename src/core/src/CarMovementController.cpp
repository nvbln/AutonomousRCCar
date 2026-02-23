#include "CarMovementController.h"
#include "IVehicleMovement.h"

void CarMovementController::controlCar() {
    MovementStatus status = mCarMovement->movementStatus();

    bool canMove = mDistance == 0 || mDistance > 50;

    if (status == MovementStatus::Forwards && !canMove) {
        mSerial->println("Stopping the car.");
        mCarMovement->stop();
    }

    if (status == MovementStatus::Still && canMove) {
        mSerial->println("Driving the car forwards.");
        mCarMovement->forward();
    }
}
