#pragma once

#include "IClock.h"
#include <gmock/gmock.h>

class MockClock : public IClock {
public:
    MOCK_METHOD(unsigned long, micros, (), (const, override));
    MOCK_METHOD(void, delayMicroseconds, (unsigned int us), (override));
};
