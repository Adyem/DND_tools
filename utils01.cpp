#include "dnd_tools.hpp"

int	ft_check_value(const char *input)
{
	long	number = 0;
	int		index = 0;
	int		sign = 1;

	if (input[index] == '+' || input[index] == '-')
		index++;
	if (!input[index])
		return (1);
	if (input[0] == '-')
		sign = -1;
	while (input[index])
	{
		if (input[index] >= '0' && input[index] <= '9')
		{
			number = (number * 10) + input[index] - '0';
			if (sign * number < -2147483648 || sign * number > 2147483647)
				return (2);
			index++;
		}
		else
			return (3);
	}
	return (0);
}

int	ft_strcmp_dnd(const char *string1, const char *string2)
{
	if (!string1 || !string2)
		return (-1);
	while (*string1 && (*string1) == (*string2))
	{
		string1++;
		string2++;
	}
	return (static_cast<int>(*string1) - static_cast<int>(*string2));
}
