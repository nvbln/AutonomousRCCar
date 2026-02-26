# Autonomous RC Car

Transforming a toy RC Car into an autonomous vehicle using Arduino.

## About

Autonomous RC Car is a personal project to bring an (old) toy RC Car to life as an autonomous vehicle, by adding a microcontroller and sensors. The project exists out of two repositories. This repository contains the microcontroller software and forms the heart of the project. In addition, the [RCCarMonitor](https://github.com/nvbln/RCCarMonitor) application is meant to complement the microcontroller software by providing a way of monitoring and tasking the RC Car while in operation.

The focus of the project is to create an autonomous car that is able to navigate well in its environment, and ultimately also fulfill some tasks like gathering data. Although the project is made with a specific RC Car and the Arduino Nano 33 BLE Sense, it is meant to be easily extendable to other vehicles and microcontrollers.

## Getting Started

Make sure that you have the [Arduino CLI](https://github.com/arduino/arduino-cli) installed to compile and flash the software to your board.

Clone the repository and its submodules:
```bash
git clone --recurse-submodules https://github.com/nvbln/AutonomousRCCar.git
```

Compile the code:
```bash
arduino-cli compile --fqbn arduino:mbed_nano:nano33ble \
 --library ./src/core \
 --library ./src/interfaces \
 --library ./src/hal \
 --library ./src/adapters \
 --library ./external/circularbuffer \
 ./src/app
```

Flash the compiled code to your board:

```bash
arduino-cli upload -p <target> --fqbn arduino:mbed_nano:nano33ble ./src/app
```
where `<target>` is the location of your board (i.e. `/dev/ttyACM0`).

Optionally, spawn a monitor to receive the serial output:
```bash
arduino-cli monitor -p <target>
```

The tests are independent of the Arduino interfaces and can be run with [CMake](https://cmake.org/). Make sure that your CMake version is between 3.15 and 4.2 (`cmake --version`). Then run the tests with:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && \
 cmake --build build && \
 ./build/core_test
```

## Contributing

Although this is intended as a personal project, I am more than happy to hear about issues, suggestions, or contributions. In the case of the latter, please open an issue to discuss the matter before creating a PR.
