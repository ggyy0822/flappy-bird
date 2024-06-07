//
// Created by 林竣堂 on 2024/3/8.
//

#ifndef FLAPPY_BIRD_BACKGROUNDIMAGE_HPP
#define FLAPPY_BIRD_BACKGROUNDIMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
//    BackgroundImage();
    explicit BackgroundImage(const std::string &path);
private:

};

#endif //FLAPPY_BIRD_BACKGROUNDIMAGE_HPP
