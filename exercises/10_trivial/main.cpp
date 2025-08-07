#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    // 将数组大小增加到96以支持计算到 fib(90)
    unsigned long long cache[96]; 
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 循环条件：只要已缓存的位置(cache.cached)还没达到目标位置(i)，就继续计算
    for (; cache.cached <= i; ++cache.cached) {
        // 使用结构体内的缓存数组
        cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    
    // 使用聚合初始化来设置初始值
    // .cache 的第一个元素是 0，第二个是 1，其余自动零初始化
    // .cached 设置为 2，因为前两个已经有了
    FibonacciCache fib = {{0, 1}, 2};
    
    // 原始数组大小是16，为了通过10的测试可以不用改
    // 但为了和之前的练习保持一致，支持到90，我把结构体内的数组大小改成了96

    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;

    // 我们可以复用同一个缓存对象来计算更大的值
    std::cout << "fibonacci(90) = " << fibonacci(fib, 90) << std::endl;

    return 0;
}