#ifndef SUMMONER_H
#define SUMMONER_H

#include <string>
#include <vector>
#include <memory>

#include "Creature.h"

class Summoner{
public:
    std::string name;
    std::vector<std::shared_ptr<Creature>>team;

public:
    Summoner(const std::string &name = "Unknown");
    Summoner(const std::vector<std::shared_ptr<Creature>>& team,const std::string &name = "Unknown");
    // 深度拷贝，Cteam 指向新的内存
    Summoner(const Summoner& summoner);

    void show_info();
    bool Non_live();

    void summon(std::shared_ptr<Creature> c);
    void summon(std::vector<std::shared_ptr<Creature>>& C);
    void attack_to(Summoner& target);

};


#endif