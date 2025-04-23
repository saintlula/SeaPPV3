//
// Created by Ehlinaz Duru Yildirim on 15/4/2025.
//

#include "UnknownCreature.h"

UnknownCreature::UnknownCreature(const std::string& name, double size, bool eggs)
        : name(name), size(size), eggs(eggs) {}

std::string UnknownCreature::getName() const
{
    return name;
}

double UnknownCreature::getSize() const
{
    return size;
}

bool UnknownCreature::hasEggs() const
{
    return eggs;
}

std::string UnknownCreature::getType() const
{
    return "Unknown";
}

nlohmann::json UnknownCreature::toJson() const
{
    return
 {
            {"name", name},
            {"size", size},
            {"eggs", eggs},
            {"type", "Unknown"},
            {"class", "Unknown"}
    };
}

std::string UnknownCreature::getClassType() const
{
    return "Unknown";
}