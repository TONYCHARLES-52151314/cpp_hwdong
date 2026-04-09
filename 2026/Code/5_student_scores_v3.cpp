#include <iostream>
using std::cout;
using std::cin;

int main() {
    int n = 0;          // 当前学生人数
    int capacity = 2;   // 当前容量
    double* scores = new double[capacity * 4];

    while (true) {
        cout << "\n===== 学生成绩管理系统 =====\n";
        cout << "1. 插入学生成绩\n";
        cout << "2. 删除学生成绩\n";
        cout << "3. 修改学生成绩\n";
        cout << "4. 查询指定学生成绩\n";
        cout << "5. 显示所有学生成绩\n";
        cout << "6. 退出系统\n";
        cout << "请选择操作 (1-6)：";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // 插入
            if (n >= capacity) {
                capacity *= 2;
                double* newScores = new double[capacity * 4];
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        newScores[i * 4 + j] = scores[i * 4 + j];
                    }
                }
                delete[] scores;
                scores = newScores;
                cout << "容量已扩展至 " << capacity << "\n";
            }
            cout << "输入学生的平时、实验、期末、总评成绩：";
            cin >> scores[n * 4 + 0] >> scores[n * 4 + 1]
                >> scores[n * 4 + 2] >> scores[n * 4 + 3];
            n++;
            cout << "学生成绩已添加。\n";

        }
        else if (choice == 2) {
            // 删除
            int index;
            cout << "输入要删除的学生编号 (1-" << n << ")：";
            cin >> index;
            if (index < 1 || index > n) {
                cout << "学生序号非法！\n";
            }
            else {
                int idx = index - 1;
                for (int i = idx; i < n - 1; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        scores[i * 4 + j] = scores[(i + 1) * 4 + j];
                    }
                }
                n--;
                cout << "学生成绩已删除。\n";
            }

        }
        else if (choice == 3) {
            // 修改
            int index;
            cout << "输入要修改的学生编号 (1-" << n << ")：";
            cin >> index;
            if (index < 1 || index > n) {
                cout << "学生序号非法！\n";
            }
            else {
                int idx = index - 1;
                cout << "输入新的平时、实验、期末、总评成绩：";
                cin >> scores[idx * 4 + 0] >> scores[idx * 4 + 1]
                    >> scores[idx * 4 + 2] >> scores[idx * 4 + 3];
                cout << "学生成绩已修改。\n";
            }

        }
        else if (choice == 4) {
            // 查询单个
            int index;
            cout << "输入要查询的学生编号 (1-" << n << ")：";
            cin >> index;
            if (index < 1 || index > n) {
                cout << "学生序号非法！\n";
            }
            else {
                int idx = index - 1;
                cout << "平时\t实验\t期末\t总评\n";
                cout << scores[idx * 4 + 0] << '\t' << scores[idx * 4 + 1] << '\t'
                    << scores[idx * 4 + 2] << '\t' << scores[idx * 4 + 3] << '\n';
            }

        }
        else if (choice == 5) {
            // 显示所有
            if (n == 0) {
                cout << "没有学生成绩数据。\n";
            }
            else {
                cout << "编号\t平时\t实验\t期末\t总评\n";
                for (int i = 0; i < n; ++i) {
                    cout << i + 1 << '\t'
                        << scores[i * 4 + 0] << '\t'
                        << scores[i * 4 + 1] << '\t'
                        << scores[i * 4 + 2] << '\t'
                        << scores[i * 4 + 3] << '\n';
                }
            }

        }
        else if (choice == 6) {
            cout << "退出系统。\n";
            break;

        }
        else {
            cout << "无效的选择，请重新输入。\n";
        }
    }

    delete[] scores;
    return 0;
}