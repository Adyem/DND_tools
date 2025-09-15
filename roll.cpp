#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

typedef int (*RollExecuteFunc)(char *, int *, int);

void ft_calculate_j(char *string, int *j)
{
    *j = 0;
    while (string[*j] && string[*j] != ')')
        (*j)++;
    if (DEBUG == 1)
        pf_printf("The new value of J is %d\n", *j);
    return ;
}

static int execute_roll_function(char *string, RollExecuteFunc func)
{
    int currentIndex = 0;
    int stringBoundary;
    int error;

    error = 0;
    ft_calculate_j(string, &stringBoundary);
    while (currentIndex < stringBoundary)
    {
        error = func(string, &currentIndex, stringBoundary);
        if (error)
            return (error);
        ft_calculate_j(string, &stringBoundary);
        currentIndex++;
    }
    return (0);
}

static int ft_command_roll_parse(char *string, int nested)
{
    int error;
    int index = nested;

    while (string[index] != '(' && string[index])
        index++;
    if (string[index] == '(')
    {
        error = ft_command_roll_parse(&string[index], 1);
        if (error)
            return (1);
    }
    if (execute_roll_function(string, ft_roll_excecute_droll))
        return 3;
    if (execute_roll_function(string, ft_roll_excecute_md))
        return 4;
    if (execute_roll_function(string, ft_roll_excecute_pm))
        return 5;
    if (DEBUG == 1)
        pf_printf("Nested is %d\n", nested);
    if (nested)
    {
        error = ft_roll_parse_brackets(string);
        if (error)
            return (6);
    }
    if (DEBUG == 1 && nested)
        pf_printf("Leaving nested braces\n");
    return (0);
}

void ft_command_roll(char **argv)
{
    char    *result = ft_nullptr;
    int        index = 0;

    while (argv[index] && DEBUG == 1)
    {
        pf_printf("%s\n", argv[index]);
        index++;
    }
    if (!argv[1])
        return ;
    index = 1;
    while (argv[index])
    {
        result = ft_strjoin_gnl(result, argv[index]);
        if (!result)
        {
            pf_printf_fd(2, "168-Error: Malloc failed in ft_strjoin_gnl\n");
            return ;
        }
        index++;
    }
    if (DEBUG == 1)
        pf_printf("%s\n", result);
    if (!result)
        return ;
    if (ft_command_roll_validate(result))
    {
        pf_printf_fd(2, "169-Command Roll Error with the string: %s\n", result);
        cma_free(result);
        return ;
    }
    ft_command_roll_parse(result, 0);
    pf_printf("%s\n", result);
    cma_free(result);
    return ;
}
