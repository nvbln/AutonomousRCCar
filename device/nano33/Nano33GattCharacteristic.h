#ifndef NANO33GATTCHARACTERISTIC_H
#define NANO33GATTCHARACTERISTIC_H

#include <ArduinoBLE.h>

#include "IGattCharacteristic.h"

class Nano33GattCharacteristic : public IGattCharacteristic {
public:
    Nano33GattCharacteristic(const std::string uuid, const int valueLength) : 
        mCharacteristic(uuid.c_str(), BLERead | BLEWrite),
        mUuid(uuid), mValueLength(valueLength) {
        mCharacteristic.writeValue(0);
    };

    std::string uuid() const override;
    BLEByteCharacteristic* characteristic();

    Result<ValueBuffer> read() override;
    bool write(const ValueBuffer& valueBuffer) override;

    bool addCallback(Callback callback) override;
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
