#ifndef ARDUINOGATTCHARACTERISTIC_H
#define ARDUINOGATTCHARACTERISTIC_H

#include <memory>


#include "ISerial.h"
#include "IBLECharacteristic.h"
#include "IBLEService.h"
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
                              const std::shared_ptr<IBLECharacteristic> characteristic) : 
        mSerial(serial),
        mCharacteristic(characteristic) {
        mCharacteristic->writeValue(0);
    };

    /**
     * @brief adds the characteristic to the service.
     *
     * @param service the BLEService to add the characteristic to.
     */
    void addCharacteristicToService(std::shared_ptr<IBLEService> service);

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
    void update() override;

private:
    const std::shared_ptr<ISerial> mSerial;
    const std::shared_ptr<IBLECharacteristic> mCharacteristic;

    static const int mMaxNumCallbacks = 5;
    int mNumCallbacks = 0;
    Callback mCallbacks[mMaxNumCallbacks];
};
#endif
