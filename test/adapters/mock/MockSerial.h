#pragma once

#include <gmock/gmock.h>
#include "ISerial.h"

class MockSerial : public ISerial {
public:
    MOCK_METHOD(void, begin, (unsigned long baud), (const, override));
    MOCK_METHOD(size_t, print, (const char str[]), (const, override));
    MOCK_METHOD(size_t, println, (const char str[]), (const, override));
    MOCK_METHOD(bool, ready, (), (const, override));
};
