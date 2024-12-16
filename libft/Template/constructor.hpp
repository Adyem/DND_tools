#ifndef CONSTRUCTOR_HPP
#define CONSTRUCTOR_HPP

#include <type_traits>
#include <utility>
#include <new>

constexpr auto* placement_new_ref = static_cast<void* (*)(std::size_t, void*)>(&::operator new);

template <typename Type, typename Arg>
void construct_at(Type* destination, Arg&& source)
{
	if constexpr (!std::is_trivially_constructible_v<Type, Arg&&>)
        ::new (destination) Type(std::forward<Arg>(source));
	else
        *destination = std::forward<Arg>(source);
	return ;
}

template <typename Type>
void construct_default_at(Type* destination)
{
	if constexpr (!std::is_trivially_constructible_v<Type>)
        ::new (destination) Type();
	else
        *destination = Type();
	return ;
}

template <typename Type>
void destroy_at(Type* object)
{
	if constexpr (!std::is_trivially_destructible_v<Type>)
        object->~Type();
	return ;
}

#endif
