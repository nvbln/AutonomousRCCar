#ifndef NANO33LED_H
#define NANO33LED_H

#include "ILed.h"

class Nano33Led : public ILed {
public:
    Nano33Led(uint8_t pin);

    void turn() override;
    void turnOn() override;
    void turnOff() override;
    uint8_t pin() const override;
private:
    bool mOn = false;
    uint8_t mPin;
};
#endif
