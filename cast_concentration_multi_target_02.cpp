#include "libft/CMA/CMA.hpp"
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
		if (target_data->target[i])
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
			pf_printf_fd(2, "118-Error trying to acces file: %s", strerror(errno));
			return (-1);
		}
		i++;
	}
	if (ft_check_write_permissions(info->save_file))
	{
		pf_printf_fd(2, "120-Error trying to acces file: %s", strerror(errno));
		return (-1);
	}
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
			abort();
		}
		i++;
	}
	return (fd);
}

static int	ft_apply_concentration(t_target_data *target_data, t_char *info, const char **input)
{
	int	i = 0;

	info->concentration.targets = (char **)cma_calloc(target_data->buff_info->target_amount,
			sizeof(char *), false);
	if (!info->concentration.targets)
		return (1);
	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i])
		{
			if (target_data->buff_info->cast_spell(target_data->target[i], input,
						target_data->buff_info))
				return (1);
			info->concentration.targets[i] = cma_strdup(target_data->Pchar_name[i], false);
			if (!info->concentration.targets[i])
				return (1);
		}
		i++;
	}
    info->concentration.concentration = 1;
    info->concentration.spell_id = target_data->buff_info->spell_id;
    info->concentration.dice_faces_mod = target_data->buff_info->dice_faces_mod;
    info->concentration.dice_amount_mod = target_data->buff_info->dice_amount_mod;
    info->concentration.duration = target_data->buff_info->duration;
    return (0);
}

static void	ft_cast_concentration_save_files(t_char *info, t_target_data *target_data, int fd)
{
	int	i = 0;

	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i])
			ft_npc_write_file(target_data->target[i], &target_data->target[i]->stats,
				&target_data->target[i]->c_resistance, target_data->fd[i]);
		i++;
	}
	ft_npc_write_file(info, &info->stats, &info->c_resistance, fd);
}

void	ft_cast_concentration_multi_target_02(t_char *info, t_target_data *target_data,
			const char **input)
{
	int	fd;

	if (ft_apply_concentration(target_data, info, input))
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}
	fd = ft_check_and_open(target_data, info);
	if (fd == -1)
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}
	ft_cast_concentration_save_files(info, target_data, fd);
	return ;
}
