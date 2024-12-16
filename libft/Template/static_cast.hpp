#ifndef STATIC_CAST_HPP
#define STATIC_CAST_HPP

#include <type_traits>
#include <utility>

template <typename Target, typename Source>
Target* static_cast_or_construct(Source&& source)
{
    if constexpr (std::is_constructible<Target, Source>::value)
        return (static_cast<Target*>(std::forward<Source>(source)));
    else if constexpr (std::is_default_constructible<Target>::value)
        return (new (source) Target());
    else
        static_assert(std::is_constructible<Target, Source>::value ||
                      std::is_default_constructible<Target>::value,
                      "Target type must be either constructible from Source or default constructible");
}

#endif
