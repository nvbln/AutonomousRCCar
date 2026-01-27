#include <Arduino.h>

#include "IGattCharacteristic.h"
#include "LedController.h"

void LedController::handle(Result<ValueBuffer> result) {
    if (!result.success || result.data.length != 1) {
        Serial.println("There was a problem reading the input value");
        return;
    }

    result.data.data[0] ? mLed->turnOn() : mLed->turnOff();
}
