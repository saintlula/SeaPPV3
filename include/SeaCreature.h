//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef SEACREATURE_H
#define SEACREATURE_H

#include <string>
#include <nlohmann/json.hpp>

class SeaCreature
{
public:
  virtual ~SeaCreature() = default;

  virtual nlohmann::json toJson() const = 0;
  virtual std::string getClassType() const = 0;  // used to distinguish derived classes
  virtual std::string getName() const = 0;
  virtual double getSize() const = 0;
  virtual bool hasEggs() const = 0;
  virtual std::string getType() const = 0;
};

#endif //SEACREATURE_H
