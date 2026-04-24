#pragma once

#include "ILed.h"
#include "IPinIO.h"

/**
 * @class ArduinoLED
 * @brief ILed implementation for Arduino
 */
class ArduinoLed : public ILed {
public:
  /**
   * @brief Creates an object representing the LED at the given pin.
   *
   * @param pin The pin that the LED is corresponds to.
   */
  ArduinoLed(IPinIO *const pinIO, uint8_t pin);

  /**
   * @see ILED:turn()
   */
  void turn() override;

  /**
   * @see ILED:turnOn()
   */
  void turnOn() override;

  /**
   * @see ILED:turnOff()
   */
  void turnOff() override;

private:
  IPinIO *const mPinIO;
  bool mOn = false;
  uint8_t mPin;
};
