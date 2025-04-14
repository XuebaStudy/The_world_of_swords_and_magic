#include "AllHeaders.h"

using namespace std;

void Menu(const string& user_name){
    do{
        cout << endl << "请选择模式：" << endl;
        cout << "1. 自定义战斗   ";
        cout << "2. 战斗示例   " ;
        cout << "Else or 0. 退出世界" << endl << endl;
        int mode;
        mode = inputInt(0, 2, 0, "模式");

        switch(mode){
            case 1:
                cout << endl;
                SimulateBattle();
                continue;
            case 2:
                cout << endl;
                ExampleBattle();
                continue;
            case 0:
                cout << endl << "欢迎下次再来！" << endl;
                return ;
        }
    }while(true);
}

void SimulateBattle(){
    cout << "欢迎来到自定义战斗！" << endl << endl;
    int n;
    string nInput;
    Summoner A("A");
    cout << "请输入A的队伍：" << endl;
    cout << "输入A的队伍人数：" << endl;
    n = inputInt(1, 5, 3, "队伍人数");
    Cteam Ateam = inputTeam(n);
    A.summon(Ateam);
    A.show_info();

    Summoner B("B");
    cout << "请输入B的队伍：" << endl;
    cout << "输入B的队伍人数：" << endl;
    n = inputInt(1, 5, 3, "队伍人数");
    Cteam Bteam = inputTeam(n);
    B.summon(Bteam);
    B.show_info();
    system("pause");

    cout << "3 秒后开始战斗" << endl << endl;
    sleep(1);
    cout << "3" << endl << endl;
    sleep(1);
    cout << "2" << endl << endl;
    sleep(1);
    cout << "1" << endl << endl;
    sleep(1);

    battle(A,B);

    cout << endl << "感谢您的试玩 !!!" << endl << endl;

    system("pause");
}

void ExampleBattle(){
    cout << "欢迎来到战斗示例！" << endl << endl;

    Summoner A("A");
    Summoner B("B");

    auto w0 = make_shared<Warrior>(15, "Warrior_0");
    auto w1 = make_shared<Warrior>(15, "Warrior_1");
    auto w2 = make_shared<Warrior>(10, "Warrior_2");
    Cteam team = {w0,w1,w2};
    A.summon(team);

    auto m0 = make_shared<Mage>(15, "Mage_0");
    auto m1 = make_shared<Mage>(15, "Mage_1");
    auto w3 = make_shared<Warrior>(10, "Warrior_3");
    team = {m0,m1,w3};
    B.summon(team);

    battle(A,B);
    cout << endl << "感谢您的试玩 !!!" << endl << endl;
    system("pause");
}