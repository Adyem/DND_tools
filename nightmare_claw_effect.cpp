#include "character.hpp"
#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void    ft_nightmare_claw_effect(t_char *info, t_equipment_id *weapon,
                                t_equipment_effect *effect, t_attack_info *attack_info)
{
	(void)info;
	(void)weapon;
    (void)effect;
    if (!attack_info->is_hit)
        return ;
    const char *message = "The target must succeed on a Charisma saving throw. Enter "
		"\"crit succes\", \"succes\", \"fail\" or \"crit fail\": ";
    int result_check = ft_readline_check_succes_or_fail(message);
    if (result_check == RL_FAIL || result_check == RL_CRIT_FAIL)
        pf_printf("The target is frightened and has disadvantage on their next turn.\n");
    else
        pf_printf("The target resists the fear.\n");
    return ;
}

