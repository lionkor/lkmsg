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
public:
    using Handler = std::function<void(const Message&)>;

private:
    Channel::Ptr m_channel;
    Handler m_handler;

    void receive(const Message& m);

    friend Channel;

public:
    Listener(Channel::Ptr channel, Handler handler);
    ~Listener();
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;

    void set_handler(Handler new_handler);
};

}

#endif // LISTENER_H
