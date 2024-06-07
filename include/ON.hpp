//
// Created by 林竣堂 on 2024/6/6.
//

#ifndef FLAPPY_BIRD_ON_HPP
#define FLAPPY_BIRD_ON_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class ON :public Util::GameObject{
public:
    ON();

    void SetPosition(const glm::vec2 &Position);

private:
};

#endif //FLAPPY_BIRD_ON_HPP
