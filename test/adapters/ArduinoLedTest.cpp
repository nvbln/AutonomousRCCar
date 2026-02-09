#include "IPinIO.h"
#include "ArduinoLed.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::NiceMock;

class MockPinIO : public IPinIO {
public:
    MOCK_METHOD(void, pinMode, (uint8_t pin, PinIOMode mode), (const, override));
    MOCK_METHOD(void, digitalWrite, (uint8_t pin, PinIOValue value), (const, override));
};

uint8_t mockPin = 0;

/**
 * There are various modes to interact with a pin
 * in Arduino. We want the software to set the current
 * in the pin, this means that the LED should set itself
 * to "driving" mode.
 */
TEST(ArduinoLedTests, ledShouldDrivePin) {
    auto mockPinIO = std::make_shared<NiceMock<MockPinIO>>();

    EXPECT_CALL(*mockPinIO, pinMode(mockPin, PinIOMode::Output));
    std::unique_ptr<ArduinoLed> arduinoLed = std::make_unique<ArduinoLed>(mockPinIO, mockPin);
}

/*
 * The ArduinoLed should start turned off. It correctly updates
 * (and keeps track of) its state, when the digitalWrite() is first
 * set to High and then to Low.
 */
TEST(ArduinoLedTests, turnShouldChangeStateOfLED) {
    auto mockPinIO = std::make_shared<NiceMock<MockPinIO>>();
    std::unique_ptr<ArduinoLed> arduinoLed = std::make_unique<ArduinoLed>(mockPinIO, mockPin);

    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::High));
    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::Low));

    arduinoLed->turn();
    arduinoLed->turn();
}

TEST(ArduinoLedTests, turnOnShouldTurnUpVoltage) {
    auto mockPinIO = std::make_shared<NiceMock<MockPinIO>>();
    std::unique_ptr<ArduinoLed> arduinoLed = std::make_unique<ArduinoLed>(mockPinIO, mockPin);

    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::High)).Times(1);
    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::Low)).Times(0);

    arduinoLed->turnOn();
}

TEST(ArduinoLedTests, turnOffShouldTurnDownVoltage) {
    auto mockPinIO = std::make_shared<NiceMock<MockPinIO>>();
    std::unique_ptr<ArduinoLed> arduinoLed = std::make_unique<ArduinoLed>(mockPinIO, mockPin);

    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::Low)).Times(1);
    EXPECT_CALL(*mockPinIO, digitalWrite(mockPin, PinIOValue::High)).Times(0);

    arduinoLed->turnOff();
}
