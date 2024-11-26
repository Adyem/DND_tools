#include "libft/CPP_class/file.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CMA/CMA.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <strings.h>

static void	ft_set_not_save_flag(t_target_data *target_data, t_char *info)
{
	int	i = 0;

	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i])
			target_data->target[i]->flags.dont_save = 1;
		if (target_data->target_copy[i])
			target_data->target_copy[i]->flags.dont_save = 1;
		i++;
	}
	info->flags.dont_save = 1;
	return ;
}

static int	ft_apply_concentration(t_target_data *target_data, t_char *info, const char **input)
{
	int	i = 0;

	info->concentration.targets = (char **)cma_calloc(target_data->buff_info->target_amount,
			sizeof(char *), false);
	if (!info->concentration.targets)
		return (FAILURE);
	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i])
		{
			if (target_data->buff_info->cast_spell(target_data->target[i], input,
						target_data->buff_info))
				return (FAILURE);
			info->concentration.targets[i] = cma_strdup(target_data->Pchar_name[i], false);
			if (!info->concentration.targets[i])
				return (FAILURE);
		}
		i++;
	}
    info->concentration.concentration = 1;
    info->concentration.spell_id = target_data->buff_info->spell_id;
    info->concentration.dice_faces_mod = target_data->buff_info->dice_faces_mod;
    info->concentration.dice_amount_mod = target_data->buff_info->dice_amount_mod;
    info->concentration.duration = target_data->buff_info->duration;
    return (SUCCES);
}

void	ft_cast_concentration_multi_target_02(t_char *info, t_target_data *target_data,
			const char **input)
{
	ft_file info_save_file;

	if (ft_apply_concentration(target_data, info, input))
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}
	info_save_file = ft_check_and_open(target_data, info);
	if (info_save_file.get_fd() == -1)
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}
	ft_cast_concentration_save_files(info, target_data, info_save_file);
	return ;
}
