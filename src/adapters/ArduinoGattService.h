#ifndef ARDUINOGATTSERVICE_H
#define ARDUINOGATTSERVICE_H

#include <memory>
#include <string>
#include <ArduinoBLE.h>

#include "IBLEDevice.h"
#include "ISerial.h"
#include "IGattService.h"

/**
 * @class ArduinoGattService
 * @brief IGattService implementation for Arduino
 */
class ArduinoGattService : public IGattService {
public:
    /**
     * @brief Creates a GATT Service for grouping Characteristics
     *
     * @param serial The Arduino Serial interface for printing messages.
     * @param uuid The ID that the service is identified by.
     */
    ArduinoGattService(const std::shared_ptr<ISerial> serial, const std::string uuid) : 
        mSerial(serial), mService(uuid.c_str()), mUuid(uuid) {};

    /**
     * @see IGattService::uuid()
     */
    std::string uuid() const override;

    /**
     * @brief adds the service to the BLE device.
     *
     * Adding the service to the BLEDevice makes it available
     * to central devices that connect to the peripheral.
     *
     * @param device The BLE peripheral device.
     */
    void addServiceToBLEDevice(std::shared_ptr<IBLEDevice> device);

    /**
     * @brief Makes the service discoverable by central devices.
     *
     * @param device the BLE peripheral device.
     */
    void advertiseServiceOnBLEDevice(std::shared_ptr<IBLEDevice> device);

    /**
     * @see IGattService::addCharacteristic()
     */
    bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) override;

    /**
     * @see IGattService::update()
     */
    void update() override;

private:
    const std::shared_ptr<ISerial> mSerial;
    std::string mUuid;
    BLEService mService;
    static const int mMaxNumCharacteristics = 5;
    int mNumCharacteristics = 0;
    std::shared_ptr<IGattCharacteristic> mCharacteristics[mMaxNumCharacteristics];
};
#endif
