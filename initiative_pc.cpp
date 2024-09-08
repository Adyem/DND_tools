#include "libft/libft/libft.hpp"
#include "dnd_tools.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

static int ft_check_int(char *content, int index, char *filename)
{
    int temp;
    int result;

    temp = index;
    if (DEBUG == 1)
        std::cout << content << std::endl;
    while (index)
    {
        content++;
        index--;
    }
    if (ft_check_value(content))
    {
        while (temp)
        {
            content--;
            temp--;
        }
        std::cerr << "2-Something is wrong with the save file from " << filename
                  << " at the line: " << content << std::endl;
        return (-99999);
    }
    result = ft_atoi(content);
    return (result);
}

static char *ft_check_string(char *content, int index)
{
    char *result;

    content = content + index;
    result = ft_strdup(content);
    return (result);
}

int ft_check_stat_pc(t_pc *player, char **content, char *filename)
{
    int i;
    int j;

    player->name = nullptr;
    player->initiative = -1;
    player->next = nullptr;
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
        if (ft_strncmp(content[i], "INITIATIVE=", 11) == 0 && (player->initiative == -1))
            player->initiative = ft_check_int(content[i], 11, filename);
        else if (ft_strncmp(content[i], "NAME=", 5) == 0 && (player->name == nullptr))
        {
            player->name = ft_check_string(content[i], 5);
            if (!player->name)
                return (1);
        }
        else
        {
            std::cerr << "3-There is an error with the line: " << content[i] << std::endl;
            return (1);
        }
        i++;
    }
    if (!(player->initiative >= 0 && player->initiative <= 50))
    {
        std::cerr << "Initiative value not found: " << player->initiative << std::endl;
        return (1);
    }
    if (!player->name)
    {
        std::cerr << "Player name not found" << std::endl;
        return (1);
    }
    return (0);
}
