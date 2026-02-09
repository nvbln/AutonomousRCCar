#ifndef MOCKBLESERVICE_H
#define MOCKBLESERVICE_H

#include "IBLEService.h"
#include "IBLECharacteristic.h"
#include <gmock/gmock.h>

class MockBLEService : public IBLEService {
public:
    MOCK_METHOD(const char*, uuid, (), (const, override));
    MOCK_METHOD(void, addCharacteristic, (std::shared_ptr<IBLECharacteristic> characteristic), (override));
};
#endif
