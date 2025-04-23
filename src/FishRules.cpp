//
// Created by Ehlinaz Duru Yildirim on 14/4/2025.
//

#include "FishRules.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool FishRules::loadRules(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in)
    {
        std::cerr << "Failed to open rules file: " << filePath << "\n";
        return false;
    }

    json j;
    in >> j;

    for (auto& [key, value] : j.items())
    {
        FishRule rule;
        rule.minSize = value["minSize"];
        rule.bagLimit = value["bagLimit"];
        rule.noKeepIfEggs = value["noKeepIfEggs"];
        rule.classType = value["class"];
        std::string name = normalize(key);
        rules[name] = rule;
    }

    return true;
}

const FishRule* FishRules::getRuleFor(const std::string& species) const
{
    std::string norm = normalize(species);
    auto it = rules.find(norm);
    if (it != rules.end())
    {
        return &it->second;
    }
    return nullptr;
}