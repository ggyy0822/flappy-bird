//
// Created by 林竣堂 on 2024/3/8.
//
#include "BackgroundImage.hpp"

//BackgroundImage::BackgroundImage() : Util::GameObject(
//        std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/background-day.png"), 0) {
//}
BackgroundImage::BackgroundImage(const std::string &path) : Util::GameObject(std::make_unique<Util::Image>(path), 0) {
}