//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef VERTEBRATECHECKER_H
#define VERTEBRATECHECKER_H

#include "SeaChecker.h"

class VertebrateChecker : public SeaChecker
{
public:
  bool check(const SeaCreature* creature) const override;
};

#endif //VERTEBRATECHECKER_H
