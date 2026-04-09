#include <iostream>

int main() {
    int n = 0; // 学生人数
    std::cout << "输入学生人数：\n";
    std::cin >> n;

    // 使用 nothrow 版本，分配失败时返回 nullptr
    auto scores = new (std::nothrow) double[n][4];
    if (scores == nullptr) {
        std::cerr << "内存分配失败！" << std::endl;
        return 1;
    }

    std::cout << "输入学生的平时、实验、期末、总评成绩：\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> scores[i][0] >> scores[i][1] >> scores[i][2] >> scores[i][3];
    }

    std::cout << "学生成绩：\n";
    for (int i = 0; i < n; ++i) {
        std::cout << scores[i][0] << '\t' << scores[i][1] << '\t'
            << scores[i][2] << '\t' << scores[i][3] << '\n';
    }

    delete[] scores;
    return 0;
}