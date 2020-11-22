#include "messages.h"

#include <iostream>
#include <string>

using namespace lk;

int main() {
    std::cout << "lk::msg version " << msg::version_string << std::endl;

    msg::Channel::Ptr channel = msg::Channel::create();

    auto fn = [&](msg::Message& m) {
        if (m.type == 0) {
            auto val = std::any_cast<const char* const>(m.data);
            std::cout << "rcv: " << val << std::endl;
        }
    };

    msg::Listener listener(channel, fn);
    msg::Listener listener2(channel, fn);

    msg::Message message(0, std::any("hello"));

    channel->send(std::move(message));
}
