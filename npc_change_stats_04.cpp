#include "libft/Printf/printf.hpp"
#include "libft/CPP_class/nullptr.hpp"
#include "dnd_tools.hpp"

void ft_change_stats_04(SharedPtr<t_char>info, const char **input)
{
    int resistance;

	if (ft_strcmp_dnd(input[1], "cast") == 0)
	{
        if (ft_strcmp_dnd(input[2], "hunters_mark") == 0)
            ft_cast_hunters_mark(info, input);
        else if (ft_strcmp_dnd(input[2], "chaos_armor") == 0)
            ft_cast_chaos_armor(info);
	}
	else if (ft_strcmp_dnd(input[3], "damage") == 0)
	{
        if (info->version_number < 2)
            ft_deal_damage(info, input[1], ft_nullptr, 0, 1);
        else
        {
            resistance = ft_get_resistance(info, input[2]);
            if (resistance == -9999)
            {
                pf_printf_fd(2, "158-Error: invalid Damage type for %s\n", info->name);
                return ;
            }
            ft_deal_damage(info, input[1], input[2], resistance, 1);
        }
    }
	else
        pf_printf_fd(2, "241-Error: command not found\n");
	return ;
}
