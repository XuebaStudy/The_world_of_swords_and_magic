
#include "Tools.h"

int rint(int n1, int n2) {
    std::random_device rd; // 随机设备，用于生成种子
    std::mt19937 gen(rd()); // 使用随机设备生成的种子随机初始化数生成器

    // 使用均匀分布生成 [n1, n2] 范围内的随机整数
    std::uniform_int_distribution<> dis(n1, n2);
    return dis(gen);
}

void sleep(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}