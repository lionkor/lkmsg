#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include <set>

namespace lk::msg {

struct Message;
class Listener;

class Channel {
private:
    Channel() = default;
    std::set<Listener*> m_listeners;

    void add_listener(Listener* listener);
    void remove_listener(Listener* listener);

    friend Listener;

public:
    using Ptr = std::shared_ptr<Channel>;
    static Ptr create();
    virtual ~Channel() = default;

    void send(Message&& message);
};
}

#endif // CHANNEL_H
