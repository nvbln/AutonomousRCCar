#include <Arduino.h>
#include <ArduinoBLE.h>

#include "ArduinoAccelerator.h"
#include "ArduinoBLEDevice.h"
#include "ArduinoBluetooth.h"
#include "ArduinoClock.h"
#include "ArduinoIMUAccelerator.h"
#include "ArduinoLed.h"
#include "ArduinoPinIO.h"
#include "ArduinoSerial.h"
#include "ArduinoUltrasound.h"
#include "ArduinoUltrasoundSingleton.h"
#include "Core.h"
#include "RCCarMovement.h"
#include "RCCarWheel.h"

#include <memory>

static constexpr uint8_t TRIG_PIN = 9;
static constexpr uint8_t ECHO_PIN = 10;
static constexpr uint8_t LEFT_FORWARD_PIN = A0;
static constexpr uint8_t LEFT_BACKWARD_PIN = A1;
static constexpr uint8_t RIGHT_FORWARD_PIN = A2;
static constexpr uint8_t RIGHT_BACKWARD_PIN = A3;

std::shared_ptr<ArduinoSerial> serial;
std::shared_ptr<ArduinoPinIO> pinIO;
std::shared_ptr<ArduinoIMUAccelerator> IMUAccelerator;
std::shared_ptr<ArduinoClock> arduinoClock;
ArduinoUltrasoundSingleton *ultrasoundSingleton;

std::shared_ptr<RCCarWheel> leftWheel;
std::shared_ptr<RCCarWheel> rightWheel;
std::shared_ptr<RCCarMovement> rcCarMovement;

std::shared_ptr<Core> core;
std::shared_ptr<ArduinoBluetooth> bluetooth;
std::shared_ptr<ArduinoLed> led;
std::shared_ptr<ArduinoAccelerator> accelerator;
std::shared_ptr<ArduinoUltrasound> ultrasound;

void setup() {
  auto bleDevice = ArduinoBLEDevice();
  serial = std::make_shared<ArduinoSerial>();
  pinIO = std::make_shared<ArduinoPinIO>();
  IMUAccelerator = std::make_shared<ArduinoIMUAccelerator>();
  arduinoClock = std::make_shared<ArduinoClock>();
  ultrasoundSingleton = ArduinoUltrasoundSingleton::instance(TRIG_PIN, ECHO_PIN);

  serial->begin(9600);
  while (!serial->ready())
    ;
  serial->println("Start");

  led = std::make_shared<ArduinoLed>(pinIO, LED_BUILTIN);
  accelerator =
      std::make_shared<ArduinoAccelerator>(serial.get(), IMUAccelerator.get(), arduinoClock.get());
  ultrasound = std::make_shared<ArduinoUltrasound>(ultrasoundSingleton);

  leftWheel = std::make_shared<RCCarWheel>(pinIO, LEFT_FORWARD_PIN, LEFT_BACKWARD_PIN);
  rightWheel = std::make_shared<RCCarWheel>(pinIO, RIGHT_FORWARD_PIN, RIGHT_BACKWARD_PIN);
  rcCarMovement = std::make_shared<RCCarMovement>(leftWheel, rightWheel);

  if (!BLE.begin()) {
    serial->println("Starting Bluetooth BLE failed!");
  } else {
    bluetooth = std::make_shared<ArduinoBluetooth>(serial.get(), &bleDevice, "LED");
    core = std::make_shared<Core>(serial, bluetooth, led, accelerator, ultrasound, rcCarMovement);
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
