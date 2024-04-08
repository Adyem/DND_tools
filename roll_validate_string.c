#include "dnd_tools.h"

static int	ft_check_open_braces(char *string, int i, int *open_braces)
{
	if (i > 0)
		if (ft_roll_check_character(string[i - 1]))
			return (1);
	if (ft_roll_check_number_next(string, i))
		return (1);
	(*open_braces)++;
	return (0);
}

static int	ft_check_close_braces(char *string, int i,
				int open_braces, int *close_braces)
{
	if (i == 0 || open_braces <= *close_braces)
		return (1);
	if (ft_roll_check_character(string[i + 1]))
		return(1);
	if (ft_roll_check_number_previous(string, i))
		return (1);
	(*close_braces)++;
	return (0);
}

static int	ft_roll_check_arg(string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '+' || string[i] == '-')
			i++;
		else if (string[i] == '/' || string[i] == '*')
			i++;
		else if (string[i] >= '0' || string[i] <= '9')
			i++;
		else if (string[i] == '(' || string[i] ==  ')')
			i++;
		else if (string[i] == 'd')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_command_roll_validate(char *string)
{
	int	open_braces;
	int	close_braces;
	int	i;

	i = 0;
	open_braces = 0;
	close_braces = 0;
	if (ft_roll_check_arg(string))
		return (1);
	while (string[i])
	{
		while (string[i] >= '0' || string[i] <= '9')
			i++;
		if (string[i] == '(')
			if (ft_check_open_braces(string, i, &open_braces))
				return(1);
		else if (string[i] == ')')
			if (ft_check_close_braces(string, i, open_braces, &close_braces))
				return (1);
		else if (string[i] == '-' || string[i] == '+')
		else if (string[i] == '/' || string[i] == '*')
		i++;
	}
	return (0);
}
