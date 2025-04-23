//
// Created by Ehlinaz Duru Yildirim on 15/4/2025.
//

#include "FreshwaterCreature.h"

FreshwaterCreature::FreshwaterCreature(const std::string& name, double size, bool eggs)
        : name(name), size(size), eggs(eggs) {}

std::string FreshwaterCreature::getName() const
{
    return name;
}

double FreshwaterCreature::getSize() const
{
    return size;
}

bool FreshwaterCreature::hasEggs() const
{
    return eggs;
}

std::string FreshwaterCreature::getType() const
{
    return "Freshwater";
}

nlohmann::json FreshwaterCreature::toJson() const
{
    return
 {
            {"name", name},
            {"size", size},
            {"eggs", eggs},
            {"type", "Freshwater"},
            {"class", "Freshwater"}
    };
}

std::string FreshwaterCreature::getClassType() const
{
    return "Freshwater";
}