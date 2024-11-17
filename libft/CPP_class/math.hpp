#ifndef MATH_HPP
#define MATH_HPP

template <typename T>
const T& max(const T& a, const T& b)
{
    if (a > b)
		return (a);
	return (b);
}

template <typename T, typename Compare>
const T& max(const T& a, const T& b, Compare comp)
{
    if (comp(a, b))
	{
        return (b);
	}
	return (a);
}

#endif
