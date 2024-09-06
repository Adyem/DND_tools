#include "dnd_tools.hpp"
#include <cstdlib>

void	ft_free_input(char **input, char *input_string)
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

int ft_free_players(t_pc *players)
{
	t_pc	*temp;

	while (players)
	{
		temp = players->next;
		if (players->name)
			free(players->name);
		free(players);
		players = temp;
	}
	return (1);
}

void	ft_free_pc(t_pc *player)
{
	free(player->name);
	free(player);
}

void	ft_free_double_char(char **content)
{
	int	i;

	i = 0;
	if (content)
	{
		while (content[i])
		{
			free(content[i]);
			i++;
		}
		free(content);
	}
	return ;
}
