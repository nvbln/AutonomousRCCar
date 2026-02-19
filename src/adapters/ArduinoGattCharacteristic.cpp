#include "IBLEService.h"
#include "ArduinoGattCharacteristic.h"

void ArduinoGattCharacteristic::addCharacteristicToService(std::shared_ptr<IBLEService> service) {
    service->addCharacteristic(mCharacteristic);
}

Result<ValueBuffer> ArduinoGattCharacteristic::read() {
    ValueBuffer buffer{};
    buffer.data[0] = mCharacteristic->value();
    buffer.length = 1;

    return Result<ValueBuffer>{true, buffer};
}

bool ArduinoGattCharacteristic::write(const ValueBuffer& buffer) {
    if (buffer.length == 0) {
        return false;
    }
    
    mCharacteristic->writeValue(buffer.data[0]);
    return true;
}

void ArduinoGattCharacteristic::update() {
    if (mCharacteristic->written()) {
        Result<ValueBuffer> result = read();
        
        // Only send callbacks if the reading was actually successful.
        if (result.success) {
            event.notify(result.data);
        } else {
            mSerial->println("There was a problem reading the input value");
        }
    }
}
