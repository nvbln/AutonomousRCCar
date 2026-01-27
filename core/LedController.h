#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <memory>

#include "ILed.h"
#include "IGattCharacteristic.h"

class LedController {
public:
    LedController(std::shared_ptr<ILed> led) : mLed(led) {};
    void handle(Result<ValueBuffer> result);
private:
    std::shared_ptr<ILed> mLed;
};
#endif
