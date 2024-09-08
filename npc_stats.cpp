#include "dnd_tools.hpp"
#include <cerrno>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int ft_npc_open_file(t_char *info)
{
    int error;
    int fd;
    char **content;

    fd = open(info->save_file, O_RDONLY);
    if (DEBUG == 1)
        std::cout << "Opening file " << info->save_file << " on fd " << fd << std::endl;
    if (fd == -1)
    {
        std::cerr << "1-Error opening file " << info->save_file << ": " << strerror(errno) << std::endl;
        return (1);
    }
    content = ft_read_file_dnd(fd);
    if (DEBUG == 1)
        std::cout << "Content is at address " << content << std::endl;

    if (!content)
        return (1);
    close(fd);
    error = ft_initialize_info(info, content);
    if (DEBUG == 1)
        std::cout << "The value of error is " << error << " " << info->flags.error << std::endl;

    if (info->flags.error || error)
        return (1);
    error = ft_npc_check_info(info);
    ft_free_double_char(content);
    if (error)
        return (1);
    return (0);
}

void ft_npc_change_stats(t_char *info, const int index, const char **input)
{
    int i = 0;

    while (DEBUG == 1 && input[i])
    {
        std::cout << input[i] << std::endl;
        i++;
    }
    i = 0;
    if (DEBUG == 1)
    {
        while (input[i])
        {
            std::cout << input[i] << std::endl;
            i++;
        }
    }
    if (index == 1)
    {
        if (info->turn)
            info->turn(info);
        else
            std::cout << info->name << " doesn't take any actions on his/her turn" << std::endl;
    }
    else if (index == 2)
        ft_npc_sstuff(info, input);
    else if (index == 3)
        ft_npc_set_stat(info, input);
    else if (index == 4)
        ft_change_stats_04(info, input);
    else
        std::cerr << "Error: Too many arguments given" << std::endl;
    ft_npc_write_file(info, &info->stats, &info->c_resistance, -1);
	return ;
}
