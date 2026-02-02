#include <Arduino.h>
#include <ArduinoBLE.h>

#include "Core.h"
#include "ArduinoSerial.h"
#include "ArduinoBluetooth.h"
#include "ArduinoLed.h"

std::shared_ptr<ArduinoSerial> serial;

std::shared_ptr<Core> core;
std::shared_ptr<ArduinoBluetooth> bluetooth;
std::shared_ptr<ArduinoLed> led;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Start");

    serial = std::make_shared<ArduinoSerial>();

    led = std::make_shared<ArduinoLed>(LED_BUILTIN);

    if (!BLE.begin()) {
        Serial.println("Starting Bluetooth BLE failed!");
    } else {
        bluetooth = std::make_shared<ArduinoBluetooth>("LED");
        core = std::make_shared<Core>(serial, bluetooth, led);
    }
}

void loop() {
    bluetooth->update();
    core->update();

    // Delay for debugging purposes.
    delay(1000);
}
