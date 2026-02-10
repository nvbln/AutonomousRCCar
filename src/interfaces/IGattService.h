#pragma once

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
    virtual void update() = 0;

};
