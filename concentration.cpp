#include "dnd_tools.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>

static void ft_concentration_remove_buf(t_char *info, t_char *target)
{
    if (DEBUG == 1)
    {
        std::cout << "Memory address of info struct: " << (void *)info << std::endl;
        std::cout << "Memory address of target struct: " << (void *)target << std::endl;
    }
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_concentration_remove_hunters_mark(info, target);
    return ;
}

int ft_remove_concentration(t_char *info)
{
    int i;
    t_char *target;
    int fd;

    if (DEBUG == 1)
        std::cout << "Removing concentration" << std::endl;

    i = 0;
    while (info->concentration.targets && info->concentration.targets[i])
    {
        if (ft_set_stats_check_name(info->concentration.targets[i]))
        {
            if (ft_check_player_character(info->concentration.targets[i]) == 0)
            {
                target = nullptr;
                i++;
                continue ;
            } 
            else
                target = nullptr;
        }
        else
        {
            target = ft_get_info(info->concentration.targets[i], info->struct_name);
            if (!target)
                return (std::cerr << "300-Error getting info " << info->concentration.targets[i] << std::endl, 1);
        }
        if (target && DEBUG == 1)
            std::cout << "Target found: " << target->name << std::endl;
        if (target)
        {
            ft_concentration_remove_buf(info, target);
            fd = open(target->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (fd == -1)
            {
                ft_free_info(target);
                return (std::cerr << "301-Error opening " << info->save_file << ": " << strerror(errno) << std::endl, 1);
            }
            ft_npc_write_file(target, &target->stats, &info->c_resistance, fd);
            ft_free_info(target);
            close(fd);
        }
        i++;
    }
    info->concentration.concentration = 0;
    info->concentration.spell_id = 0;
    info->concentration.dice_amount_mod = 0;
    info->concentration.dice_faces_mod = 0;
    info->concentration.base_mod = 0;
    ft_free_double_char(info->concentration.targets);
    info->concentration.targets = nullptr;
    info->bufs.chaos_armor.duration = 0;
    return (0);
}

void ft_check_concentration(t_char *info, int damage)
{
    int difficulty;
    int result;

    if (DEBUG == 1)
        std::cout << "Rolling con save for concentration " << info->name << std::endl;

    if (!info->concentration.concentration)
        return ;
    result = ft_saving_throw(info, "constitution", info->stats.con, info->save_mod.con);
    difficulty = 10;
    if (difficulty < damage / 2)
        difficulty = damage / 2;
    if (result < difficulty)
    {
        std::cout << info->name << " failed his/her concentration save" << std::endl;
        ft_remove_concentration(info);
    }
    else
        std::cout << info->name << " made his/her concentration save" << std::endl;
    return ;
}
