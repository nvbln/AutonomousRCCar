#include <ArduinoBLE.h>

#include "ArduinoBLECentral.h"

const char* ArduinoBLECentral::address() const {
    return mCentral.address().c_str();
}

bool ArduinoBLECentral::connected() const {
    return mCentral.connected();
}
