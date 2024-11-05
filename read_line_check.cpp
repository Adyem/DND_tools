#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>

int	ft_read_line_confirm(const char *message)
{
	char	*input;

	while ((input = rl_readline(message)) != ft_nullptr)
	{
		if ((ft_strcmp_dnd(input, "y") == 0) || (ft_strcmp_dnd(input, "Y") == 0) ||
				(ft_strcmp_dnd(input, "yes") == 0))
		{
			cma_free(input);
			return (0);
		}
		else if ((ft_strcmp_dnd(input, "n") == 0) || (ft_strcmp_dnd(input, "N") == 0) ||
				(ft_strcmp_dnd(input, "no") == 0))
		{
			cma_free(input);
			return (1);
		}
	}
	pf_printf_fd(2, "116-Error: read line memory allocation failed\n");
	return (-1);
}
