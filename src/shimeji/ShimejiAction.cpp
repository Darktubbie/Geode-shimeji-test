#include "ShimejiAction.hpp"

#include <Geode/cocos/robtop/xml/pugixml.hpp>

using namespace geode::prelude;

namespace {

CCPoint parsePoint(std::string const& value) {
    auto comma = value.find(',');

    if (comma == std::string::npos) {
        return {0.f, 0.f};
    }

    try {
        float x = std::stof(value.substr(0, comma));
        float y = std::stof(value.substr(comma + 1));

        return {x, y};
    }
    catch (...) {
        return {0.f, 0.f};
    }
}

}

std::vector<ShimejiAction> loadActions(std::string const& path) {
    std::vector<ShimejiAction> actions;

    pugi::xml_document document;

    auto result = document.load_file(path.c_str());

    if (!result) {
        log::error(
            "Failed to load actions.xml: {}",
            result.description()
        );

        return actions;
    }

    auto actionList = document.child("Mascot").child("ActionList");

    if (!actionList) {
        log::error("actions.xml does not contain ActionList");
        return actions;
    }

    for (auto actionNode : actionList.children("Action")) {
        ShimejiAction action;

        action.name = actionNode.attribute("Name").as_string();
        action.type = actionNode.attribute("Type").as_string();
        action.borderType = actionNode.attribute("BorderType").as_string();

        auto animationNode = actionNode.child("Animation");

        if (animationNode) {
            for (auto poseNode : animationNode.children("Pose")) {
                ShimejiPose pose;

                pose.image =
                    poseNode.attribute("Image").as_string();

                pose.imageAnchor =
                    parsePoint(
                        poseNode.attribute("ImageAnchor").as_string()
                    );

                pose.velocity =
                    parsePoint(
                        poseNode.attribute("Velocity").as_string()
                    );

                pose.duration =
                    poseNode.attribute("Duration").as_float(0.f);

                action.animation.poses.push_back(pose);
            }
        }

        actions.push_back(action);
    }

    log::info(
        "Loaded {} Shimeji actions from {}",
        actions.size(),
        path
    );

    return actions;
}
