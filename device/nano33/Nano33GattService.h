#ifndef NANO33GATTSERVICE_H
#define NANO33GATTSERVICE_H

#include <memory>
#include <string>
#include <ArduinoBLE.h>

#include "IGattService.h"

class Nano33GattService : public IGattService {
public:
    Nano33GattService(const std::string uuid) : mService(uuid.c_str()), mUuid(uuid) {};

    std::string uuid() const override;
    BLEService* service();
    bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) override;
    void update() override;
private:
    std::string mUuid;
    BLEService mService;
    static const int mMaxNumCharacteristics = 5;
    int mNumCharacteristics = 0;
    std::shared_ptr<IGattCharacteristic> mCharacteristics[mMaxNumCharacteristics];
};
#endif
