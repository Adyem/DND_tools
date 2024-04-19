#include "dnd_tools.h"

int	ft_roll_excecute_md(char *string, int *i, int j)
{
	char	sign;
	int		result;
	int		first_number;
	int		second_number;
	int		x;

	while(*i < j)
	{
		if (!(string[*i]))
			break ;
		if (string[*i] == '/' || string[*i] == '*')
		{
			sign = string[*i];
			x = *i;
			if (*i > 0)
				(*i)--;
			x++;
			if (DEBUG == 1)
				ft_printf("before calculation the value of x is %i\n", x);
			first_number = ft_roll_convert_previous(string, i);
			second_number = ft_roll_convert_next(string, x);
			if (sign == '/' && second_number != 0)
				result = first_number / second_number;
			else if (sign == '*')
				result = first_number * second_number;
			else
				return (1);
			if (DEBUG == 1)
				ft_printf("result = %i and i=%i\n", result, *i);
			if (ft_roll_itoa(result, i, string))
				return (1);
			if (DEBUG == 1)
				ft_printf("the value of i = %i and x = %i\n", *i, x);
			if (string[x] == '-' || string[x] == '+')
				x++;
			while (string[x] >= '0' && string[x] <= '9')
				x++;
			if (DEBUG == 1)
				ft_printf("the value of i = %i and x = %i\n", *i, x);
			while (string[x])
			{
				if (DEBUG == 1)
					ft_printf("copying over value %c\n" \
						"check 2:the value of i = %i and x = %i\n", string[x], *i, x);
				string[*i] = string[x];
				(*i)++;
				x++;
			}
			string[*i] = '\0';
		}
		(*i)++;
	}
	if (DEBUG == 1)
		ft_printf("after md the result is %s\n", string);
	return (0);
}
