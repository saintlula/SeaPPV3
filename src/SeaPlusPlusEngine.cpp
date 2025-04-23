//
// Created by Ehlinaz Duru Yildirim on 8/4/2025.
//

#include "SeaPlusPlusEngine.h"
#include "VertebrateCreature.h"
#include "InvertebrateCreature.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "VertebrateChecker.h"
#include "InvertebrateChecker.h"
#include "UnknownCreature.h"
#include "FreshwaterCreature.h"

void SeaPlusPlusEngine::run()
{
    loadBuckets();
    std::cout << "What is your name? ";
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, currentUser);

    if (userBuckets.find(currentUser) != userBuckets.end())
    {
        std::cout << "Welcome back, " << currentUser << "!\n";
    } else
    {
        std::cout << "Oh... you don not seem to have a bucket yet!\n";
        std::cout << "You are now added, " << currentUser << "! We'll remember your bucket from now on.\n";
        userBuckets[currentUser] = {};
    }

    if (!fishRules.loadRules("../rules.json"))
    {
        std::cout << "The rules did not load! Regulation might be faulty!";
    }

    bool running = true;

    while (running)
    {
        std::cout << "\n Sea++ \n";
        std::cout << "1. Add Fish to Bucket\n";
        std::cout << "2. View Bucket\n";
        std::cout << "3. Check If Your Bucket Is Legal\n";
        std::cout << "4. Take Fish Out Of Bucket\n";
        std::cout << "5. Download Bucket Information\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "Choose option: ";
        while (!(std::cin >> choice) || choice < 1 || choice > 6)
        {
            std::cout << "Invalid input! Please enter a number between 1 and 6 :) ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        switch (choice)
        {
            case 1:
                addCreature();
                break;
            case 2:
                listCreatures();
                break;
            case 3:
                checkCreatures();
                break;
            case 4:
                removeFishFromBucket();
                break;
            case 5:
                exportBucketToTxt();
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid option\n";
        }
    }

    saveBuckets();
    cleanup();
}

