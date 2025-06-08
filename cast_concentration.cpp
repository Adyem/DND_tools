#include "character.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/file.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>


static void ft_cast_concentration_cleanup(t_char *info, t_char *target,
											ft_file save_files[2], t_buff *buff, int error)
{
	if (info)
	{
		if (error != -1)
			info->flags.dont_save = 1;
        ft_npc_write_file(info, &info->stats, &info->c_resistance, save_files[0]);
	}
	if (target)
	{
		if (error != -1)
			target->flags.dont_save = 1;
		ft_npc_write_file(target, &target->stats, &target->c_resistance, save_files[1]);
	}
	if (error == 1)
        pf_printf("305-Error: can't cast %s on yourself\n", buff->spell_name);
	else if (error == 2)
        pf_printf("299-Error allocating memory for targets\n");
	else if (error == 3)
        pf_printf("299-Error allocating memory for targets[0]\n");
	else if (error == 4)
        pf_printf("320-Error opening file: %s\n", strerror(errno));
	else if (error == 5)
        pf_printf("321-Error opening file: %s\n", strerror(errno));
	if (target)
		ft_free_info(target);
	return ;
}

static int ft_apply_concentration_buff(t_char *info, t_char *target,
								ft_file save_files[2], const char **input, t_buff *buff)
{
    char	**temp;

    temp = static_cast<char **>(cma_calloc(2, sizeof(char *)));
    if (!temp)
    {
		ft_cast_concentration_cleanup(info, target, save_files, buff, 2);
        return (1);
    }
    temp[0] = static_cast<char *>(cma_malloc((ft_strlen_size_t(input[3]) + 1) * sizeof(char)));
    if (!temp[0])
    {
		ft_cast_concentration_cleanup(info, target, save_files, buff, 3);
        return (1);
    }
    info->concentration.targets = temp;
    int index = 0;
    while (input[3][index])
    {
        info->concentration.targets[0][index] = input[3][index];
        index++;
    }
	info->concentration.extra = buff->mod;
    info->concentration.targets[0][index] = '\0';
    info->concentration.concentration = 1;
    info->concentration.spell_id = buff->spell_id;
    info->concentration.dice_faces_mod = buff->dice_faces_mod;
    info->concentration.dice_amount_mod = buff->dice_amount_mod;
    info->concentration.duration = buff->duration;
    return (0);
}

static int ft_cast_concentration_open_file(ft_file save_files[2], t_char *info,
		t_char * target)
{
    if (ft_open_file_write_only(info->save_file, save_files[0]))
    {
        pf_printf_fd(2, "Unexpected error opening file %s: %s\n", info->save_file,
				strerror(errno));
        return (1);
    }
    if (ft_open_file_write_only(target->save_file, save_files[1]))
    {
        pf_printf_fd(2, "Unexpected error opening file %s: %s\n", target->save_file,
				strerror(errno));
		cma_free(info->concentration.targets[0]);
		cma_free(info->concentration.targets);
	    info->concentration.targets = ft_nullptr;
    	info->concentration.concentration = 0;
    	info->concentration.spell_id = 0;
    	info->concentration.dice_faces_mod = 0;
    	info->concentration.dice_amount_mod = 0;
    	info->concentration.duration = 0;
		ft_npc_write_file(info, &info->stats, &info->c_resistance, save_files[1]);
		return (1);
    }
    return (0);
}

int	ft_cast_concentration(t_char *info, const char **input, t_buff *buff)
{
    ft_file	save_files[2];
	t_char 	*target = ft_nullptr;

    if (ft_remove_concentration(info))
        return (1);
    if (DEBUG == 1)
        pf_printf("casting hunter's mark %s %s\n", input[0], input[3]);
    if (ft_set_stats_check_name(input[3]))
    {
        if (ft_check_player_character(input[3]))
            return (1);
    }
    else
    {
        target = ft_get_info(input[3], info->struct_name);
        if (!target)
			return (pf_printf("297-Error getting info %s\n", input[2]), 1);
    }
    if (ft_strcmp_dnd(target->name, info->name) == 0)
    {
		ft_cast_concentration_cleanup(info, target, save_files, buff, 1);
        return (1);
    }
    if (target && target->version_number >= 2)
    {
        if (buff->cast_spell(target, input, buff))
        {
			ft_cast_concentration_cleanup(info, target, save_files, buff, 0);
            return (1);
        }
    }
	if (ft_remove_concentration(info))
        return (ft_cast_concentration_cleanup(info, target, save_files, buff, 0), 1);
	if (ft_apply_concentration_buff(info, target, save_files, input, buff))
        return (1);
	if (ft_cast_concentration_open_file(save_files, info, target))
        return (1);
    ft_cast_concentration_cleanup(info, target, save_files, buff, -1);
    return (0);
}
