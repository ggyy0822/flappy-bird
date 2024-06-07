//
// Created by 林竣堂 on 2024/6/6.
//
#include "ON.hpp"

ON::ON() : Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/ON.png"), 95) {
}

void ON::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }