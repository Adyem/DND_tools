#include "libft/Printf/printf.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/CPP_class/file.hpp"
#include "dnd_tools.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int ft_open_file_write_only(const char *filename, ft_file &file)
{
    file.open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file.get_error_code())
	{
        pf_printf_fd(2, "Error opening file %s: %s\n", filename, file.get_error_message());
		return (1);
	}
    return (0);
}

void ft_dual_save_file(ft_sharedptr<t_char> &info, ft_sharedptr<t_char> &target)
{
    ft_file file_info;
    ft_file file_target;

	ft_open_file_write_only(target->save_file, file_target);
    if (file_target.get_error_code())
    {
        info->flags.alreaddy_saved = 1;
        return ;
    }
	ft_open_file_write_only(info->save_file, file_info);
    if (file_target.get_error_code() || file_info.get_error_code())
    {
        info->flags.alreaddy_saved = 1;
        ft_free_info(target);
        return ;
    }
    ft_npc_write_file(target, &target->stats, &target->c_resistance, file_target);
    ft_npc_write_file(info, &info->stats, &info->c_resistance, file_info);
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

void	ft_cast_concentration_save_files(ft_sharedptr<t_char> &info, t_target_data *target_data,
											ft_file &file)
{
	int	i = 0;

	while (i < target_data->buff_info->target_amount)
	{
		ft_npc_write_file(target_data->target[i], &target_data->target[i]->stats,
				&target_data->target[i]->c_resistance, target_data->file[i]);
		i++;
	}
	ft_npc_write_file(info, &info->stats, &info->c_resistance, file);
	return ;
}

static void	ft_revert_changes_info(ft_sharedptr<t_char> &info, ft_file &file)
{
	cma_free(info->concentration.targets[0]);
	cma_free(info->concentration.targets);
    info->concentration.targets = ft_nullptr;
   	info->concentration.concentration = 0;
   	info->concentration.spell_id = 0;
   	info->concentration.dice_faces_mod = 0;
   	info->concentration.dice_amount_mod = 0;
   	info->concentration.duration = 0;
	ft_npc_write_file(info, &info->stats, &info->c_resistance, file);
	return ;
}

ft_file ft_check_and_open(t_target_data *target_data, ft_sharedptr<t_char> &info)
{
    int target_index = 0;
    ft_file info_save_file;
	ft_open_file_write_only(info->save_file, info_save_file);
    if (info_save_file.get_error_code())
    {
        pf_printf_fd(2, "122-Error opening file: %s", info_save_file.get_error_message());
        return (-1);
    }
	if (DEBUG == 1)
		pf_printf("memory address of buff info is %p", target_data->buff_info);
    while (target_index < target_data->buff_info->target_amount)
    {
        ft_open_file_write_only(target_data->target[target_index]->save_file,
			target_data->file[target_index]);
        if (target_data->file[target_index].get_error_code())
        {
            pf_printf_fd(2, "119-Error opening file: %s", strerror(errno));
            ft_revert_changes_info(info, info_save_file);
            int rollback_index = 0;
            while (rollback_index <= target_index)
            {
                if (target_data->target_copy[rollback_index])
                {
                    ft_sharedptr<t_char> target = target_data->target_copy[rollback_index];
                    ft_npc_write_file(target, &target->stats,
                            &target->c_resistance, target_data->file[rollback_index]);
                }
                rollback_index++;
            }
            return (-1);
        }
        target_index++;
    }
    return (info_save_file);
}
