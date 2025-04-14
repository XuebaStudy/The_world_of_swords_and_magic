#include <iostream>

#include "Effect.h"

using namespace std;

    
SkillEffect::SkillEffect(const std::string& name, int duration, EffectType type)
    : name(name), duration(duration) ,type(type) {}

void SkillEffect::deDuration(int num) {
    if (duration > 0) {
        duration-= num;
    }
}

bool SkillEffect::isExpired() const {
    return duration <= 0;
}


FixedEffect::FixedEffect(const std::string& name, int duration, EffectType type,
        int HP_bonus, int ATK_bonus, int DEF_bonus)
    : SkillEffect(name, duration, type), 
        ATK_bonus(ATK_bonus), DEF_bonus(DEF_bonus), HP_bonus(HP_bonus) {}

void FixedEffect::applyEffect(Creature& c){
    cout << name << " effect -> " << c.name << endl;
    c.ATK += ATK_bonus;
    c.DEF += DEF_bonus;
    c.HP += HP_bonus;
}

void FixedEffect::removeEffect(Creature& c){
    c.ATK -= ATK_bonus;
    c.DEF -= DEF_bonus;
    c.HP -= HP_bonus;
}