#include <cstddef>
#include <new>
#include "../CMA/CMA.hpp"

void* operator new(std::size_t size)
{
    void *pointer = cma_malloc(size);
	if (!pointer)
		throw std::bad_alloc();
	return (pointer);
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return (cma_malloc(size));
}

void operator delete(void* ptr) noexcept
{
    cma_free(ptr);
	return ;
}

void operator delete(void* ptr, std::size_t) noexcept
{
    cma_free(ptr);
	return ;
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept
{
    cma_free(ptr);
	return ;
}

void* operator new[](std::size_t size)
{
    void *pointer = cma_malloc(size);
	if (!pointer)
		throw std::bad_alloc();
	return (pointer);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return (cma_malloc(size));
}

void operator delete[](void* ptr) noexcept
{
    cma_free(ptr);
	return ;
}

void operator delete[](void* ptr, std::size_t) noexcept
{
    cma_free(ptr);
	return ;
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept
{
    cma_free(ptr);
	return ;
}

void* operator new(std::size_t size, std::align_val_t align)
{
	(void)align;
    void* pointer = cma_malloc(size);
    if (!pointer)
        throw std::bad_alloc();
    return (pointer);
}

void operator delete(void* ptr, std::align_val_t) noexcept
{
    cma_free(ptr);
	return ;
}

void* operator new[](std::size_t size, std::align_val_t align)
{
	(void)align;
    void* pointer = cma_malloc(size);
    if (!pointer)
        throw std::bad_alloc();
    return (pointer);
}

void operator delete[](void* ptr, std::align_val_t) noexcept
{
    cma_free(ptr);
	return ;
}
