#ifndef SET_UTILS_HPP
# define SET_UTILS_HPP

#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Template/set.hpp"
#include <cstring>

template <typename ValueType>
inline const ValueType    *ft_set_get_raw_data(const ft_set<ValueType> &values)
{
    const ValueType    *pointer;

    pointer = ft_nullptr;
    std::memcpy(&pointer, &values, sizeof(pointer));
    return (pointer);
}

#endif
