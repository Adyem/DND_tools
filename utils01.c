#include "dnd_tools.h"

int	ft_check_value(const char *input)
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
			if (sign * check < -2147483648 || sign * check > 2147483647)
				return (1);
			i++;
		}
		else
			return (1);
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
	return ((int)(*string1) - (int)(*string2));
}
