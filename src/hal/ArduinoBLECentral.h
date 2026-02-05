#ifndef ARDUINOBLECENTRAL_H
#define ARDUINOBLECENTRAL_H

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
    const char* address() const override;

    /**
     * @see IBLECentral::connected()
     */
    bool connected() const override;
private:
    BLEDevice mCentral; 
};
#endif
