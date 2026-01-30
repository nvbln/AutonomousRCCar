#ifndef NANO33GATTSERVICE_H
#define NANO33GATTSERVICE_H

#include <memory>
#include <string>
#include <ArduinoBLE.h>

#include "IGattService.h"

/**
 * @class ArduinoGattService
 * @brief IGattService implementation for Nano 33 BLE Sense
 */
class ArduinoGattService : public IGattService {
public:
    /**
     * @brief Creates a GATT Service for grouping Characteristics
     *
     * @param uuid The ID that the service is identified by.
     */
    ArduinoGattService(const std::string uuid) : mService(uuid.c_str()), mUuid(uuid) {};

    /**
     * @see IGattService::uuid()
     */
    std::string uuid() const override;

    /**
     * @brief returns the Service from the ArduinoBLE library.
     *
     * For some operations, the BLEService and BLECharacteristic need
     * access to one another.
     * @return the BLEService underlying the Service.
     */
    BLEService* service();

    /**
     * @see IGattService::addCharacteristic()
     */
    bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) override;

    /**
     * @see IGattService::update()
     */
    void update() override;
private:
    std::string mUuid;
    BLEService mService;
    static const int mMaxNumCharacteristics = 5;
    int mNumCharacteristics = 0;
    std::shared_ptr<IGattCharacteristic> mCharacteristics[mMaxNumCharacteristics];
};
#endif
