#include "MultiListener.h"

using namespace lk::msg;

void MultiListener::receive(Message& msg) {
    if (m_handler) {
        m_handler(msg);
    }
}

MultiListener::MultiListener(std::initializer_list<Channel::Ptr>&& list, decltype(m_handler) handler)
    : m_handler(handler) {
    std::function<void(Message&)> internal_handler = std::bind(&MultiListener::receive, this, std::placeholders::_1);
    for (auto& channel_ptr : list) {
        m_listeners.emplace(channel_ptr, internal_handler);
    }
}
