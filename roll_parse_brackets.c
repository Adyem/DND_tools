#include "dnd_tools.h"

int	ft_roll_parse_brackets(char *string, int *i, int j)
{
	int	x;

	while (*i < j)
	{
		x = *i;
		if (string && string[*i] == '(')
			(*i)++;
		while (string && (string[*i] >= '0' && string[*i] <= '9'))
			(*i)++;
		if (string && string[*i] == ')')
		{
			while (string && string[*i] != ')')
				string[x] = string[x + 1];
			if (string && string[x + 1] == ')')
			{
				while (string && string[x + 2])
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
