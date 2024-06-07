//
// Created by 林竣堂 on 2024/3/18.
//

#ifndef FLAPPY_BIRD_BASE_HPP
#define FLAPPY_BIRD_BASE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Base : public Util::GameObject {
public:
    Base();

    void SetPosition(const glm::vec2 &Position);

private:

};

#endif //FLAPPY_BIRD_BASE_HPP
