#include <experimental/memory_resource>
#include <vector>
#include <iostream>

class resource_monitor : public std::experimental::pmr::memory_resource
{
public:
    explicit resource_monitor() = default;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void  do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool  do_is_equal(const memory_resource& other) const noexcept override;

private:
    resource_monitor(const resource_monitor&) = delete;
    resource_monitor& operator=(const resource_monitor&) = delete;
};

void* resource_monitor::do_allocate(std::size_t bytes, std::size_t alignment)
{
    std::cout << "Allocate " << bytes << " Bytes" << '\n';
    return nullptr;
}

void resource_monitor::do_deallocate(void* p, std::size_t bytes, std::size_t alignment)
{
    std::cout << "Deallocate " << bytes << " Bytes" << '\n';
}

bool resource_monitor::do_is_equal(const memory_resource& other) const noexcept
{
    return this == &other;
}

int main()
{
    resource_monitor                                                     rm;
    std::vector<int, std::experimental::pmr::polymorphic_allocator<int>> vec(&rm);
}