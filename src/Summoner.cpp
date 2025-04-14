#include "Summoner.h"
#include <iostream>

using namespace std;

Summoner::Summoner(const string &name)
    : name(name) {}

Summoner::Summoner(const vector<shared_ptr<Creature>>& team, const std::string& name)
    : team(team), name(name) {}

// 深度拷贝，Cteam 指向新的内存
Summoner::Summoner(const Summoner& summoner)
    : name(summoner.name) {
    for (const auto& c : summoner.team) {
        if (c) {
            team.push_back(c->clone());
        }
    }
}

void Summoner::show_info() {
    cout << "Summoner: " << name << endl;
    int i = 1;
    for (auto& creature : team) {
        cout << i << ". ";
        creature->show_info();
        i++;
    }
    cout << endl;
}

bool Summoner::Non_live() {
    for (auto& creature : team) {
        if(creature->HP>0)
            return false;
    }
    return true;
}

// 召唤生物
void Summoner::summon(shared_ptr<Creature> c) {
    team.push_back(c);
}

void Summoner::summon(vector<shared_ptr<Creature>>& C) {
    for (auto& creature : C) {
        team.push_back(creature);
    }
}

// 攻击另一个召唤师
void Summoner::attack_to(Summoner& target) {
    for (auto& attacker : this->team) {
        if(attacker->HP<=0)
            continue;
        attacker->round(*this, target);
    }
}