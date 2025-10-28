#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "libft/Errno/errno.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Math/roll.hpp"
#include "libft/Printf/printf.hpp"

int math_roll_validate(char *string);

static int  ft_contains_uppercase_dice_identifier(const char *expression)
{
    size_t  index;

    if (!expression)
        return (0);
    index = 0;
    while (expression[index] != '\0')
    {
        if (expression[index] == 'D')
            return (1);
        index++;
    }
    return (0);
}

int *ft_command_roll(char **argv)
{
    char    *expression;
    char    *joined;
    int     index;
    int     *value;

    if (!argv || !argv[1])
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        pf_printf_fd(2, "401-Error: Roll command expression is missing\n");
        ft_errno = FT_ERR_INVALID_ARGUMENT;
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
            ft_errno = FT_ERR_NO_MEMORY;
            pf_printf_fd(2,
                "402-Error: Failed to concatenate roll command arguments\n");
            ft_errno = FT_ERR_NO_MEMORY;
            return (ft_nullptr);
        }
        expression = joined;
        index++;
    }
    if (ft_contains_uppercase_dice_identifier(expression))
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        pf_printf_fd(2, "403-Error: Failed to evaluate roll expression: %s\n",
            expression);
        cma_free(expression);
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (ft_nullptr);
    }
    char    *normalized;

    normalized = cma_strdup(expression);
    if (!normalized)
    {
        ft_errno = FT_ERR_NO_MEMORY;
        pf_printf_fd(2, "403-Error: Failed to evaluate roll expression: %s\n",
            expression);
        cma_free(expression);
        ft_errno = FT_ERR_NO_MEMORY;
        return (ft_nullptr);
    }
    ft_to_lower(normalized);
    value = math_roll(normalized);
    cma_free(normalized);
    if (!value)
    {
        int error_code;

        if (ft_errno == ER_SUCCESS)
            ft_errno = FT_ERR_INVALID_ARGUMENT;
        error_code = ft_errno;
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
    int result;
    int final_error;

    if (!expression)
    {
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        pf_printf_fd(2, "404-Error: Roll validation expression is missing\n");
        ft_errno = FT_ERR_INVALID_ARGUMENT;
        return (1);
    }
    result = 0;
    final_error = ER_SUCCESS;
    {
        ft_string   original_expression(expression);

        if (original_expression.get_error() != ER_SUCCESS)
        {
            final_error = FT_ERR_INVALID_ARGUMENT;
            result = 1;
        }
        else if (ft_contains_uppercase_dice_identifier(
                original_expression.c_str()))
        {
            final_error = FT_ERR_INVALID_ARGUMENT;
            pf_printf_fd(2,
                "405-Error: Roll validation failed for expression: %s\n",
                original_expression.c_str());
            result = 1;
        }
        else
        {
            char    *normalized;

            normalized = cma_strdup(expression);
            if (!normalized)
            {
                final_error = FT_ERR_NO_MEMORY;
                pf_printf_fd(2,
                    "405-Error: Roll validation failed for expression: %s\n",
                    expression);
                result = 1;
            }
            else
            {
                int *value;

                ft_to_lower(normalized);
                value = math_roll(normalized);
                cma_free(normalized);
                if (!value)
                {
                    if (ft_errno == ER_SUCCESS)
                        final_error = FT_ERR_INVALID_ARGUMENT;
                    else
                        final_error = ft_errno;
                    pf_printf_fd(2,
                        "405-Error: Roll validation failed for expression: %s\n",
                        original_expression.c_str());
                    result = 1;
                }
                else
                {
                    cma_free(value);
                    final_error = ER_SUCCESS;
                    result = 0;
                }
            }
        }
    }
    ft_errno = final_error;
    return (result);
}
