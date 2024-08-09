#include "dnd_tools.h"

int	ft_roll_parse_brackets(char *string, int *i, int j)
{
	int	x;

	if (DEBUG == 1)
		ft_printf("parsing brackets %s i=%i j=%i\n", string, *i, j);
	while (*i < j)
	{
		x = *i;
		if (string && string[*i] == '(')
			(*i)++;
		if (string)
		{
			while (string && string[*i] != ')')
			{
				string[x] = string[x + 1];
				x++;
			}
			if (string[x + 1] && string[x + 1] == ')')
			{
				while (string[x + 2] && string[x + 2])
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
