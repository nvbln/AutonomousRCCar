#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <memory>

#include "ILed.h"
#include "IGattCharacteristic.h"

/**
 * @class LedController
 * @brief Processes incoming commands to control an LED.
 *
 * This controller updates the state of the ILed instance based on the
 * command passed through the ValueBuffer, where the first element is
 * treated as an on/off flag.
 */
class LedController {
public:
    /**
     * @brief Creates a controller for a specific LED instance.
     *
     * @param led ILed implementation that will be controlled by this
     *            object.
     */
    LedController(std::shared_ptr<ILed> led) : mLed(led) {};

    /**
     * @brief Sets the LED state based on the given command.
     *
     * The first element of the buffer determines the LED state:
     * - `1` turns the LED on.
     * - Any other value turns the LED off.
     *
     * @param buffer A ValueBuffer containing the command.
     */
    void handle(ValueBuffer buffer);

private:
    std::shared_ptr<ILed> mLed;
};
#endif
