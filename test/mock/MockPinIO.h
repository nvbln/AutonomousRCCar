#pragma once

#include "IPinIO.h"
#include <gmock/gmock.h>

class MockPinIO : public IPinIO {
public:
    MOCK_METHOD(void, pinMode, (uint8_t pin, PinIOMode mode), (const, override));
    MOCK_METHOD(void, digitalWrite, (uint8_t pin, PinIOValue value), (const, override));
    MOCK_METHOD(unsigned long, pulseIn, (uint8_t pin, PinIOValue value, unsigned long timeout), (const, override));
};
