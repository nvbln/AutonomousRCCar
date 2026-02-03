#ifndef ARDUINOGATTSERVICE_H
#define ARDUINOGATTSERVICE_H

#include <memory>
#include <string>
#include <ArduinoBLE.h>

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
    const std::shared_ptr<ISerial> mSerial;
    std::string mUuid;
    BLEService mService;
    static const int mMaxNumCharacteristics = 5;
    int mNumCharacteristics = 0;
    std::shared_ptr<IGattCharacteristic> mCharacteristics[mMaxNumCharacteristics];
};
#endif
