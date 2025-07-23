#include "libft/Libft/libft.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/RNG/dice_roll.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>

int	ft_readline_confirm(const char *message)
{
	char	*input;

	if (g_dnd_test == true)
		return (ft_dice_roll(1, 2) - 1);
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

int     ft_readline_check_succes_or_fail(const char *message)
{
        char    *input;

        if (g_dnd_test == true)
                return (ft_dice_roll(1, 4));
        while ((input = rl_readline(message)) != ft_nullptr)
        {
                if ((ft_strcmp_dnd(input, "crit succes") == 0)
                        || (ft_strcmp_dnd(input, "crit success") == 0))
                {
                        cma_free(input);
                        return (RL_CRIT_SUCCES);
                }
                else if ((ft_strcmp_dnd(input, "succes") == 0)
                        || (ft_strcmp_dnd(input, "success") == 0))
                {
                        cma_free(input);
                        return (RL_SUCCES);
                }
                else if ((ft_strcmp_dnd(input, "crit fail") == 0)
                        || (ft_strcmp_dnd(input, "critical fail") == 0))
                {
                        cma_free(input);
                        return (RL_CRIT_FAIL);
                }
                else if ((ft_strcmp_dnd(input, "fail") == 0)
                        || (ft_strcmp_dnd(input, "failure") == 0))
                {
                        cma_free(input);
                        return (RL_FAIL);
                }
        }
        pf_printf_fd(2, "116-Error: read line memory allocation failed\n");
        return (-1);
}

static int ft_check_spell_slots(int spell_level, t_char * character)
{
	if (spell_level == 1 && character->spell_slots.level_1.available == 0)
		return (-1);
	else if (spell_level == 2 && character->spell_slots.level_2.available == 0)
		return (-1);
	else if (spell_level == 3 && character->spell_slots.level_3.available == 0)
		return (-1);
	else if (spell_level == 4 && character->spell_slots.level_4.available == 0)
		return (-1);
	else if (spell_level == 5 && character->spell_slots.level_5.available == 0)
		return (-1);
	else if (spell_level == 6 && character->spell_slots.level_6.available == 0)
		return (-1);
	else if (spell_level == 7 && character->spell_slots.level_7.available == 0)
		return (-1);
	else if (spell_level == 8 && character->spell_slots.level_8.available == 0)
		return (-1);
	else if (spell_level == 9 && character->spell_slots.level_9.available == 0)
		return (-1);
	return (0);
}

int ft_readline_spell_level(const char *message, t_char * character,
								int *invalid_input_amount)
{
	char	*input;
	int		spell_level;

	while (1)
	{
		input = rl_readline(message);
		if (!input)
			return (-1);
		if (ft_strcmp_dnd("exit", input) == 0)
			return (-1);
		if (ft_check_value(input))
		{
			pf_printf_fd(2, "Invalid input\n");
			(*invalid_input_amount)++;
			if (*invalid_input_amount >= 5)
				return (-1);
			continue ;
		}
		spell_level = ft_atoi(input);
		cma_free(input);
		input = ft_nullptr;
		if (spell_level < 1 || spell_level > 9)
		{
			pf_printf_fd(2, "Invalid input\n");
			(*invalid_input_amount)++;
			if (*invalid_input_amount >= 5)
				return (-1);
			continue ;
		}
		if (ft_check_spell_slots(spell_level, character) == -1)
		{
			pf_printf_fd(2, "No spell slots left at level %i\n", spell_level);
			(*invalid_input_amount)++;
			if (*invalid_input_amount >= 5)
				return (-1);
			continue ;
		}
		break ;
	}
	return (spell_level);
}
