#include "messages.h"

#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace lk;

int main() {
    std::cout << "lk::msg version " << msg::version_string << std::endl;

    msg::Channel::Ptr channel = msg::Channel::create();

    std::thread t1 { [&] {
        auto id = std::this_thread::get_id();
        lk::msg::Listener::Handler fn = [&](const lk::msg::Message& msg) -> void {
            std::string data = std::any_cast<std::string>(msg.data);
            std::cout << "rcv: " << id << ": " << data << std::endl;
        };

        lk::msg::Listener listener(channel, fn);
        while (channel->is_open()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } };
    t1.detach();

    std::thread t2 { [&] {
        auto id = std::this_thread::get_id();
        lk::msg::Listener::Handler fn = [&](const lk::msg::Message& msg) -> void {
            std::string data = std::any_cast<std::string>(msg.data);
            std::cout << "rcv: " << id << ": " << data << std::endl;
        };

        lk::msg::Listener listener(channel, fn);
        while (channel->is_open()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } };
    t2.detach();

    while (channel->is_open()) {
        std::cout << ">>> ";
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "close") {
            channel->close();
        }
        lk::msg::Message m(0, msg);
        bool ok = channel->send(std::move(m));
        if (!ok) {
            std::cout << "error!" << std::endl;
        }
    }

    std::cout << "gracefully terminating..." << std::endl;

    /*
    msg::Channel::Ptr channel = msg::Channel::create();

    auto fn = [&](const msg::Message& m) {
        if (m.purpose == 0) {
            auto val = std::any_cast<const char* const>(m.data);
            std::cout << "rcv: " << val << std::endl;
        }
    };

    {
        msg::Listener listener(channel, fn);
        msg::Listener listener2(channel, fn);

        msg::Message message(0, std::any("hello"));

        channel->send(std::move(message));
    }

    msg::Channel::Ptr channel2 = msg::Channel::create();

    msg::MultiListener multi_listener({ channel2, channel }, fn);

    msg::Message message(0, std::any("hello from channel 1"));
    msg::Message message2(0, std::any("hello from channel 2"));

    channel->send(std::move(message));
    channel2->send(std::move(message2));

    */
}
