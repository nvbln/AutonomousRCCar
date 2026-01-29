#ifndef IGATTCHARACTERISTIC_H
#define IGATTCHARACTERISTIC_H

#include <string>
#include <functional>

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
    size_t length;
};

template<typename T>
/**
 * @struct Result
 * @brief Represents the data retrievel operation result.
 *
 * This struct combines the goal of returning data with
 * communicating whether the data retrieval itself was
 * successful and therefore whether the data is good or not.
 *
 * @tparam T the type of data that is retrieved.
 */
struct Result {
    /**
     * @brief Whether the data was successfully retrieved and stored
     */
    bool success;

    /**
     * @brief The retrieved data.
     */
    T data;
};

/**
 * @class IGattCharacteristic
 * @brief A channel for reading/writing data over Bluetooth
 *
 * This interface provides control over the GATT Characteristics
 * in BLuetooth BLE. They are channels to read data from or write
 * data to, in order to communicate with central devices.
 */
class IGattCharacteristic {
public:
    /**
     * @brief Callback type used for handling newly written data to the Characteristic.
     *
     * Represents a function that receives the written value through the
     * Result<ValueBuffer> and passes it to the listener.
     */
    using Callback = std::function<void(ValueBuffer)>;

    virtual ~IGattCharacteristic() = default;

    /**
     * @brief returns the UUID that the Characteristic is identified by.
     *
     * @return UUID of the Characteristic
     */
    virtual std::string uuid() const = 0;

    /**
     * @brief reads the value from the Characteristic
     *
     * @return whether the read was successful, if so, the value of the Characteristic.
     */
    virtual Result<ValueBuffer> read() = 0;

    /**
     * @brief writes the buffer to the Characteristic.
     *
     * @return whether the write operation was successful.
     */
    virtual bool write(const ValueBuffer& valueBuffer) = 0;

    /**
     * @brief adds the given callback to the Characteristic.
     *
     * The Callback is called when the value of the
     * Characteristic is updated.
     * @return whether the callback was added.
     */
    virtual bool addCallback(Callback callback) = 0;

    /**
     * @brief check if the Characteristic was updated.
     *
     * Specifically, checks if a new value has been written to the Characteristic.
     */
    virtual void update() = 0;
};
#endif
