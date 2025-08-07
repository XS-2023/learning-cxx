#include "../exercise.h"
#include <iostream>

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;
    // (为了安全，最好也把容量存下来，但为了遵循题目框架，我们假设调用者会保证不越界)
    // int capacity; 

public:
    // TODO: 实现动态设置容量的构造器
    // 使用成员初始化列表来初始化成员
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        // ASSERT(capacity >= 2, "Capacity must be at least 2"); // 好的实践是验证输入
        // 在构造函数体中，为缓存设置初始值
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        // 使用 delete[] 来释放由 new[] 分配的数组内存
        // 如果忘记这一步，会导致内存泄漏
        delete[] cache;
        std::cout << "Destructor called, memory released." << std::endl;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 循环逻辑和之前一样，按需计算
        // 注意：这里没有边界检查，因为我们没有存储 capacity
        // 在实际项目中，必须进行检查以防越界
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    { // 添加一个作用域块
        DynFibonacci fib(128); // 构造函数被调用，在堆上分配了 128 个 size_t 的空间
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
        ASSERT(fib.get(90) == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
        std::cout << "fibonacci(90) = " << fib.get(90) << std::endl;
    } // fib 对象离开作用域，它的析构函数 ~DynFibonacci() 会被自动调用
    
    // 程序在这里可以继续执行其他操作...
    return 0;
}