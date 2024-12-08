#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>

int	ft_readline_confirm(const char *message)
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

int ft_readline_spell_level(const char *message)
{
	char	*input;
	int		invalid_input_amount = 0;
	int		return_value;

	while (1)
	{
		input = rl_readline(message);
		if (!input)
			return (-1);
		if (ft_check_value(input))
		{
			pf_printf_fd(2, "Invalid input\n");
			invalid_input_amount++;
			if (invalid_input_amount >= 5)
				return (-1);
			continue ;
		}
		return_value = atoi(input);
		cma_free(input);
		if (return_value < 1 || return_value > 9)
		{
			pf_printf_fd(2, "Invalid input\n");
			invalid_input_amount++;
			if (invalid_input_amount >= 5)
				return (-1);
			continue ;
		}
		break ;
	}
	return (return_value);
}
