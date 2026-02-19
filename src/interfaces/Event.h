#pragma once

#include <cstdint>

/**
 * @class Event
 * @brief Fixed-capacity event dispatcher.
 *
 * This class implements a lightweight publish/subscribe mechanism
 * Subscribers register a callback of type `CallbackType`, which is
 * the specific callback used by the class that requires callbacks.
 * All registered callbacks are invoked when `notify()` is called.
 *
 * @tparam CallbackType The type of callback stored by the event.
 * @tparam maxSubscribers Maximum number of callbacks that can be registered.
 * @tparam Args... The argument types forwarded to each callback.
 */
template<typename CallbackType, uint8_t maxSubscribers, typename... Args>
class Event {
public:
    /**
     * @brief Registers a new callback.
     *
     * @param callback The callback function to register.
     * @return whether the callback was successfully registered.
     */
    bool subscribe(CallbackType callback) {
        if (mNumSubscribers >= maxSubscribers) {
            return false;
        }
        
        mCallbacks[mNumSubscribers] = callback;
        mNumSubscribers++;

        return true;
    }

    /**
     * @brief Invokes all registered callbacks in the order of subscription.
     *
     * @param args Arguments forwarded to each callback.
     */
    void notify(Args... args) {
        for (int i = 0; i < mNumSubscribers; i++) {
            mCallbacks[i](args...);
        }
    }

private:
    uint8_t mNumSubscribers = 0;
    CallbackType mCallbacks[maxSubscribers];
};
