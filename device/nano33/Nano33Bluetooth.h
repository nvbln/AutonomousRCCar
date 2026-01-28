#ifndef NANO33BLUETOOTH_H
#define NANO33BLUETOOTH_H

#include <string>
#include <memory>

#include "IBluetooth.h"
#include "IGattCharacteristic.h"

class Nano33Bluetooth : public IBluetooth {
public:
    Nano33Bluetooth(std::string name) : mName(name) {};

    bool start() override;
    void update();
    bool stop() override;
    std::shared_ptr<IGattService> createService(const std::string uuid) const override;
    std::shared_ptr<IGattCharacteristic> createCharacteristic(const std::string uuid, const int valueLength) const override;
    bool addService(std::shared_ptr<IGattService> service) override;

private:
    std::string mName;
    static const int mMaxNumServices = 5;
    std::shared_ptr<IGattService> mServices[mMaxNumServices];
    int mNumServices = 0;
};
#endif;
