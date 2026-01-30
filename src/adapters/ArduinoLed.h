#ifndef NANO33LED_H
#define NANO33LED_H

#include "ILed.h"

/**
 * @class ArduinoLED
 * @brief ILed implementation for Nano 33 BLE Sense
 */
class ArduinoLed : public ILed {
public:
    /**
     * @brief creates an object representing the LED at the given pin.
     *
     * @param pin The pin that the LED is corresponds to.
     */
    ArduinoLed(uint8_t pin);

    /**
     * @see ILED:turn()
     */
    void turn() override;

    /**
     * @see ILED:turnOn()
     */
    void turnOn() override;

    /**
     * @see ILED:turnOff()
     */
    void turnOff() override;

private:
    bool mOn = false;
    uint8_t mPin;
};
#endif
