#include "Message.h"

using namespace lk::msg;

Message::Message(int purpose, std::any&& data)
    : purpose(purpose)
    , data(data) { }
