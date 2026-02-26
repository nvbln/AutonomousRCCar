#include "LedController.h"
#include "ValueBuffer.h"

void LedController::handle(ValueBuffer buffer) {
  buffer.data[0] ? mLed->turnOn() : mLed->turnOff();
}
