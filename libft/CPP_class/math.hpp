#ifndef MATH_HPP
# define MATH_HPP

template <typename T>
const T& max(const T& a, const T& b);

template <typename T, typename Compare>
const T& max(const T& a, const T& b, Compare comp);

#endif
