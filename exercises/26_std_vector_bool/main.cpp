#include "../exercise.h"
#include <vector>
#include <iostream> // for std::cout

// READ: std::vector<bool> <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 使用构造函数 (count, value) 创建一个包含 100 个 true 的 vector
    std::vector<bool> vec(100, true);
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    // 在 GCC/Clang (Linux) 64位系统上，通常是 40 字节。
    // 在 MSVC (Windows) 64位系统上，通常是 32 或 40 字节。
    // 我们假设是 40 字节。
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // `vec[30]` 返回的不是 bool&，而是一个代理对象 std::vector<bool>::reference
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`"); // 此时 ref 代理的 bit 位是 true
        
        ref = false; // 通过代理对象，将原始 vector 中的 bit 位设置为 false
        
        ASSERT(!ref, "Fill in `ref` or `!ref`"); // 再次检查代理对象，它现在反映了新的 false 值
        
        // THINK: WHAT and WHY?
        // vec[30] 也被修改了，因为 ref 是它的一个“代理引用”。
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}