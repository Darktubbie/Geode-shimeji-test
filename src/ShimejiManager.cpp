#include "ShimejiManager.hpp"

using namespace geode::prelude;

ShimejiManager& ShimejiManager::get() {
    static ShimejiManager instance;
    return instance;
}

void ShimejiManager::scan() {
    m_shimejis.clear();

    auto base = dirs::getModConfigDir() / "shimejis";

    log::info(
        "[Shimeji] Scanning custom Shimejis: {}",
        base.string()
    );

    if (!std::filesystem::exists(base)) {
        log::info(
            "[Shimeji] Shimejis directory does not exist. Creating it..."
        );

        std::error_code error;
        std::filesystem::create_directories(base, error);

        if (error) {
            log::error(
                "[Shimeji] Failed to create shimejis directory: {}",
                error.message()
            );
        }

        return;
    }

    std::error_code error;

    for (auto const& entry :
         std::filesystem::directory_iterator(base, error)) {

        if (error) {
            log::error(
                "[Shimeji] Failed to enumerate directory: {}",
                error.message()
            );
            break;
        }

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

        ShimejiDefinition definition;
        definition.name = name;
        definition.directory = directory;
        definition.actionsFile = actions;
        definition.behaviorsFile = behaviors;

        m_shimejis.push_back(std::move(definition));

        log::info(
            "[Shimeji] Found custom Shimeji: {}",
            name
        );
    }

    log::info(
        "[Shimeji] Custom Shimeji scan complete: {} found",
        m_shimejis.size()
    );
}

std::vector<ShimejiDefinition> const&
ShimejiManager::getShimejis() const {
    return m_shimejis;
}
