#ifndef LISTENER_H
#define LISTENER_H

#include "Channel.h"
#include <functional>
#include <memory>

namespace lk::msg {

/*
 * A Listener listens to a single channel and calls a callback on each
 * message received. For Listening to multiple channels at once, use
 * MultiListener.
 */
class Listener final {
private:
    Channel::Ptr m_channel;
    std::function<void(const Message&)> m_handler;

    void receive(const Message& m);

    friend Channel;

public:
    Listener(Channel::Ptr channel, decltype(m_handler) handler);
    ~Listener();
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;

    void set_handler(decltype(m_handler) new_handler);
};

}

#endif // LISTENER_H
