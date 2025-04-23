//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef VERTEBRATECREATURE_H
#define VERTEBRATECREATURE_H

#include "SeaCreature.h"

class VertebrateCreature : public SeaCreature
{
private:
  std::string name;
  double size;
  bool eggs;

public:
  VertebrateCreature(const std::string& name, double size, bool eggs);
  std::string getName() const override;
  double getSize() const override;
  bool hasEggs() const override;
  std::string getType() const override;
  nlohmann::json toJson() const override;
  std::string getClassType() const override;
};

#endif //VERTEBRATECREATURE_H
