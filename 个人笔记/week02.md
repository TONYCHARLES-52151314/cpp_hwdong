# 程序结构
****
## 函数

调用
实参形参
模块化，反复调用，可读性

## 注释
多行注释不可以嵌套

## 预处理语句
预处理器用文件内容替换掉该语句
包含指令： #include
文件包含
#include<>  系统文件
#include "" 当前目录

宏定义
为常量表达式或表达式取名字
#define

## 条件编译
#if #else #elif #endif

* 调试
```
#ifdef DEBUG
    str
```

* 头文件保护
```
// my_math.h

#ifndef MY_MATH_H    // 如果没有定义这个宏
#define MY_MATH_H    // 那么定义它，并继续编译后面的内容

// 这里放置你的声明
void myFunction();

#endif // MY_MATH_H   // 结束保护
```

* 跨平台使用
```
#include <stdio.h>

// 根据系统引入不同的头文件
#ifdef _WIN32
    #include <windows.h> // Windows 专有库
#else
    #include <unistd.h>  // Unix/Linux 专有库
#endif

void universal_sleep(int milliseconds) {
    #ifdef _WIN32
        // Windows 的 Sleep 单位是毫秒
        Sleep(milliseconds);
    #else
        // Unix 的 usleep 单位是微秒，所以要乘以 1000
        usleep(milliseconds * 1000);
    #endif
}

int main() {
    printf("Starting... (Waiting for 2 seconds)\n");
    
    universal_sleep(2000);
    
    printf("Done!\n");
    return 0;
}
```

## 标准输入输出库
输入流对象输出流对象没听懂
endl强制刷新缓存区

## 运算符

## 变量：命名的内存块
• 数据：常量和变量， 变量就是一块内存，每个变量都有确定的类型。
• 类型：决定了对变量能进行说明运算、变量占内存大小、变量值范围

列表初始化？没听懂

变量命名

## 名字空间
解决名字冲突问题
名字限定    名字空间名::名字
引入整个名字空间
整个空间using namespace std 任有风险？
或者using std::cout
定义自己的名字空间
```
namespace 名字空间名{
    xxx
}
```
名字空间的嵌套

## 字符
## 常量定义
```
在现代 C++（C++11 及以后）中，constexpr 是定义常量的首选方式。如果说 const 是告诉编译器“这个变量只读”，那么 constexpr 就是告诉编译器“这个变量在编译时就得算出来”。

把计算留给编译器，把速度留给运行期。这就是 constexpr 的核心哲学。

1. constexpr vs const：本质区别
很多初学者会混淆这两者，其实区别很明确：

const (只读)： 它的值可以在运行时确定。例如：const int my_age = get_user_input();。你一旦初始化了它，就不能改了，但初始化发生在程序运行的时候。

constexpr (常量表达式)： 它的值必须在编译时就能确定。例如：constexpr int days_in_week = 7;。如果你尝试用一个运行时的函数给它赋值，编译器会直接报错。

特性	#define	const	constexpr
类型安全	❌ (纯文本替换)	✅	✅
有无作用域	❌ (全局污染)	✅	✅
编译时求值	✅	❌ (通常是运行期)	✅ (强制要求)
调试友好	❌ (符号表里没有)	✅	✅
2. 基础用法：定义数值和数组
C++
// 1. 基础类型
constexpr double PI = 3.1415926535;
constexpr int MAX_BUFFER = 1024 * 64; // 编译时直接计算出结果

// 2. 用于数组大小（必须是编译时常量）
int my_array[MAX_BUFFER]; 

// 3. 修饰对象（要求构造函数也是 constexpr）
struct Point {
    int x, y;
    constexpr Point(int ix, int iy) : x(ix), y(iy) {}
};
constexpr Point origin{0, 0}; // 编译时就存在的对象
3. 进阶武器：constexpr 函数
这是 constexpr 最强大的地方。它可以让复杂的逻辑（循环、递归、分支）在编译阶段运行。

C++
// 编译时计算阶乘
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main() {
    // 编译后，这行代码直接变成了 int res = 120;
    // 运行期间完全不需要进行乘法运算
    constexpr int res = factorial(5); 
    
    int dynamic_n = 5;
    int val = factorial(dynamic_n); // 也可以当普通函数在运行期调用
}
4. C++17 的大招：if constexpr
在写模板（Template）代码时，if constexpr 可以让编译器根据条件丢弃掉不符合分支的代码。这解决了以前需要写极其复杂的模板偏特化才能解决的问题。

C++
template <typename T>
void print_value(T v) {
    if constexpr (std::is_pointer_v<T>) {
        printf("Pointer value: %p\n", v);
    } else {
        printf("Normal value: %d\n", v);
    }
}
编译时，如果 T 是 int，整个 if 分支会被编译器彻底删掉，不会留下任何运行时开销。

5. C++20/23 的新成员
为了进一步压榨编译器的潜力，现代 C++ 又增加了两个兄弟：

consteval (C++20)： 更加激进。它修饰的函数必须在编译时运行。如果由于某种原因（比如参数是运行时的）导致无法在编译时运行，直接报错。

constinit (C++20)： 强制要求变量在编译时初始化，但它不要求变量是只读的。主要用来解决“静态初始化顺序陷阱”。

💡 总结建议
能用 constexpr 就不用 const：因为它不仅安全，还能通过编译时计算提升性能。

告别 #define 常量：#define 没有类型检查，没有作用域，是 C 语言时代的遗留物。

头文件保护：在头文件中定义 constexpr 变量通常是安全的，因为它们默认具有内部链接属性（Internal Linkage）。
```

## 标准输入输出流
## 标准库类型std::string
## 程序控制流

****
# 变量
## 不同初始化方式
列表在编译阶段就把窄化情况给排除了
类型推断：auto

## typeid

## const

## decltype