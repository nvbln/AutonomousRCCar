#ifndef IBLUETOOTH_H
#define IBLUETOOTH_H

#include <memory>
#include <string>

#include "IGattService.h"
#include "IGattCharacteristic.h"

/**
 * @class IBluetooth
 * @brief General interface for interacting with the Bluetooth component.
 *
 * This interface provides a way for the application logic to interact with
 * the bluetooth component from the device layer. It manages the bluetooth
 * component itself and provides methods to create bluetooth-related
 * objects such as services and characteristics.
 */
class IBluetooth {
public:
    virtual ~IBluetooth() = default;

    /**
     * @brief Starts broadcasting over Bluetooth.
     *
     * Starts the Bluetooth component by broadcasting the added services
     * and their characteristics, allowing for read/write operations
     * by central devices.
     */
    virtual bool start() = 0;

    /**
     * @brief Stops broadcasting over Bluetooth.
     */
    virtual bool stop() = 0;

    /**
     * @brief Creates a GATT Service and returns it.
     *
     * Instructs the device to create a low-level service object,
     * and returns it in the form of the IGattService interface.
     * The service does not get automatically added.
     * @see addService() for adding the service.
     * 
     * @param uuid The ID that identifies the service to other devices.
     */
    virtual std::shared_ptr<IGattService> createService(const char* uuid) const = 0;

    /**
     * @brief Creates a GATT Characteristic and returns it.
     *
     * Instructs the device to create a low-level characteristic object,
     * and returns it in the form of the IGattCharacteristic interface.
     *
     * @param uuid The ID that identifies the characteristic to other devices.
     * @param valueLength Not implemented yet.
     */
    virtual std::shared_ptr<IGattCharacteristic> createCharacteristic(const char* uuid) const = 0;

    /**
     * @brief Adds the service for broadcasting.
     *
     * Enables the service to be broadcasted when the Bluetooth
     * is started. Its characteristics will in turn be made
     * available for reading/write operations.
     *
     * @param service The service to be broadcasted.
     * @return whether the Service was added.
     */
    virtual bool addService(std::shared_ptr<IGattService> service) = 0;

};
#endif
