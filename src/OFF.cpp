//
// Created by 林竣堂 on 2024/6/6.
//
#include "OFF.hpp"

OFF::OFF() : Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/OFF.png"), 95) {
}

void OFF::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }