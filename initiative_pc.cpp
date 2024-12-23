#include "libft/CMA/CMA.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"
#include <cstdlib>
#include <cstring>

static int ft_check_int(char *content, int index, char *filename)
{
    int temp;
    int result;

    temp = index;
    if (DEBUG == 1)
        pf_printf("%s\n", content);
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
        pf_printf_fd(2, "2-Something is wrong with the save file from %s at the line: %s\n", filename, content);
        return (-99999);
    }
    result = ft_atoi(content);
    return (result);
}

static char *ft_check_string(char *content, int index)
{
    char *result;

    content = content + index;
    result = cma_strdup(content, false);
    return (result);
}

int ft_check_stat_pc(t_pc *player, char **content, char *filename)
{
    int line_index = 0;

    player->name = ft_nullptr;
    player->initiative = -1;
    player->next = ft_nullptr;
    while (content[line_index])
    {
        int char_index = 0;
        while (content[line_index][char_index])
        {
            if (content[line_index][char_index] == '\n')
                content[line_index][char_index] = '\0';
            char_index++;
        }
        if (ft_strncmp(content[line_index], "INITIATIVE=", 11) == 0 && player->initiative == -1)
            player->initiative = ft_check_int(content[line_index], 11, filename);
        else if (ft_strncmp(content[line_index], "NAME=", 5) == 0 && player->name == ft_nullptr)
        {
            player->name = ft_check_string(content[line_index], 5);
            if (!player->name)
                return (1);
        }
        else
        {
            pf_printf_fd(2, "3-There is an error with the line: %s\n", content[line_index]);
            return (1);
        }
        line_index++;
    }
    if (!(player->initiative >= 0 && player->initiative <= 50))
    {
        pf_printf_fd(2, "Initiative value not found: %d\n", player->initiative);
        return (1);
    }
    if (!player->name)
    {
        pf_printf_fd(2, "Player name not found\n");
        return (1);
    }
    return (0);
}
