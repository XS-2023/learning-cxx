#include "../exercise.h"

// READ: 数组 <https://zh.cppreference.com/w/cpp/language/array>

// arr 被初始化为 {0, 1, 0, 0, ...}
unsigned long long arr[90]{0, 1}; 
unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            // TODO: 补全三目表达式缺失の部分
            // 检查 arr[i] 是否已经计算过（非0），如果计算过，直接返回缓存的值，否则计算、缓存并返回。
            return arr[i] != 0 ? arr[i] : (arr[i] = fibonacci(i - 1) + fibonacci(i - 2));
    }
}

int main(int argc, char **argv) {
    // TODO: 为此 ASSERT 填写正确的值
    // 数组大小 = 元素个数 * 单个元素大小
    // 在典型的64位系统上，unsigned long long 是 8 字节。
    // 所以总大小是 90 * 8 = 720 字节。
    ASSERT(sizeof(arr) == 720, "sizeof array is size of all its elements");

    // ---- 不要修改以下代码 ----
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(20) == 6765, "fibonacci(20) should be 6765");
    ASSERT(fibonacci(80) == 23416728348467685, "fibonacci(80) should be 23416728348467685");
    return 0;
}