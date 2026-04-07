# if 0 
//顺序查找
//sequential search
#include <iostream>

int main() {
    int a[]{ 12, 46, 25, 43, 7, 92, 5, 29, 80, 105 };
    int x;
    std::cout << "请输入要查找的值：";
    std::cin >> x;

    bool found = false;
    for (int e : a) {          // 范围for循环遍历每个元素
        if (e == x) {
            found = true;
            break;
        }
    }

    if (found)
        std::cout << "在数组a中找到了：" << x << '\n';
    else
        std::cout << "在数组a中未找到：" << x << '\n';

    return 0;
}
#endif

# if 0 
//二分查找
//binary search
#include <iostream>
#include <iterator>   // C++17 提供 std::size

int main() {
    int a[]{ 5, 7, 12, 25, 34, 37, 43, 46, 58, 80, 82, 105 };
    constexpr int n = std::size(a);   // 计算数组元素个数

    int x;
    std::cout << "请输入要查找的值：";
    std::cin >> x;

    int low = 0;
    int high = n - 1;
    bool found = false;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == x) {
            found = true;
            break;
        } else if (x < a[mid]) {
            high = mid - 1;   // 到左半区间查找
        } else {
            low = mid + 1;    // 到右半区间查找
        }
    }

    if (found)
        std::cout << "在数组a中找到了：" << x << '\n';
    else
        std::cout << "在数组a中未找到：" << x << '\n';

    return 0;
}
#endif

# if 0 
//冒泡排序 bubble sort
#include <iostream>

int main() {
    int a[]{ 49, 38, 27, 97, 76, 13, 27, 49 };
    int n = sizeof(a) / sizeof(a[0]);   // 计算数组长度

    for (int i = n - 1; i > 0; --i) {
        bool swapped = false;           // 标记本趟是否发生过交换
        for (int j = 0; j < i; ++j) {
            if (a[j] > a[j + 1]) {
                // 交换两个元素
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = true;
            }
        }
        // 输出本趟结果（便于观察过程）
        for (int e : a) std::cout << e << '\t';
        std::cout << '\n';

        if (!swapped) break;   // 没有交换，已有序，提前结束
    }

    return 0;
}
#endif

# if 0 
//基于指针的冒泡排序
//Pointer-based bubble sort
#include <iostream>

int main() {
    int a[]{ 49, 38, 27, 97, 76, 13, 27, 49 };
    int n = sizeof(a) / sizeof(a[0]);
    int* end = a + n - 1;   // 指向最后一个元素

    for (int* p = end; p > a; --p) {
        bool swapped = false;
        for (int* q = a; q < p; ++q) {
            if (*q > *(q + 1)) {
                int temp = *q;
                *q = *(q + 1);
                *(q + 1) = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    // 输出排序后的结果
    for (int e : a) std::cout << e << ' ';
    std::cout << '\n';

    return 0;
}
#endif

# if 0 
//简单选择排序 
//Simple selection sort
#include <iostream>

int main() {
    int a[]{ 49, 38, 27, 97, 76, 13, 27, 49 };
    int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;               // 假设第i个元素最小
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIdx])
                minIdx = j;           // 找到更小的，更新下标
        }
        if (minIdx != i) {
            int temp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = temp;
        }

        // 输出本趟结果（可选）
        for (int e : a) std::cout << e << '\t';
        std::cout << '\n';
    }

    return 0;
}
#endif

#if 0
// 选择排序，按总评成绩降序
//Select sorting order, in descending order of overall score.
for (int i = 0; i < n - 1; ++i) {
    int maxIdx = i;
    for (int j = i + 1; j < n; ++j) {
        if (scores[j * 4 + 3] > scores[maxIdx * 4 + 3])
            maxIdx = j;
    }
    if (maxIdx != i) {
        // 交换第 i 个学生和第 maxIdx 个学生的所有4项成绩
        for (int k = 0; k < 4; ++k) {
            double temp = scores[i * 4 + k];
            scores[i * 4 + k] = scores[maxIdx * 4 + k];
            scores[maxIdx * 4 + k] = temp;
        }
    }
}
#endif
