//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef SEACHECKER_H
#define SEACHECKER_H

#include "SeaCreature.h"

class SeaChecker
{
public:
  virtual ~SeaChecker() = default;
  virtual bool check(const SeaCreature* creature) const = 0;
};

#endif //SEACHECKER_H
