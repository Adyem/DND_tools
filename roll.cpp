#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Math/roll.hpp"
#include "libft/Printf/printf.hpp"

int math_roll_validate(char *string);

int *ft_command_roll(char **argv)
{
    char    *expression;
    char    *joined;
    int     index;
    int     *value;

    if (!argv || !argv[1])
    {
        ft_errno = FT_EINVAL;
        pf_printf_fd(2, "401-Error: Roll command expression is missing\n");
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
            pf_printf_fd(2,
                "402-Error: Failed to concatenate roll command arguments\n");
            ft_errno = FT_EALLOC;
            return (ft_nullptr);
        }
        expression = joined;
        index++;
    }
    value = math_roll(expression);
    if (!value)
    {
        if (ft_errno == ER_SUCCESS)
            ft_errno = FT_EINVAL;
        int error_code = ft_errno;

        pf_printf_fd(2, "403-Error: Failed to evaluate roll expression: %s\n",
            expression);
        cma_free(expression);
        ft_errno = error_code;
        return (ft_nullptr);
    }
    cma_free(expression);
    ft_errno = ER_SUCCESS;
    return (value);
}

int ft_command_roll_validate(char *expression)
{
    int validation_result;

    if (!expression)
    {
        ft_errno = FT_EINVAL;
        pf_printf_fd(2, "404-Error: Roll validation expression is missing\n");
        ft_errno = FT_EINVAL;
        return (1);
    }
    validation_result = math_roll_validate(expression);
    if (validation_result == 0)
    {
        ft_errno = ER_SUCCESS;
        return (0);
    }
    ft_errno = FT_EINVAL;
    pf_printf_fd(2, "405-Error: Roll validation failed for expression: %s\n",
        expression);
    ft_errno = FT_EINVAL;
    return (validation_result);
}
