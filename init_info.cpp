#include "libft/Printf/printf.hpp"
#include "libft/Libft/libft.hpp"
#include "dnd_tools.hpp"

int ft_check_stat(ft_sharedptr<t_char> &info, const char *stat, int index)
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
        pf_printf_fd(2, "2-Something is wrong with the save file from %s at the line: %s\n",
				info->name, stat);
        return (-99999);
    }
    result = ft_atoi(stat);
    return (result);
}

int ft_initialize_info(ft_sharedptr<t_char> &character, char **content)
{
    int line_index;
    int char_index;
    int error_code = 0;

    line_index = 0;
    while (content[line_index])
    {
        char_index = 0;
        while (content[line_index][char_index])
        {
            if (content[line_index][char_index] == '\n')
                content[line_index][char_index] = '\0';
            char_index++;
        }
        line_index++;
    }
    error_code += ft_set_stats(character, content);
    return error_code;
}
