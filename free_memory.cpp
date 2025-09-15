#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include <cstdlib>
#include <unistd.h>

void    ft_free_input(char **input, char *input_string)
{
    int    index = 0;
    while (input[index])
    {
        cma_free(input[index]);
        index++;
    }
    cma_free(input);
    cma_free(input_string);
}

int ft_free_players(t_pc *players)
{
    t_pc    *temp;

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

void    ft_free_pc(t_pc *player)
{
    cma_free(player->name);
    cma_free(player);
}

void    ft_free_memory_cmt(t_target_data *target_data, int amount)
{
    int index = 0;

    while (index < amount)
    {
        if (target_data->target[index])
        {
            ft_free_info(target_data->target[index]);
            target_data->target[index] = ft_nullptr;
        }
        if (target_data->target_copy[index])
        {
            ft_free_info(target_data->target_copy[index]);
            target_data->target_copy[index] = ft_nullptr;
        }
        if (target_data->Pchar_name[index])
        {
            cma_free(target_data->Pchar_name[index]);
            target_data->Pchar_name[index] = ft_nullptr;
        }
        index++;
    }
    return ;
}
