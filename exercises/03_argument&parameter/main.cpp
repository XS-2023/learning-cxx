#include "../exercise.h"

// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>
// THINK: 参数都有哪些传递方式？如何选择传递方式？

void func(int);

// TODO: 为下列 ASSERT 填写正确的值
int main(int argc, char **argv) {
    auto arg = 99;
    ASSERT(arg == 99, "arg should be 99"); // `arg` 被初始化为 99
    std::cout << "befor func call: " << arg << std::endl;

    func(arg); // 调用 func，将 arg 的值传递过去

    ASSERT(arg == 99, "arg should be 99"); // `arg` 的值没有被 func 改变
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

// TODO: 为下列 ASSERT 填写正确的值
void func(int param) { // param 是 arg 的一个副本
    ASSERT(param == 99, "param should be 99"); // param 接收了 arg 的值 99
    std::cout << "befor add: " << param << std::endl;

    param += 1; // 修改副本 param 的值

    ASSERT(param == 100, "param should be 100"); // 副本 param 的值变为 100
    std::cout << "after add: " << param << std::endl;
}