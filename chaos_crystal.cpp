#include <cerrno>
#include "dnd_tools.hpp"
#include "chaos_crystal.hpp"
#include "libft/Libft/libft.hpp"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>

static void ft_chaos_crystal_damage(t_char *info)
{
    char *temp;
    char **content;
    int fd;
    int length;
    int result;

    fd = open("data/data--initiative", O_RDONLY);
    if (fd == -1)
    {
        std::cerr << "280-Error opening file: " << strerror(errno) << std::endl;
        return ;
    }
    content = ft_read_file_dnd(fd);
    close(fd);
    if (!content)
    {
        std::cerr << "281-Error opening file: " << strerror(errno) << std::endl;
        return ;
    }
    length = ft_double_char_length(content);
    result = -1;
    while (result == -1 || (ft_strncmp(content[result], "PC--", 4) != 0
                && ft_strncmp(content[result], "--turn--PC--", 12) != 0))
    {
        result = ft_dice_roll(1, length) - 1;
        if (DEBUG == 1)
            std::cout << "result = " << result << std::endl;
    }
    temp = ft_strchr(content[result], '=');
    if (temp)
        *temp = '\0';
    std::cout << info->name << " shoots a magic missile at " << &content[result][4]
              << " and he/she takes 1 force damage, the target " \
			  "does not need to make a concentration save for this damage"
              << std::endl;
    ft_free_double_char(content);
    return ;
}

void ft_chaos_crystal_turn(t_char *info)
{
    ft_update_buf(info);
    ft_chaos_crystal_damage(info);
    std::cout << "Chaos_crystal currently has " << info->stats.health << "/"
              << info->dstats.health << " hp" << std::endl;
}

static void ft_initialize_gear_and_feats(t_char *info)
{
    (void)info;
    return ;
}

t_char *ft_chaos_crystal(const int index, const char **input, t_name *name, int exception)
{
    int error;
    t_char *info;

    info = (t_char *)calloc(1, sizeof(t_char));
    if (!info)
    {
        std::cerr << "103-Error: Failed to allocate memory info " << input[0] << std::endl;
        return (nullptr);
    }
    *info = CHAOS_CRYSTAL_INFO;
    info->name = input[0];
    info->struct_name = name;
    info->save_file = ft_strjoin("data/", input[0]);
    if (!info->save_file)
    {
        std::cerr << "106-Error: Failed to allocate memory save_file name "
			<< info->name << std::endl;
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
        return (info) ;
    ft_npc_change_stats(info, index, input);
    ft_free_info(info);
    return (nullptr);
}

