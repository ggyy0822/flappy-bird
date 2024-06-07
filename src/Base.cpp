//
// Created by 林竣堂 on 2024/3/18.
//
#include "Base.hpp"

Base::Base() : Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/base.png"), 1) {
}

void Base::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

