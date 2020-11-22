#ifndef MULTILISTENER_H
#define MULTILISTENER_H

#include "Channel.h"
#include "Listener.h"

#include <functional>
#include <initializer_list>
#include <stack>

namespace lk::msg {

class MultiListener {
    std::stack<Listener> m_listeners;
    std::function<void(Message&)> m_handler;

    void receive(Message& msg);

public:
    MultiListener(std::initializer_list<Channel::Ptr>&& list, decltype(m_handler) handler);
};

}

#endif // MULTILISTENER_H
