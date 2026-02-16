#pragma once

#include "IBLEDevice.h"
#include <gmock/gmock.h>

class MockBLEDevice : public IBLEDevice {
public:
    MOCK_METHOD(bool, begin, (), (override));
    MOCK_METHOD(void, end, (), (override));
    MOCK_METHOD(void, setLocalName, (const char* name), (override));
    MOCK_METHOD(std::shared_ptr<IBLEService>, createService, (const char* uuid), (const, override));
    MOCK_METHOD(std::shared_ptr<IBLECharacteristic>, createCharacteristic, (const char* uuid), (const, override));
    MOCK_METHOD(void, addService, (std::shared_ptr<IBLEService>), (override));
    MOCK_METHOD(void, setAdvertisedService, (std::shared_ptr<IBLEService>), (override));
    MOCK_METHOD(void, advertise, (), (override));
    MOCK_METHOD(const std::shared_ptr<IBLECentral>, central, (), (const, override));
};
