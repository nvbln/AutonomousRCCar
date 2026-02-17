#pragma once

#include <ArduinoBLE.h>

#include "IBLECentral.h"

/**
 * @class ArduinoBLECentral
 * @brief wrapper implementation of the ArduinoBLE BLEDevice for central devices
 */
class ArduinoBLECentral : public IBLECentral {
public:
    ArduinoBLECentral(BLEDevice central) : mCentral(central) {};

    /**
     * @see IBLECentral::address()
     */
    const char* address() const override {
        return mCentral.address().c_str();
    }

    /**
     * @see IBLECentral::connected()
     */
    bool connected() const override {
        return mCentral.connected();
    }

private:
    BLEDevice mCentral; 
};
