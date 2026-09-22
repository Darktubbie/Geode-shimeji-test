#pragma once

#include <Geode/Geode.hpp>

#include <string>
#include <vector>

struct ShimejiDefinition {
    std::string name;
    std::string directory;
    std::string actionsFile;
    std::string behaviorsFile;
};

class ShimejiManager {
public:
    static ShimejiManager& get();

    void scan();

    std::vector<ShimejiDefinition> const& getShimejis() const;

private:
    std::vector<ShimejiDefinition> m_shimejis;
};
