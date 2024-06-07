//
// Created by 林竣堂 on 2024/3/15.
//
#include "Message.hpp"

Message::Message() : Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/message.png"), 0) {
}