#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "libft/ReadLine/readline.hpp"
#include <cstdlib>

static char	**ft_parse_input(char *input_string)
{
	char **input;

	input = cma_split(input_string, ' ', false);
	if (!input)
	{
		cma_free(input_string);
		ft_printf_fd(2, "006-Error splitting input\n");
	}
	return (input);
}

static int ft_handle_custom_commands(char **input, int argc, t_name *name)
{
	t_name *temp;

	temp = name;
	while (temp != nullptr)
	{
		if (argc > 0 && ft_strcmp_dnd(input[0], temp->name) == 0)
		{
			temp->function(argc, (const char **)input, name, 0);
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
	else if (i == 3 && ft_strcmp_dnd(input[1], "player") == 0)
		ft_player((const char **)input);
	else
		return (0);
	return (1);
}

void ft_request_input(t_name *name)
{
    char *input_string;
    char **input;
    int found;
    int i;

    while ((input_string = rl_readline("dndtools: ")) != nullptr)
    {
        input = ft_parse_input(input_string);
        if (!input)
            continue ;
        i = ft_double_char_length(input);
        found = ft_handle_builtins(input, i, name, input_string);
        if (found == -1)
		{
			rl_clear_history();
            return ;
		}
        else if (!found)
            found = ft_handle_custom_commands(input, i, name);
        if (!found)
			ft_printf_fd(2, "007-Error unknown command: %s\n", input_string);
        ft_free_input(input, input_string);
    }
	return ;
}
