#include "Listener.h"

#include "Message.h"

using namespace lk::msg;

void Listener::receive(Message& m) {
    if (m_handler) {
        m_handler(m);
    }
}

Listener::Listener(Channel::Ptr channel, decltype(m_handler) handler)
    : m_channel(channel)
    , m_handler(handler) {
    m_channel->add_listener(this);
}

Listener::~Listener() {
    m_channel->remove_listener(this);
}