void SeaPlusPlusEngine::addCreature()
{
    std::string name;
    double size;
    bool eggs;

    std::cout << "Enter name ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter size in cm ";
    while (!(std::cin >> size) || size <= 0 || size > 200)
    {
        std::cout << "\nThat can't be right! Please add fish size in cms. ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    int eggInput;
    std::cout << "Did it have eggs? (1 for yes, 0 for no): ";
    while (!(std::cin >> eggInput) || (eggInput != 0 && eggInput != 1))
    {
        std::cout << "Please enter either 1 or 0: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    const FishRule* rule = fishRules.getRuleFor(name);
    if (!rule)
    {
        std::cout << name << " was not in our system! Don't worry it will be added as Unknown.\n";
        userBuckets[currentUser].push_back(new UnknownCreature(name, size, eggs));
    } else if (rule->classType == "Vertebrate")
    {
        userBuckets[currentUser].push_back(new VertebrateCreature(name, size, eggs));
    } else if (rule->classType == "Invertebrate")
    {
        userBuckets[currentUser].push_back(new InvertebrateCreature(name, size, eggs));
    } else if (rule->classType == "Freshwater")
    {
        userBuckets[currentUser].push_back(new FreshwaterCreature(name, size, eggs));
    }
}

void SeaPlusPlusEngine::listCreatures() const
{
    auto it = userBuckets.find(currentUser);
    if (it == userBuckets.end() || it->second.empty())
    {
        std::cout << "There's no creatures in your bucket yet.\n";
        return;
    }

    const auto& bucket = it->second;
    VertebrateChecker vCheck;
    InvertebrateChecker iCheck;

    std::cout << "\n Vertebrate Creatures \n";
    for (const auto& creature : bucket)
    {
        if (vCheck.check(creature))
        {
            std::cout << creature->getName()
                      << " Size: " << creature->getSize() << " cm"
                      << " Eggs: " << (creature->hasEggs() ? "Yes" : "No") << "\n";
        }
    }

    std::cout << "\n Invertebrate Creatures \n";
    for (const auto& creature : bucket)
    {
        if (iCheck.check(creature))
        {
            std::cout << creature->getName()
                      << " Size: " << creature->getSize() << " cm"
                      << " Eggs: " << (creature->hasEggs() ? "Yes" : "No") << "\n";
        }
    }

    std::cout << "\n Unknown Creatures \n";
    for (const auto& creature : bucket)
    {
        if (creature->getType() == "Unknown")
        {
            std::cout << creature->getName()
                      << " Size: " << creature->getSize() << " cm"
                      << " Eggs: " << (creature->hasEggs() ? "Yes" : "No") << "\n";
        }
    }

    std::cout << "\n Freshwater Creatures \n";
    for (const auto& creature : bucket)
    {
        if (creature->getType() == "Freshwater")
        {
            std::cout << creature->getName()
                      << " Size: " << creature->getSize() << " cm"
                      << " Eggs: " << (creature->hasEggs() ? "Yes" : "No") << "\n";
        }
    }

}

void SeaPlusPlusEngine::checkCreatures() const
{
    auto it = userBuckets.find(currentUser);
    if (it == userBuckets.end() || it->second.empty())
    {
        std::cout << "Your bucket is empty!\n";
        return;
    }

    const auto& bucket = it->second;
    std::unordered_map<std::string, std::vector<const SeaCreature*>> grouped;

    for (const auto& creature : bucket)
    {
        grouped[creature->getName()].push_back(creature);
    }

    std::map<std::string, int> illegalCountMap;
    std::map<std::string, int> excessCountMap;
    std::vector<std::string> missingRules;

    for (const auto& [name, group] : grouped)
    {
        const FishRule* rule = fishRules.getRuleFor(name);

        if (!rule)
        {
            missingRules.push_back(name);
            continue;
        }

        std::vector<const SeaCreature*> legalFish;

        for (const auto& fish : group)
        {
            bool legal = true;

            if (fish->getSize() < rule->minSize)
            {
                legal = false;
            }

            if (rule->noKeepIfEggs && fish->hasEggs())
            {
                legal = false;
            }

            if (legal) legalFish.push_back(fish);
            else illegalCountMap[name]++;
        }

        if ((int)legalFish.size() > rule->bagLimit)
        {
            int throwBack = (int)legalFish.size() - rule->bagLimit;
            excessCountMap[name] = throwBack;
        }
    }

    std::cout << "\n Regulation Check \n";

    if (!illegalCountMap.empty() || !excessCountMap.empty())
    {
        std::cout << "You can take your bucket home only if you throw back:\n";

        for (const auto& [name, count] : illegalCountMap)
        {
            std::cout << "- " << count << " illegal " << name << "(s) (either too small or with eggs)\n";
        }

        for (const auto& [name, count] : excessCountMap)
        {
            std::cout << "- " << count << " extra " << name << "(s) (you're over the bag limit)\n";
        }
    }
    else if (!missingRules.empty())
    {
        std::cout << "Your bucket is safe! BUT we couldn't find rules for:\n";
        for (const auto& name : missingRules)
        {
            std::cout << "- " << name << "\n";
        }
        std::cout << "Try not to get caught to the fish police!\n";
    }
    else
    {
        std::cout << "Your bucket is safe to take home!\n";
    }
}

void SeaPlusPlusEngine::removeFishFromBucket()
{
    auto& bucket = userBuckets[currentUser];
    if (bucket.empty())
    {
        std::cout << "Your bucket is empty.\n";
        return;
    }

    std::cout << "\n🎣 Your Fish Bucket 🎣\n";
    for (size_t i = 0; i < bucket.size(); ++i)
    {
        const auto* c = bucket[i];
        std::cout << i + 1 << ". " << c->getName()
                  << " - " << c->getType()
                  << " Size: " << c->getSize()
                  << " cm - Eggs: " << (c->hasEggs() ? "Yes" : "No") << "\n";
    }

    int index;
    std::cout << "Which fish would you like to delete? (Enter number): ";

    while (!(std::cin >> index) || index < 1 || index > static_cast<int>(bucket.size())) {
        std::cout << "Invalid input! Please enter a number between 1 and " << bucket.size() << ". ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    delete bucket[index - 1];
    bucket.erase(bucket.begin() + (index - 1));
    std::cout << "Fish removed from your bucket.\n";
}

void SeaPlusPlusEngine::exportBucketToTxt() const
{
    auto it = userBuckets.find(currentUser);
    if (it == userBuckets.end() || it->second.empty())
    {
        std::cout << "But there's no fish in your bucket to export! Add some first!\n";
        return;
    }

    std::ofstream out("SecretBucket.txt");
    if (!out.is_open())
    {
        std::cout << "Uh oh! Could not create export file.\n";
        return;
    }

    out << "Bucket for 🎣" << currentUser << "🎣\n";
    for (const auto* c : it->second)
    {
        out << c->getName() << " - " << c->getType()
            << " Size: " << c->getSize() << " cm"
            << " Eggs: " << (c->hasEggs() ? "Yes" : "No") << "\n";
    }

    out.close();
    std::cout << "Your bucket was exported to 'SecretBucket.txt'\n";
}

void SeaPlusPlusEngine::cleanup()
{
    for (auto& [user, bucket] : userBuckets)
    {
        for (auto* c : bucket)
        {
            delete c;
        }
        bucket.clear();
    }
}

void SeaPlusPlusEngine::saveBuckets() const
{
    json j;

    for (const auto& [user, bucket] : userBuckets)
    {
        for (const auto* creature : bucket)
        {
            j[user].push_back(creature->toJson());
        }
    }

    std::ofstream out("buckets.json");
    if (out.is_open())
    {
        out << j.dump(4);
        out.close();
    }
}

void SeaPlusPlusEngine::loadBuckets()
{
    std::ifstream in("buckets.json");
    if (!in.is_open()) return;

    json j;
    in >> j;
    in.close();

    for (auto& [user, list] : j.items())
    {
        for (auto& item : list)
        {
            std::string classType = item["class"];
            std::string name = item["name"];
            double size = item["size"];
            bool eggs = item["eggs"];

            if (classType == "Vertebrate")
            {
                userBuckets[user].push_back(new VertebrateCreature(name, size, eggs));
            } else if (classType == "Invertebrate")
            {
                userBuckets[user].push_back(new InvertebrateCreature(name, size, eggs));
            } else if (classType == "Freshwater")
            {
                userBuckets[user].push_back(new FreshwaterCreature(name, size, eggs));
            } else if (classType == "Unknown")
            {
                userBuckets[user].push_back(new UnknownCreature(name, size, eggs));
            } else
            {
                std::cout << "Warning! Unknown class type '" << classType << "' while loading bucket. Skipped.\n";
            }
        }
    }
}

SeaPlusPlusEngine::~SeaPlusPlusEngine()
{
    cleanup();
}