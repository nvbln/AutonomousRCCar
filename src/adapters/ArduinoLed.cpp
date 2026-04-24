#include "ArduinoLed.h"
#include "IPinIO.h"

ArduinoLed::ArduinoLed(IPinIO *const pinIO, uint8_t pin) : mPinIO(pinIO), mPin(pin) {
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
