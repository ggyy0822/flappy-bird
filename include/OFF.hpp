//
// Created by 林竣堂 on 2024/6/6.
//

#ifndef FLAPPY_BIRD_OFF_HPP
#define FLAPPY_BIRD_OFF_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class OFF :public Util::GameObject{
public:
    OFF();

    void SetPosition(const glm::vec2 &Position);

private:
};
#endif //FLAPPY_BIRD_OFF_HPP
