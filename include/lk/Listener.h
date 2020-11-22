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
    Listener(Channel::Ptr channel, decltype(m_handler) handler = nullptr);
    ~Listener();
};

}

#endif // LISTENER_H
