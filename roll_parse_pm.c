#include "dnd_tools.h"

int ft_roll_excecute_pm(char *string, int *i, int j)
{
    int error;

	if (DEBUG == 1)
		ft_printf("CHECKING PM\n");
	error = 0;
    while (*i < j)
    {
        if (DEBUG == 1)
            ft_printf("PM i=%i and j=%i\n", *i, j);
        if (!string[*i] || string[*i] == ')')
            break ;
		if (string[*i] == '+' || string[*i] == '-')
		{
			if (ft_process_sign(string, i, j, &error))
				return (1);
			ft_calculate_j(string, &j);
			(*i) = 0;
		}
		else
			(*i)++;
    }
	ft_calculate_j(string, &j);
    if (DEBUG == 1)
        ft_printf("the result after pm is %s\n", string);
    return (0);
}
