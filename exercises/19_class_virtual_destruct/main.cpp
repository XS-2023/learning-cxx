#include "../exercise.h"
#include <iostream>

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    static int num_a;

    A() {
        ++num_a;
    }
    // 析构函数必须是虚函数，以确保通过基类指针删除派生类对象时，能正确调用派生类的析构函数
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};
// 在类外定义和初始化静态成员
int A::num_a = 0;

struct B final : public A {
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
// 在类外定义和初始化静态成员
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // 使用 dynamic_cast 进行安全的向下转型
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    delete ab;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}