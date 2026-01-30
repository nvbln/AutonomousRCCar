#include <Arduino.h>
#include <ArduinoBLE.h>

#include "Core.h"
#include "Nano33Bluetooth.h"
#include "Nano33Led.h"

std::shared_ptr<Core> core;
std::shared_ptr<Nano33Bluetooth> bluetooth;
std::shared_ptr<Nano33Led> led;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Start");

    led = std::make_shared<Nano33Led>(LED_BUILTIN);

    if (!BLE.begin()) {
        Serial.println("Starting Bluetooth BLE failed!");
    } else {
        bluetooth = std::make_shared<Nano33Bluetooth>("LED");
        core = std::make_shared<Core>(bluetooth, led);
    }
}

void loop() {
    bluetooth->update();
    core->update();

    // Delay for debugging purposes.
    delay(1000);
}
