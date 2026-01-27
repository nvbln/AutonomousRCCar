#ifndef ILED_H
#define ILED_H

class ILed {
public:
    virtual ~ILed() = default;

    virtual void turn() = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual uint8_t pin() const = 0;

};
#endif
