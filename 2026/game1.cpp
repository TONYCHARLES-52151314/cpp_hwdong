#include <iostream>  
#include <ctime>     
#include <cstdlib>   // 用于 rand() 随机函数

using namespace std;

int main() {

    srand(time(0));

    int hull = 100;         // 船体健康度 (0-100)
    int fuel = 100;         // 燃料 (0-100)
    int distance = 500;     // 距离安全区的距离 (km)
    int score = 0;          // 科学数据 (得分)
    int turn = 1;           // 回合计数器
    bool gameOver = false;  // 游戏结束标志

    cout << "======= [ 深空绝境：奇点逃离 ] =======" << endl;
    cout << "任务：在船体崩溃前，航行至 0km 安全区！" << endl;
 while (hull > 0 && fuel > 0 && distance > 0 && !gameOver) {
        
        cout << "\n[ 远程雷达图 ]" << endl;
        for (int i = 0; i < 20; i++) { // 用 for 循环画出 20 个格子的进度条
            if (i == (500 - distance) / 25) cout << "V"; // 计算飞船当前位置
            else if (i == 0) cout << "O";                // 0 位置是黑洞
            else cout << "-";                            // 其他是星空
        }
        cout << " [安全区]" << endl;

        // 打印当前状态表
        cout << "第 " << turn << " 回合 | 船体: " << hull << "% | 燃料: " << fuel << "% | 剩余距离: " << distance << "km" << endl;
        int choice;
        // 交互：获取玩家指令
        cout << "指令：1.全速前进  2.维修滑行  3.扫描数据  4.自毁程序" << endl;
        cout << "执行编号: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "引擎满功率运载！前进 100km。" << endl;
                distance -= 100;
                fuel -= 20;
                break;
            case 2:
                cout << "开启惯性滑行并自动维修。前进 30km。" << endl;
                distance -= 30;
                fuel -= 5;
                hull += 10; // 维修加血
                break;
            case 3:
                cout << "停止推进，正在采集黑洞边缘数据..." << endl;
                score += 25; // 增加得分
                fuel -= 10;
                break;
             case 4:
                cout << "警告：你启动了自毁协议..." << endl;
                gameOver = true; // 触发这个标志位
                break;
            default:
                cout << "警告：指令未识别，飞船在原地漂流！" << endl;
                // 不做任何属性改变，相当于浪费了一回合
                break;
        }
        
        // 1. 引力伤害：随回合数增加
        int damage = turn * 2; 
        hull -= damage;
        cout << "受到引力拉扯，船体受损: " << damage << "%" << endl;

        // 2. 随机事件：10% 概率遇到空间碎片
        if (rand() % 10 == 0) {
            cout << "警告：遭遇空间碎片撞击！船体损毁严重！" << endl;
            hull -= 20;
        }

        if (hull > 100) hull = 100;
        if (distance < 0) distance = 0;

        turn++;
    }
     
    cout << "\n========================================" << endl;
    if (distance <= 0 && hull > 0) {
        cout << "   [ 任务成功 ] 你成功脱离了黑洞引力圈！" << endl;
        cout << "   最终科学评分: " << score << endl;
        if (score >= 50) cout << "   评价：科学界的传奇英雄！" << endl;
        else cout << "   评价：一名优秀的幸存者。" << endl;
    } else {
        cout << "   [ 任务失败 ] ";
        if (hull <= 0) cout << "飞船在强引力下崩解了..." << endl;
        else if (fuel <= 0) cout << "燃料耗尽，你成为了太空尘埃..." << endl;
    }
    cout << "========================================" << endl;

    return 0;
}
 