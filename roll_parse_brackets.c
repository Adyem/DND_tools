#include "dnd_tools.h"

int	ft_roll_parse_brackets(char *string, int *i, int j)
{
	int	x;

	while (*i < j)
	{
		x = *i;
		if (string[*i] == '(')
			i++;
		while (string[*i] >= '0' && string[*i] <= '9')
			i++;
		if (string[*i] == ')')
		{
			while (string[*i] != ')')
				string[x] = string[x + 1];
			if (string[x + 1] == ')')
			{
				while (string[x + 2])
				{
					string[x] = string[x + 2];
					x++;
				}
			}
		}
		(*i)++;
	}
	return (0);
}
