#include <iostream>
#include <random>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

// 增加一个隐藏光标的辅助函数，提升游戏视觉体验
void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
#endif

int main() {
    // 隐藏光标 (仅限 Windows)
#ifdef _WIN32
    HideCursor();
#endif

    // --- 1. 初始化数据 ---
    int player_x = 10;        // 玩家横向位置
    int obs_y = 0, obs_x = 5; // 障碍物位置
    int score = 0;
    bool is_running = true;
    int width = 20, height = 15;

    // 随机数引擎
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, width - 2);

    // 可以在游戏开始前清空一次屏幕，防止背景有杂乱字符
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J"; 
#endif

    // --- 2. 游戏主循环 ---
    while (is_running) {
        // A. 处理输入 (增加了跨平台宏保护)
#ifdef _WIN32
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && player_x > 1) player_x--;
            else if (key == 'd' && player_x < width - 2) player_x++;
            else if (key == 'q') break;
        }
#endif

        // B. 更新逻辑 (计算障碍物下落)
        obs_y++;
        if (obs_y >= height) {
            obs_y = 0;
            obs_x = dist(gen); // 障碍物回到顶部，随机位置
            score++;
        }

        // C. 碰撞检测 (【修复】：判断玩家所在的 height - 2 行)
        if (obs_y == height - 2 && obs_x == player_x) {
            is_running = false; // 撞到了
        }

        // D. 渲染画面
#ifdef _WIN32
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
#else
        std::cout << "\033[H";
#endif

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (y == 0 || y == height - 1) std::cout << "-"; // 顶底边框
                else if (x == 0 || x == width - 1) std::cout << "|"; // 左右边框
                else if (x == player_x && y == height - 2) std::cout << "A"; // 玩家
                else if (x == obs_x && y == obs_y) std::cout << "*"; // 障碍物
                else std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Score: " << score << " (Press 'a'-Left, 'd'-Right, 'q'-Quit)" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // --- 3. 游戏结束 ---
    std::cout << "\nGAME OVER! Final Score: " << score << std::endl;
    return 0;
}