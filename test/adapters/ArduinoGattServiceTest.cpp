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
  std::unique_ptr<IBLEService> mockBLEService = std::make_unique<MockBLEService>();
  auto mockBLEDevice = std::make_shared<MockBLEDevice>();

  EXPECT_CALL(*mockBLEDevice, addService(mockBLEService.get())).Times(1);

  auto arduinoService =
      std::make_unique<ArduinoGattService>(&mockSerial, std::move(mockBLEService));
  arduinoService->addServiceToBLEDevice(mockBLEDevice.get());
}

TEST(ArduinoGattServiceTests, shouldAdvertiseServiceOnBLEDevice) {
  auto mockSerial = MockSerial();
  std::unique_ptr<IBLEService> mockBLEService = std::make_unique<MockBLEService>();
  auto mockBLEDevice = std::make_shared<MockBLEDevice>();

  EXPECT_CALL(*mockBLEDevice, setAdvertisedService(mockBLEService.get())).Times(1);

  auto arduinoService =
      std::make_unique<ArduinoGattService>(&mockSerial, std::move(mockBLEService));
  arduinoService->advertiseServiceOnBLEDevice(mockBLEDevice.get());
}

TEST(ArduinoGattServiceTests, shouldAddAndUpdateCharacteristic) {
  auto mockSerial = MockSerial();
  auto mockBLEService = std::make_unique<NiceMock<MockBLEService>>();
  auto mockBLECharacteristic = std::make_unique<NiceMock<MockBLECharacteristic>>();

  uint8_t expectedValue = 200;
  EXPECT_CALL(*mockBLECharacteristic, value()).Times(1).WillOnce(Return(expectedValue));
  EXPECT_CALL(*mockBLECharacteristic, written()).Times(1).WillOnce(Return(true));

  auto arduinoCharacteristic =
      ArduinoGattCharacteristic(&mockSerial, std::move(mockBLECharacteristic));

  uint8_t receivedValue = 0;

  arduinoCharacteristic.addCallback(
      [&receivedValue](ValueBuffer buffer) { receivedValue = buffer.data[0]; });

  auto arduinoService =
      std::make_unique<ArduinoGattService>(&mockSerial, std::move(mockBLEService));
  arduinoService->addCharacteristic(&arduinoCharacteristic);
  arduinoService->update();

  EXPECT_EQ(expectedValue, receivedValue);
}

TEST(ArduinoGattServiceTests, numberCharacteristicsShouldHaveMaximum) {
  auto mockSerial = MockSerial();
  auto mockBLEService = std::make_unique<NiceMock<MockBLEService>>();
  auto mockBLECharacteristic = std::make_unique<NiceMock<MockBLECharacteristic>>();
  auto arduinoCharacteristic =
      ArduinoGattCharacteristic(&mockSerial, std::move(mockBLECharacteristic));
  auto arduinoService =
      std::make_unique<ArduinoGattService>(&mockSerial, std::move(mockBLEService));

  arduinoService->addCharacteristic(&arduinoCharacteristic);
  arduinoService->addCharacteristic(&arduinoCharacteristic);
  arduinoService->addCharacteristic(&arduinoCharacteristic);
  arduinoService->addCharacteristic(&arduinoCharacteristic);
  bool success5 = arduinoService->addCharacteristic(&arduinoCharacteristic);
  bool success6 = arduinoService->addCharacteristic(&arduinoCharacteristic);

  EXPECT_TRUE(success5);
  EXPECT_FALSE(success6);
}
