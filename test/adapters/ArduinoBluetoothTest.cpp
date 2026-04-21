#include "ArduinoBluetooth.h"
#include "ArduinoGattService.h"
#include "IBLECentral.h"
#include "IGattService.h"
#include "MockBLECharacteristic.h"
#include "MockBLEDevice.h"
#include "MockBLEService.h"
#include "MockSerial.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::NiceMock;
using ::testing::Return;

class MockBLECentral : public IBLECentral {
public:
  MOCK_METHOD(const char *, address, (), (const, override));
  MOCK_METHOD(bool, connected, (), (const, override));
};

class MockGattService : public IGattService {
public:
  MOCK_METHOD(bool, addCharacteristic, (std::shared_ptr<IGattCharacteristic>), (override));
  MOCK_METHOD(void, update, (), (override));
};

TEST(ArduinoBluetoothTests, shouldStartAndBroadcastServices) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();
  std::shared_ptr<IBLEService> mockBLEService = std::make_shared<MockBLEService>();

  const char *expectedName = "Test";

  EXPECT_CALL(mockBLEDevice, setLocalName(testing::StrEq(expectedName))).Times(1);
  EXPECT_CALL(mockBLEDevice, addService(mockBLEService)).Times(1);
  EXPECT_CALL(mockBLEDevice, setAdvertisedService(mockBLEService)).Times(1);
  EXPECT_CALL(mockBLEDevice, advertise()).Times(1);

  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, expectedName);
  auto arduinoService = ArduinoGattService(&mockSerial, mockBLEService);
  arduinoBluetooth.addService(&arduinoService);
  bool result = arduinoBluetooth.start();

  EXPECT_TRUE(result);
}

TEST(ArduinoBluetoothTests, shouldUpdateServicesIfConnectedToCentral) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();
  auto mockBLECentral = std::make_shared<MockBLECentral>();
  auto mockGattService = MockGattService();

  EXPECT_CALL(*mockBLECentral, connected()).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*mockBLECentral, address()).Times(1);
  EXPECT_CALL(mockBLEDevice, central()).Times(1).WillOnce(Return(mockBLECentral));
  EXPECT_CALL(mockGattService, update()).Times(1);

  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, "Test");
  arduinoBluetooth.addService(&mockGattService);
  arduinoBluetooth.update();
}

TEST(ArduinoBluetoothTests, shouldEndBLEDeviceOnStop) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();

  EXPECT_CALL(mockBLEDevice, end()).Times(1);

  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, "Test");
  bool result = arduinoBluetooth.stop();

  EXPECT_TRUE(result);
}

TEST(ArduinoBluetoothTests, shouldCreateArduinoGattCharacteristic) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();
  auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();

  const char *expectedUuid = "test";

  EXPECT_CALL(mockBLEDevice, createCharacteristic(testing::StrEq(expectedUuid)))
      .Times(1)
      .WillOnce(Return(mockBLECharacteristic));

  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, "Test");
  auto arduinoCharacteristic = arduinoBluetooth.createCharacteristic(expectedUuid);

  EXPECT_TRUE(arduinoCharacteristic);
}

TEST(ArduinoBluetoothTests, shouldCreateArduinoGattService) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();
  auto mockBLEService = std::make_shared<MockBLEService>();

  const char *expectedUuid = "test";

  EXPECT_CALL(mockBLEDevice, createService(testing::StrEq(expectedUuid)))
      .Times(1)
      .WillOnce(Return(mockBLEService));

  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, "Test");
  auto arduinoService = arduinoBluetooth.createService(expectedUuid);

  EXPECT_TRUE(arduinoService);
}

TEST(ArduinoBluetoothTests, numberServicesShouldHaveMaximum) {
  auto mockSerial = NiceMock<MockSerial>();
  auto mockBLEDevice = MockBLEDevice();
  auto mockBLEService = std::make_shared<MockBLEService>();
  auto arduinoService = ArduinoGattService(&mockSerial, mockBLEService);
  auto arduinoBluetooth = ArduinoBluetooth(&mockSerial, &mockBLEDevice, "Test");

  arduinoBluetooth.addService(&arduinoService);
  arduinoBluetooth.addService(&arduinoService);
  arduinoBluetooth.addService(&arduinoService);
  arduinoBluetooth.addService(&arduinoService);
  bool success5 = arduinoBluetooth.addService(&arduinoService);
  bool success6 = arduinoBluetooth.addService(&arduinoService);

  EXPECT_TRUE(success5);
  EXPECT_FALSE(success6);
}
