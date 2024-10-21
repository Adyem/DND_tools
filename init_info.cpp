#include "libft/Printf/ft_printf.hpp"
#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"

int ft_check_stat(t_char *info, const char *stat, int index)
{
    int temp;
    int result;

    temp = index;
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
        ft_printf_fd(2, "2-Something is wrong with the save file from %s at the line: %s\n",
				info->name, stat);
        return (-99999);
    }
    result = ft_atoi(stat);
    return (result);
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
    return (error);
}
