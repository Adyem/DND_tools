#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Math/roll.hpp"

int *ft_command_roll(char **argv)
{
    char    *expression;
    char    *joined;
    int     index;
    int     *value;

    if (!argv || !argv[1])
    {
        ft_errno = FT_EINVAL;
        return (ft_nullptr);
    }
    expression = ft_nullptr;
    index = 1;
    while (argv[index])
    {
        joined = ft_strjoin_gnl(expression, argv[index]);
        if (!joined)
        {
            if (expression)
                cma_free(expression);
            ft_errno = FT_EALLOC;
            return (ft_nullptr);
        }
        expression = joined;
        index++;
    }
    value = math_roll(expression);
    cma_free(expression);
    if (!value)
        return (ft_nullptr);
    ft_errno = ER_SUCCESS;
    return (value);
}
