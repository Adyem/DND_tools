#include "character.hpp"
#include "initialize.hpp"
#include "libft/Libft/libft.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"
#include "identification.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

static void ft_concentration_remove_buf(t_char * info, t_target_data *targets)
{
    if (info->concentration.spell_id == HUNTERS_MARK_ID)
        ft_concentration_remove_hunters_mark(info, targets);
    return ;
}

static int    ft_remove_concentration_fetch_targets(t_target_data *targets,
                t_char * info, int i)
{
    int    error = 0;

    targets->target[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
            info, &error);
    if (error || !targets->target[i])
    {
        ft_free_memory_cmt(targets, i);
        return (FAILURE);
    }
    targets->target_copy[i] = ft_validate_and_fetch_target(info->concentration.targets[i],
            info, &error);
    if (error || !targets->target_copy[i])
    {
        ft_free_memory_cmt(targets, i);
        return (FAILURE);
    }
    return (SUCCES);
}

int ft_remove_concentration(t_char * info)
{
    t_target_data    targets;
    int                i;

    ft_initialize_variables(&targets);
    if (DEBUG == 1)
        pf_printf("Removing concentration\n");
    i = 0;
    targets.buff_info = ft_nullptr;
    while (info->concentration.targets && info->concentration.targets[i])
    {
        if (ft_remove_concentration_fetch_targets(&targets, info, i))
            return (FAILURE);
        i++;
    }
    t_buff buff = INITIALIZE_T_BUFF;
    buff.target_amount = ft_double_char_length(const_cast<const char **>(info->concentration.targets));
    targets.buff_info = &buff;
    ft_file info_save_file(ft_check_and_open(&targets, info));
    if (info_save_file.get_error())
        return (FAILURE);
    ft_concentration_remove_buf(info, &targets);
    ft_cast_concentration_save_files(info, &targets, info_save_file);
    info->flags.alreaddy_saved = 0;
    return (SUCCES);
}
