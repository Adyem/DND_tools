#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

SharedPtr<t_char> ft_validate_and_fetch_target(char *target_name, SharedPtr<t_char> info,
		int *error_code)
{
    if (!ft_set_stats_check_name(target_name))
    {
        pf_printf("111-Error: target does not exist\n");
        *error_code = 1;
        return (SharedPtr<t_char> ());
    }

    if (ft_check_player_character(target_name))
    {
        *error_code = 0;
        return (SharedPtr<t_char> ());
    }
    SharedPtr<t_char> target_info = ft_get_info(target_name, info->struct_name);
    if (!target_info)
    {
        pf_printf("109-Error: getting info for %s\n", target_name);
        *error_code = 2;
        return (SharedPtr<t_char> ());
    }
    *error_code = 0;
    return (target_info);
}
