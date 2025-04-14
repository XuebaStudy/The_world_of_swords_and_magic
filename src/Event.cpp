
#include <iostream>

#include "Summoner.h"
#include "Tools.h"

using namespace std;

void battle(Summoner& A, Summoner& B) {
    Summoner C(A),D(B);
    cout << "Battle between " << C.name << " and " << D.name << " !!!" << endl;
    cout << "两个召唤师的队伍如下:" << endl;
    C.show_info();  // 显示 C 的队伍信息
    D.show_info();  // 显示 D 的队伍信息

    for (int R = 1; R < 100; R++) {
        system("pause");

        cout << endl << "---------------------------";
        cout << "Round " << R << ": " ;

        if(R%2){
            cout << "(" << C.name << "'s Round)" << endl;
            C.attack_to(D);

        }else{
            cout << "(" << D.name << "'s Round)" << endl;
            D.attack_to(C);

        }
        if (C.Non_live()) {
            cout << endl << "Summoner " << C.name << " has been defeated!" << endl << endl;
            break;}
        if (D.Non_live()) {
            cout << endl << "Summoner " << D.name << " has been defeated!" << endl << endl;
            break;}
        
        C.show_info();  // 显示 C 的队伍信息
        D.show_info();  // 显示 D 的队伍信息
    }
    cout << "结果如下" << endl;
    C.show_info();  // 显示 C 的队伍信息
    D.show_info();  // 显示 D 的队伍信息
    system("pause");
}