//
// Created by 林竣堂 on 2024/3/29.
//
#include "Bird.hpp"

Bird::Bird() : Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Character/yellowbird.png"), 2) {
}

void Bird::SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

const glm::vec2 &Bird::GetPosition() const { return m_Transform.translation; }

bool Bird::isOverlap(const std::shared_ptr<Util::GameObject> &target) {
    float x1 = GetPosition().x - GetScaledSize().x / 2;
    float y1 = GetPosition().y + GetScaledSize().y / 2;
    float x2 = target->GetTransform().translation.x - target->GetScaledSize().x / 2;
    float y2 = target->GetTransform().translation.y + target->GetScaledSize().y / 2;

    bool x_overlap =
            ((x1 > x2) && (x1 < x2 + target->GetScaledSize().x)) || ((x2 > x1) && (x2 < x1 + GetScaledSize().x));

    bool y_overlap =
            ((y1 > y2 - target->GetScaledSize().y) && (y1 < y2)) || ((y2 > y1 - GetScaledSize().y) && (y2 < y1));

    return x_overlap && y_overlap;
}