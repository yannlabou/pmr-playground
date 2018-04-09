#include <experimental/memory_resource>

class resource_monitor : public std::experimental::pmr::memory_resource
{
public:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void  do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool  do_is_equal(const memory_resource& other) const noexcept override;
};

int main() {}