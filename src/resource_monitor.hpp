#include <iostream>
#include <experimental/memory_resource>

using void_ptr = void*;

class resource_monitor : public std::experimental::pmr::memory_resource
{
public:
    explicit resource_monitor() = default;

protected:
    void_ptr do_allocate(std::size_t bytes, std::size_t alignment) override;
    void     do_deallocate(void_ptr p, std::size_t bytes, std::size_t alignment) override;
    bool     do_is_equal(const memory_resource& other) const noexcept override;

private:
    resource_monitor(const resource_monitor&) = delete;
    resource_monitor& operator=(const resource_monitor&) = delete;
};

void_ptr resource_monitor::do_allocate(std::size_t bytes, std::size_t alignment)
{
    std::cout << "[" << this << "]"
              << " allocating " << bytes << " bytes.\n";
    return ::operator new(bytes, std::align_val_t(alignment));
}

void resource_monitor::do_deallocate(void_ptr p, std::size_t bytes, std::size_t alignment)
{
    std::cout << "[" << this << "]"
              << " may deallocate " << bytes << " bytes.\n";
    ::operator delete(p, bytes, std::align_val_t(alignment));
}

bool resource_monitor::do_is_equal(const memory_resource& other) const noexcept
{
    return this == &other;
}