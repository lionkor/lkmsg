#ifndef MESSAGE_H
#define MESSAGE_H

#include <any>

namespace lk::msg {

struct Message final {
    int purpose;
    std::any data;

    Message(int purpose, std::any&& data);
};

}

#endif // MESSAGE_H
