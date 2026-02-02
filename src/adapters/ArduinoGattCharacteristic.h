#ifndef ARDUINOGATTCHARACTERISTIC_H
#define ARDUINOGATTCHARACTERISTIC_H

#include <ArduinoBLE.h>

#include "IGattCharacteristic.h"

/**
 * @class ArduinoGattCharacteristic
 * @brief IGattCharacteristic implementation for Arduino
 */
class ArduinoGattCharacteristic : public IGattCharacteristic {
public:
    /**
     * @brief Creates a GATT Characteristic for sending/receiving data over Bluetooth
     *
     * @param uuid The UUID that the Characteristic is identified by.
     * @param valueLength not implemented yet.
     */
    ArduinoGattCharacteristic(const std::string uuid, const int valueLength) : 
        mCharacteristic(uuid.c_str(), BLERead | BLEWrite),
        mUuid(uuid), mValueLength(valueLength) {
        mCharacteristic.writeValue(0);
    };

    /**
     * @see IGattCharacteristic::uuid()
     */
    std::string uuid() const override;

    /**
     * @brief returns the Characteristic from the ArduinoBLE library.
     *
     * For some operations, the BLECharacteristic and BLEService need
     * access to one another.
     * @return the BLEByteCharacteristic underlying the Characteristic.
     */
    BLEByteCharacteristic* characteristic();

    /**
     * @see IGattCharacteristic::read()
     */
    Result<ValueBuffer> read() override;

    /**
     * @see IGattCharacteristic::write()
     */
    bool write(const ValueBuffer& valueBuffer) override;

    /**
     * @see IGattCharacteristic::addCallback()
     */
    bool addCallback(Callback callback) override;

    /**
     * @see IGattCharacteristic::update()
     */
    void update();

private:
    // TODO: Make it type independent
    BLEByteCharacteristic mCharacteristic;
    std::string mUuid;
    int mValueLength;

    static const int mMaxNumCallbacks = 5;
    int mNumCallbacks = 0;
    Callback mCallbacks[mMaxNumCallbacks];
};
#endif
