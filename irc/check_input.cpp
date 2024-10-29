#include <cstdlib>
#include "irc.hpp"

static int	ft_check_value(const char *input)
{
	long	check;
	int		i;
	int		sign;

	check = 0;
	i = 0;
	sign = 1;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (!input[i])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			check = (check * 10) + input[i] - '0';
			if (sign * check < 1 || sign * check > 65535)
				return (2);
			i++;
		}
		else
			return (3);
	}
	return (0);
}

int	ft_check_input(char *input)
{
	if (ft_check_value(input))
		return (-1);
	return (atoi(input));
}
