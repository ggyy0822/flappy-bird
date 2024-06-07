//
// Created by 林竣堂 on 2024/3/29.
//

#ifndef FLAPPY_BIRD_BIRD_HPP
#define FLAPPY_BIRD_BIRD_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Bird : public Util::GameObject {
public:
    Bird();

    void SetPosition(const glm::vec2 &Position);

    const glm::vec2 &GetPosition() const;

    bool isOverlap(const std::shared_ptr<Util::GameObject> &target);

private:
};

#endif //FLAPPY_BIRD_BIRD_HPP
