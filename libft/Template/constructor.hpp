#ifndef CONSTRUCTOR_HPP
# define CONSTRUCTOR_HPP

#include <type_traits>

template <typename T>
void construct_at(T* p, const T& value)
{
    if constexpr (!std::is_trivially_constructible_v<T>)
        new (p) T(value);
    else
        *p = value;
}

template <typename T>
void construct_default_at(T* p)
{
    if constexpr (!std::is_trivially_constructible_v<T>)
        new (p) T();
    else
        *p = T();
}

template <typename T>
void destroy_at(T* p)
{
	if constexpr (!std::is_trivially_destructible_v<T>)
        p->~T();
}

#endif
