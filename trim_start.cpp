#include "dnd_tools.hpp"
#include <cstdlib>
#include <cstring>
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CPP_class/nullptr.hpp"

static size_t str_len(const char *str)
{
    size_t i = 0;

    while (str[i])
        i++;
    return (i);
}

static char *str_new(size_t n)
{
    char *str = (char *)cma_malloc(sizeof(char) * (n + 1));

	if (!str)
		return (ft_nullptr);
	size_t index = 0;
    while (index <= n)
	{
        str[index] = '\0';
		index++;
	}
    return (str);
}

char *ft_strtrim_prefix(const char *s1, const char *prefix)
{
    size_t prefix_len;
    size_t s1_len;
    char *trimmed_str;

    if (!s1 || !prefix)
        return (ft_nullptr);
    prefix_len = str_len(prefix);
    s1_len = str_len(s1);

    if (ft_strncmp(s1, prefix, prefix_len) == 0)
    {
        trimmed_str = str_new(s1_len - prefix_len);
        if (!trimmed_str)
            return (ft_nullptr);
        strcpy(trimmed_str, s1 + prefix_len);
    }
    else
    {
        trimmed_str = str_new(s1_len);
        if (!trimmed_str)
            return (ft_nullptr);
        strcpy(trimmed_str, s1);
    }
    return (trimmed_str);
}
