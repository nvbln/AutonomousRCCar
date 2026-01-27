#ifndef NANO33GATTCHARACTERISTIC_H
#define NANO33GATTCHARACTERISTIC_H

#include <ArduinoBLE.h>

#include "IGattCharacteristic.h"

class Nano33GattCharacteristic : public IGattCharacteristic {
public:
    Nano33GattCharacteristic(const std::string uuid, const int valueLength) : 
        mCharacteristic(uuid.c_str(), BLERead | BLEWrite),
        mService(uuid.c_str()), mUuid(uuid), mValueLength(valueLength) {
        mService.addCharacteristic(mCharacteristic); 
        mCharacteristic.writeValue(0);
    };

    std::string uuid() const override;
    BLEService* service();

    Result<ValueBuffer> read() override;
    bool write(const ValueBuffer& valueBuffer) override;

    bool addCallback(Callback callback) override;
    void update();

private:
    // TODO: Make a separate service class
    BLEService mService;
    // TODO: Make it type independent
    BLEByteCharacteristic mCharacteristic;
    std::string mUuid;
    int mValueLength;

    static const int mMaxNumCallbacks = 5;
    int mNumCallbacks = 0;
    Callback mCallbacks[mMaxNumCallbacks];
};
#endif
