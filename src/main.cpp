#include <Geode/Geode.hpp>
#include <Geode/ui/OverlayManager.hpp>

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

        log::info(
            "Test Shimeji sprite loaded successfully! Size: {}% (scale: {})",
            size,
            scale
        );

        return true;
    }
};

$on_mod(Loaded) {
    log::info("Geode Shimeji Test loaded!");

    auto layer = ShimejiLayer::create();

    if (!layer) {
        log::error("Failed to create ShimejiLayer!");
        return;
    }

    OverlayManager::get()->addChild(layer, 9999);

    log::info("Shimeji added to OverlayManager!");
}
