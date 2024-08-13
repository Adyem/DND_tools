#include "dnd_tools.h"

typedef int (*RollExecuteFunc)(char *, int *, int);

void	ft_calculate_j(char *string, int *j)
{
	*j = 0;
	while (string[*j] && string[*j] != ')')
		(*j)++;
	return ;
}

int execute_roll_function(char *string, RollExecuteFunc func, const char *debug_tag, int nested)
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
		if (DEBUG == 1)
			printf("%s nested=%i i=%i j=%i\n", debug_tag, nested, i, j);
		if (error)
			return error;
		i++;
	}
	return (0);
}

int ft_command_roll_parse(char *string, int nested)
{
	int error;
	int i;

	if (DEBUG == 1)
		printf("running ft_command_roll_parse\n");
	i = 0 + nested;
	while (string[i] != '(' && string[i])
		i++;
	if (string[i] == '(')
	{
		error = ft_command_roll_parse(&string[i], 1);
		if (DEBUG == 1)
			printf("The value of error is %i\n", error);
		if (error)
			return 1;
	}
	error = execute_roll_function(string, ft_roll_excecute_droll, "DICE", nested);
	if (error)
		return (3);
	error = execute_roll_function(string, ft_roll_excecute_md, "MD", nested);
	if (error)
		return (4);
	error = execute_roll_function(string, ft_roll_excecute_pm, "PM", nested);
	if (error)
		return (5);
	if (DEBUG == 1)
		printf("nested is %i\n", nested);
	if (nested)
	{
		if (DEBUG == 1)
			printf("the string before parsing brackets is %s\n", string);
		error = ft_roll_parse_brackets(string);
		if (error)
			return 6;
	}
	if (DEBUG == 1)
		printf("%s\n", string);
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
			return ;
		i++;
	}
	if (DEBUG == 1)
		ft_printf("%s\n", result);
	if (!result)
		return ;
	if (ft_command_roll_validate(result))
	{
		ft_printf_fd(2, "Roll error with the string: %s\n", result);
		return ;
	}
	ft_command_roll_parse(result, 0);
	ft_printf("%s\n", result);
	free(result);
	return ;
}
