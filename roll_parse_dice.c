#include "dnd_tools.h"

int	ft_roll_excecute_droll(char *string, int *i, int j)
{
	int	result;
	int	first_number;
	int	second_number;
	int x;

	while(*i < j)
	{
		if (!(string[*i]))
			break ;
		if (string[*i] == 'd')
		{
			x = *i;
			(*i)--;
			x++;
			if (string[*i] >='0' && string[*i] <= '9')
			{
				while (string[*i] >= '0' && string[*i] <= '9')
					(*i)--;
				(*i)++;
				first_number = ft_atoi(&string[*i]);
			}
			else
				first_number = 1;
			if (string[x] >= '0' && string[x] <= '9')
				second_number = ft_atoi(&string[x]);
			else
				return (1);
			result = ft_dice_roll(first_number, second_number);
			if (!result)
				return (1);
			while (result)
			{
				string[*i] = result % 10 + '0';
				result = result / 10;
				(*i)++;
			}
			while (string[x] >= '0' && string[x] <= '9')
				x++;
			while (string[x])
			{
				string[*i] = string[x];
				(*i)++;
				x++;
			}
			while (string[*i])
			{
				string[*i] = '\0';
				(*i)++;
			}
		}
		(*i)++;
	}
	return (0);
}