#include "dnd_tools.h"

void	ft_calculate_j(char *string, int *j)
{
	*j = 0;
	while (string[*j] && string[*j] != ')')
		(*j)++;
	return ;
}

static int	ft_command_roll_parse(char *string, int nested)
{
	int error;
	int	i;
	int	j;

	if (DEBUG == 1)
		ft_printf("running ft_command_roll_parse\n");
	i = 0 + nested;
	while (string[i] != '(' && string[i])
		i++;
	if (string[i] == '(')
	{
		error = ft_command_roll_parse(&string[i], 1);
		if (DEBUG == 1)
			ft_printf("The value of error is %i\n", error);
		if (error)
			return (1);
	}
	ft_calculate_j(string, &j);
	i = 0;
	while (i < j)
	{
		error = ft_roll_excecute_droll(string, &i, j);
		if (DEBUG == 1)
			ft_printf("DICE nested=%i i=%i j=%i\n", nested, i,  j);
		if (error)
			return (3);
		i++;
	}
	ft_calculate_j(string, &j);
	i = 0;
	while (i < j)
	{
		error = ft_roll_excecute_md(string, &i, j);
		if (DEBUG == 1)
			ft_printf("MD nested=%i i=%i j=%i\n", nested, i,  j);
		if (error)
			return (4);
		i++;
	}
	ft_calculate_j(string, &j);
	i = 0;
	while (i < j)
	{
		error = ft_roll_excecute_pm(string, &i, j);
		if (DEBUG == 1)
			ft_printf("PM nested=%i i=%i j=%i\n", nested, i,  j);
		if (error)
			return (5);
		i++;
	}
	i = 0;
	if (DEBUG == 1)
		ft_printf("nested is %i\n", nested);
	if (nested)
	{
		if (DEBUG == 1)
			ft_printf("the string before parsing brackets is %s\n", string);
		error = ft_roll_parse_brackets(string);
		if (error)
			return (6);
		i++;
	}
	if (DEBUG == 1)
		ft_printf("%s\n", string);
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
