#include "Listener.h"

#include "Message.h"

using namespace lk::msg;

void Listener::receive(const Message& m) {
    if (m_handler) {
        m_handler(m);
    }
}

Listener::Listener(Channel::Ptr channel, Handler handler)
    : m_channel(channel)
    , m_handler(handler) {
    m_channel->add_listener(this);
}

Listener::~Listener() {
    m_channel->remove_listener(this);
}

void Listener::set_handler(Handler new_handler) {
    m_handler = new_handler;
}
