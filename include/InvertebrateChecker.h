//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef INVERTEBRATECHECKER_H
#define INVERTEBRATECHECKER_H

#include "SeaChecker.h"

class InvertebrateChecker : public SeaChecker
{
public:
  bool check(const SeaCreature* creature) const override;
};

#endif //INVERTEBRATECHECKER_H
