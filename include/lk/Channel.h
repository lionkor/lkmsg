#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include <set>

namespace lk::msg {

struct Message;
class Listener;

/*
 * A Channel distributes Messages to Listeners.
 * On creation, a channel is open. Only open channels
 * will distribute a message. `send()` will return false if
 * the channel is closed, and the message will not be sent,
 * and will instead be destructed silently.
 */
class Channel {
private:
    Channel() = default;
    bool m_open { true };
    std::set<Listener*> m_listeners;

    void add_listener(Listener* listener);
    void remove_listener(Listener* listener);

    friend Listener;

public:
    using Ptr = std::shared_ptr<Channel>;
    static Ptr create();
    virtual ~Channel() = default;
    [[nodiscard]] bool send(Message&& message);
    bool is_open() const;
    void close();
    void open();
};
}

#endif // CHANNEL_H
