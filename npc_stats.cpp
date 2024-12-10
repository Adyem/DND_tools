#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "dnd_tools.hpp"
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int ft_npc_open_file(t_char *info)
{
    int error;
    char **content;

    ft_file info_file(info->save_file, O_RDONLY);
    if (info_file.get_error_code())
    {
        pf_printf_fd(2, "1-Error opening file %s: %s\n", info->save_file,
				info_file.get_error_message());
        return (1);
    }
	if (DEBUG == 1)
        pf_printf("Opening file %s on fd %d\n", info->save_file, info_file.get_fd());
    content = ft_read_file_lines(info_file);
    if (DEBUG == 1)
        pf_printf("Content is at address %p\n", content);
    if (!content)
        return (1);
    error = ft_initialize_info(info, content);
	cma_free_double(content);
    if (DEBUG == 1)
        pf_printf("The value of error is %d %d\n", error, info->flags.error);
    if (info->flags.error || error)
        return (1);
    error = ft_npc_check_info(info);
    if (error)
        return (1);
    return (0);
}

void ft_npc_change_stats(t_char *info, const int index, const char **input)
{
    int i = 0;

	while (DEBUG == 1 && input[i])
    {
        pf_printf("%s\n", input[i]);
        i++;
    }
    i = 0;
    if (index == 1)
    {
        if (info->turn)
            info->turn(info);
        else
            pf_printf("%s doesn't take any actions on his/her turn\n", info->name);
    }
    else if (index == 2)
        ft_npc_sstuff(info, input);
    else if (index == 3)
        ft_npc_set_stat(info, input);
    else if (index == 4)
        ft_change_stats_04(info, input);
    else
        pf_printf_fd(2, "Error: Too many arguments given\n");
    ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    ft_npc_write_file(info, &info->stats, &info->d_resistance, file);
    return ;
}
