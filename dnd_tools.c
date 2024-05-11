#include "dnd_tools.h"

static int	ft_create_dir()
{
	struct	stat st = {0};

	if (stat("data", &st) == -1)
	{
		if (mkdir("data", 0700) == -1)
		{
			ft_printf_fd(2, "Failed to create directory: %s\n", strerror(errno));
			return (1);
		}
		else
			if (DEBUG == 1)
				ft_printf("Data folder created succesfully\n");
	}
	else if (DEBUG == 1)
		ft_printf("Data folder alreaddy exists\n");
	return (0);
}

static void	ft_free_input(char **input, char *input_string)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	free(input_string);
}

static void	ft_request_input(t_name *name)
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
			ft_player(input);
			found = 1;
		}
		else
		{
			while (temp != NULL && !found)
			{
				if (i > 0 && ft_strcmp_dnd(input[0], temp->name) == 0)
				{
					temp->function(i, input, 0);
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

int main(int argc, char **argv)
{
	t_name	*name;

	(void)argv;
	if (argc > 1)
	{
		ft_printf_fd(2, "Error: expecting no arguments\n");
		return (1);
	}
	srand((unsigned)time(NULL));
	if (DEBUG == 1)
	{
		ft_printf("DEBUGGING\n");
		ft_printf("Rand Max = %i\n", RAND_MAX);
	}
	if (ft_create_dir())
		return (1);
	name = ft_allocate_memory_name();
	ft_request_input(name);
	ft_free_memory_name(name, 0);
	clear_history();
	return (0);
}
