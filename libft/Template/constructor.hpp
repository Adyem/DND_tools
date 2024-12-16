#ifndef CONSTRUCTOR_HPP
#define CONSTRUCTOR_HPP

#include <type_traits>
#include <utility> // For std::forward
#include <new>     // For placement new

template <typename Type, typename Arg>
void construct_at(Type* destination, Arg&& source)
{
    if constexpr (!std::is_trivially_constructible_v<Type, Arg&&>)
        new (destination) Type(std::forward<Arg>(source)); // Correctly recognized as placement new
    else
        *destination = std::forward<Arg>(source);
}

template <typename Type>
void construct_default_at(Type* destination)
{
    if constexpr (!std::is_trivially_constructible_v<Type>)
        new (destination) Type(); // Correctly recognized as placement new
    else
        *destination = Type();
}

template <typename Type>
void destroy_at(Type* object)
{
    if constexpr (!std::is_trivially_destructible_v<Type>)
        object->~Type();
}

#endif
