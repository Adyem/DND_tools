#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>

static int ft_initiative_copy_v(t_pc *head, t_pc *players, char *content)
{
    char *temp;

    temp = ft_strchr(content, '\n');
    if (temp)
        *temp = '\0';
    temp = ft_strchr(content, '=');
    if (!temp)
    {
        pf_printf("Error did not find = sign\n");
        return (ft_free_players(head));
    }
    *temp = '\0';
    temp++;
    players->name = cma_strdup(content, false);
    if (!players->name)
    {
        pf_printf("257 Error allocating memory\n");
        return (ft_free_players(head));
    }
    if (ft_check_value(temp))
    {
        pf_printf("There is an error on the line: %s\n", temp);
        return (ft_free_players(head));
    }
    players->initiative = ft_atoi(temp);
    if (DEBUG == 1)
        pf_printf("The initiative from %s = %d\n", players->name, players->initiative);
    return (0);
}

static void ft_initiative_players_init(t_pc *players)
{
    players->next = ft_nullptr;
    players->name = ft_nullptr;
    players->initiative = -2;
	return ;
}

t_pc *ft_initiative_players_am(char **content)
{
    t_pc *players;
    t_pc *temp;

    players = (t_pc *)cma_malloc(sizeof(t_pc), false);
    if (!players)
    {
        pf_printf("Error allocating memory: players\n");
        return (ft_nullptr);
    }
    ft_initiative_players_init(players);
    players->initiative = -2;
    if (ft_initiative_copy_v(players, players, content[0]))
        return (ft_nullptr);
    temp = players;
    int index = 1;
    while (content[index])
    {
        temp->next = (t_pc *)cma_malloc(sizeof(t_pc), false);
        if (!temp->next)
        {
            pf_printf("Error allocating memory: players->next\n");
            ft_free_players(players);
            return (ft_nullptr);
        }
        ft_initiative_players_init(temp->next);
        if (ft_initiative_copy_v(players, temp->next, content[index]))
            return (ft_nullptr);
        temp = temp->next;
        index++;
    }
    return (players);
}

void ft_initiative_sort(ft_file &file)
{
    t_pc *players;
    char **content;

    content = ft_read_file_lines(file);
    if (!content)
        return ;
    players = ft_initiative_players_am(content);
    cma_free_double(content);
    if (!players)
        return ;
    ft_initiative_sort_2(players);
    ft_free_players(players);
    ft_initiative_print();
	return ;
}
