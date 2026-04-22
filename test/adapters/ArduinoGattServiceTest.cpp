#include "ArduinoGattService.h"
#include "ArduinoGattCharacteristic.h"
#include "IBLEService.h"
#include "MockBLECharacteristic.h"
#include "MockBLEDevice.h"
#include "MockBLEService.h"
#include "MockSerial.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::NiceMock;
using ::testing::Return;

TEST(ArduinoGattServiceTests, shouldAddServiceToBLEDevice) {
  auto mockSerial = MockSerial();
  std::shared_ptr<IBLEService> mockBLEService = std::make_shared<MockBLEService>();
  auto mockBLEDevice = std::make_shared<MockBLEDevice>();

  EXPECT_CALL(*mockBLEDevice, addService(mockBLEService)).Times(1);

  auto arduinoService = std::make_unique<ArduinoGattService>(&mockSerial, mockBLEService);
  arduinoService->addServiceToBLEDevice(mockBLEDevice.get());
}

TEST(ArduinoGattServiceTests, shouldAdvertiseServiceOnBLEDevice) {
  auto mockSerial = MockSerial();
  std::shared_ptr<IBLEService> mockBLEService = std::make_shared<MockBLEService>();
  auto mockBLEDevice = std::make_shared<MockBLEDevice>();

  EXPECT_CALL(*mockBLEDevice, setAdvertisedService(mockBLEService)).Times(1);

  auto arduinoService = std::make_unique<ArduinoGattService>(&mockSerial, mockBLEService);
  arduinoService->advertiseServiceOnBLEDevice(mockBLEDevice.get());
}

TEST(ArduinoGattServiceTests, shouldAddAndUpdateCharacteristic) {
  auto mockSerial = MockSerial();
  auto mockBLEService = std::make_shared<NiceMock<MockBLEService>>();
  auto mockBLECharacteristic = std::make_unique<NiceMock<MockBLECharacteristic>>();

  uint8_t expectedValue = 200;
  EXPECT_CALL(*mockBLECharacteristic, value()).Times(1).WillOnce(Return(expectedValue));
  EXPECT_CALL(*mockBLECharacteristic, written()).Times(1).WillOnce(Return(true));

  auto arduinoCharacteristic =
      std::make_shared<ArduinoGattCharacteristic>(&mockSerial, std::move(mockBLECharacteristic));

  uint8_t receivedValue = 0;

  arduinoCharacteristic->addCallback(
      [&receivedValue](ValueBuffer buffer) { receivedValue = buffer.data[0]; });

  auto arduinoService = std::make_unique<ArduinoGattService>(&mockSerial, mockBLEService);
  arduinoService->addCharacteristic(arduinoCharacteristic);
  arduinoService->update();

  EXPECT_EQ(expectedValue, receivedValue);
}

TEST(ArduinoGattServiceTests, numberCharacteristicsShouldHaveMaximum) {
  auto mockSerial = MockSerial();
  auto mockBLEService = std::make_shared<NiceMock<MockBLEService>>();
  auto mockBLECharacteristic = std::make_unique<NiceMock<MockBLECharacteristic>>();
  auto arduinoCharacteristic =
      std::make_shared<ArduinoGattCharacteristic>(&mockSerial, std::move(mockBLECharacteristic));
  auto arduinoService = std::make_unique<ArduinoGattService>(&mockSerial, mockBLEService);

  arduinoService->addCharacteristic(arduinoCharacteristic);
  arduinoService->addCharacteristic(arduinoCharacteristic);
  arduinoService->addCharacteristic(arduinoCharacteristic);
  arduinoService->addCharacteristic(arduinoCharacteristic);
  bool success5 = arduinoService->addCharacteristic(arduinoCharacteristic);
  bool success6 = arduinoService->addCharacteristic(arduinoCharacteristic);

  EXPECT_TRUE(success5);
  EXPECT_FALSE(success6);
}
