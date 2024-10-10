#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include <cstdlib>

void	ft_free_input(char **input, char *input_string)
{
	int	i;

	i = 0;
	while (input[i])
	{
		cma_free(input[i]);
		i++;
	}
	cma_free(input);
	cma_free(input_string);
}

int ft_free_players(t_pc *players)
{
	t_pc	*temp;

	while (players)
	{
		temp = players->next;
		if (players->name)
			cma_free(players->name);
		cma_free(players);
		players = temp;
	}
	return (1);
}

void	ft_free_pc(t_pc *player)
{
	cma_free(player->name);
	cma_free(player);
}
