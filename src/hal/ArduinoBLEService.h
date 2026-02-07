#ifndef ARDUINOBLESERVICE_H
#define ARDUINOBLESERVICE_H

#include <ArduinoBLE.h>
#include "ArduinoBLEDevice.h"
#include "IBLEService.h"

/**
 * @class ArduinoBLEService
 * @brief wrapper implementation of the ArduinoBLE BLEService
 *
 * This connects the IBLEService to the ArduinoBLE library,
 * such that the application can run on Arduino devices.
 */
class ArduinoBLEService : public IBLEService {
public:
    ArduinoBLEService(const char* uuid) : mService(uuid) {};

    const char* uuid() const override;
    void addCharacteristic(BLECharacteristic& characteristic) override;
private:
    friend class ArduinoBLEDevice;
    BLEService mService;
};
#endif
