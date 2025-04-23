//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#include "InvertebrateChecker.h"

bool InvertebrateChecker::check(const SeaCreature* creature) const
{
  return creature->getType() == "Invertebrate";
}