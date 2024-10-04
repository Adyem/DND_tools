#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>

int	ft_read_line_confirm(const char *message)
{
	char	*input;

	while ((input = readline(message)) != nullptr)
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
	ft_printf_fd(2, "116-Error: read line memory allocation failed\n");
	return (-1);
}
