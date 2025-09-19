#include "libft/CPP_class/class_file.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/CMA/CMA.hpp"
#include "libft/CPP_class/class_nullptr.hpp"
#include "character.hpp"
#include "dnd_tools.hpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <strings.h>

static void    ft_set_not_save_flag(t_target_data *target_data, t_char * info)
{
    int    index = 0;

    while (index < target_data->buff_info->target_amount)
    {
        if (target_data->target[index])
            target_data->target[index]->flags.dont_save = 1;
        if (target_data->target_copy[index])
            target_data->target_copy[index]->flags.dont_save = 1;
        index++;
    }
    info->flags.dont_save = 1;
    return ;
}

static void    ft_cleanup_concentration_targets(t_char * info, int last_index)
{
    int    cleanup_index;

    if (!info->concentration.targets)
        return ;
    cleanup_index = last_index;
    while (cleanup_index >= 0)
    {
        if (info->concentration.targets[cleanup_index])
        {
            cma_free(info->concentration.targets[cleanup_index]);
            info->concentration.targets[cleanup_index] = ft_nullptr;
        }
        cleanup_index--;
    }
    cma_free(info->concentration.targets);
    info->concentration.targets = ft_nullptr;
    return ;
}

static int    ft_apply_concentration(t_target_data *target_data, t_char * info, const char **input)
{
    int    index = 0;

    info->concentration.targets =
        static_cast<char **>(cma_calloc(static_cast<size_t>(target_data->buff_info->target_amount + 1),
            sizeof(char *)));
    if (!info->concentration.targets)
        return (FAILURE);
    while (index < target_data->buff_info->target_amount)
    {
        if (target_data->target[index])
        {
            if (target_data->buff_info->cast_spell(target_data->target[index], input,
                        target_data->buff_info))
            {
                ft_cleanup_concentration_targets(info, index - 1);
                return (FAILURE);
            }
            info->concentration.targets[index] = cma_strdup(target_data->Pchar_name[index]);
            if (!info->concentration.targets[index])
            {
                ft_cleanup_concentration_targets(info, index - 1);
                return (FAILURE);
            }
        }
        index++;
    }
    info->concentration.targets[target_data->buff_info->target_amount] = ft_nullptr;
    info->concentration.concentration = 1;
    info->concentration.extra = target_data->buff_info->mod;
    info->concentration.spell_id = target_data->buff_info->spell_id;
    info->concentration.dice_faces_mod = target_data->buff_info->dice_faces_mod;
    info->concentration.dice_amount_mod = target_data->buff_info->dice_amount_mod;
    info->concentration.duration = target_data->buff_info->duration;
    return (SUCCES);
}

void    ft_cast_concentration_multi_target_02(t_char * info,
        t_target_data *target_data, const char **input)
{
    ft_file info_save_file;

    if (ft_apply_concentration(target_data, info, input))
    {
        ft_set_not_save_flag(target_data, info);
        return ;
    }
    info_save_file = ft_check_and_open(target_data, info);
    if (info_save_file == -1)
    {
        ft_set_not_save_flag(target_data, info);
        return ;
    }
    ft_cast_concentration_save_files(info, target_data, info_save_file);
    return ;
}
