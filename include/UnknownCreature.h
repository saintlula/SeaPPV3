//
// Created by Ehlinaz Duru Yildirim on 15/4/2025.
//

#ifndef UNKNOWNCREATURE_H
#define UNKNOWNCREATURE_H

#include "SeaCreature.h"

class UnknownCreature : public SeaCreature
{
protected:
    std::string name;
    double size;
    bool eggs;

public:
    UnknownCreature(const std::string& name, double size, bool eggs);

    std::string getName() const override;
    double getSize() const override;
    bool hasEggs() const override;
    std::string getType() const override;
    nlohmann::json toJson() const override;
    std::string getClassType() const override;
};

#endif