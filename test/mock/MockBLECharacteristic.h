#pragma once

#include "IBLECharacteristic.h"
#include <gmock/gmock.h>

class MockBLECharacteristic : public IBLECharacteristic {
public:
    MOCK_METHOD(void, writeValue, (const uint8_t value), (override));
    MOCK_METHOD(uint8_t, read, (), (override));
    MOCK_METHOD(uint8_t, value, (), (override));
    MOCK_METHOD(bool, written, (), (override));
};
