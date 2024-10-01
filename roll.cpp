#include "dnd_tools.hpp"
#include "libft/get_next_line/get_next_line.hpp"
#include <iostream>

typedef int (*RollExecuteFunc)(char *, int *, int);

void ft_calculate_j(char *string, int *j)
{
    *j = 0;
	while (string[*j] && string[*j] != ')')
		(*j)++;
	if (DEBUG == 1)
		std::cout << "The new value of J is " << *j << std::endl;
	return ;
}

int execute_roll_function(char *string, RollExecuteFunc func)
{
    int i = 0;
    int j;
    int error;

    error = 0;
    ft_calculate_j(string, &j);
    while (i < j)
    {
        error = func(string, &i, j);
        if (error)
            return (error);
        ft_calculate_j(string, &j);
        i++;
    }
    return (0);
}

int ft_command_roll_parse(char *string, int nested)
{
    int error;
    int i = nested;

    while (string[i] != '(' && string[i])
        i++;
    if (string[i] == '(')
    {
        error = ft_command_roll_parse(&string[i], 1);
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
        std::cout << "Nested is " << nested << std::endl;
    if (nested)
    {
        error = ft_roll_parse_brackets(string);
        if (error)
            return (6);
    }
    if (DEBUG == 1 && nested)
        std::cout << "Leaving nested braces" << std::endl;
    return (0);
}

void ft_command_roll(char **argv)
{
    char	*result = nullptr;
    int		i = 0;

    while (argv[i] && DEBUG == 1)
    {
        std::cout << argv[i] << std::endl;
        i++;
    }
    if (!argv[1])
        return ;
    i = 1;
    while (argv[i])
    {
        result = ft_strjoin_gnl_old(result, argv[i]);
        if (!result)
        {
            std::cerr << "168-Error: Malloc failed in ft_strjoin_gnl" << std::endl;
            return ;
        }
        i++;
    }
    if (DEBUG == 1)
        std::cout << result << std::endl;
    if (!result)
        return ;
    if (ft_command_roll_validate(result))
    {
        std::cerr << "169-Command Roll Error with the string: " << result << std::endl;
        free(result);
        return ;
    }
    ft_command_roll_parse(result, 0);
    std::cout << result << std::endl;
    free(result);
	return ;
}
