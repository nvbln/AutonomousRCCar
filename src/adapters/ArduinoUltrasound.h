#pragma once

#include "Event.h"
#include "IUltrasound.h"
#include "IUltrasoundSource.h"

/**
 * @class ArduinoUltrasound
 * @brief notifies subscribers on new ultrasound data from IUltrasoundSource.
 */
class ArduinoUltrasound : public IUltrasound {
public:
  /**
   * @brief creates an object that handles the Ultrasound distance measurements.
   *
   */
  ArduinoUltrasound(IUltrasoundSource *ultrasound) : mUltrasound(ultrasound) {}

  /**
   * @see IUltrasound::addCallback()
   */
  bool subscribe(Callback callback) override { return event.subscribe(callback); }

  /**
   * @brief Notifies its subscribers of the most up-to-date distance measurement.
   *
   * Due to the nature that the distance measurement is calculated on Arduino,
   * there is no guarantee that this is new data. There is only the guarantee
   * that this is the most recent measurement.
   *
   * @see IUltrasound::update()
   */
  void update() override;

private:
  IUltrasoundSource *mUltrasound;

  Event<Callback, 5, float> event;
};
