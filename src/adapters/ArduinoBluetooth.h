#ifndef ARDUINOBLUETOOTH_H
#define ARDUINOBLUETOOTH_H

#include <string>
#include <memory>

#include "ISerial.h"
#include "IBluetooth.h"
#include "IGattCharacteristic.h"

/**
 * @class ArduinoBluetooth
 * @brief IBluetooth implementation for Arduino
 */
class ArduinoBluetooth : public IBluetooth {
public:
    /**
     * @brief Creates an instance representing the Bluetooth component.
     *
     * @param serial The Arduino Serial interface for printing messages.
     * @param name The name that it uses to advertise itself on Bluetooth.
     */
    ArduinoBluetooth(const std::shared_ptr<ISerial> serial, const std::shared_ptr<IBLEDevice> bleDevice, std::string name) : mBLEDevice(bleDevice), mSerial(serial), mName(name) {};

    /**
     * @brief Starts broadcasting the services and characteristics over Bluetooth.
     *
     * @return whether startup was successful (and it's broadcasting).
     */
    bool start() override;

    /**
     * @brief Responds to any changes/transactions
     *
     * This includes checking whether any central device wants to
     * connect and (if connected) whether any services/characteristics
     * were updated by the central device.
     */
    void update();

    /**
     * @brief Stops the broadcasting over Bluetooth
     *
     * @return whether shutdown was successful.
     */
    bool stop() override;

    /**
     * @brief Creates a new device-specific GATT Service and returns it as a general IGattService.
     *
     * A device-specific GATT Service is created that the device-layer 
     * can cast down to from the IGattService, but is returned as an IGattService
     * to keep the abstraction in the application logic.
     * @return a shared pointer to the object as an IGattService.
     */
    std::shared_ptr<IGattService> createService(const char* uuid) const override;

    /**
     * @brief Creates a new device-specific GATT Characteristic and returns it as a general IGattCharacteristic.
     *
     * A device-specific GATT Characteristic is created that the device-layer
     * can cast down to from the IGattCharacteristic, but is returned as an
     * IGattCharacteristic to keep the abstraction in the application logic.
     * @return a shared pointer to the object as an IGattCharacteristic.
     */
    std::shared_ptr<IGattCharacteristic> createCharacteristic(const char* uuid, const int valueLength) const override;

    /**
     * @see IBluetooth::addService()
     */
    bool addService(std::shared_ptr<IGattService> service) override;

private:
    std::shared_ptr<IBLEDevice> mBLEDevice;
    const std::shared_ptr<ISerial> mSerial;
    std::string mName;
    static const int mMaxNumServices = 5;
    std::shared_ptr<IGattService> mServices[mMaxNumServices];
    int mNumServices = 0;
};
#endif;
