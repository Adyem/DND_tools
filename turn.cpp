#include "dnd_tools.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/GetNextLine/get_next_line.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static int ft_turn_check_marker(t_pc *players)
{
    t_pc *temp;
    int marker;

    temp = players;
    marker = 0;
    while (temp)
    {
        if (ft_strncmp("--turn--", temp->name, 8) == 0)
            marker++;
        temp = temp->next;
    }
    if (marker == 0)
        pf_printf("File is corrupted no turn marker found\n");
    else if (marker > 1)
        pf_printf("File is corrupted multiple turn markers found\n");
    return (marker);
}

static int ft_turn_move_marker(t_pc *players)
{
    t_pc *temp;
    char *name;

    temp = players;
    while (temp)
    {
        if (ft_strncmp("--turn--", temp->name, 8) == 0)
        {
            name = ft_strtrim_prefix(temp->name, "--turn--");
            if (!name)
                pf_printf("244-Error allocating memory turn\n");
            cma_free(temp->name);
            temp->name = name;
            if (temp->next)
            {
                name = cma_strjoin("--turn--", temp->next->name);
                if (!name)
                {
                    pf_printf("245-Error allocating memory turn strjoin\n");
                    return (1);
                }
                cma_free(temp->next->name);
                temp->next->name = name;
            }
            else
            {
                name = cma_strjoin("--turn--", players->name);
                if (!name)
                {
                    pf_printf("246-Error allocating memory turn strjoin\n");
                    return (1);
                }
                cma_free(players->name);
                players->name = name;
            }
            break ;
        }
        temp = temp->next;
    }
    return (0);
}

static int ft_turn_write(t_pc *players)
{
    t_pc *temp;

    ft_file initiative_file("data/data--initiative", O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR);
    if (initiative_file.get_error())
    {
        pf_printf("263-Error opening file %s\n", initiative_file.get_error_str());
        return (1);
    }
    temp = players;
    while (temp)
    {
        pf_printf_fd(initiative_file, "%s=%d\n", temp->name, temp->initiative);
        temp = temp->next;
    }
    return (0);
}

static int ft_turn_run(t_pc *players, t_name *name)
{
    t_pc *pc_temp;
    t_name *n_temp;
    char *character_name = ft_nullptr;
    const char *temp[2];
    int found;

    pc_temp = players;
    found = 0;
    while (pc_temp && found == 0)
    {
        if (ft_strncmp("--turn--", pc_temp->name, 8) == 0)
        {
            found = 1;
            character_name = ft_strtrim_prefix(pc_temp->name, "--turn--");
            if (!character_name)
            {
                pf_printf("247-Error allocating memory strtrim\n");
                return (1);
            }
            n_temp = name;
            while (n_temp != ft_nullptr && found != 2)
            {
                if (ft_strcmp_dnd(n_temp->name, character_name) == 0)
                {
                    temp[0] = character_name;
                    temp[1] = ft_nullptr;
                    n_temp->function(1, temp, name, 0);
                    found = 2;
                }
                n_temp = n_temp->next;
            }
        }
        if (ft_strncmp("--turn--PC--", pc_temp->name, 12) == 0)
            pf_printf("the current turn is for %s\n", &pc_temp->name[12]);
        pc_temp = pc_temp->next;
    }
    cma_free(character_name);
    return (0);
}

void ft_turn_next(t_name *name)
{
    t_pc *players;
    char **content;

    ft_file initiative_file("data/data--initiative", O_RDONLY);
    if (initiative_file.get_error())
    {
        pf_printf("Error opening data initiative file %s\n", initiative_file.get_error_str());
        return ;
    }
    content = ft_read_file_lines(initiative_file);
    if (!content)
        return ;
    players = ft_initiative_players_am(content);
    cma_free_double(content);
    if (!players)
        return ;
    if (ft_turn_check_marker(players) != 1)
    {
        ft_free_players(players);
        return ;
    }
    if (ft_turn_run(players, name))
    {
        ft_free_players(players);
        return ;
    }
    if (ft_turn_move_marker(players))
    {
        ft_free_players(players);
        return ;
    }
    ft_turn_write(players);
    ft_free_players(players);
    return ;
}
