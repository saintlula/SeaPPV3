//
// Created by Ehlinaz Duru Yildirim on 14/4/2025.
//

#ifndef FISHRULES_H
#define FISHRULES_H

#include <string>
#include <unordered_map>

struct FishRule
{
  double minSize;
  int bagLimit;
  bool noKeepIfEggs;
  std::string classType;
};

class FishRules
{
  private:
    std::unordered_map<std::string, FishRule> rules;

  public:
    bool loadRules(const std::string& filePath);
    const FishRule* getRuleFor(const std::string& species) const;
};

inline std::string normalize(const std::string& str) {
  std::string result;
  // Trim and convert to lowercase
  size_t start = str.find_first_not_of(" \t");
  size_t end = str.find_last_not_of(" \t");

  if (start == std::string::npos || end == std::string::npos) {
    return "";
  }

  result = str.substr(start, end - start + 1);
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

#endif //FISHRULES_H
