#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cstdlib>
#include <unistd.h>

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

void	ft_free_memory_cmt(t_target_data *target_data, int amount)
{
    int j = 0;

    while (j < amount)
    {
        if (target_data->target[j])
        {
            ft_free_info(target_data->target[j]);
            target_data->target[j] = ft_sharedptr<t_char>();
        }
		if (target_data->target_copy[j])
		{
			ft_free_info(target_data->target_copy[j]);
			target_data->target[j] = ft_sharedptr<t_char>();
		}
        if (target_data->Pchar_name[j])
        {
            cma_free(target_data->Pchar_name[j]);
            target_data->Pchar_name[j] = ft_nullptr;
        }
        j++;
    }
	return ;
}
