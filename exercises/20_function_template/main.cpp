#include "../exercise.h"
#include <cmath> // 引入 cmath 来使用 std::abs

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>

// TODO: 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // 当浮点数可以被二进制精确表示时（如整数、0.5、0.25、1.25），可以直接用 == 判断。
    // 当浮点数是无法精确表示的十进制小数（如 0.1, 0.2），或经过了复杂的计算导致精度损失时，
    // 必须判断它们的差值是否在一个可接受的误差范围内。
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    // TODO: 修改判断条件使测试通过
    // 检查 plus(0.1, 0.2) 的结果与 0.3 的差的绝对值是否小于一个很小的数（epsilon）。
    ASSERT(std::abs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}