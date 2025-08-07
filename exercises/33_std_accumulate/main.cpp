#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    int size = std::accumulate(std::begin(shape), std::end(shape),
                                 1, // 连乘的初始值必须是 1
                                 std::multiplies<int>()) // 使用标准库的乘法函数对象
               * sizeof(DataType); // 将元素总数乘以单个元素的大小
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
