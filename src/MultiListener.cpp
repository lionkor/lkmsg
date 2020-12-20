#include "MultiListener.h"

using namespace lk::msg;

void MultiListener::receive(const Message& msg) {
    if (m_handler) {
        m_handler(msg);
    }
}

MultiListener::MultiListener(std::initializer_list<Channel::Ptr>&& list, Listener::Handler handler)
    : m_handler(handler) {
    Listener::Handler internal_handler = std::bind(&MultiListener::receive, this, std::placeholders::_1);
    for (auto& channel_ptr : list) {
        m_listeners.emplace(channel_ptr, internal_handler);
    }
}
