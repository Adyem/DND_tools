#include "dnd_tools.hpp"

int	ft_roll_check_number_next(char *string, int i)
{
	if (!(string[i + 1] == '+' || string[i + 1] == '-' ||
			(string[i + 1] >= '0' && string[i + 1] <= '9')))
		return (1);
	if (string[i + 1] == '+' || string[i + 1] == '-')
		if (!(string[i + 2] >= '0' && string[i + 2] <= '9'))
			return (1);
	return (0);
}

int	ft_roll_check_number_previous(char *string, int i)
{
	if (i == 1)
		if (!(string[i - 1] >= '0' && string[i - 1] <= '9'))
			return (1);
	return (0);
}

int	ft_roll_check_character(char c)
{
	if (c == 0)
		return (0);
	if (c == '-' || c == '+' || c == '/' || c == '*')
		return (0);
	return (1);
}
