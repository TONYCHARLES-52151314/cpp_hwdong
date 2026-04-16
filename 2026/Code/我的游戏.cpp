#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // 使用 ctime 库初始化随机数种子，确保每次游戏遇到的随机事件不同
    srand(time(0));

    // appRunning 变量控制整个程序的运行，用于支持游戏结束后的重玩功能
    bool appRunning = true;

    while (appRunning) {
        // 初始化单局游戏的数据：生命值、得分、金币以及房间状态
        bool isPlaying = true;
        int playerHP = 100;
        int maxHP = 100;
        int score = 0;
        int gold = 0;
        int currentRoom = 0; // 核心状态变量：0=主菜单, 1=入口, 2=兵器库, 3=恶龙通道, 4=宝库, 5=出口
        
        // 使用 bool 变量记录剧情道具，替代还没学到的数组或背包系统
        bool hasSword = false;
        bool hasRelic = false;
        bool dragonDefeated = false;
        int dragonHP = 50;

        // 游戏主逻辑循环，只要玩家活着且没达到通关条件就会一直运行
        while (isPlaying) {
            int choice = 0;

            // 使用 switch 语句实现“状态机”逻辑，根据当前房间编号执行不同的场景描述
            switch (currentRoom) {
                case 0: { // 主菜单界面逻辑
                    cout << "\n====================================\n";
                    cout << "      深渊之王的迷宫 (Abyssal Labyrinth)\n";
                    cout << "====================================\n";
                    cout << "1. 举起火把，进入迷宫\n2. 感到恐惧，退出游戏\n";
                    
                    // 使用 while(true) 配合 cin.fail() 实现鲁棒的输入检测，防止非法字符崩溃
                    while (true) {
                        cout << "请输入您的选择(1-2): ";
                        cin >> choice;
                        if (cin.fail() || choice < 1 || choice > 2) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "-> [非法输入] 请输入正确的数字。\n";
                        } else break;
                    }

                    if (choice == 1) currentRoom = 1; 
                    else { isPlaying = false; appRunning = false; }
                    break;
                }

                case 1: { // 入口场景：展示 if-else 分支处理不同的探索选择
                    cout << "\n[地点：入口] 生命值: " << playerHP << " | 金币: " << gold << "\n";
                    cout << "1. 搜索地面\n2. 前往左侧兵器库\n3. 前往右侧通道\n";
                    
                    while (true) {
                        cin >> choice;
                        if (cin.fail() || choice < 1 || choice > 3) {
                            cin.clear(); cin.ignore(1000, '\n');
                        } else break;
                    }

                    if (choice == 1) { // 概率随机事件逻辑
                        if (rand() % 100 < 40) {
                            int found = 10 + rand() % 16;
                            gold += found; score += 5;
                            cout << "-> 捡到了 " << found << " 枚金币。\n";
                        } else cout << "-> 啥也没发现。\n";
                    } 
                    else if (choice == 2) currentRoom = 2;
                    else currentRoom = 3;
                    break;
                }

                case 2: { // 兵器库场景：展示逻辑标志位 (bool) 如何改变交互选项
                    cout << "\n[地点：兵器库] ";
                    if (!hasSword) cout << "1. 拔出长剑\n";
                    else cout << "1. 投币休息(10金币)\n";
                    cout << "2. 返回入口\n";

                    while (true) {
                        cin >> choice;
                        if (cin.fail() || choice < 1 || choice > 2) {
                            cin.clear(); cin.ignore(1000, '\n');
                        } else break;
                    }

                    if (choice == 1) {
                        if (!hasSword) { hasSword = true; score += 20; cout << "-> 获得长剑！攻击力提升。\n"; }
                        else if (gold >= 10) { gold -= 10; playerHP = min(maxHP, playerHP + 20); cout << "-> 回复了生命。\n"; }
                    } else currentRoom = 1;
                    break;
                }

                case 3: { // 战斗逻辑：展示 if 分支嵌套实现的数值对抗系统
                    cout << "\n[地点：通道] ";
                    if (dragonDefeated) {
                        cout << "1. 经过龙尸(通往宝库)\n2. 返回入口\n";
                        cin >> choice;
                        currentRoom = (choice == 1) ? 4 : 1;
                    } else {
                        cout << "恶龙拦路！HP: " << dragonHP << "\n1. 战斗\n2. 逃跑\n";
                        cin >> choice;
                        if (choice == 1) {
                            // 根据是否拥有长剑变量计算不同的随机伤害值
                            int dmg = hasSword ? (15 + rand() % 16) : (5 + rand() % 6);
                            dragonHP -= dmg;
                            cout << "-> 你造成了 " << dmg << " 点伤害！\n";
                            if (dragonHP <= 0) { dragonDefeated = true; score += 100; cout << "-> 巨龙倒下了！\n"; }
                            else {
                                int rec_dmg = 10 + rand() % 10;
                                playerHP -= rec_dmg; cout << "-> 受到反击 " << rec_dmg << " 点伤害！\n";
                            }
                        } else { playerHP -= 5; currentRoom = 1; }
                    }
                    break;
                }

                case 4: { // 宝库场景
                    cout << "\n[地点：宝库] 1. 夺取圣物\n2. 走向尽头大门\n";
                    cin >> choice;
                    if (choice == 1 && !hasRelic) { hasRelic = true; score += 50; cout << "-> 拿到了圣物！\n"; }
                    else if (choice == 2) currentRoom = 5;
                    break;
                }

                case 5: { // 最终判定场景：根据多个 bool 变量状态判断胜负结果
                    cout << "\n[地点：出口大门] 1. 尝试开启\n2. 返回\n";
                    cin >> choice;
                    if (choice == 1) {
                        if (hasRelic) { cout << "-> 圣物发光，你获胜了！\n"; score += 200; isPlaying = false; }
                        else cout << "-> 门锁住了，似乎需要某种圣物。\n";
                    } else currentRoom = 4;
                    break;
                }
            } 

            // 每轮逻辑结束后，检查玩家生命值，若为0则跳出循环结束游戏
            if (playerHP <= 0 && isPlaying) {
                cout << "\n你倒在了迷宫中... 游戏结束。\n";
                isPlaying = false;
            }
        } 

        // 游戏结束后的重玩逻辑，通过控制 appRunning 实现
        if (appRunning) {
            cout << "\n最终得分: " << score << "\n是否重玩? (y/n): ";
            char rep; cin >> rep;
            if (rep == 'n' || rep == 'N') appRunning = false;
        }
    } 

    return 0;
}