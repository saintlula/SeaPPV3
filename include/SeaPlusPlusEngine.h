//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#ifndef SEAPLUSPLUSENGINE_H
#define SEAPLUSPLUSENGINE_H

#include <vector>
#include "SeaCreature.h"
#include "FishRules.h"
#include <unordered_map>

class SeaPlusPlusEngine
{
private:
  std::unordered_map<std::string, std::vector<SeaCreature*>> userBuckets;
  std::string currentUser;

  FishRules fishRules;
  void saveBuckets() const;
  void loadBuckets();
  void addCreature();
  void cleanup();

public:
  ~SeaPlusPlusEngine();
  void run();
  void listCreatures() const;
  void checkCreatures() const;
  void removeFishFromBucket();
  void exportBucketToTxt() const;
};

#endif //SEAPLUSPLUSENGINE_H
