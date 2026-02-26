#pragma once

#include <cstdint>

/**
 * @struct ValueBuffer
 * @brief Represents a buffer of bytes from a Bluetooth Characteristic.
 *
 * This struct stores the bytes that are written/read by Bluetooth
 * characteristics. They can vary in size and therefore come with
 * a size counter (length).
 */
struct ValueBuffer {
  /**
   * @brief The array of bytes.
   */
  uint8_t data[20];

  /**
   * @brief the length of the array of bytes.
   */
  std::size_t length;
};
