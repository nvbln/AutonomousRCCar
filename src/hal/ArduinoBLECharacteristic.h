#pragma once

#include <memory>

#include <ArduinoBLE.h>

#include "IBLECharacteristic.h"

/**
 * @class ArduinoBLECharacteristic
 * @brief wrapper implementation of the ArduinoBLE BLECharacteristic
 *
 * This connects the IBLECharacteristic to the ArduinoBLE library,
 * such that the application can run on Arduino devices.
 */
class ArduinoBLECharacteristic : public IBLECharacteristic {
public:
    ArduinoBLECharacteristic(const char* uuid) : 
        mCharacteristic(uuid, BLERead | BLEWrite) {};

    /**
     * @see IBLECharacteristic::writeValue()
     */
    void writeValue(const uint8_t value) override {
        mCharacteristic.writeValue(value);
    }

    /**
     * @see IBLECharacteristic::read()
     */
    uint8_t read() override {
        return mCharacteristic.read();
    }

    /**
     * @see IBLECharacteristic::value()
     */
    uint8_t value() override {
        return mCharacteristic.value();
    }

    /**
     * @see IBLECharacteristic::written()
     */
    bool written() override {
        return mCharacteristic.written();
    }

private:
    friend class ArduinoBLEService;
    BLEByteCharacteristic mCharacteristic;
};
