#include "dnd_tools.h"

typedef int (*RollExecuteFunc)(char *, int *, int);

void	ft_calculate_j(char *string, int *j)
{
	*j = 0;
	while (string[*j] && string[*j] != ')')
		(*j)++;
	if (DEBUG == 1)
		ft_printf("the new value of J is %i\n", *j);
	return ;
}

int execute_roll_function(char *string, RollExecuteFunc func)
{
	int i;
	int	j;
	int error;

	i = 0;
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
	int i;

	i = 0 + nested;
	while (string[i] != '(' && string[i])
		i++;
	if (string[i] == '(')
	{
		error = ft_command_roll_parse(&string[i], 1);
		if (error)
			return 1;
	}
	if (execute_roll_function(string, ft_roll_excecute_droll))
		return (3);
	if (execute_roll_function(string, ft_roll_excecute_md))
		return (4);
	if (execute_roll_function(string, ft_roll_excecute_pm))
		return (5);
	if (DEBUG == 1)
		printf("nested is %i\n", nested);
	if (nested)
	{
		error = ft_roll_parse_brackets(string);
		if (error)
			return 6;
	}
	if (DEBUG == 1 && nested)
		ft_printf("leaving nested braces\n");
	return (0);
}

void	ft_command_roll(char **argv)
{
	char	*result;
	int		i;

	i = 0;
	while (argv[i] && DEBUG == 1)
	{
		ft_printf("%s\n", argv[i]);
		i++;
	}
	if (!argv[1])
		return ;
	result = NULL;
	i = 1;
	while(argv[i])
	{
		result = ft_strjoin_gnl(result, argv[i]);
		if (!result)
		{
			ft_printf_fd(2, "168-Error: Malloc failed ft_strjoin_gnl\n");
			return ;
		}
		i++;
	}
	if (DEBUG == 1)
		ft_printf("%s\n", result);
	if (!result)
		return ;
	if (ft_command_roll_validate(result))
	{
		ft_printf_fd(2, "169-Command Roll Error with the string: %s\n", result);
		free(result);
		return ;
	}
	ft_command_roll_parse(result, 0);
	ft_printf("%s\n", result);
	free(result);
	return ;
}
