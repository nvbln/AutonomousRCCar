#include "mock/MockSerial.h"
#include "mock/MockBLEDevice.h"
#include "mock/MockBLEService.h"
#include "mock/MockBLECharacteristic.h"
#include "ArduinoBluetooth.h"
#include "ArduinoGattService.h"
#include "IBLECentral.h"
#include "IGattService.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

class MockBLECentral : public IBLECentral {
public:
    MOCK_METHOD(const char*, address, (), (const, override));
    MOCK_METHOD(bool, connected, (), (const, override));
};

class MockGattService : public IGattService {
public:
    MOCK_METHOD(bool, addCharacteristic, (std::shared_ptr<IGattCharacteristic>), (override));
    MOCK_METHOD(void, update, (), (override));
};

/*class MockGattCharacteristic : public IGattCharacteristic {
public:
    MOCK_METHOD(Result<ValueBuffer>, read, (), (override));
    MOCK_METHOD(bool, write, (const ValueBuffer& valueBuffer), (override));
    MOCK_METHOD(bool, addCallback, (Callback callback), (override));
    MOCK_METHOD(void, update, (), (override));
};*/

TEST(ArduinoBluetoothTests, shouldStartAndBroadcastServices) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();
    std::shared_ptr<IBLEService> mockBLEService = std::make_shared<MockBLEService>();

    const char* expectedName = "Test";

    EXPECT_CALL(*mockBLEDevice, setLocalName(testing::StrEq(expectedName))).Times(1);
    EXPECT_CALL(*mockBLEDevice, addService(mockBLEService)).Times(1);
    EXPECT_CALL(*mockBLEDevice, setAdvertisedService(mockBLEService)).Times(1);
    EXPECT_CALL(*mockBLEDevice, advertise()).Times(1);

    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, expectedName);
    auto arduinoService = std::make_shared<ArduinoGattService>(mockSerial, mockBLEService);
    arduinoBluetooth->addService(arduinoService);
    bool result = arduinoBluetooth->start();

    EXPECT_TRUE(result);
}

TEST(ArduinoBluetoothTests, shouldUpdateServicesIfConnectedToCentral) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();
    auto mockBLECentral = std::make_shared<MockBLECentral>();
    auto mockGattService = std::make_shared<MockGattService>();

    EXPECT_CALL(*mockBLECentral, connected()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*mockBLECentral, address()).Times(1);
    EXPECT_CALL(*mockBLEDevice, central()).Times(1).WillOnce(Return(mockBLECentral));
    EXPECT_CALL(*mockGattService, update()).Times(1);

    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, "Test");
    arduinoBluetooth->addService(mockGattService);
    arduinoBluetooth->update();
}

TEST(ArduinoBluetoothTests, shouldEndBLEDeviceOnStop) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();

    EXPECT_CALL(*mockBLEDevice, end()).Times(1);

    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, "Test");
    bool result = arduinoBluetooth->stop();

    EXPECT_TRUE(result);
}

TEST(ArduinoBluetoothTests, shouldCreateArduinoGattCharacteristic) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();
    auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();

    const char* expectedUuid = "test";

    EXPECT_CALL(*mockBLEDevice, createCharacteristic(testing::StrEq(expectedUuid))).Times(1).WillOnce(Return(mockBLECharacteristic));

    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, "Test");
    auto arduinoCharacteristic = arduinoBluetooth->createCharacteristic(expectedUuid);

    EXPECT_TRUE(arduinoCharacteristic);
}

TEST(ArduinoBluetoothTests, shouldCreateArduinoGattService) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();
    auto mockBLEService = std::make_shared<MockBLEService>();

    const char* expectedUuid = "test";

    EXPECT_CALL(*mockBLEDevice, createService(testing::StrEq(expectedUuid))).Times(1).WillOnce(Return(mockBLEService));

    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, "Test");
    auto arduinoService = arduinoBluetooth->createService(expectedUuid);

    EXPECT_TRUE(arduinoService);
}

TEST(ArduinoBluetoothTests, numberServicesShouldHaveMaximum) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLEDevice = std::make_shared<MockBLEDevice>();
    auto mockBLEService = std::make_shared<MockBLEService>();
    auto arduinoService = std::make_shared<ArduinoGattService>(mockSerial, mockBLEService);
    auto arduinoBluetooth = std::make_shared<ArduinoBluetooth>(mockSerial, mockBLEDevice, "Test");
    
    arduinoBluetooth->addService(arduinoService);
    arduinoBluetooth->addService(arduinoService);
    arduinoBluetooth->addService(arduinoService);
    arduinoBluetooth->addService(arduinoService);
    bool success5 = arduinoBluetooth->addService(arduinoService);
    bool success6 = arduinoBluetooth->addService(arduinoService);

    EXPECT_TRUE(success5);
    EXPECT_FALSE(success6);
}
