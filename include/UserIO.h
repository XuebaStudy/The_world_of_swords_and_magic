#ifndef USERIO_H
#define USERIO_H

#include "battle/Creature.h"

// 输入职业类型
std::string inputJob(const std::string& defaultJob);

//输入一个符合要求的整数
int inputInt(int min, int max, int defaultValue, const std::string& thing);

// 输入姓名
std::string inputName(const std::string& defaultName, const std::string& thing);

Cteam inputTeam(int n);

#endif