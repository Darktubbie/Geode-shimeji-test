#include "ShimejiManager.hpp"

using namespace geode::prelude;

ShimejiManager& ShimejiManager::get() {
    static ShimejiManager instance;
    return instance;
}

void ShimejiManager::scan() {
    m_shimejis.clear();

    auto base = dirs::getModConfigDir() / "shimejis";

    log::info("[Shimeji] Scanning: {}", base.string());

    if (!std::filesystem::exists(base)) {
        log::info("[Shimeji] Creating shimejis directory");

        std::filesystem::create_directories(base);
        return;
    }

    for (auto const& entry : std::filesystem::directory_iterator(base)) {
        if (!entry.is_directory()) {
            continue;
        }

        auto directory = entry.path();
        auto name = directory.filename().string();

        auto conf = directory / "conf";
        auto actions = conf / "actions.xml";
        auto behaviors = conf / "behaviors.xml";

        if (!std::filesystem::exists(actions)) {
            log::warn(
                "[Shimeji] Ignoring '{}': missing conf/actions.xml",
                name
            );
            continue;
        }

        if (!std::filesystem::exists(behaviors)) {
            log::warn(
                "[Shimeji] Ignoring '{}': missing conf/behaviors.xml",
                name
            );
            continue;
        }

        ShimejiDefinition definition{
            name,
            directory.string(),
            actions.string(),
            behaviors.string()
        };

        m_shimejis.push_back(std::move(definition));

        log::info("[Shimeji] Found: {}", name);
    }

    log::info(
        "[Shimeji] Scan complete: {} Shimeji(s)",
        m_shimejis.size()
    );
}

std::vector<ShimejiDefinition> const& ShimejiManager::getShimejis() const {
    return m_shimejis;
}
