// 《现代C++编程实战》第4章实战项目之二：Pong游戏
// 这是一个简单的控制台双人对战游戏

#include <iostream>
#include <random>    // 用于生成现代随机数
#include <thread>    // 用于控制游戏帧率（sleep）
#include <chrono>    // 时间库
#include <string>

// --- 平台兼容性处理 ---
#ifdef _WIN32
// Windows 平台相关的头文件和光标控制函数
#include <windows.h>
#include <conio.h>
void hide_cursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE; // 隐藏光标以减少闪烁
    SetConsoleCursorInfo(console, &cursorInfo);
}
void show_cursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = TRUE;  // 显示光标
    SetConsoleCursorInfo(console, &cursorInfo);
}
#else
// 类 Unix (Linux/macOS) 平台的兼容层
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// 模拟 Windows 的 _kbhit()：检查键盘是否有输入（非阻塞）
int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

// 模拟 Windows 的 _getch()：读取单个字符而不回显
char _getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// 使用 ANSI 转义序列隐藏/显示光标
void hide_cursor() { std::cout << "\033[?25l"; }
void show_cursor() { std::cout << "\033[?25h"; }
#endif

// 宏定义：生成一个随机的速度方向
// velDist: 速度大小分布，dirDist: 方向分布 (正负)
#define RANDOM_DIRECTION(gen, velDist, dirDist) \
    (velDist(gen) * (dirDist(gen) ? 1 : -1))

