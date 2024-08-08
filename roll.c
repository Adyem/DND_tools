#include "dnd_tools.h"

static void	ft_command_roll_parse(char *string, int nested)
{
	int error;
	int	i;
	int	j;

	if (DEBUG == 1)
		ft_printf("running ft_command_roll_parse\n");
	j = 0;
	i = 0 + nested;
	while (string[i] != '(' && string[i])
		i++;
	if (string[i] == '(')
		ft_command_roll_parse(&string[i], 1);
	else if (string[i] == ')' && nested == 0)
		return ;
	else if (!string[i] && nested == 1)
		return ;
	else if (string[i] == ')' && nested == 1)
		j = i;
	while (string[j] && string[j] != ')')
		j++;
	i = 0;
	if (DEBUG == 1)
		ft_printf("j = %i\n", j);
	while (i < j)
	{
		error = ft_roll_excecute_droll(string, &i, j);
		if (error)
			return ;
		i++;
	}
	i = 0;
	while (i < j)
	{
		error = ft_roll_excecute_md(string, &i, j);
		if (error)
			return ;
		i++;
	}
	i = 0;
	while (i < j)
	{
		error = ft_roll_excecute_pm(string, &i, j);
		if (error)
			return ;
		i++;
	}
	i = 0;
	while (i < j)
	{
		error = ft_roll_parse_brackets(string - nested, &i, j);
		if (error)
			return ;
		i++;
	}
	if (DEBUG == 1)
		ft_printf("%s\n", string);
	return ;
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
