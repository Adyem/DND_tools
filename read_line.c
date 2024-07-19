#include "dnd_tools.h"

static char	**ft_parse_input(char *input_string)
{
	char **input;

	input = ft_split(input_string, ' ');
	if (!input)
	{
		free(input_string);
		ft_printf_fd(2, "Error splitting input\n");
	}
	return (input);
}

static int ft_handle_custom_commands(char **input, int argc, t_name *name)
{
	t_name *temp;

	temp = name;
	while (temp != NULL)
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
	int	found;

	found = 0;
	if (ft_strcmp_dnd(input[0], "roll") == 0 && !found)
	{
		ft_command_roll(input);
		found = 1;
	}
	else if (i == 1 && ft_strcmp_dnd(input[0], "exit") == 0 && !found)
	{
		ft_free_input(input, input_string);
		found = -1;
	}
	else if (i == 1 && ft_strcmp_dnd(input[0], "fclean") == 0 && !found)
	{
		ft_fclean();
		found = 1;
	}
	else if (i == 1 && ft_strcmp_dnd(input[0], "clean") == 0 && !found)
	{
		ft_clean();
		found = 1;
	}
	else if (i == 1 && ft_strcmp_dnd(input[0], "initiative") == 0 && !found)
	{
		ft_open_all_files(name);
		found = 1;
	}
	else if (i == 1 && ft_strcmp_dnd(input[0], "turn") == 0 && !found)
	{
		ft_turn_next(name);
		found = 1;
	}
	else if (i == 3 && ft_strcmp_dnd(input[1], "player") == 0 && !found)
	{
		ft_player((const char **)input);
		found = 1;
	}
	return (found);
}

void	ft_request_input(t_name *name)
{
	char	*input_string;
	char	**input;
	int		found;
	int		i;
	
	while ((input_string = readline("dndtools: ")) != NULL)
	{
		if (*input_string)
			add_history(input_string);
		input = ft_parse_input(input_string);
		if (!input)
			continue ;
		i = ft_double_char_length(input);
		found = ft_handle_builtins(input, i, name, input_string);
		if (found == -1)
			return ;
		else if (!found)
			found = ft_handle_custom_commands(input, i, name);
		if (!found)
			ft_printf_fd(2, "1-Error, unknown command: %s\n", input_string);
		ft_free_input(input, input_string);
	}
	return ;
}
