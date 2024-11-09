#include "libft/Printf/ft_printf.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <strings.h>

static void	ft_set_not_save_flag(t_target_data *target_data, t_char *info)
{
	int	i;

	i = 0;
	while (i < target_data->buff_info->target_amount)
	{
		target_data->target[i]->flags.dont_save = 1;
		i++;
	}
	info->flags.dont_save = 1;
	return ;
}

static int	ft_check_and_open(t_target_data *target_data, t_char *info)
{
	int	i;
	int	fd;

	i = 0;
	while (i < target_data->buff_info->target_amount)
	{
		if (ft_check_write_permissions(target_data->target[i]->save_file))
		{
			ft_set_not_save_flag(target_data, info);
			pf_printf_fd(2, "118-Error trying to acces file: %s", strerror(errno));
			return (-1);
		}
		i++;
	}
	if (ft_check_write_permissions(info->save_file))
	{
		ft_set_not_save_flag(target_data, info);
		pf_printf_fd(2, "120-Error trying to acces file: %s", strerror(errno));
		return (-1);
	}
	i = 0;
	fd = ft_open_file_write_only(info->save_file);
	if (fd == -1)
	{
		pf_printf_fd(2, "121-Error opening file: %s", strerror(errno));
		abort();
	}
	while (i < target_data->buff_info->target_amount)
	{
		target_data->fd[i] = ft_open_file_write_only(target_data->target[i]->save_file);
		if (target_data->fd[i] == -1)
		{
			pf_printf_fd(2, "119-Error opening file: %s", strerror(errno));
			abort();
		}
		i++;
	}
	return (fd);
}

void	ft_cast_concentration_multi_target_02(t_char *info, t_target_data *target_data)
{
	int	fd;
	
	fd = ft_check_and_open(target_data, info);
	if (fd == -1)
		return ;
	return ;
}
