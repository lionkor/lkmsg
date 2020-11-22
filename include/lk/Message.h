#ifndef MESSAGE_H
#define MESSAGE_H

#include <any>

namespace lk::msg {

using Type = int;

struct Message final {

    Type type;
    std::any data;

    Message(Type type, std::any&& data);
};

}

#endif // MESSAGE_H
