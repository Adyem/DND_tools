#ifndef SET_UTILS_HPP
# define SET_UTILS_HPP

#include "libft/Modules/CPP_class/class_nullptr.hpp"
#include "libft/Modules/Basic/basic.hpp"
#include "libft/Modules/Template/set.hpp"

template <typename ValueType>
inline const ValueType    *ft_set_get_raw_data(const ft_set<ValueType> &values)
{
    const ValueType    *pointer;

    pointer = ft_nullptr;
    ft_memcpy(&pointer, &values, sizeof(pointer));
    return (pointer);
}

#endif
