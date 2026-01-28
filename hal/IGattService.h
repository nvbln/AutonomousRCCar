#ifndef IGATTSERVICE_H 
#define IGATTSERVICE_H

#include <string>

#include "IGattCharacteristic.h"

class IGattService {
public:
    virtual ~IGattService() = default;

    virtual std::string uuid() const = 0;
    virtual bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) = 0;
    virtual void update();

};
#endif
