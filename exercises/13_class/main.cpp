#include "../exercise.h"
#include <iostream>

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[128]; // 数组大小最好大一些以支持更大的输入
    int cached;

public:
    // TODO: 实现构造器
    Fibonacci() {
        // 在构造函数中完成初始化工作
        cache[0] = 0;
        cache[1] = 1;
        cached = 2; // 表示 cache[0] 和 cache[1] 已经就绪
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 确保 i 不会超过数组边界，这是一个好的实践
        if (i >= 128) {
            // 在实际项目中，这里应该抛出异常或返回错误码
            return -1; // 返回一个错误标记
        }

        // 循环逻辑和之前一样，按需计算
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib; // 在这里，Fibonacci() 构造函数被自动调用
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    
    // 我们还可以验证一下更大的数
    std::cout << "fibonacci(90) = " << fib.get(90) << std::endl;
    return 0;
}