#include "MockSerial.h"
#include "MockBLECharacteristic.h"
#include "MockBLEService.h"
#include "IBLECharacteristic.h"
#include "IGattCharacteristic.h"
#include "ArduinoGattCharacteristic.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::NiceMock;

TEST(ArduinoGattCharacteristicTests, valueShouldBeZeroOnInstantiation) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLECharacteristic = std::make_shared<MockBLECharacteristic>();

    EXPECT_CALL(*mockBLECharacteristic, writeValue(0)).Times(1);

    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);
}

TEST(ArduinoGattCharacteristicTests, shouldAddCharacteristicToService) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    std::shared_ptr<IBLECharacteristic> mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();
    auto mockBLEService = std::make_shared<MockBLEService>();

    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);

    EXPECT_CALL(*mockBLEService, addCharacteristic(mockBLECharacteristic)).Times(1);

    arduinoCharacteristic->addCharacteristicToService(mockBLEService);
}

TEST(ArduinoGattCharacteristicTests, shouldReadValueFromCharacteristic) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();

    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);

    EXPECT_CALL(*mockBLECharacteristic, value()).Times(1).WillOnce(Return(200));
    Result<ValueBuffer> result = arduinoCharacteristic->read();
    ASSERT_EQ(true, result.success);
    EXPECT_EQ(1, result.data.length);
    EXPECT_EQ(200, result.data.data[0]);
}

TEST(ArduinoGattCharacteristicTests, shouldWriteValueToCharacteristic) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();

    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);

    uint8_t expectedValue = 200;
    EXPECT_CALL(*mockBLECharacteristic, writeValue(expectedValue)).Times(1);

    ValueBuffer buffer{};
    buffer.data[0] = expectedValue;
    buffer.length = 1;
    arduinoCharacteristic->write(buffer);
}

TEST(ArduinoGattCharacteristicTests, shouldAddAndUpdateCallback) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();
    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);

    uint8_t expectedValue = 200;
    EXPECT_CALL(*mockBLECharacteristic, value()).Times(1).WillOnce(Return(expectedValue));
    EXPECT_CALL(*mockBLECharacteristic, written()).Times(1).WillOnce(Return(true));

    uint8_t receivedValue = 0;

    arduinoCharacteristic->addCallback([&receivedValue](ValueBuffer buffer) {
        receivedValue = buffer.data[0];
    });

    arduinoCharacteristic->update();

    EXPECT_EQ(expectedValue, receivedValue);
}

TEST(ArduinoGattCharacteristicTests, numberCallbacksShouldHaveMaximum) {
    auto mockSerial = std::make_shared<NiceMock<MockSerial>>();
    auto mockBLECharacteristic = std::make_shared<NiceMock<MockBLECharacteristic>>();
    auto arduinoCharacteristic = std::make_unique<ArduinoGattCharacteristic>(mockSerial, mockBLECharacteristic);

    arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});
    arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});
    arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});
    arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});
    bool success5 = arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});
    bool success6 = arduinoCharacteristic->addCallback([](ValueBuffer buffer) {});

    EXPECT_TRUE(success5);
    EXPECT_FALSE(success6);
}
