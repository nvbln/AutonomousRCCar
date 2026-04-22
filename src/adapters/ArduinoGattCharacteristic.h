#pragma once

#include <memory>

#include "Event.h"
#include "IBLECharacteristic.h"
#include "IBLEService.h"
#include "IGattCharacteristic.h"
#include "ISerial.h"

/**
 * @class ArduinoGattCharacteristic
 * @brief IGattCharacteristic implementation for Arduino
 */
class ArduinoGattCharacteristic : public IGattCharacteristic {
public:
  /**
   * @brief Creates a GATT Characteristic for sending/receiving data over Bluetooth
   *
   * @param serial The Arduino Serial interface for printing messages.
   * @param uuid The UUID that the Characteristic is identified by.
   * @param valueLength not implemented yet.
   */
  ArduinoGattCharacteristic(const ISerial *serial,
                            std::unique_ptr<IBLECharacteristic> characteristic)
      : mSerial(serial), mCharacteristic(std::move(characteristic)) {
    mCharacteristic->writeValue(0);
  };

  /**
   * @brief adds the characteristic to the service.
   *
   * @param service the BLEService to add the characteristic to.
   */
  void addCharacteristicToService(IBLEService *service);

  /**
   * @see IGattCharacteristic::read()
   */
  Result<ValueBuffer> read() override;

  /**
   * @see IGattCharacteristic::write()
   */
  bool write(const ValueBuffer &valueBuffer) override;

  /**
   * @see IGattCharacteristic::addCallback()
   */
  bool addCallback(Callback callback) override { return event.subscribe(callback); }

  /**
   * @see IGattCharacteristic::update()
   */
  void update() override;

private:
  const ISerial *mSerial;
  std::unique_ptr<IBLECharacteristic> mCharacteristic;

  Event<Callback, 5, ValueBuffer> event;
};
