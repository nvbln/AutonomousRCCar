#ifndef CORE_H
#define CORE_H

#include "IBluetooth.h"
#include "ILed.h"

/**
 * @class Core
 * @brief Main controller of all application logic.
 *
 * This class controls the flow of the application.
 * It handles or delegates all the logic that is not device-specific.
 * In order to do so, it communicates with the device through the interfaces
 * provided by the HAL layer.
 * @see main.cpp of the respective devices for the device-level control flow.
 */
class Core {
public:
    /**
     * @brief Sets up the main control flow for the application.
     *
     * Takes the instances of the hardware components of the device
     * through a more general HAL interface.
     *
     * @param bluetooth Instance of the Bluetooth provided by the device.
     * @param led       Instance of the LED provided by the device.
     */
    Core(std::shared_ptr<IBluetooth> bluetooth, std::shared_ptr<ILed> led);

    /**
     * @brief Updates the state of the application logic.
     *
     * Updates the application logic layer by working through the
     * event queue (to be implemented) and state changes that occurred this cycle.
     */
    void update();

private:
    std::shared_ptr<IBluetooth> mBluetooth;
    std::shared_ptr<ILed> mLed;
};
#endif
