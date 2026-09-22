#pragma once

#include <Geode/Geode.hpp>

#include <filesystem>
#include <string>
#include <vector>

struct ShimejiDefinition {
    std::string name;

    std::filesystem::path directory;
    std::filesystem::path actionsFile;
    std::filesystem::path behaviorsFile;
};

class ShimejiManager {
public:
    static ShimejiManager& get();

    void scan();

    std::vector<ShimejiDefinition> const& getShimejis() const;

private:
    std::vector<ShimejiDefinition> m_shimejis;
};
