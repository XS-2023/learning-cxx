// #include "../exercise.h"

// constexpr unsigned long long fibonacci(int i) {
//     switch (i) {
//         case 0:
//             return 0;
//         case 1:
//             return 1;
//         default:
//             return fibonacci(i - 1) + fibonacci(i - 2);
//     }
// }

// int main(int argc, char **argv) {
//     constexpr auto FIB20 = fibonacci(20);
//     ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
//     std::cout << "fibonacci(20) = " << FIB20 << std::endl;

//     // TODO: 观察错误信息，修改一处，使代码编译运行
//     // PS: 编译运行，但是不一定能算出结果……
//     constexpr auto ANS_N = 90;
//     auto ANS = fibonacci(ANS_N);
//     std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

//     return 0;
// }
#include <iostream>

// 使用迭代法的高效斐波那契函数
unsigned long long fibonacci_fast(int n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long a = 0;
    unsigned long long b = 1;

    // 从 2 开始循环到 n
    for (int i = 2; i <= n; ++i) {
        unsigned long long next = a + b; // 计算下一个数
        a = b;                           // 更新前一个数
        b = next;                        // 更新当前数
    }
    return b;
}

int main() {
    constexpr int ANS_N = 90;
    unsigned long long ans = fibonacci_fast(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ans << std::endl;
    return 0;
}