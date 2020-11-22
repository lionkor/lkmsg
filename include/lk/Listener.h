#ifndef LISTENER_H
#define LISTENER_H

#include "Channel.h"
#include <functional>
#include <memory>

namespace lk::msg {

class Listener final {
private:
    Channel::Ptr m_channel;
    std::function<void(Message&)> m_handler;

    void receive(Message& m);

    friend Channel;

public:
    Listener(Channel::Ptr channel, decltype(m_handler) handler);
    ~Listener();
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;
};

}

#endif // LISTENER_H
