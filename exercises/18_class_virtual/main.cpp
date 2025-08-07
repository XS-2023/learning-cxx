#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // ---- Group 1: Direct calls on objects ----
    // Calls are resolved based on the object's actual type.
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // D inherits C's virtual_name
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // ---- Group 2: Calls through references ----
    A &rab = b; // Reference of type A, refers to an object of type B
    B &rbc = c; // Reference of type B, refers to an object of type C
    C &rcd = d; // Reference of type C, refers to an object of type D

    // Virtual calls: Resolved at RUNTIME based on the ACTUAL type of the object.
    ASSERT(rab.virtual_name() == 'B', MSG); // rab refers to a B object
    ASSERT(rbc.virtual_name() == 'C', MSG); // rbc refers to a C object
    ASSERT(rcd.virtual_name() == 'C', MSG); // rcd refers to a D object, D inherits C's final virtual_name

    // Direct calls: Resolved at COMPILE-TIME based on the DECLARED type of the reference.
    ASSERT(rab.direct_name() == 'A', MSG); // rab is declared as A&
    ASSERT(rbc.direct_name() == 'B', MSG); // rbc is declared as B&
    ASSERT(rcd.direct_name() == 'C', MSG); // rcd is declared as C&

    // ---- Group 3: More calls through references ----
    A &rac = c; // Reference of type A, refers to an object of type C
    B &rbd = d; // Reference of type B, refers to an object of type D

    ASSERT(rac.virtual_name() == 'C', MSG); // rac refers to a C object
    ASSERT(rbd.virtual_name() == 'C', MSG); // rbd refers to a D object, D inherits C's final virtual_name
    ASSERT(rac.direct_name() == 'A', MSG); // rac is declared as A&
    ASSERT(rbd.direct_name() == 'B', MSG); // rbd is declared as B&

    // ---- Group 4: Final call through reference ----
    A &rad = d; // Reference of type A, refers to an object of type D

    ASSERT(rad.virtual_name() == 'C', MSG); // rad refers to a D object, D inherits C's final virtual_name
    ASSERT(rad.direct_name() == 'A', MSG); // rad is declared as A&

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
