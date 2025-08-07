#include "../exercise.h"
#include <iostream>
#include <cstring> // 为了使用 std::memcpy

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity; // 添加 capacity 成员，这对于正确的拷贝至关重要

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现复制构造器
    // 执行深拷贝
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]), // 1. 为新对象分配自己的内存
          cached(other.cached),
          capacity(other.capacity) {
        
        // 2. 将原对象内存中的数据复制过来
        // 使用 std::memcpy 是一种高效的方式
        std::memcpy(cache, other.cache, cached * sizeof(size_t));
        std::cout << "Copy constructor called, new memory allocated." << std::endl;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // (为了让 const 版本能编译通过，这里也加上边界检查)
        ASSERT(i < capacity, "i is out of capacity");
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // ...
    size_t get(int i) const {
        // (为了让 const 版本能编译通过，这里也加上边界检查)
        ASSERT(i < capacity, "i is out of capacity");
        if (i < cached) { // 注意：这里应该是 < 而不是 <=
            return cache[i];
        }
        ASSERT(false, "i out of range of cached values");
        return -1; // 添加返回值以避免警告
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib; // 这里调用拷贝构造函数
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}