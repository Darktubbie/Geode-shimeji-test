#include <Geode/Geode.hpp>
#include <Geode/ui/OverlayManager.hpp>
#include "shimeji/ShimejiAction.hpp"

using namespace geode::prelude;

class ShimejiLayer : public CCLayer {
public:
    static ShimejiLayer* create() {
        auto ret = new ShimejiLayer();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    bool init() {
        if (!CCLayer::init()) {
            return false;
        }

        auto sprite = CCSprite::create("test.png"_spr);

        if (!sprite) {
            log::error("Failed to load test.png");
            return true;
        }

        auto size = Mod::get()->getSettingValue<int64_t>("shimeji-size");
        float scale = static_cast<float>(size) / 100.0f;

        sprite->setScale(scale);
        sprite->setPosition({100.f, 100.f});

        this->addChild(sprite);

        m_sprite = sprite;
        m_speed = 80.f;
        m_direction = 1.f;

        this->scheduleUpdate();

        log::info(
            "Test Shimeji sprite loaded successfully! Size: {}% (scale: {})",
            size,
            scale
        );

        return true;
    }

    void update(float dt) override {
        if (!m_sprite) {
            return;
        }

        auto position = m_sprite->getPosition();

        position.x += m_speed * m_direction * dt;

        auto screenSize = CCDirector::sharedDirector()->getWinSize();

        float halfWidth = m_sprite->getContentSize().width *
            m_sprite->getScaleX() / 2.0f;

        if (position.x + halfWidth >= screenSize.width) {
            position.x = screenSize.width - halfWidth;
            m_direction = -1.f;
        }
        else if (position.x - halfWidth <= 0.f) {
            position.x = halfWidth;
            m_direction = 1.f;
        }

        m_sprite->setPosition(position);
    }

private:
    CCSprite* m_sprite = nullptr;

    float m_speed = 80.f;
    float m_direction = 1.f;
};

$on_mod(Loaded) {
    log::info("Geode Shimeji Test loaded!");

    auto actions = loadActions(
    Mod::get()->getResourcesDir() /
    "shimeji/Natsuki/conf/actions.xml"
);

for (auto const& action : actions) {
    log::info(
        "Action: {} | Type: {} | Poses: {}",
        action.name,
        action.type,
        action.animation.poses.size()
    );
}

    auto layer = ShimejiLayer::create();

    if (!layer) {
        log::error("Failed to create ShimejiLayer!");
        return;
    }

    OverlayManager::get()->addChild(layer, 9999);

    log::info("Shimeji added to OverlayManager!");
}
