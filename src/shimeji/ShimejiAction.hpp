#pragma once

#include <Geode/Geode.hpp>
#include <string>
#include <vector>

struct ShimejiPose {
    std::string image;
    cocos2d::CCPoint imageAnchor;
    cocos2d::CCPoint velocity;
    float duration = 0.f;
};

struct ShimejiAnimation {
    std::vector<ShimejiPose> poses;
};

struct ShimejiAction {
    std::string name;
    std::string type;
    std::string borderType;
    ShimejiAnimation animation;
};

std::vector<ShimejiAction> loadActions(std::string const& path);
