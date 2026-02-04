#include <memory>

#include "IPinIO.h"
#include "ArduinoLed.h"

ArduinoLed::ArduinoLed(std::shared_ptr<IPinIO> pinIO, uint8_t pin) : mPinIO(pinIO), mPin(pin) {
    mPinIO->pinMode(pin, PinIOMode::Output);

    // Always turn the led off at the start.
    turnOff();
}

void ArduinoLed::turn() {
    if (mOn) {
        turnOff();
    } else {
        turnOn();
    }
}

void ArduinoLed::turnOn() {
    mPinIO->digitalWrite(mPin, PinIOValue::High);
    mOn = true;
}

void ArduinoLed::turnOff() {
    mPinIO->digitalWrite(mPin, PinIOValue::Low);
    mOn = false;
}
