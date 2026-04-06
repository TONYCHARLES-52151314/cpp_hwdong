#include <iostream>

int main() {
    int n = 0;      // 学生人数
    int cols = 4;   // 每个学生的成绩个数

    std::cout << "输入学生人数：\n";
    std::cin >> n;

    // 使用 nothrow 版本
    double* scores = new (std::nothrow) double[n * cols];
    if (scores == nullptr) {
        std::cerr << "内存分配失败！" << std::endl;
        return 1;
    }

    std::cout << "输入学生的平时、实验、期末、总评成绩：\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> scores[i * cols + 0] >> scores[i * cols + 1]
            >> scores[i * cols + 2] >> scores[i * cols + 3];
    }

    std::cout << "学生成绩：\n";
    for (int i = 0; i < n; ++i) {
        std::cout << scores[i * cols + 0] << '\t' << scores[i * cols + 1] << '\t'
            << scores[i * cols + 2] << '\t' << scores[i * cols + 3] << '\n';
    }

    delete[] scores;
    return 0;
}