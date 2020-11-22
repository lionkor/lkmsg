#include "Message.h"

using namespace lk::msg;

Message::Message(Type type, std::any&& data)
    : type(type)
    , data(data) { }