int main() {
    // 1. 初始化游戏基础数据
    auto WIDTH{ 120 }, HEIGHT{ 40 };   // 游戏场地宽高
    auto ball_x{ WIDTH / 2 }, ball_y{ HEIGHT / 2 }; // 球的初始位置（居中）
    auto ball_vec_x{ 0 }, ball_vec_y{ 0 };          // 球的运动速度向量

    auto paddle_w{ 3 }, paddle_h{ 10 }; // 挡板尺寸
    // 左挡板位置与速度
    auto paddle1_x{ 0 }, paddle1_y{ HEIGHT / 2 - paddle_h / 2 }, paddle1_vec{ 3 }; 
    // 右挡板位置与速度
    auto paddle2_x{ WIDTH - paddle_w }, paddle2_y{ HEIGHT / 2 - paddle_h / 2 }, paddle2_vec{ 3 }; 

    // 分数及其显示位置
    auto score1{ 0 }, score2{ 0 };
    auto score1_x{ paddle_w + 8 }, score1_y{ 2 };
    auto score2_x{ WIDTH - 8 - paddle_w }, score2_y{ 2 };

    // 现代 C++ 随机数生成器设置
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> velDist(1, 3); // 速度在 1 到 3 之间
    std::uniform_int_distribution<int> dirDist(0, 1); // 0 为负方向，1 为正方向

    // 给球一个初始的随机速度
    ball_vec_x = RANDOM_DIRECTION(gen, velDist, dirDist);
    ball_vec_y = RANDOM_DIRECTION(gen, velDist, dirDist);

    // 【核心优化】：创建一个字符串作为“帧缓冲区”
    // 将一整帧的内容先写到内存字符串中，再一次性输出到屏幕，极大减少闪烁
    std::string framebuffer(HEIGHT * (WIDTH + 1), ' '); 

    hide_cursor(); // 隐藏光标，让画面更整洁

    // --- 游戏主循环 ---
    while (true) {
        // --- 1. 处理输入事件 ---
        if (_kbhit()) {
            char key = _getch();

            // 左挡板控制: W 向上, S 向下
            if ((key == 'w' || key == 'W') && paddle1_y > paddle1_vec) {
                paddle1_y -= paddle1_vec;
            }
            else if ((key == 's' || key == 'S') && paddle1_y + paddle1_vec + paddle_h < HEIGHT) {
                paddle1_y += paddle1_vec;
            }
            // 右挡板控制: 方向键上 (72) 与 下 (80)
            // 注意：某些系统上方向键会返回多个字节，这里简化处理 Windows ASCII 码
            else if (key == 72 && paddle2_y > paddle2_vec) { 
                paddle2_y -= paddle2_vec;
            }
            else if (key == 80 && paddle2_y + paddle2_vec + paddle_h < HEIGHT) {
                paddle2_y += paddle2_vec;
            }
            // 退出游戏
            else if (key == 'q' || key == 'Q') {
                break;
            }
        }

        // --- 2. 更新游戏逻辑 (物理计算) ---
        ball_x += ball_vec_x; // 移动球
        ball_y += ball_vec_y;

        // 检测与上下墙壁的碰撞
        if (ball_y <= 0 || ball_y >= HEIGHT - 1) { 
            ball_vec_y = -ball_vec_y; // 垂直速度反转
        }

        // 检测与左挡板的碰撞
        if (ball_x < paddle_w && ball_y >= paddle1_y && ball_y < paddle1_y + paddle_h) {
            ball_vec_x = -ball_vec_x; // 水平速度反转
            // score1 += 1; // 击中挡板可以加分（可选逻辑）
        }
        // 检测与右挡板的碰撞
        else if (ball_x > WIDTH - paddle_w && ball_y >= paddle2_y && ball_y < paddle2_y + paddle_h) {
            ball_vec_x = -ball_vec_x;
            // score2 += 1;
        }

        // 检测得分（球跑出左右边界）
        if (ball_x < 0 || ball_x >= WIDTH) {
            if (ball_x < 0) score2++; // 右边得分
            else score1++;          // 左边得分
            
            // 球回到中心并重新随机出发
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_vec_x = RANDOM_DIRECTION(gen, velDist, dirDist);
            ball_vec_y = RANDOM_DIRECTION(gen, velDist, dirDist);
        }

        // 重置光标位置到 (0,0)，而不是清屏（清屏会导致剧烈闪烁）
#ifdef _WIN32  
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
#else
        std::cout << "\033[H"; 
#endif

        // --- 3. 绘制画面到缓冲区 ---
        int frame_idx = 0;
        std::string s1 = std::to_string(score1);
        std::string s2 = std::to_string(score2);

        // A. 绘制顶部边界
        for (auto x = 0; x < WIDTH; x++) framebuffer[frame_idx++] = '=';
        framebuffer[frame_idx++] = '\n';

        // B. 绘制中间游戏区域
        for (auto y = 1; y < HEIGHT - 1; y++) {
            for (auto x = 0; x < WIDTH; x++) {
                // 绘制球
                if (x == ball_x && y == ball_y)
                    framebuffer[frame_idx++] = 'O';
                // 绘制左挡板
                else if (y >= paddle1_y && y < paddle1_y + paddle_h
                    && x >= paddle1_x && x < paddle1_x + paddle_w)
                    framebuffer[frame_idx++] = 'Z';
                // 绘制右挡板
                else if (y >= paddle2_y && y < paddle2_y + paddle_h
                    && x >= paddle2_x && x < paddle2_x + paddle_w)
                    framebuffer[frame_idx++] = 'Z';
                // 绘制左侧分数
                else if (y == score1_y && x == score1_x) {
                    for (char c : s1) framebuffer[frame_idx++] = c;
                    x += s1.size() - 1;
                }
                // 绘制右侧分数
                else if (y == score2_y && x == score2_x) {
                    for (char c : s2) framebuffer[frame_idx++] = c;
                    x += s2.size() - 1;
                }
                // 绘制边框和中线
                else if (x == 0 || x == WIDTH / 2 || x == WIDTH - 1)
                    framebuffer[frame_idx++] = '|';
                // 填充背景空白
                else 
                    framebuffer[frame_idx++] = ' ';
            }
            framebuffer[frame_idx++] = '\n';
        }

        // C. 绘制底部边界
        for (auto x = 0; x < WIDTH; x++) framebuffer[frame_idx++] = '=';
        framebuffer[frame_idx++] = '\n';

        // --- 4. 将缓冲区内容一次性打印到屏幕 ---
        std::cout << framebuffer;

        // 控制游戏速度（每秒约 20 帧）
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    show_cursor(); // 游戏结束，恢复光标
    return 0;
}