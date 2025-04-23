//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#include "VertebrateChecker.h"

bool VertebrateChecker::check(const SeaCreature* creature) const
{
  return creature->getType() == "Vertebrate";
}