//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#include "InvertebrateCreature.h"

InvertebrateCreature::InvertebrateCreature(const std::string& name, double size, bool eggs)
    : name(name), size(size), eggs(eggs) {}

std::string InvertebrateCreature::getName() const
{
  return name;
}

double InvertebrateCreature::getSize() const
{
    return size;
}

bool InvertebrateCreature::hasEggs() const
{
  return eggs;
}

std::string InvertebrateCreature::getType() const
{
  return "Invertebrate";
}

nlohmann::json InvertebrateCreature::toJson() const
{
    return
    {
            {"name", name},
            {"size", size},
            {"eggs", eggs},
            {"type", getType()},
            {"class", "Invertebrate"}
    };
}

std::string InvertebrateCreature::getClassType() const
{
    return "Invertebrate";
}
