#include "dnd_tools.hpp"
#include "goblin_warmaster.hpp"
#include <iostream>
#include "libft/libft/libft.hpp"

void ft_goblin_warmaster_turn(t_char *info)
{
    ft_update_buf(info);
    if (info->flags.prone)
    {
        std::cout << info->name << " will use his/her action to stand up" << std::endl;
        info->flags.prone = 0;
    }
    else
    {
        std::cout << "The warmaster will attempt a strategic melee or ranged attack during his turn" << std::endl;
    }
    std::cout << "Warmaster currently has " << info->stats.health << "/" << info->dstats.health << " hp" << std::endl;
    if (info->stats.health < info->dstats.health / 2)
    {
        std::cout << "The warmaster is on low health and may use the command ability as a bonus action" << std::endl;
    }
}

static void ft_initialize_gear_and_feats(t_char *info)
{
    (void)info;
    return;
}

t_char *ft_goblin_warmaster(const int index, const char **input, t_name *name, int exception)
{
    int error;
    t_char *info;

    info = (t_char *)calloc(1, sizeof(t_char));
    if (!info)
        return (nullptr);
    *info = WARM_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = ft_strjoin("data/", input[0]);
    if (!info->save_file)
    {
        ft_free_info(info);
        return (nullptr);
    }
    if (index == 2)
    {
        if (ft_strcmp_dnd(input[1], "init") == 0)
        {
            ft_npc_write_file(info, &info->dstats, &info->d_resistance, -1);
            std::cout << "Stats for " << info->name << " written on a file" << std::endl;
            ft_free_info(info);
            return (nullptr);
        }
    }
    error = ft_npc_open_file(info);
    if (error)
    {
        ft_free_info(info);
        return (nullptr);
    }
    error = ft_npc_check_info(info);
    if (error)
    {
        ft_free_info(info);
        return (nullptr);
    }
    ft_initialize_gear_and_feats(info);
    if (exception)
        return (info);
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (nullptr);
}