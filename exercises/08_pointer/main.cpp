#include "../exercise.h"

// READ: 数组向指针退化 <https://zh.cppreference.com/w/cpp/language/array#%E6%95%B0%E7%BB%84%E5%88%B0%E6%8C%87%E9%92%88%E7%9A%84%E9%80%80%E5%8C%96>
bool is_fibonacci(int *ptr, int len, int stride) {
    ASSERT(len >= 3, "`len` should be at least 3");
    // TODO: 编写代码判断从 ptr 开始，每 stride 个元素取 1 个元素，组成长度为 n 的数列是否满足
    // arr[i + 2] = arr[i] + arr[i + 1]

    // 我们需要遍历这个逻辑上的数列，检查每一组连续的三个数。
    // 循环变量 i 代表的是逻辑数列中的索引，而不是物理内存的偏移量。
    // 循环到 len - 2 即可，因为每次检查都需要 i, i+1, i+2 这三个元素。
    for (int i = 0; i < len - 2; ++i) {
        // 使用指针和步长来定位逻辑数列中的三个连续元素
        // 逻辑第 i   个数的地址是: ptr + i * stride
        // 逻辑第 i+1 个数的地址是: ptr + (i+1) * stride
        // 逻辑第 i+2 个数的地址是: ptr + (i+2) * stride
        // C++ 的 [] 运算符是 *(ptr + offset) 的语法糖。
        // 所以我们可以直接用 ptr[i * stride] 来获取值。
        
        if (ptr[(i + 2) * stride] != ptr[i * stride] + ptr[(i + 1) * stride]) {
            // 只要有一组不满足斐波那契条件，整个数列就不是斐波那契数列。
            return false;
        }
    }

    // 如果循环顺利结束，说明所有检查都通过了。
    return true;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};
    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on
    return 0;
}
