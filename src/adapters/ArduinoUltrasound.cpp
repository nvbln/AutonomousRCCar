#include "IUltrasoundSource.h"

#include "ArduinoUltrasound.h"

void ArduinoUltrasound::update() {
    unsigned long duration = mUltrasound->duration(); 
    if (duration != -1) {
        float distance = float(duration) * 0.01715; // sound of speed in cm/us divided by 2.
        event.notify(distance);
    }

    // Measure duration for the next cycle.
    mUltrasound->measureDuration();
}
