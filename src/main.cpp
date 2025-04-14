#include "AllHeaders.h"
#include "SFMLUI.h"
#include <cstdlib>
#include <thread>  // for std::thread
#include <mutex>   // for std::mutex

using namespace std;

// 互斥锁，用于保护共享资源
std::mutex uiMutex;

void startMenu() {
    lock_guard<std::mutex> lock(uiMutex);  // 确保线程安全
    cout << "欢迎来到剑与魔法的世界！" << endl << endl;
    string user_name;
    user_name = inputName("冒险者", "你的名字");
    cout << "你好，" << user_name << "！" << endl;

    Menu(user_name);  // 假设 Menu 是一个阻塞函数
}

int UIW = 2000;
int UIH = 1236;

int main() {
    system("chcp 65001");
    system("cls");

    SFMLUI ui("Game UI", UIW, UIH);
    ui.addText("Welcome to the world of swords and magic!", UIW * 0.5, UIH * 0.1, UIW * 0.08);
    ui.addBackgroundImage("../assets/images/outskirts.png");

    ui.addButton("Play Sound", UIW * 0.3, UIH * 0.9, UIH * 0.1, [&ui] {
        cout << "Playing Menu sound..." << endl;
        if (!ui.sounds.empty()) {
            ui.sounds[0].play();
        }
    });

    ui.addSound("../assets/sounds/Time Flows Ever Onward - Evan Call.wav", []{
        cout << "Playing Menu sound..." << endl;
    });

    ui.addButton("Stop Sound", UIW * 0.7, UIH * 0.9, UIH * 0.1, [&ui] {
        cout << "Stopping Menu sound..." << endl;
        if (!ui.sounds.empty()) {
            ui.sounds[0].stop();
        }
    });
    ui.addButton("Start Menu", UIW * 0.5, UIH * 0.6, UIH * 0.1, [&ui] {
        // 使用线程运行 startMenu
        thread menuThread(startMenu);
        menuThread.detach();  // 分离线程，让它独立运行
    });


    ui.run();

    return 0;
}