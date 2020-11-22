#ifndef MULTILISTENER_H
#define MULTILISTENER_H

#include "Channel.h"
#include "Listener.h"

#include <functional>
#include <initializer_list>
#include <stack>

namespace lk::msg {

/*
 * A MultiListener listens to many channels at the same time.
 * This is not default behavior of a Listener, since usually channels
 * dont share common types / conventions.
 */
class MultiListener {
    std::stack<Listener> m_listeners;
    std::function<void(Message&)> m_handler;

    void receive(Message& msg);

public:
    MultiListener(std::initializer_list<Channel::Ptr>&& list, decltype(m_handler) handler);
};

}

#endif // MULTILISTENER_H
