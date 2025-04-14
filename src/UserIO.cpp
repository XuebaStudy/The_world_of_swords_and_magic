#include <iostream>
#include <string>
#include <sstream>

#include "Creature.h"
#include "UserIO.h"

using namespace std;

string inputJob(const string& defaultJob) {
    string job;
    ostringstream oss;

    // 动态生成提示信息
    oss << "请输入职业(";
    for (const auto& pair : CList::jobMap) {
        oss << pair.first << ": " << pair.second << ", ";
    }
    string prompt = oss.str();
    prompt.pop_back(); // 删除最后一个逗号
    prompt.pop_back(); // 删除最后一个空格

    // 添加默认职业提示
    prompt += ")(回车默认设置为 " + defaultJob + " ):";

    cout << prompt;
    getline(cin, job);

    // 转换为小写
    for (char &c : job) c = tolower(c);

    if (job.empty()) {
        return defaultJob;
    }

    // 查找 jobType 是否在映射中
    auto it = CList::jobMap.find(job);
    if (it != CList::jobMap.end()) {
        return it->second;
    }

    // 如果输入无效，提示并返回默认职业
    cout << "无效职业选择，已自动设置为 " << defaultJob << endl;
    return defaultJob;
}

int inputInt(int min, int max, int defaultValue, const string& thing) {
    string input;
    cout << "请输入" << thing << "(" <<  min << "~" << max << ")(回车默认设置为" << defaultValue << "):";
    getline(cin, input);

    int value;
    if (input.empty()) {
        value = defaultValue;
    } else {
        stringstream ss(input);
        ss >> value;
        if (ss.fail() || !ss.eof()) {
            cout << "输入无效，已自动设置为 " << defaultValue <<  endl;
            value = defaultValue;
        }
    }
    if(value < min || value > max){
        cout << thing << "超出范围，已自动设置为 " << defaultValue <<  endl;
        value = defaultValue;
    }
    return value;
}

// 输入姓名
string inputName(const string& defaultName, const string& thing){
    string name;
    cout << "请输入" << thing << "(回车默认设置为 "<<defaultName<<" ):";
    getline(cin, name);
    return name.empty() ? defaultName : name;
}

Cteam inputTeam(int n) {
    Cteam team;
    cout << "请输入" << n << "个角色：" << endl << endl;
    for (int i = 1; i <= n; i++) {
        cout << "第 " << i << " 个角色：" << endl;

        // 输入职业、等级和姓名
        string job = inputJob("Warrior");
        int level = inputInt(1, 40, 10, "等级");
        string name = inputName("Unknown","姓名");

        // 使用工厂类创建角色
        auto character = CList::createCreature(job, level, name);
        if (character) {
            team.push_back(character);
        } else {
            cout << "创建角色失败，请检查职业类型。" << endl;
        }

        cout << endl;
    }

    return team;
}
