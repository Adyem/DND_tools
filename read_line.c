#include "dnd_tools.h"

void	ft_request_input(t_name *name)
{
	t_name	*temp;
	char	*input_string;
	char	**input;
	int		i;
	int		found;
	
	while ((input_string = readline("dndtools: ")) != NULL)
	{
		if (*input_string)
			add_history(input_string);
		input = ft_split(input_string, ' ');
		if (!input)
		{
			ft_printf_fd(2, "Error splitting input\n");
			free(input_string);
			continue ;
		}
		i = 0;
		while (input[i])
			i++;
		found = 0;
		temp = name;
		if (ft_strcmp_dnd(input[0], "roll") == 0 && !found)
		{
			found = 1;
			ft_command_roll(input);
		}
		else if (i == 1 && ft_strcmp_dnd(input[0], "exit") == 0 && !found)
		{
			ft_free_input(input, input_string);
			break ;
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
		else
		{
			while (temp != NULL && !found)
			{
				if (i > 0 && ft_strcmp_dnd(input[0], temp->name) == 0)
				{
					temp->function(i, (const char **)input, name, 0);
					found = 1;
				}
				temp = temp->next;
			}
		}
		if (!found)
			ft_printf_fd(2, "1-Error, unknown command: %s\n", input_string);
		ft_free_input(input, input_string);
	}
	return ;
}
