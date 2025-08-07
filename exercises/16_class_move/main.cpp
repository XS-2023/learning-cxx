#include "../exercise.h"
#include <iostream>
#include <utility> // 为了使用 std::move

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached) { // 1. 直接“窃取”源对象的指针和状态
        // 2. 将源对象置于“已移动”状态，防止其析构函数释放我们已接管的内存
        other.cache = nullptr;
        other.cached = 0;
        std::cout << "Move constructor called." << std::endl;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        // 1. 检查自我赋值
        if (this != &other) {
            // 2. 释放当前对象持有的旧资源
            delete[] cache;

            // 3. “窃取”源对象的资源
            cache = other.cache;
            cached = other.cached;

            // 4. 将源对象置于“已移动”状态
            other.cache = nullptr;
            other.cached = 0;
            std::cout << "Move assignment operator called." << std::endl;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        // 对 nullptr 调用 delete[] 是安全的（什么也不做）
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    // (这里也重载了 [] 运算符，这是一个很好的实践)
    size_t operator[](int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i < cached, "i out of range"); // 修正：应为 <
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // std::move 将 fib (左值) 强制转换为右值引用，使其可以匹配移动构造函数
    DynFibonacci fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);
    fib1[10]; // 预计算一下，确保 fib1 有缓存数据

    fib0 = std::move(fib1); // 调用移动赋值运算符
    ASSERT(!fib1.is_alive(), "fib1 moved");

    fib0 = std::move(fib0); // 测试自我移动
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}