#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/class_nullptr.hpp"

t_char *ft_validate_and_fetch_target(char *target_name, t_char * info,
        int *error_code)
{
    int        name_status;
    int        pc_status;
    t_char    *target_info;

    name_status = ft_set_stats_check_name(target_name);
    if (name_status != 0)
    {
        pc_status = ft_check_player_character(target_name);
        if (pc_status == 0)
        {
            *error_code = 0;
            return (ft_nullptr);
        }
        if (pc_status < 0)
        {
            *error_code = pc_status;
            return (ft_nullptr);
        }
        pf_printf("111-Error: target does not exist\n");
        *error_code = name_status;
        return (ft_nullptr);
    }
    pc_status = ft_check_player_character(target_name);
    if (pc_status == 0)
    {
        *error_code = 0;
        return (ft_nullptr);
    }
    if (pc_status < 0)
    {
        *error_code = pc_status;
        return (ft_nullptr);
    }
    target_info = ft_get_info(target_name, info->struct_name);
    if (!target_info)
    {
        pf_printf("109-Error: getting info for %s\n", target_name);
        *error_code = 2;
        return (ft_nullptr);
    }
    *error_code = 0;
    return (target_info);
}
