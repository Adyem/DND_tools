#include "dnd_tools.h"

int	ft_read_line_confirm(char *message)
{
	char	*input;

	while ((input = readline(message)) != NULL)
	{
		if (*input)
			add_history(input);
		if ((ft_strcmp_dnd(input, "y") == 0) || (ft_strcmp_dnd(input, "Y") == 0) ||
				(ft_strcmp_dnd(input, "yes") == 0))
		{
			free(input);
			return (0);
		}
		else if ((ft_strcmp_dnd(input, "n") == 0) || (ft_strcmp_dnd(input, "N") == 0) ||
				(ft_strcmp_dnd(input, "no") == 0))
		{
			free(input);
			return (1);
		}
	}
	return (-1);
}
