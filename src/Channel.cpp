#include "Channel.h"
#include "Listener.h"

#include <iostream>

using namespace lk::msg;

void Channel::add_listener(Listener* listener) {
    if (listener) {
        m_listeners.insert(listener);
        std::cout << "added listener " << listener << std::endl;
    }
}

void Channel::remove_listener(Listener* listener) {
    if (listener) {
        m_listeners.erase(listener);
        std::cout << "removed listener " << listener << std::endl;
    }
}

Channel::Ptr Channel::create() {
    return Ptr(new Channel);
}

void Channel::send(Message&& message) {
    for (auto* listener : m_listeners) {
        listener->receive(message);
    }
}
