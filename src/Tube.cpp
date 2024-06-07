//
// Created by 林竣堂 on 2024/3/22.
//
#include "Tube.hpp"

Tube::Tube(const std::string &path) : Util::GameObject(std::make_unique<Util::Image>(path), 2) {
}

void Tube::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

const glm::vec2 &Tube::GetPosition() const { return m_Transform.translation; }
