#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int ft_double_char_length(const char **double_char)
{
    int i;

    if (!double_char)
        return (0);
    i = 0;
    while (double_char[i])
        i++;
    return (i);
}

int ft_open_file_write_only(const char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
        ft_printf_fd(2, "Error opening file %s: %s\n", filename, strerror(errno));
    return (fd);
}

void ft_dual_save_file(t_char *info, t_char *target)
{
    int fd_target;
    int fd_info;

    fd_target = ft_open_file_write_only(target->save_file);
    if (fd_target == -1)
    {
        info->flags.alreaddy_saved = 1;
        return ;
    }
    fd_info = ft_open_file_write_only(info->save_file);
    if (fd_target == -1 || fd_info == -1)
    {
        if (fd_target != -1)
            close(fd_target);
        if (fd_info != -1)
            close(fd_info);
        info->flags.alreaddy_saved = 1;
        ft_free_info(target);
        return ;
    }
    ft_npc_write_file(target, &target->stats, &target->c_resistance, fd_target);
    ft_npc_write_file(info, &info->stats, &info->c_resistance, fd_info);
    return ;
}

void	ft_remove_element(const char **array, const char *element)
{
	int	i;
	int	j;

	if (!array || !element)
		return ;
	i = 0;
	while (array[i] && array[i] != element)
		i++;
	if (array[i] == element)
	{
		j = i;
		while (array[j])
		{
			array[j] = array[j + 1];
			j++;
		}
	}
	return ;
}
