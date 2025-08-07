#include "../exercise.h"
#include <iostream> // 为了使用 std::cout

// Fibonacci 结构体现在像一个“类”，封装了数据和操作
struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    // `get` 是一个成员函数，它可以直接访问 `this` 对象的成员 `cache` 和 `cached`
    unsigned long long get(int i) {
        // 循环条件：只要已缓存的位置(this->cached)还没达到目标位置(i)，就继续计算
        for (; cached <= i; ++cached) {
            // 在成员函数内部，可以直接使用成员变量名
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // 使用聚合初始化来设置初始值
    // .cache 的第一个元素是 0，第二个是 1，其余自动零初始化
    // .cached 设置为 2，因为前两个已经有了
    Fibonacci fib = {{0, 1}, 2};
    
    // 调用成员函数 get
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}