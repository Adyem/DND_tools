#include "character.hpp"
#include "dnd_tools.hpp"

void    ft_attack_additional_effects(t_char *info, t_equipment_id *weapon,
                                        t_attack_info *attack_info)
{
    if (weapon->action_01.function)
        weapon->action_01.function(info, weapon, &weapon->action_01, attack_info);
    return ;
}
