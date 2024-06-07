//
// Created by 林竣堂 on 2024/3/6.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_TUBE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_TUBE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Tube : public Util::GameObject {

public:
    explicit Tube(const std::string &path);

    void SetPosition(const glm::vec2 &Position);

    const glm::vec2 &GetPosition() const;

private:

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_TUBE_HPP