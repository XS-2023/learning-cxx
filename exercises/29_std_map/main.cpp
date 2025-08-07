#include "../exercise.h"
#include <map>
#include <string>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // 使用 find 方法检查 key 是否存在。
    // find 返回一个迭代器，如果找不到 key，则返回 map.end()。
    return map.find(key) != map.end();
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // 使用下标运算符[]来插入或更新键值对。
    // 如果 key 不存在，会创建一个新条目；如果存在，会更新其值。
    map[key] = value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}