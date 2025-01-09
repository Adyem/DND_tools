#ifndef MATH_HPP
#define MATH_HPP

#include <type_traits>
#include <cstddef>
#include <type_traits>

template <typename T>
const T& ft_max(const T& a, const T& b)
{
    if (a > b)
		return (a);
	return (b);
}

template <typename T, typename Compare>
const T& ft_max(const T& a, const T& b, Compare comp)
{
	if (comp(a, b))
        return (b);
	return (a);
}

template <typename T>
const T& ft_min(const T& a, const T& b)
{
    if (a < b)
		return (a);
	return (b);
}

template <typename T, typename Compare>
const T& ft_min(const T& a, const T& b, Compare comp)
{
	if (comp(a, b))
        return (b);
	return (a);
}

template <typename... Args>
struct is_single_convertible_to_size_t : std::false_type {};

template <typename Arg>
struct is_single_convertible_to_size_t<Arg> : std::is_convertible<std::decay_t<Arg>, size_t> {};

#endif
