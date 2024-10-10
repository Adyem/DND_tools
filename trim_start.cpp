#include "dnd_tools.hpp"
#include <cstdlib>
#include <cstring>
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"

static size_t str_len(const char *str)
{
    size_t i = 0;

    while (str[i])
        i++;
    return (i);
}

static char *str_new(size_t n)
{
    char *str = (char *)cma_malloc(sizeof(char) * (n + 1), false);

    if (!str)
        return (nullptr);
    for (size_t i = 0; i <= n; i++)
        str[i] = '\0';
    return (str);
}

char *ft_strtrim_prefix(const char *s1, const char *prefix)
{
    size_t prefix_len;
    size_t s1_len;
    char *trimmed_str;

    if (!s1 || !prefix)
        return (nullptr);
    prefix_len = str_len(prefix);
    s1_len = str_len(s1);

    if (ft_strncmp(s1, prefix, prefix_len) == 0)
    {
        trimmed_str = str_new(s1_len - prefix_len);
        if (!trimmed_str)
            return (nullptr);
        strcpy(trimmed_str, s1 + prefix_len);
    }
    else
    {
        trimmed_str = str_new(s1_len);
        if (!trimmed_str)
            return (nullptr);
        strcpy(trimmed_str, s1);
    }
    return (trimmed_str);
}
