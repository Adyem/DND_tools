#include "libft/Printf/ft_printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int ft_open_file_write_only(const char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
        pf_printf_fd(2, "Error opening file %s: %s\n", filename, strerror(errno));
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

int ft_check_write_permissions(const char *filepath)
{
    if (access(filepath, F_OK) == 0)
    {
        if (access(filepath, W_OK) != 0)
            return (-1);
    }
    return (0);
}

void	ft_cast_concentration_save_files(t_char *info, t_target_data *target_data, int fd)
{
	int	i = 0;

	while (i < target_data->buff_info->target_amount)
	{
		ft_npc_write_file(target_data->target[i], &target_data->target[i]->stats,
				&target_data->target[i]->c_resistance, target_data->fd[i]);
		i++;
	}
	ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
}

static void	ft_revert_changes_info(t_char *info, int fd)
{
	cma_free(info->concentration.targets[0]);
	cma_free(info->concentration.targets);
    info->concentration.targets = ft_nullptr;
   	info->concentration.concentration = 0;
   	info->concentration.spell_id = 0;
   	info->concentration.dice_faces_mod = 0;
   	info->concentration.dice_amount_mod = 0;
   	info->concentration.duration = 0;
	ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
	return ;
}

int	ft_check_and_open(t_target_data *target_data, t_char *info)
{
	int	i;
	int	fd;

	i = 0;
	fd = ft_open_file_write_only(info->save_file);
	if (fd == -1)
	{
		pf_printf_fd(2, "121-Error opening file: %s", strerror(errno));
		return (-1);
	}
	while (i < target_data->buff_info->target_amount)
	{
		target_data->fd[i] = ft_open_file_write_only(target_data->target[i]->save_file);
		if (target_data->fd[i] == -1)
		{
			pf_printf_fd(2, "119-Error opening file: %s", strerror(errno));
			ft_revert_changes_info(info, fd);
			int j = 0;
			while (j <= i)
			{
				if (target_data->target_copy[j])
				{
					t_char *target = target_data->target_copy[j];
					ft_npc_write_file(target, &target->stats,
							&target->c_resistance, target_data->fd[j]);
				}
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (fd);
}

