#include <Arduino.h>
#include <ArduinoBLE.h>

#include "Core.h"
#include "ArduinoBLEDevice.h"
#include "ArduinoPinIO.h"
#include "ArduinoSerial.h"
#include "ArduinoBluetooth.h"
#include "ArduinoLed.h"
#include "ArduinoIMUAccelerator.h"
#include "ArduinoAccelerator.h"
#include "ArduinoClock.h"
#include "ArduinoUltrasound.h"

#include <memory>

static const uint8_t TRIG_PIN = 9;
static const uint8_t ECHO_PIN = 10;

std::shared_ptr<ArduinoBLEDevice> bleDevice;
std::shared_ptr<ArduinoSerial> serial;
std::shared_ptr<ArduinoPinIO> pinIO;
std::shared_ptr<ArduinoIMUAccelerator> IMUAccelerator;
std::shared_ptr<ArduinoClock> arduinoClock;
std::shared_ptr<ArduinoUltrasound> ultrasound;

std::shared_ptr<Core> core;
std::shared_ptr<ArduinoBluetooth> bluetooth;
std::shared_ptr<ArduinoLed> led;
std::shared_ptr<ArduinoAccelerator> accelerator;

void setup() {
    bleDevice = std::make_shared<ArduinoBLEDevice>();
    serial = std::make_shared<ArduinoSerial>();
    pinIO = std::make_shared<ArduinoPinIO>();
    IMUAccelerator = std::make_shared<ArduinoIMUAccelerator>();
    arduinoClock = std::make_shared<ArduinoClock>();

    serial->begin(9600);
    while (!serial->ready());
    serial->println("Start");

    led = std::make_shared<ArduinoLed>(pinIO, LED_BUILTIN);
    accelerator = std::make_shared<ArduinoAccelerator>(serial, IMUAccelerator, arduinoClock);
    ultrasound = std::make_shared<ArduinoUltrasound>(arduinoClock, pinIO, TRIG_PIN, ECHO_PIN);

    if (!BLE.begin()) {
        serial->println("Starting Bluetooth BLE failed!");
    } else {
        bluetooth = std::make_shared<ArduinoBluetooth>(serial, bleDevice, "LED");
        core = std::make_shared<Core>(serial, bluetooth, led, accelerator, ultrasound);
    }
}

void loop() {
    accelerator->update();
    ultrasound->update();
    bluetooth->update();
    core->update();

    // Delay for debugging purposes.
    delay(10);
}
