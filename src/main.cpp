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

        auto sprite = CCSprite::create("shimeji/test.png");

        if (!sprite) {
            log::error("Failed to load shimeji/test.png");
            return true;
        }

        sprite->setPosition({100.f, 100.f});
        this->addChild(sprite);

        log::info("Test Shimeji sprite loaded!");

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
