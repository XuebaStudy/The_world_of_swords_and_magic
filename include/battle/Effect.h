#ifndef EFFECT_H
#define EFFECT_H

#include "Creature.h"
#include "EffectType.h"

class SkillEffect {
public:
    std::string name;          // 技能效果的名称
    int duration;              // 持续时间（回合数）
    EffectType type;

    SkillEffect(const std::string& name, int duration, EffectType type);

    virtual ~SkillEffect() = default;

    virtual void applyEffect(Creature& creature) = 0;  // 应用效果
    virtual void removeEffect(Creature& creature) = 0; // 移除效果

    void deDuration(int num=1);
    bool isExpired() const;
};

class FixedEffect : public SkillEffect {
public:
    int HP_bonus;
    int ATK_bonus;
    int DEF_bonus;

    FixedEffect(const std::string& name, int duration, EffectType type,
            int HP_bonus = 0, int ATK_bonus = 0, int DEF_bonus = 0 );

    void applyEffect(Creature& creature) override;
    void removeEffect(Creature& creature) override;
};




#endif