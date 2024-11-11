#include "libft/Printf/ft_printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CMA/CMA.hpp"
#include "dnd_tools.hpp"
#include "TemporaryFile.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <memory>

static void ft_cast_concentration_cleanup(t_char *info, t_char *target,
                                          TemporaryFile* temp_info_file,
                                          TemporaryFile* temp_target_file,
                                          t_buff *buff, int error)
{
    if (info)
    {
        if (error != -1)
            info->flags.dont_save = 1;

        if (temp_info_file && temp_info_file->fd != -1)
        {
            try
            {
                ft_npc_write_file(info, &info->stats, &info->c_resistance, temp_info_file->fd);
                temp_info_file->finalize();
            }
            catch (const std::exception& e)
            {
                pf_printf_fd(2, "Error writing to info's temporary file: %s\n", e.what());
                info->flags.dont_save = 1;
            }
        }
    }

    if (target)
    {
        if (error != -1)
            target->flags.dont_save = 1;

        if (temp_target_file && temp_target_file->fd != -1)
        {
            try
            {
                ft_npc_write_file(target, &target->stats, &target->c_resistance,
						temp_target_file->fd);
                temp_target_file->finalize();
            }
            catch (const std::exception& e)
            {
                pf_printf_fd(2, "Error writing to target's temporary file: %s\n", e.what());
                target->flags.dont_save = 1;
            }
        }
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
    return;
}

int ft_apply_concentration_buff(t_char *info, t_char *target, const char **input, t_buff *buff)
{
    char    **temp;
    int     i;

    temp = (char **)cma_calloc(2, sizeof(char *), false);
    if (!temp)
    {
        ft_cast_concentration_cleanup(info, target, nullptr, nullptr, buff, 2);
        return 1;
    }
    temp[0] = (char *)cma_malloc((ft_strlen(input[3]) + 1) * sizeof(char), false);
    if (!temp[0])
    {
        ft_cast_concentration_cleanup(info, target, nullptr, nullptr, buff, 3);
        return 1;
    }
    info->concentration.targets = temp;
    i = 0;
    while (input[3][i])
    {
        info->concentration.targets[0][i] = input[3][i];
        i++;
    }
    info->concentration.targets[0][i] = '\0';
    info->concentration.concentration = 1;
    info->concentration.spell_id = buff->spell_id;
    info->concentration.dice_faces_mod = buff->dice_faces_mod;
    info->concentration.dice_amount_mod = buff->dice_amount_mod;
    info->concentration.duration = buff->duration;
    return 0;
}

static int ft_cast_concentration_open_file(std::unique_ptr<TemporaryFile>& temp_info_file,
                                           std::unique_ptr<TemporaryFile>& temp_target_file,
                                           t_char *info, t_char *target)
{
    // Check write permissions
    if (ft_check_write_permissions(info->save_file) != 0)
    {
        info->flags.alreaddy_saved = 1;
        ft_cast_concentration_cleanup(info, target, temp_info_file.get(),
				temp_target_file.get(), nullptr, 4);
        return 1;
    }
    if (ft_check_write_permissions(target->save_file) != 0)
    {
        ft_cast_concentration_cleanup(info, target, temp_info_file.get(),
				temp_target_file.get(), nullptr, 5);
        return 1;
    }

    // Create temporary files
    try
    {
        temp_info_file = std::make_unique<TemporaryFile>(info->save_file);
        temp_target_file = std::make_unique<TemporaryFile>(target->save_file);
    }
    catch (const std::exception& e)
    {
        pf_printf_fd(2, "Error creating temporary files: %s\n", e.what());
        ft_cast_concentration_cleanup(info, target, temp_info_file.get(), 
				temp_target_file.get(), nullptr, 0);
        return 1;
    }

    return 0;
}

int ft_cast_concentration(t_char *info, const char **input, t_buff *buff)
{
    t_char *target;
    std::unique_ptr<TemporaryFile> temp_info_file;
    std::unique_ptr<TemporaryFile> temp_target_file;

    if (ft_remove_concentration(info))
        return 1;

    if (DEBUG == 1)
        pf_printf("casting hunter's mark %s %s\n", input[0], input[3]);

    if (ft_set_stats_check_name(input[3]))
    {
        if (ft_check_player_character(input[3]))
            return 1;
        else
            target = ft_nullptr;
    }
    else
    {
        target = ft_get_info(input[3], info->struct_name);
        if (!target)
            return (pf_printf("297-Error getting info %s\n", input[2]), 1);
    }

    if (ft_strcmp_dnd(target->name, info->name) == 0)
    {
        ft_cast_concentration_cleanup(info, target, nullptr, nullptr, buff, 1);
        return 1;
    }

    if (target && target->version_number >= 2)
    {
        if (buff->cast_spell(target, input, buff))
        {
            ft_cast_concentration_cleanup(info, target, temp_info_file.get(),
					temp_target_file.get(), buff, 0);
            return 1;
        }
    }

    if (ft_remove_concentration(info))
    {
        ft_cast_concentration_cleanup(info, target, temp_info_file.get(),
				temp_target_file.get(), buff, 0);
        return 1;
    }

    if (ft_apply_concentration_buff(info, target, input, buff))
        return 1;

    if (ft_cast_concentration_open_file(temp_info_file, temp_target_file, info, target))
        return 1;

    ft_cast_concentration_cleanup(info, target, temp_info_file.get(), temp_target_file.get(),
			buff, -1);
    return 0;
}
