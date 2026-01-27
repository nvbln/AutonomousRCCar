#ifndef IBLUETOOTH_H
#define IBLUETOOTH_H

#include <memory>
#include <string>

#include "IGattCharacteristic.h"

class IBluetooth {
public:
    virtual ~IBluetooth() = default;

    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual std::shared_ptr<IGattCharacteristic> createCharacteristic(const std::string uuid, const int valueLength) const = 0;
    virtual bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) = 0;

};
#endif
