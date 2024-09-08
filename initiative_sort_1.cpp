#include "dnd_tools.hpp"
#include "libft/libft/libft.hpp"
#include <iostream>
#include <cstring>
#include <cerrno>

static int ft_initiative_copy_v(t_pc *head, t_pc *players, char *content)
{
    char *temp;

    temp = ft_strchr(content, '\n');
    if (temp)
        *temp = '\0';
    temp = ft_strchr(content, '=');
    if (!temp)
    {
        std::cerr << "Error did not find = sign" << std::endl;
        return (ft_free_players(head));
    }
    *temp = '\0';
    temp++;
    players->name = ft_strdup(content);
    if (!players->name)
    {
        std::cerr << "257 Error allocating memory" << std::endl;
        return (ft_free_players(head));
    }
    if (ft_check_value(temp))
    {
        std::cerr << "There is an error on the line: " << temp << std::endl;
        return (ft_free_players(head));
    }
    players->initiative = ft_atoi(temp);
    if (DEBUG == 1)
        std::cout << "The initiative from " << players->name << " = " << players->initiative << std::endl;
    return (0);
}

static void ft_initiative_players_init(t_pc *players)
{
    players->next = nullptr;
    players->name = nullptr;
    players->initiative = -2;
	return ;
}

t_pc *ft_initiative_players_am(char **content)
{
    t_pc *players;
    t_pc *temp;
    int i;

    players = (t_pc *)malloc(sizeof(t_pc));
    if (!players)
    {
        std::cerr << "Error allocating memory: players" << std::endl;
        return (nullptr);
    }
    ft_initiative_players_init(players);
    players->initiative = -2;
    if (ft_initiative_copy_v(players, players, content[0]))
        return (nullptr);
    temp = players;
    i = 1;
    while (content[i])
    {
        temp->next = (t_pc *)malloc(sizeof(t_pc));
        if (!temp->next)
        {
            std::cerr << "Error allocating memory: players->next" << std::endl;
            ft_free_players(players);
            return (nullptr);
        }
        ft_initiative_players_init(temp->next);
        if (ft_initiative_copy_v(players, temp->next, content[i]))
            return (nullptr);
        temp = temp->next;
        i++;
    }
    return (players);
}

void ft_initiative_sort(int fd)
{
    t_pc *players;
    char **content;

    if (fd == -1)
    {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return ;
    }
    content = ft_read_file_dnd(fd);
    close(fd);

    if (!content)
        return ;
    players = ft_initiative_players_am(content);
    ft_free_double_char(content);
    if (!players)
        return ;
    ft_initiative_sort_2(players);
    ft_free_players(players);
    ft_initiative_print();
	return ;
}
