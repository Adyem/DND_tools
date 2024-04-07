#include "dnd_tools.h"

static int	ft_roll_check(char c)
{
	if (c == '-' || c == '+')
		return (0);
	else if (c == '/' || c == '*')
		return (0);
	else if (c == 'd')
		return (0);
	else if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	ft_command_roll_validate(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_roll_check(string[i]))
			return (1);
		i++;
	}
	return (0);
}
