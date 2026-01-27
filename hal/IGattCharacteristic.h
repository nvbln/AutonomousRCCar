#ifndef IGATTCHARACTERISTIC_H
#define IGATTCHARACTERISTIC_H

#include <string>
#include <functional>

struct ValueBuffer {
    uint8_t data[20];
    size_t length;
};

template<typename T>
struct Result {
    bool success;
    T data;
};

class IGattCharacteristic {
public:
    using Callback = std::function<void(Result<ValueBuffer>)>;
    virtual ~IGattCharacteristic() = default;

    virtual std::string uuid() const = 0;
    virtual Result<ValueBuffer> read() = 0;
    virtual bool write(const ValueBuffer& valueBuffer) = 0;

    virtual bool addCallback(Callback callback) = 0;
    virtual void update() = 0;
};
#endif
