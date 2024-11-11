#include "libft/CMA/CMA.hpp"
#include "libft/Printf/ft_printf.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include "TemporaryFile.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <vector>
#include <memory>

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

static bool	ft_check_write_permissions(t_target_data *target_data, t_char *info)
{
	int	i;

	i = 0;
	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i] && ft_check_write_permissions(target_data->target[i]->save_file))
		{
			pf_printf_fd(2, "118-Error trying to access file: %s", strerror(errno));
			return (false);
		}
		i++;
	}
	if (ft_check_write_permissions(info->save_file))
	{
		pf_printf_fd(2, "120-Error trying to access file: %s", strerror(errno));
		return (false);
	}
	return (true);
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

static bool	ft_cast_concentration_save_files(t_char *info, t_target_data *target_data,
		std::vector<std::unique_ptr<TemporaryFile>>& temp_files)
{
	int	i = 0;

	// Write to each target's temporary file first
	while (i < target_data->buff_info->target_amount)
	{
		if (target_data->target[i])
		{
			try
			{
				// Example: Assuming ft_npc_write_file writes all necessary data to the
				// temporary file
				// Modify ft_npc_write_file to accept a TemporaryFile object or its file descriptor
				ft_npc_write_file(target_data->target[i], &target_data->target[i]->stats,
					&target_data->target[i]->c_resistance, temp_files[i]->fd);
			}
			catch (const std::exception& e)
			{
				pf_printf_fd(2, "Error writing to temporary file for target %d: %s", i, e.what());
				return (false);
			}
		}
		i++;
	}

	// Write to the info's temporary file
	try
	{
		ft_npc_write_file(info, &info->stats, &info->c_resistance, temp_files[i]->fd);
	}
	catch (const std::exception& e)
	{
		pf_printf_fd(2, "Error writing to temporary file for info: %s", e.what());
		return (false);
	}

	return (true);
}

void	ft_cast_concentration_multi_target_02(t_char *info, t_target_data *target_data,
			const char **input)
{
	// Step 1: Apply concentration effects
	if (ft_apply_concentration(target_data, info, input))
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}

	// Step 2: Check write permissions
	if (!ft_check_write_permissions(target_data, info))
	{
		ft_set_not_save_flag(target_data, info);
		return ;
	}

	// Step 3: Create temporary files
	std::vector<std::unique_ptr<TemporaryFile>> temp_files;
	try
	{
		// Create temporary file for info
		temp_files.emplace_back(std::make_unique<TemporaryFile>(info->save_file));

		// Create temporary files for each target
		for (int i = 0; i < target_data->buff_info->target_amount; i++)
		{
			if (target_data->target[i])
			{
				temp_files.emplace_back(std::make_unique<TemporaryFile>(target_data->target[i]
							->save_file));
			}
			else
			{
				// If target is null, push a nullptr to keep indexing consistent
				temp_files.emplace_back(nullptr);
			}
		}
	}
	catch (const std::exception& e)
	{
		pf_printf_fd(2, "Error creating temporary files: %s", e.what());
		ft_set_not_save_flag(target_data, info);
		return ;
	}

	// Step 4: Write data to temporary files
	if (!ft_cast_concentration_save_files(info, target_data, temp_files))
	{
		pf_printf_fd(2, "Error writing to temporary files. Aborting save operation.");
		ft_set_not_save_flag(target_data, info);
		return ;
	}

	// Step 5: Finalize and replace original files with temporary files
	try
	{
		// Finalize info's temporary file
		if (temp_files[0])
			temp_files[0]->finalize();

		// Finalize each target's temporary file
		for (int i = 0; i < target_data->buff_info->target_amount; i++)
		{
			if (target_data->target[i] && temp_files[i + 1])
				temp_files[i + 1]->finalize();
		}
	}
	catch (const std::exception& e)
	{
		pf_printf_fd(2, "Error finalizing temporary files: %s", e.what());
		ft_set_not_save_flag(target_data, info);
		return ;
	}

	// At this point, all files have been successfully written and replaced
	return ;
}
