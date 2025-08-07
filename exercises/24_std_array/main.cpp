#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        // .size() 返回元素的个数，这是在模板参数中指定的。
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        // sizeof() 返回整个对象占用的总字节数。5个int，每个4字节，总共 5 * 4 = 20 字节。
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");
        
        int ans[]{1, 2, 3, 4, 5};
        // std::memcmp 比较内存区域。
        // arr.data() 返回指向底层C风格数组的指针。
        // 第三个参数是需要比较的总字节数。
        ASSERT(std::memcmp(arr.data(), ans, sizeof(arr)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        // 元素个数是 8。
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        // 8个double，每个8字节，总共 8 * 8 = 64 字节。
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        // "Hello, InfiniTensor!" 包含20个字符，加上末尾的空字符'\0'，共21个字符。
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        // 元素个数是 21。
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        // 21个char，每个1字节，总共 21 字节。
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        // std::strcmp 比较以空字符结尾的字符串。
        // arr.data() 返回指向底层字符数组的指针，可以被当成 C 风格字符串使用。
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
}