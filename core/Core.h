#ifndef CORE_H
#define CORE_H

#include "IBluetooth.h"
#include "ILed.h"

class Core {
public:
    Core(std::shared_ptr<IBluetooth> bluetooth, std::shared_ptr<ILed> led);
    void update();

private:
    std::shared_ptr<IBluetooth> mBluetooth;
    std::shared_ptr<ILed> mLed;
};
#endif
