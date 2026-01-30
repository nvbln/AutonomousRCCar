#ifndef ILED_H
#define ILED_H

/**
 * @class ILed
 * @brief Interface for interacting with an LED.
 */
class ILed {
public:
    virtual ~ILed() = default;

    /**
     * @brief switches the state of the LED (on->off, off->on).
     */
    virtual void turn() = 0;

    /**
     * @brief turns the LED off, regardless of its state.
     */
    virtual void turnOn() = 0;

    /**
     * @brief turns the LED on, regardless of its state.
     */
    virtual void turnOff() = 0;

};
#endif
