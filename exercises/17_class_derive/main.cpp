#include "../exercise.h"
#include <iostream>

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

static int i = 0;

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << ++i << ". " << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << ++i << ". " << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << ++i << ". " << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << ++i << ". " << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : a(other.a) {
        std::cout << ++i << ". " << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << ++i << ". " << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;

    B(int b) : A(1), x(b) {
        std::cout << ++i << ". " << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << ++i << ". " << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << ++i << ". " << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};

int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // TODO: 补全三个类型的大小
    static_assert(sizeof(X) == sizeof(int), "There is an int in X");
    static_assert(sizeof(A) == sizeof(int), "There is an int in A");
    static_assert(sizeof(B) == sizeof(int) * 2, "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // 1. 构造一个临时的 B 对象 (B(5))。这会依次构造 A(1), X(5), B(1, X(5))。
    // 2. 用这个临时的 B 对象来初始化 A 类型的 ab。这个过程会调用 A 的拷贝构造函数 A(A const &)。
    //    此时，B 对象被“切片”，只有其中的 A 子对象部分被用来拷贝。
    // 3. 临时的 B 对象被析构。这会依次析构 B, X, A。
    //
    // THINK: 这样的代码是“安全”的吗？
    // 它是 C++ 语法上安全的（行为是良定义的），但通常是危险的设计。
    // 因为它会导致信息丢失（B 中非 A 的部分被丢弃）和多态失效。
    // 这种现象被称为“对象切片 (Object Slicing)”。
    // 应该使用指针或引用来避免切片。

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    return 0; // main 函数结束时，x, a, b, ab 会按构造逆序析构
}
