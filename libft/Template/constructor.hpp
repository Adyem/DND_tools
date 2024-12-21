#ifndef CONSTRUCTOR_HPP
#define CONSTRUCTOR_HPP

#include <type_traits>
#include <utility>
#include <new>

constexpr auto* placement_new_ref = static_cast<void* (*)(std::size_t, void*)>(&::operator new);

template <typename T, typename... Args>
T* construct_at(T* destination, Args&&... args)
{
    if constexpr (std::is_trivially_constructible_v<T, Args...>)
        *destination = T(std::forward<Args>(args)...);
    else
        ::new (static_cast<void*>(destination)) T(std::forward<Args>(args)...);
    return (destination);
}

template <typename T>
T* construct_default_at(T* destination)
{
    if constexpr (std::is_trivially_default_constructible_v<T>)
        *destination = T();
    else
        ::new (static_cast<void*>(destination)) T();
    return (destination);
}

template <typename T>
void destroy_at(T* object)
{
	if constexpr (!std::is_trivially_destructible_v<T>)
        object->~T();
	return ;
}

#endif
