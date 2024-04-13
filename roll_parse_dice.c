#include "dnd_tools.h"

int	ft_roll_excecute_droll(char *string, int *i, int j)
{
	char	*test;
	int		result;
	int		first_number;
	int		second_number;
	int 	x;

	while(*i < j)
	{
		if (!(string[*i]))
			break ;
		if (string[*i] == 'd')
		{
			x = *i;
			if (*i > 0)
				(*i)--;
			x++;
			if (string[*i] >='0' && string[*i] <= '9')
			{
				while (*i > 0)
				{
					if (string[*i] >= '0' && string[*i] <= '9')
						(*i)--;
					else
						break ;
				}
				if (string[*i] < '0' || string[*i] > '9')
					(*i)++;
				first_number = ft_atoi(&string[*i]);
			}
			else
				first_number = 1;
			if (string[x] >= '0' && string[x] <= '9')
				second_number = ft_atoi(&string[x]);
			else
				return (1);
			if (first_number <= 0 || second_number <= 0)
				return (1);
			result = ft_dice_roll(first_number, second_number);
			if (!result)
				return (1);
			test = ft_roll_itoa(result, i, string);
			if (!test)
				return (1);
			while (string[x] >= '0' && string[x] <= '9')
				x++;
			while (string[x])
			{
				string[*i] = string[x];
				(*i)++;
				x++;
			}
			string[*i] = '\0';
		}
		(*i)++;
	}
	if (DEBUG == 1)
		ft_printf("%s\n", string);
	return (0);
}
