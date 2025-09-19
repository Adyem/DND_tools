#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

char *ft_strtrim_prefix(const char *s1, const char *prefix)
{
    size_t prefix_len;
    size_t s1_len;
    char *trimmed_str;

    if (!s1 || !prefix)
        return (ft_nullptr);
    prefix_len = ft_strlen_size_t(prefix);
    s1_len = ft_strlen_size_t(s1);
    if (prefix_len <= s1_len && ft_strncmp(s1, prefix, prefix_len) == 0)
    {
        trimmed_str = cma_strdup(s1 + prefix_len);
        if (!trimmed_str)
            return (ft_nullptr);
        return (trimmed_str);
    }
    trimmed_str = cma_strdup(s1);
    if (!trimmed_str)
        return (ft_nullptr);
    return (trimmed_str);
}
