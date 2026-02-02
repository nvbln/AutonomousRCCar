#ifndef ISERIAL_H
#define ISERIAL_H

#include <cstddef>

/**
 * @class ISerial
 * @brief thin wrapper for the Serial class in the Arduino library.
 *
 * The main purpose of this wrapper is to separate the
 * application logic from the Arduino library that relies
 * on the Arduino hardware. Removing the (direct) dependency
 * of the application on the hardware.
 */
class ISerial {
public:
   virtual ~ISerial() = default;

   /**
    * @brief Prints the text to the serial console.
    *
    * @see the Arduino.h API
    */
   virtual size_t print(const char str[]); 

   /**
    * @brief Prints the text to the serial console with a newline.
    *
    * @see the Arduino.h API
    */
   virtual size_t println(const char str[]);
};
#endif
