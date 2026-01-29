#include "IGattCharacteristic.h"
#include "LedController.h"

void LedController::handle(ValueBuffer buffer) {
    buffer.data[0] ? mLed->turnOn() : mLed->turnOff();
}
