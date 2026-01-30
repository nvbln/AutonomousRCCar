#ifndef IGATTSERVICE_H 
#define IGATTSERVICE_H

#include <string>

#include "IGattCharacteristic.h"

/**
 * @class IGattService
 * @brief A grouping of GATT Characteristics for Bluetooth
 *
 * The purpose of services in Bluetooth BLE is to group the
 * GATT Characteristics. Every Characteristic is published
 * over Bluetooth through a GATT Service. This interface 
 * reflects this behaviour.
 */
class IGattService {
public:
    virtual ~IGattService() = default;

    /**
     * @brief returns the UUID that the Service is identified by.
     *
     * Note: can be the same as the UUID of the Characteristic.
     * @return UUID of the Service.
     */
    virtual std::string uuid() const = 0;

    /**
     * @brief adds the Characteristic to the Service
     *
     * GATT Characteristics need to be added to GATT services
     * to be broadcasted. The Service also takes care of updating
     * the Characteristic (i.e. notifies when its values has changed).
     * @param characteristic pointer to the GATT Characteristic to add to the service.
     * @return whether the Characteristic was added to the service.
     */
    virtual bool addCharacteristic(std::shared_ptr<IGattCharacteristic> characteristic) = 0;

    /**
     * @brief check if the characteristics in the service were updated.
     */
    virtual void update();

};
#endif
