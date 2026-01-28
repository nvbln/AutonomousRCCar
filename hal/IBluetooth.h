#ifndef IBLUETOOTH_H
#define IBLUETOOTH_H

#include <memory>
#include <string>

#include "IGattService.h"
#include "IGattCharacteristic.h"

class IBluetooth {
public:
    virtual ~IBluetooth() = default;

    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual std::shared_ptr<IGattService> createService(const std::string uuid) const = 0;
    virtual std::shared_ptr<IGattCharacteristic> createCharacteristic(const std::string uuid, const int valueLength) const = 0;
    virtual bool addService(std::shared_ptr<IGattService> service) = 0;

};
#endif
