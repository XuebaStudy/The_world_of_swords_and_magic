
#include <iostream>
#include <iomanip>

#include "Creature.h"
#include "Summoner.h"
#include "Tools.h"
#include "Effect.h"

using namespace std;

Creature::Creature(int HP, int ATK, const std::string& name, int DEF )
    : HP(HP), ATK(ATK), DEF(DEF), name(name) {}

Creature::Creature(const Creature& c)
    : HP(c.HP), ATK(c.ATK), DEF(c.DEF),  name(c.name) {}

shared_ptr<Creature> Creature:: clone() const {
    return make_shared<Creature>(*this);
}

void Creature::show_info() {
    cout << left << setw(12) << name;
    cout << "HP:" << setw(5) << ((HP > 0) ? HP : 0);
    cout << "ATK:" << setw(5) << ATK; 
    if (DEF) {
        cout << "DEF:" << setw(5) << DEF;
    }
    cout << endl;
}

void Creature::show_HP() {
    cout << this->name << "  ";
    if (this->HP <= 0)
        cout << "HP:0" << endl;
        return ;
    cout << "HP:(" << this->HP << ") " << std::string(this->HP/10 +1, 'x') << endl;
}

bool Creature::have_died() {
    if (this->HP <= 0) {
        cout << this->name << " has died." << endl;
        return true;
    } else {
        return false;
    }
}

void Creature::round(Summoner& master,Summoner& opponent){
    updateEffects();
    action(master,opponent);
    cout << endl;
}
void Creature::action(Summoner& master,Summoner& opponent) {
    attack_to(opponent.team);
}

void Creature::attack_to(Cteam& team) {
    for(auto& c: team){
        if(c->HP <= 0)
            continue;
        else{
            if (this->ATK > c->DEF) {
                cout << this->name << " :: Attack" << endl;
                cout << c->name << " -" << this->ATK - c->DEF << "HP" ;
                c->HP -= this->ATK - c->DEF;
            }
            if (c->ATK > this->DEF) {
                cout << " (self -" << c->ATK - this->DEF << "HP)" ;
                this->HP -= c->ATK - this->DEF;
            }
            cout << endl;
            break;
        }
    }
}

void Creature::addEffect(const shared_ptr<SkillEffect>& effect) {
    effects.push_back(effect);
    effect->applyEffect(*this);  // 立即应用效果
}

// 更新技能效果（每个回合调用）
void Creature::updateEffects() {
    for (auto it = effects.begin(); it != effects.end();) {
        it->get()->deDuration();
        if (it->get()->isExpired()) {
            it->get()->removeEffect(*this);
            it = effects.erase(it);
        } else {
            // 根据效果类型执行额外逻辑
            if (it->get()->type == EffectType::Normal) {
                it->get()->applyEffect(*this);
            }
            ++it;
        }
    }
}

// 清除所有效果
void Creature::clearEffects() {
    for (auto& effect : effects) {
        effect->removeEffect(*this);  // 移除每个效果
    }
    effects.clear();  // 清空效果列表
}





Warrior::Warrior(int level, const std::string& name)
    : Creature
    (Warrior_level_HAD(level)[0],
    Warrior_level_HAD(level)[1], 
    name, 
    Warrior_level_HAD(level)[2] ) {}

Warrior::Warrior(int HP, int ATK, const std::string& name, int DEF)
    : Creature(HP, ATK, name, DEF) {}

Warrior::Warrior(const Warrior& w)
    : Creature(w) {}  // 调用基类的拷贝构造函数

vector<int> Warrior::Warrior_level_HAD(int level){
    vector<int> HAD(3);
    HAD[0] = 100 + 10 * level;
    HAD[1] = 10 + 5 * level;
    HAD[2] = 5 + 3 * level;
    return HAD;
}

shared_ptr<Creature> Warrior::clone() const{
    return make_shared<Warrior>(*this);
}


void Warrior::action(Summoner& master,Summoner& opponent){
    int r = rint(1,10);
    if(r<=3){
        Battle_Roar(master.team);
        attack_to(opponent.team);
    }
    else{
        attack_to(opponent.team);
    }
}
void Warrior::Battle_Roar (Cteam& Fteam){
    cout << this->name << " :: Battle Roar." << endl;
    for(auto& c: Fteam){
        if(c->HP <= 0)
            continue;
        else{
            c->addEffect(make_shared<FixedEffect>("ATK+10", 2, EffectType::Normal, 0,10,0));
        }
    }
}



Mage::Mage(int level, const std::string& name)
    : Creature
    (Mage_level_HAD(level)[0],
    Mage_level_HAD(level)[1], 
    name, 
    Mage_level_HAD(level)[2] ) {}

Mage::Mage(int HP, int ATK, const std::string& name, int DEF)
    : Creature(HP, ATK, name, DEF) {}

Mage::Mage(const Mage& m)
    : Creature(m) {}

vector<int> Mage::Mage_level_HAD(int level){
    vector<int> HAD(3);
    HAD[0] = 60 + 10 * level;
    HAD[1] = 10 + 5 * level;
    HAD[2] = 0 + 1 * level;
    return HAD;
}

shared_ptr<Creature> Mage::clone() const{
    return make_shared<Mage>(*this);
}

void Mage::action(Summoner& master,Summoner& opponent){
    int r = rint(1,10);
    if(r<=8){
        Lightning_Chain(opponent.team);
    }
    else{
        attack_to(opponent.team);
    }
}

void Mage::Lightning_Chain(Cteam& team){
    cout << this->name << " :: Lightning Chain." << endl;
    for(auto& c: team){
        if(c->HP <= 0)
            continue;
        else{
            int damage = 40 + rint(0,5);
            cout << "Lightning Chain hits " << c->name << " " << damage << "HP" << endl;
            c->HP -= damage;
        }
    }
}


shared_ptr<Creature> CList::createCreature(const string& jobType, int level, const string& name) {

    if (jobType == "Warrior") {
        if(name == "Unknown")
            return make_shared<Warrior>(level);
        else
            return make_shared<Warrior>(level, name);
    } else if (jobType == "Mage") {
        if(name == "Unknown")
            return make_shared<Mage>(level);
        else
            return make_shared<Mage>(level, name);
    }
    // 如果未找到，输出提示信息并返回默认的 Warrior 对象
    cout << "无效职业选择，已自动设置为 Warrior。" << endl;
    return make_shared<Warrior>(level, name);
}
