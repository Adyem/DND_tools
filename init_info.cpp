#include "libft/libft/libft.hpp"
#include "dnd_tools.hpp"
#include <iostream>

int ft_check_stat(t_char *info, const char *stat, int index)
{
    int temp;
    int result;

    temp = index;
    if (DEBUG == 1)
        std::cout << stat << std::endl;
    while (index)
    {
        stat++;
        index--;
    }
    if (ft_check_value(stat))
    {
        while (temp)
        {
            stat--;
            temp--;
        }
        std::cerr << "2-Something is wrong with the save file from " << info->name
                  << " at the line: " << stat << std::endl;
        return (-99999);
    }
    result = ft_atoi(stat);
    return (result);
}

void ft_print_info(t_char *info)
{
    if (DEBUG != 1)
        return;
    std::cout << "info->stats.health=" << info->stats.health << std::endl;
	return ;
}

int ft_initialize_info(t_char *info, char **content)
{
    int j;
    int i;
    int error = 0;

    i = 0;
    while (content[i])
    {
        j = 0;
        while (content[i][j])
        {
            if (content[i][j] == '\n')
                content[i][j] = '\0';
            j++;
        }
        i++;
    }
    error += ft_set_stats(info, content);
    ft_print_info(info);
    return (error);
}
