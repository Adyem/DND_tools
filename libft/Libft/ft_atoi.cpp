#include "libft.hpp"

int	ft_atoi(const char *string)
{
	int	index = 0;
	int	sign = 1;
	int	result = 0;

	while (string[index] == ' ' || ((string[index] >= '\t')
				&& (string[index] <= '\r')))
		index++;
	if (string[index] == '+' || string[index] == '-')
	{
		if (string[index] == '-')
			sign = -1;
		index++;
	}
	while (string[index] && ((string[index] >= '0')
				&& (string[index] <= '9')))
	{
		result = result * 10 + (string[index] - '0');
		index++;
	}
	return (result * sign);
}
