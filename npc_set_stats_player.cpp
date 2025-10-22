#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"

int    ft_set_stat_player(size_t key_len, const char **field, const char *content)
{
    size_t        content_len;
    const char    *previous_value;
    char          *duplicate;

    content_len = ft_strlen(content);
    if (content_len < key_len)
    {
        pf_printf_fd(2, "Error: Content is shorter than key!\n");
        return (-1);
    }
    previous_value = *field;
    duplicate = cma_strdup(&content[key_len]);
    if (!duplicate)
        return (-1);
    if (ft_check_player_entry(duplicate))
    {
        cma_free(duplicate);
        return (-1);
    }
    if (previous_value)
        cma_free(const_cast<char *>(previous_value));
    *field = duplicate;
    return (0);
}
