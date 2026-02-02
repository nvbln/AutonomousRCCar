#include <Arduino.h>

#include "ArduinoSerial.h"

size_t ArduinoSerial::print(const char str[]) {
    Serial.print(str);
}

size_t ArduinoSerial::println(const char str[]) {
    Serial.println(str);
}
