#include "resource_monitor.hpp"
#include <vector>

int main()
{
    using namespace std::experimental::pmr;
    resource_monitor                             rm;
    std::vector<int, polymorphic_allocator<int>> vec(&rm);

    constexpr int size = 100;
    vec.reserve(size);
    for (int i = 0; i < size; ++i)
        vec.push_back(i);
}