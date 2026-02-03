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
    serial = std::make_shared<ArduinoSerial>();

    serial->begin(9600);
    while (!serial->ready());
    serial->println("Start");

    led = std::make_shared<ArduinoLed>(LED_BUILTIN);

    if (!BLE.begin()) {
        serial->println("Starting Bluetooth BLE failed!");
    } else {
        bluetooth = std::make_shared<ArduinoBluetooth>(serial, "LED");
        core = std::make_shared<Core>(serial, bluetooth, led);
    }
}

void loop() {
    bluetooth->update();
    core->update();

    // Delay for debugging purposes.
    delay(1000);
}
