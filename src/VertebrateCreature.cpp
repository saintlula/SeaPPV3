#include "VertebrateCreature.h"
#include <nlohmann/json.hpp>

VertebrateCreature::VertebrateCreature(const std::string& name, double size, bool eggs)
    : name(name), size(size), eggs(eggs) {}

std::string VertebrateCreature::getName() const
{
    return name;
}

double VertebrateCreature::getSize() const
{
    return size;
}

bool VertebrateCreature::hasEggs() const
{
    return eggs;
}

std::string VertebrateCreature::getType() const
{

return "Vertebrate";
}
nlohmann::json VertebrateCreature::toJson() const
{
    return
 {
            {"name", name},
            {"size", size},
            {"eggs", eggs},
            {"type", getType()},
            {"class", "Vertebrate"}
    };
}

std::string VertebrateCreature::getClassType() const
{
    return "Vertebrate";
}