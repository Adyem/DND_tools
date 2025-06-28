#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cstdlib>

static char	**ft_parse_input(char *input_string)
{
	char **input;

	input = cma_split(input_string, ' ');
	if (!input)
	{
		cma_free(input_string);
		pf_printf_fd(2, "006-Error splitting input\n");
	}
	return (input);
}

static int ft_handle_custom_commands(char **input, int argc, t_name *name)
{
	t_name *temp;

	temp = name;
	while (temp != ft_nullptr)
	{
		if (argc > 0 && ft_strcmp_dnd(input[0], temp->name) == 0)
		{
			temp->function(argc, const_cast<const char **>(input), name, 0);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static int ft_handle_builtins(char **input, int i, t_name *name, char *input_string)
{
	if (ft_strcmp_dnd(input[0], "roll") == 0)
		ft_command_roll(input);
	else if (i == 1 && ft_strcmp_dnd(input[0], "exit") == 0)
		return (ft_free_input(input, input_string), -1);
	else if (i == 1 && ft_strcmp_dnd(input[0], "fclean") == 0)
		ft_fclean();
	else if (i == 1 && ft_strcmp_dnd(input[0], "clean") == 0)
		ft_clean();
	else if (i == 1 && ft_strcmp_dnd(input[0], "initiative") == 0)
		ft_open_all_files(name);
	else if (i == 1 && ft_strcmp_dnd(input[0], "turn") == 0)
            ft_turn_next(name);
	else if (i == 1 && ft_strcmp_dnd(input[0], "test") == 0)
            ft_test(name);
	else if (i == 1 && ft_strcmp_dnd(input[0], "help") == 0)
            ft_print_help();
	else if (i == 3 && ft_strcmp_dnd(input[1], "player") == 0)
            ft_player(const_cast<const char **>(input));
	else if (i == 2 && ft_strcmp_dnd(input[0], "encounter") == 0)
		ft_encounter(input[1], name);
	else
		return (0);
	return (1);
}

void ft_request_input(t_name *name)
{
    char *input_string;
    char **input;

    while ((input_string = rl_readline("dndtools: ")) != ft_nullptr)
    {
        input = ft_parse_input(input_string);
        if (!input)
            continue ;
        int index = ft_double_char_length(const_cast<const char **>(input));
        int found = ft_handle_builtins(input, index, name, input_string);
        if (found == -1)
		{
			rl_clear_history();
            return ;
		}
        else if (!found)
            found = ft_handle_custom_commands(input, index, name);
        if (!found)
			pf_printf_fd(2, "007-Error unknown command: %s\n", input_string);
        ft_free_input(input, input_string);
    }
	return ;
}
