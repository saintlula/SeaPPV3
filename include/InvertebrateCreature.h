//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef INVERTEBRATECREATURE_H
#define INVERTEBRATECREATURE_H

#include "SeaCreature.h"

class InvertebrateCreature : public SeaCreature
{
private:
  std::string name;
  double size;
  bool eggs;
public:
  InvertebrateCreature(const std::string& name, double size, bool eggs);

  std::string getName() const override;
  double getSize() const override;
  bool hasEggs() const override;
  std::string getType() const override;
  nlohmann::json toJson() const override;
  std::string getClassType() const override;
};


#endif //INVERTEBRATECREATURE_H
