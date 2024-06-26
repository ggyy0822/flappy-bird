#ifndef FLAPPY_BIRD_TEXT_HPP
#define FLAPPY_BIRD_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class Text : public Util::GameObject {
private:
    std::string m_Text;
public:
    Text();

    std::string &GetText();

    void SetText(const std::string &str);

    void SetPosition(const glm::vec2 &Position);

    [[nodiscard]] const glm::vec2 &GetPosition() const;
};


#endif //FLAPPY_BIRD_TEXT_HPP
