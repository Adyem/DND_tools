#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"

t_char *ft_validate_and_fetch_target(char *target_name, t_char * info,
		int *error_code)
{
    if (!ft_set_stats_check_name(target_name))
    {
        pf_printf("111-Error: target does not exist\n");
        *error_code = 1;
        return (ft_nullptr);
    }
    if (ft_check_player_character(target_name))
    {
        *error_code = 0;
        return (ft_nullptr);
    }
    t_char *target_info = ft_get_info(target_name, info->struct_name);
    if (!target_info)
    {
        pf_printf("109-Error: getting info for %s\n", target_name);
        *error_code = 2;
        return (ft_nullptr);
    }
    *error_code = 0;
    return (target_info);
}
