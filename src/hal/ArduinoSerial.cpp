#include <Arduino.h>

#include "ArduinoSerial.h"

void ArduinoSerial::begin(unsigned long baud) const {
    Serial.begin(baud);
}

size_t ArduinoSerial::print(const char str[]) const {
    Serial.print(str);
}

size_t ArduinoSerial::println(const char str[]) const {
    Serial.println(str);
}

