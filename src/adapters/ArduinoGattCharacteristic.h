#ifndef ARDUINOGATTCHARACTERISTIC_H
#define ARDUINOGATTCHARACTERISTIC_H

#include <ArduinoBLE.h>

#include "ISerial.h"
#include "IGattService.h"
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
     * @param serial The Arduino Serial interface for printing messages.
     * @param uuid The UUID that the Characteristic is identified by.
     * @param valueLength not implemented yet.
     */
    ArduinoGattCharacteristic(const std::shared_ptr<ISerial> serial,
                              const std::string uuid,
                              const int valueLength) : 
        mSerial(serial),
        mCharacteristic(uuid.c_str(), BLERead | BLEWrite),
        mUuid(uuid), mValueLength(valueLength) {
        mCharacteristic.writeValue(0);
    };

    /**
     * @see IGattCharacteristic::uuid()
     */
    std::string uuid() const override;

    /**
     * @brief adds the characteristic to the service.
     *
     * @param service the BLEService to add the characteristic to.
     */
    void addCharacteristicToService(BLEService& service);

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
    const std::shared_ptr<ISerial> mSerial;

    // TODO: Make it type independent
    BLEByteCharacteristic mCharacteristic;
    std::string mUuid;
    int mValueLength;

    static const int mMaxNumCallbacks = 5;
    int mNumCallbacks = 0;
    Callback mCallbacks[mMaxNumCallbacks];
};
#endif
