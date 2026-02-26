#pragma once

#include "ISerial.h"
#include "IUltrasound.h"
#include "IVehicleMovement.h"
#include "ValueBuffer.h"

#include <memory>

/**
 * @class CarMovementController
 * @brief Controls the movement of the car, by integrating sensor/actuator data.
 */
class CarMovementController {
public:
  /**
   * @brief Creates an instance of the controller.
   */
  CarMovementController(std::shared_ptr<ISerial> serial, std::shared_ptr<IUltrasound> ultrasound,
                        std::shared_ptr<IVehicleMovement> carMovement)
      : mSerial(serial), mCarMovement(carMovement) {
    ultrasound->addCallback([this](float distance) { this->mDistance = distance; });
  }

  /**
   * @brief Evaluates the current situation and picks a movement to perform.
   *
   * It basically functions as a control-loop for updating the car movement
   * over time. In order to do so, this function should be called
   * continuously.
   */
  void controlCar();

  /**
   * @brief Turns the motors on and off based on the given command.
   *
   * The first element of the buffer determines the motor state:
   * - `1` turns the motor state on.
   * - Any other value turns the motor state off.
   * The motor state here refers to whether the motors are
   * 'unlocked' or not. Not whether they will actually turn on
   * or not.
   *
   * @param buffer A ValueBuffer containing the command.
   */
  void handle(ValueBuffer buffer);

private:
  float mDistance = 0;
  bool mMotorsLocked = true;

  std::shared_ptr<ISerial> mSerial;
  std::shared_ptr<IVehicleMovement> mCarMovement;
};
